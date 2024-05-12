#include "object.h"
#include "camera.h"

#include <string>


camera::camera() : object() {
    this->transform = new transform_();
}

camera::camera(vector3* position) : object() {
    this->transform = new transform_();
    this->transform->position = position;
}

camera::camera(vector3* position, vector3* rotation) : object() {
    this->transform = new transform_();
    this->transform->position = position;
    this->transform->rotation = rotation;
}


std::string camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform->to_string() + "\n}");
}
