//plane.cpp
#include "plane.h"
#include "colorRGB.h"

plane::plane() : object() {
    this->transform = new transform_();
}

plane::plane(vector3* scale) : object() {
    this->transform = new transform_();
    this->transform->scale = scale;
}

plane::plane(vector3* scale, vector3* position) : object() {
    this->transform = new transform_();
    this->transform->scale = scale;
    this->transform->position = position;
}

plane::plane(vector3* scale, vector3* position, vector3* rotation ) : object() {
    this->transform = new transform_();
    this->transform->scale = scale;
    this->transform->position = position;
    this->transform->rotation = rotation;
}

std::string plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform->to_string() + "\n}");
}
