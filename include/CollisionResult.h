#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H
#include <string>
#include <algorithm>
#include "Material.h"
#include "Vector3.h"

struct CollisionResult {
    double t = -1;
    Vector3 normal;
    Material material;

    std::string to_string() {
        return ("{\n\tt: " + std::to_string(t) + "\n\tnormal: " + normal.to_string() + "\n\tcolor: " + material.color.to_string() + "\n}");
    }
};

#endif // COLLISIONRESULT_H
