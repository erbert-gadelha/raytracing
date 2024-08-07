#include "Vector3.h"
#include <iostream>
#include <string>
#include <math.h>

const Vector3 Vector3::ONE = {1, 1, 1};
const Vector3 Vector3::ZERO = {0, 0, 0};
const Vector3 Vector3::UP = {0, 1, 0};
const Vector3 Vector3::RIGHT = {1, 0, 0};
const Vector3 Vector3::FORWARD = {0, 0, 1};

Vector3::Vector3() {}

Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


double Vector3::Norm() {
    return Product(*this,*this);
}

double Vector3::Magnitude() {
    return sqrt(Norm());
}

Vector3 Vector3::Normalized() {
    double m = Magnitude();

    if(m != 0) 
        return {x/m,y/m,z/m};
        
    return Vector3::ZERO;
}

/**Função estática que retorna angulo formado entre dois vetores do R3
 */
double Vector3::Angle(Vector3 a, Vector3 b) {
    double dotProduct = Vector3::Product(a,b);
    double magnitudeProduct = a.Magnitude() * b.Magnitude();

    if (magnitudeProduct == 0.0) {
        //throw std::invalid_argument("Cannot calculate angle with zero magnitude vector.");
        return 0;
    }

    double cosTheta = dotProduct / magnitudeProduct;

    if (cosTheta < -1.0) cosTheta = -1.0;
    if (cosTheta > 1.0) cosTheta = 1.0;

    return std::acos(cosTheta) / 3.14;
}


double Vector3::Distance(Vector3 v1, Vector3 v2) {
    return (v1-v2).Magnitude();
}

std::string Vector3::to_string() {
    //return ("(" + std::to_string(cord_XYZ[0]) + ", " + std::to_string(cord_XYZ[1]) + ", " + std::to_string(cord_XYZ[2]) + ")");
    return ("(" + doubleToString(x) + ", " + doubleToString(y) + ", " + doubleToString(z) + ")");
}

std::string Vector3::doubleToString(double value) {
    std::string str = std::to_string(value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

/**
 * Produto vetorial no R3
 */
double Vector3::Product(Vector3 a, Vector3 b) {
    Vector3 v = a*b;
    return v.x + v.y + v.z;
}



Vector3 Vector3::CrossProduct(Vector3 v1, Vector3 v2) {
    //(a.y*b.z - a.z*b.y),(a.z*b.x - a.x*b.z),(a.x*b.y - a.y*b.x)
    /*std::cout << "A:" << v1.to_string() << std::endl;
    std::cout << "B:" << v2.to_string() << std::endl;

    std::cout << "X:" << (v1.getY()*v2.getZ() - v1.getZ()*v2.getY()) << std::endl;
    std::cout << "Y:" << (v1.getZ()*v2.getX() - v1.getX()*v2.getZ()) << std::endl;
    std::cout << "Z:" << (v1.getX()*v2.getY() - v1.getY()*v2.getX()) << std::endl;
    std::cout << std::endl;*/

    
    return Vector3 (
        v1.y*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
    );
}