#ifndef VECTOR3_H
#define VECTOR3_H
#include <string>
#include <iostream>

class Vector3 {
public:
    //static const vector3 ONE;
    //static const vector3 ZERO;

    Vector3(double x, double y, double z);
    std::string to_string();

    Vector3* operator+(const Vector3& other) const { return new Vector3(cord_XYZ[0]+other.cord_XYZ[0], cord_XYZ[1]+other.cord_XYZ[1], cord_XYZ[2]+other.cord_XYZ[2]); }
    Vector3* operator-(const Vector3& other) const { return new Vector3(cord_XYZ[0]-other.cord_XYZ[0], cord_XYZ[1]-other.cord_XYZ[1], cord_XYZ[2]-other.cord_XYZ[2]); }
    Vector3* operator*(const double scale) const { return new Vector3(cord_XYZ[0]*scale, cord_XYZ[1]*scale, cord_XYZ[2]*scale); }
    Vector3* operator/(const double scale) const { return new Vector3(cord_XYZ[0]/scale, cord_XYZ[1]/scale, cord_XYZ[2]/scale); }

    void setX(double x);
    void setY(double y);
    void setZ(double y);
    double getX();
    double getY();
    double getZ();

private:
    double cord_XYZ[3];
};

#endif
