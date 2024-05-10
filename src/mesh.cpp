#include "mesh.h"
#include <string>
#include "vector3.h"

//mesh::mesh() {}

//mesh::mesh(vector3*position) { this->position = position; }

std::string mesh::to_string() {
    return ("{ mesh: undefined, position: " + position->to_string() + "}");
}

