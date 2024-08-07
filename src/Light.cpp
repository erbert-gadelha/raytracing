#include "Light.h"
#include <vector>

Light::Light() {

}
Light::Light(colorRGB color, Vector3 position) {
    this->color = color;
    this->transform.position = position;
}
Light::Light(colorRGB color, double intensity, Vector3 position) {
    this->intensity = intensity;
    this->color = color;
    this->transform.position = position;
}

std::string Light::to_string() {
    return ("{\n\tobject: light,\n\tcolor: (" + color.to_string() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
