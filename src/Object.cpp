#include "Object.h"
#include <vector>

Object::~Object() {
}

Object::Object() {
}
void Object::setColor(int r, int g, int b) {
    color.red = r;
    color.green = g;
    color.blue = b;
}


std::vector<Vector3> Object::cast(Ray ray) {
    std::vector<Vector3> result;
    return result;
}

std::string Object::getColor() {
    return (std::to_string(this->color.red) + " " + std::to_string(this->color.green) + " " + std::to_string(this->color.blue));

}

std::string Object::to_string() {
    return "undefined";
}
