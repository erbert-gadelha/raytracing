#include "object.h"

object::~object() {
    // Faça a limpeza necessária, se houver
}

object::object() {
}

/*object::object(vector3* scale) {
}
object::object(vector3* scale, vector3* position) {
}
object::object(vector3* scale, vector3* position, vector3* rotation) {
}*/



std::string object::to_string() {
    return "undefined";
}
