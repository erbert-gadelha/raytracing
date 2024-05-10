// sphere.cpp
#include "sphere.h"
#include <iostream>
#include "transform_.h"
#include "vector3.h"

sphere::sphere() : object() {
    this->color = new colorRGB();
    this->transform = new transform_();
}

sphere::sphere(vector3* scale) : object() {
    this->color = new colorRGB();
    this->transform = new transform_();
    this->transform->scale = scale;
}

sphere::sphere(vector3* scale, vector3* position) : object() {
    this->color = new colorRGB();
    this->transform = new transform_();
    this->transform->scale = scale;
    this->transform->position = position;
}

sphere::sphere(vector3* scale, vector3* position, vector3* rotation ) : object() {
    this->color = new colorRGB();
    this->transform = new transform_();
    this->transform->scale = scale;
    this->transform->position = position;
    this->transform->rotation = rotation;
}

std::string sphere::to_string() {
    return ("{\n\tmesh: sphere,\n\tcolor: (" + this->color->to_string() + ")\n\ttransform: " + this->transform->to_string() + "\n}");
}
