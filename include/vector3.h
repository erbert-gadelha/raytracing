#ifndef VECTOR3_H
#define VECTOR3_H
#include <string>
#include <iostream>

class vector3 {
public:
    //static const vector3 ONE;
    //static const vector3 ZERO;

    vector3(double x, double y, double z);
    std::string to_string();

    vector3* operator+(const vector3& other) const { return new vector3(cord_XYZ[0]+other.cord_XYZ[0], cord_XYZ[1]+other.cord_XYZ[1], cord_XYZ[2]+other.cord_XYZ[2]); }
    vector3* operator-(const vector3& other) const { return new vector3(cord_XYZ[0]-other.cord_XYZ[0], cord_XYZ[1]-other.cord_XYZ[1], cord_XYZ[2]-other.cord_XYZ[2]); }
    vector3* operator*(const double scale) const { return new vector3(cord_XYZ[0]*scale, cord_XYZ[1]*scale, cord_XYZ[2]*scale); }
    vector3* operator/(const double scale) const { return new vector3(cord_XYZ[0]/scale, cord_XYZ[1]/scale, cord_XYZ[2]/scale); }

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
