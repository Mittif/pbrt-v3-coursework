#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct PPMImage {
    int width, height, maxValue;
    std::vector<int> data;
};

PPMImage readPPM(const std::string& filename) {
    PPMImage image;
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        file.close();
        return image;
    }

    std::string magic;
    file >> magic;

    if (magic != "P6") {
        std::cerr << "Invalid PPM file format" << std::endl;
        file.close();
        return image;
    }

    file >> image.width >> image.height >> image.maxValue;
    file.ignore(1, '\n');

    image.data.resize(image.width * image.height * 3);

    for (int i = 0; i < image.width * image.height * 3; ++i) {
        image.data[i] = file.get();
    }
    file.close();
    return image;
}
//
//int main() {
//    // Load the image
//    PPMImage image = readPPM("test1.ppm");
//
//    // Check if image was loaded successfully
//    if (image.data.empty()) {
//        std::cerr << "Failed to load image" << std::endl;
//        return 1;
//    }
//
//    std::cout << image.height*image.width << " " << image.data.size();
//
//    return 0;
//}
