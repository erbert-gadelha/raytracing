#include "Vector3.h"
#include <iostream>
#include <string>

//const vector3 *vector3::ONE(1, 1, 1);
//const vector3 *vector3::ZERO(0, 0, 0);

Vector3::Vector3(double x, double y, double z) {
    this->cord_XYZ[0] = x;
    this->cord_XYZ[1] = y;
    this->cord_XYZ[2] = z;
}

void Vector3::setX(double x) {    this->cord_XYZ[0] = x;    }
void Vector3::setY(double y) {    this->cord_XYZ[1] = y;    }
void Vector3::setZ(double z) {    this->cord_XYZ[2] = z;    }
double Vector3::getX() {    return this->cord_XYZ[0];   }
double Vector3::getY() {    return this->cord_XYZ[1];   }
double Vector3::getZ() {    return this->cord_XYZ[2];   }

std::string Vector3::to_string() {
    return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");
}

