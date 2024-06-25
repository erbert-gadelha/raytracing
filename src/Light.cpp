#include "Light.h"
#include <vector>

Light::Light() {

}
Light::Light(Vector3 position, colorRGB color) {
    this->color = color;
    this->transform.position = position;
}

std::string Light::to_string() {
    return ("{\n\tobject: light,\n\tcolor: (" + color.to_string() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
