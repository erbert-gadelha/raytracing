#include "Object.h"

Object::~Object() {
}

Object::Object() {
}
void Object::setColor(int r, int g, int b) {
    color.red = r;
    color.green = g;
    color.blue = b;
}


Vector3* Object::cast(Vector3* point, Vector3* vector) {
    return nullptr;
}

std::string Object::getColor() {
    return (std::to_string(this->color.red) + " " + std::to_string(this->color.green) + " " + std::to_string(this->color.blue));

}

std::string Object::to_string() {
    return "undefined";
}
