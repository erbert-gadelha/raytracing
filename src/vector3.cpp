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

void vector3::setX(double x) {    this->cord_XYZ[0] = x;    }
void vector3::setY(double y) {    this->cord_XYZ[1] = y;    }
void vector3::setZ(double z) {    this->cord_XYZ[2] = z;    }
double vector3::getX() {    return this->cord_XYZ[0];   }
double vector3::getY() {    return this->cord_XYZ[1];   }
double vector3::getZ() {    return this->cord_XYZ[2];   }

std::string vector3::to_string() {
    return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");
}

