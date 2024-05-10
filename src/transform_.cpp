#include "transform_.h"
#include <string>

transform_::transform_() {
    scale = new vector3(1,1,1);
    position = new vector3(0,0,0);
    rotation = new vector3(0,0,0);
}

std::string transform_::to_string () {
        return ("{\n\tscale: " + scale->to_string() + "\n\tposition: " + position->to_string() +",\n\trotation: " + rotation->to_string() + "\n}");

}
