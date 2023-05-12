
#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_SHAPES_DISPLACEMENTSPHERE_H
#define PBRT_SHAPES_DISPLACEMENTSPHERE_H

// shapes/displacementsphere.h*
#include "shapes/triangle.h"

namespace pbrt {

    std::vector<std::shared_ptr<Shape>> CreateDisplacementSphere(
            const Transform *o2w, const Transform *w2o, bool reverseOrientation,
            const ParamSet &params,
            std::map<std::string, std::shared_ptr<Texture<Float>>> *floatTextures =
            nullptr);

}  // namespace pbrt

#endif  // PBRT_SHAPES_PLYMESH_H
