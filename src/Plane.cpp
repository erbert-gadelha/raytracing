//plane.cpp
#include "Plane.h"
#include "colorRGB.h"

Plane::Plane() : Object() {
    this->transform = new Transform();
}

Plane::Plane(Vector3* scale) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
}

Plane::Plane(Vector3* scale, Vector3* position) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
    this->transform->position = position;
}

Plane::Plane(Vector3* scale, Vector3* position, Vector3* rotation ) : Object() {
    this->transform = new Transform();
    this->transform->scale = scale;
    this->transform->position = position;
    this->transform->rotation = rotation;
}

std::string Plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform->to_string() + "\n}");
}
