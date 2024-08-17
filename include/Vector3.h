#ifndef VECTOR3_H
#define VECTOR3_H
#include <string>
#include <iostream>

struct Vector3 {
    
    static const Vector3 ONE;
    static const Vector3 ZERO;
    static const Vector3 UP;
    static const Vector3 RIGHT;
    static const Vector3 FORWARD;

    double x = 0;
    double y = 0;
    double z = 0;

    Vector3();
    Vector3(double x, double y, double z);
    std::string to_string();

    inline Vector3 operator+(const Vector3 other) const { return {x+other.x,y+other.y,z+other.z}; }
    inline Vector3 operator-(const Vector3 other) const { return {x-other.x,y-other.y,z-other.z}; }
    inline Vector3 operator*(const Vector3 other) const { return {x*other.x,y*other.y,z*other.z}; }
    inline Vector3 operator*(const double t) const { return {x*t,y*t,z*t}; }
    inline Vector3 operator/(const double t) const { return {x/t,y/t,z/t};  }

    double Norm();
    double Magnitude();
    Vector3 Normalized();
    static double Angle(Vector3 v1, Vector3 v2);
    static double Distance(Vector3 v1, Vector3 v2);
    static double Product(Vector3 v1, Vector3 v2);
    static Vector3 CrossProduct(Vector3 v1, Vector3 v2);
    static double Proj(Vector3 v1, Vector3 v2);


private:
    std::string doubleToString(double value);
};

#endif
