#include "Light.h"
#include <vector>

Light::Light() {

}
Light::Light(colorRGB color, std::vector<Vector3> points) {
    this->color = color;
    this->points = points;
}
Light::Light(colorRGB color, double intensity, std::vector<Vector3> points) {
    this->intensity = intensity;
    this->color = color;
    this->points = points;
}

std::string Light::to_string() {
    //return ("{\n\tobject: light,\n\tcolor: (" + color.to_string() + ")\n\ttransform: " + this->points[0].to_string() + "\n}");
    return "";
}
