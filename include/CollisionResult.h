#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H
#include <string>
#include <algorithm>
#include "colorRGB.h"
#include "Vector3.h"

struct CollisionResult {
    double t = -1;
    Vector3 normal;
    colorRGB color;
    double k_d;
    double k_s;
    double k_a;
    double k_r;
    double k_t;
    double n;

    std::string to_string() {
        return ("{\n\tt: " + std::to_string(t) + "\n\tnormal: " + normal.to_string() + "\n\tcolor: " + color.to_string() + "\n}");
    }
};

#endif // COLLISIONRESULT_H
