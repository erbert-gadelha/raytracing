#include "Vector3.h"
#include <iostream>
#include <string>
#include <math.h>

const Vector3 Vector3::ONE = Vector3(1, 1, 1);
const Vector3 Vector3::ZERO = Vector3(0, 0, 0);
const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);

Vector3::Vector3() {
    this->cord_XYZ[0] = 0;
    this->cord_XYZ[1] = 0;
    this->cord_XYZ[2] = 0;
}

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


double Vector3::Magnitude() {
    return sqrt((cord_XYZ[0]*cord_XYZ[0])+(cord_XYZ[1]*cord_XYZ[1])+(cord_XYZ[2]*cord_XYZ[2]));
}

Vector3 Vector3::Normalized() {
    return Vector3(cord_XYZ[0],cord_XYZ[1],cord_XYZ[2])/Magnitude();
}


double Vector3::Distance(Vector3 v1, Vector3 v2) {
    return (v1-v2).Magnitude();
}

std::string Vector3::to_string() {
    return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");
}

