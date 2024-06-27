#include "Transform.h"
#include <string>
#include <math.h>
#include "Vector3.h"

static const double pi = atan(1)*4;

Transform::Transform() {
    scale = Vector3(1,1,1);
    position = Vector3(0,0,0);
    rotation = Vector3(0,0,0);
}

Vector3 Transform::up() {    return relative_vector3(Vector3().UP);}
Vector3 Transform::right() {    return relative_vector3(Vector3().RIGHT);}
Vector3 Transform::forward() {    return relative_vector3(Vector3().FORWARD); }


Vector3 Transform::relative_vector3(Vector3 v) {
    double cos_x = cos(rotation.x*(pi/180));
    double sin_x = sin(rotation.x*(pi/180));

    double cos_y = cos(rotation.y*(pi/180));
    double sin_y = sin(rotation.y*(pi/180));

    double cos_z = cos(rotation.z*(pi/180));
    double sin_z = sin(rotation.z*(pi/180));

    double x = v.x;
    double y = v.y;
    double z = v.z;

    v.x = (cos_y*cos_z*x) - (sin_z*cos_y*y) + (sin_y*z);
    v.y = (sin_x*sin_y*cos_z + sin_z*cos_x)*x + (cos_x*cos_z - sin_z*sin_x*sin_y)*y - (sin_x*cos_y*z);
    v.z = (-cos_x*sin_y*cos_z)*x + (sin_x*cos_z + sin_z*cos_x*sin_y)*y + (cos_x*cos_y*z);

    return v;
}

std::string Transform::to_string () {
        return ("{\n\tscale: " + scale.to_string() + "\n\tposition: " + position.to_string() +",\n\trotation: " + rotation.to_string() + "\n}");

}
