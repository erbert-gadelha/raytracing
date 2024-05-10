#include "vector3.h"
#include <iostream>
#include <string>

//const vector3 *vector3::ONE(1, 1, 1);
//const vector3 *vector3::ZERO(0, 0, 0);

vector3::vector3(double x, double y, double z) {
    this->cord_XYZ[0] = x;
    this->cord_XYZ[1] = y;
    this->cord_XYZ[2] = z;
}

std::string vector3::to_string() {
    return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");
}

