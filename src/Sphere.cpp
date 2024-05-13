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

std::string Sphere::to_string() {
    return ("{\n\tmesh: sphere,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform->to_string() + "\n}");
}
