// shapes/displacementsphere.cpp*
#include "shapes/triangle.h"
#include "textures/constant.h"
#include "paramset.h"
#include "ext/rply.h"
#include "shapes/plymesh.h"
#include "shapes/plymesh.cpp"

#include <iostream>
#include "shapes/ppm.cpp"


namespace pbrt {
    using namespace std;

    /// rgb to gray ///

    int rgb2gray(int r, int g, int b) {
        return static_cast<int>(0.3 * r + 0.59 * g + 0.11 * b); // rgb to grayscale formula
    }

    /// get the grayscale from the .ppm file and normalized to [0-1] ///

    void graymap(const std::string &filename, int &width, int &height, std::vector<float> &grayscale_pixels) {
        PPMImage image = readPPM(filename);

        std::vector<int> pixels(image.data.size());
        for (size_t i = 0; i < image.data.size(); ++i) {
            pixels[i] = static_cast<int>(image.data[i]);
        }

        width = image.width;
        height = image.height;

        grayscale_pixels.resize(width * height);

        for (int i = 0, j = 0; i < width * height * 3; i += 3, ++j) {
            int r = image.data[i];
            int g = image.data[i + 1];
            int b = image.data[i + 2];
            grayscale_pixels[j] = rgb2gray(r, g, b) / 255.0;
//            cout << grayscale_pixels[j];
        }

    }

    /// most of CreateDisplacementSphere() same as CreatePLYMesh() in plymesh.cpp ///

