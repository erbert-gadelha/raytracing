#include "Camera.h"

Camera::Camera() {
    this->transform = new Transform();
    this->horizontal = 256;
    this->vertical = 256;
    this->screen = new Screen(horizontal,vertical);
    this->distance = 1;
}

Camera::Camera(int horizontal, int vertical, double distance) {
    this->transform = new Transform();
    this->horizontal = horizontal;
    this->vertical = vertical;
    this->screen = new Screen(horizontal,vertical);
    this->distance = distance;
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform->to_string() + "\n}");
}
