#include "camera.h"

camera::camera() {
    this->transform = new transform_();
}

std::string camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform->to_string() + "\n}");
}
