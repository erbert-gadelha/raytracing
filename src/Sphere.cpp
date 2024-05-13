// sphere.cpp
#include "Sphere.h"
#include <iostream>
#include "Transform.h"
#include "Vector3.h"

Sphere::Sphere() : Object() {
    this->transform = new Transform();
}

Sphere::Sphere(Vector3* scale) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
}

Sphere::Sphere(Vector3* scale, Vector3* position) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
    this->transform->position = position;
}

Sphere::Sphere(Vector3* scale, Vector3* position, Vector3* rotation ) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
    this->transform->position = position;
    this->transform->rotation = rotation;
}




Vector3* Sphere::cast(Vector3* point, Vector3* vector) {
    double radius = this->transform->scale->getX()/2;
    Vector3* position = this->transform->position;
    std::cout << "casting : {\n";
    std::cout << "   sphere: { radius: " << radius << ", position: (" << position->getX() << ',' << position->getY() << ',' << position->getZ() << ") }\n";
    std::cout << "   line: { point: (" << point->getX() << ',' << point->getY() << ',' <<  point->getZ() << "), vector: (" << vector->getX() << ',' << vector->getY() << ',' <<  vector->getZ() << ") }\n";
    std::cout << "};\n";

    return nullptr;
}



std::string Sphere::to_string() {
    return ("{\n\tmesh: sphere,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform->to_string() + "\n}");
}
