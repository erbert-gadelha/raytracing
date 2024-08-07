#include "Object.h"
#include <vector>

Object::~Object() {
}

Object::Object() {
}



CollisionResult Object::cast(Ray ray) {
    CollisionResult result;
    return result;
}



std::string Object::to_string() {
    return "undefined";
}
