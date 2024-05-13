#include "Camera.h"

Camera::Camera() {
    this->transform = new Transform();
    this->screen = new Screen(64,64);
    this->distance = 1;
}

Camera::Camera(int w, int h, double distance) {
    this->transform = new Transform();
    this->screen = new Screen(w, h);
    this->distance = distance;
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform->to_string() + "\n}");
}