    std::vector<std::shared_ptr<Shape>> CreateDisplacementSphere(
            const Transform *o2w, const Transform *w2o, bool reverseOrientation,
            const ParamSet &params,
            std::map<std::string, std::shared_ptr<Texture<Float>>> *floatTextures) {

        const std::string filename = params.FindOneFilename("filename", "");

        int width, height;
        std::vector<float> grayscale_pixels;

        /// Need to import .ppm file here!!! ///
        graymap("displacementmap.ppm", width, height, grayscale_pixels);

        p_ply ply = ply_open(filename.c_str(), rply_message_callback, 0, nullptr);
        if (!ply) {
            Error("Couldn't open PLY file \"%s\"", filename.c_str());
            return std::vector<std::shared_ptr<Shape>>();
        }

        if (!ply_read_header(ply)) {
            Error("Unable to read the header of PLY file \"%s\"", filename.c_str());
            return std::vector<std::shared_ptr<Shape>>();
        }

        p_ply_element element = nullptr;
        long vertexCount = 0, faceCount = 0;

        /* Inspect the structure of the PLY file */
        while ((element = ply_get_next_element(ply, element)) != nullptr) {
            const char *name;
            long nInstances;

            ply_get_element_info(element, &name, &nInstances);
            if (!strcmp(name, "vertex"))
                vertexCount = nInstances;
            else if (!strcmp(name, "face"))
                faceCount = nInstances;
        }

        if (vertexCount == 0 || faceCount == 0) {
            Error("%s: PLY file is invalid! No face/vertex elements found!",
                  filename.c_str());
            return std::vector<std::shared_ptr<Shape>>();
        }

        CallbackContext context;

        if (ply_set_read_cb(ply, "vertex", "x", rply_vertex_callback, &context,
                            0x030) &&
            ply_set_read_cb(ply, "vertex", "y", rply_vertex_callback, &context,
                            0x031) &&
            ply_set_read_cb(ply, "vertex", "z", rply_vertex_callback, &context,
                            0x032)) {
            context.p = new Point3f[vertexCount];
        } else {
            Error("%s: Vertex coordinate property not found!",
                  filename.c_str());
            return std::vector<std::shared_ptr<Shape>>();
        }

        if (ply_set_read_cb(ply, "vertex", "nx", rply_vertex_callback, &context,
                            0x130) &&
            ply_set_read_cb(ply, "vertex", "ny", rply_vertex_callback, &context,
                            0x131) &&
            ply_set_read_cb(ply, "vertex", "nz", rply_vertex_callback, &context,
                            0x132))
            context.n = new Normal3f[vertexCount];

        /* There seem to be lots of different conventions regarding UV coordinate
         * names */
        if ((ply_set_read_cb(ply, "vertex", "u", rply_vertex_callback, &context,
                             0x220) &&
             ply_set_read_cb(ply, "vertex", "v", rply_vertex_callback, &context,
                             0x221)) ||
            (ply_set_read_cb(ply, "vertex", "s", rply_vertex_callback, &context,
                             0x220) &&
             ply_set_read_cb(ply, "vertex", "t", rply_vertex_callback, &context,
                             0x221)) ||
            (ply_set_read_cb(ply, "vertex", "texture_u", rply_vertex_callback,
                             &context, 0x220) &&
             ply_set_read_cb(ply, "vertex", "texture_v", rply_vertex_callback,
                             &context, 0x221)) ||
            (ply_set_read_cb(ply, "vertex", "texture_s", rply_vertex_callback,
                             &context, 0x220) &&
             ply_set_read_cb(ply, "vertex", "texture_t", rply_vertex_callback,
                             &context, 0x221)))
            context.uv = new Point2f[vertexCount];

        /* Allocate enough space in case all faces are quads */
        context.indices = new int[faceCount * 6];
        context.vertexCount = vertexCount;

        ply_set_read_cb(ply, "face", "vertex_indices", rply_face_callback, &context,
                        0);
        if (ply_set_read_cb(ply, "face", "face_indices", rply_face_callback, &context,
                            1))
            // Extra space in case they're quads
            context.faceIndices = new int[faceCount];

        if (!ply_read(ply)) {
            Error("%s: unable to read the contents of PLY file",
                  filename.c_str());
            ply_close(ply);
            return std::vector<std::shared_ptr<Shape>>();
        }

        ply_close(ply);

        if (context.error) return std::vector<std::shared_ptr<Shape>>();

        // Look up an alpha texture, if applicable
        std::shared_ptr<Texture<Float>> alphaTex;
        std::string alphaTexName = params.FindTexture("alpha");
        if (alphaTexName != "") {
            if (floatTextures->find(alphaTexName) != floatTextures->end())
                alphaTex = (*floatTextures)[alphaTexName];
            else
                Error("Couldn't find float texture \"%s\" for \"alpha\" parameter",
                      alphaTexName.c_str());
        } else if (params.FindOneFloat("alpha", 1.f) == 0.f) {
            alphaTex.reset(new ConstantTexture<Float>(0.f));
        }

        std::shared_ptr<Texture<Float>> shadowAlphaTex;
        std::string shadowAlphaTexName = params.FindTexture("shadowalpha");
        if (shadowAlphaTexName != "") {
            if (floatTextures->find(shadowAlphaTexName) != floatTextures->end())
                shadowAlphaTex = (*floatTextures)[shadowAlphaTexName];
            else
                Error(
                        "Couldn't find float texture \"%s\" for \"shadowalpha\" "
                        "parameter",
                        shadowAlphaTexName.c_str());
        } else if (params.FindOneFloat("shadowalpha", 1.f) == 0.f)
            shadowAlphaTex.reset(new ConstantTexture<Float>(0.f));

        /// my code for displacement ///
        /// main idea: add the displacement value which produced by grayscale and normal to the orignal vertices coordinate ///

        std::vector<Point3f> vertices(vertexCount);

        // copy vertices
        for (size_t i = 0; i < vertexCount; ++i) {
            vertices[i] = context.p[i];
        }
        cout << "vertices: " << vertices[vertexCount-1] << endl;

        for (size_t i = 0; i < vertexCount; ++i) {
            // get UV coordinate
            const Point2f& texCoord = context.uv[i];

            // calculate and map uv coordinate to grayscale ppm
            int x = static_cast<int>(texCoord.x * (width - 1));
            int y = static_cast<int>(texCoord.y * (height - 1));

            // displacement value
            float displacement = grayscale_pixels[y * width + x];
//            cout << "displacement: " << displacement << endl;

            // vertex and normal update
            Point3f vertex = vertices[i];
            Normal3f normal = context.n[i];
            Float dx = displacement * normal.x;
            Float dy = displacement * normal.y;
            Float dz = displacement * normal.z;
            vertices[i] = Point3f(vertex.x + dx, vertex.y + dy, vertex.z + dz);
//            cout << vertices[i] << "\n" << context.p[i];
        }

        cout << "vertices: " << vertices[vertexCount-1] << endl;

        return CreateTriangleMesh(o2w, w2o, reverseOrientation,
                                  context.indexCtr / 3, context.indices,
                                  vertexCount, vertices.data(), nullptr, context.n,
                                  context.uv, alphaTex, shadowAlphaTex,
                                  context.faceIndices);
    }
}  // namespace pbrt
