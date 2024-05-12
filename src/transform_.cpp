#include "transform_.h"
#include <string>
#include <math.h>

const double pi = atan(1)*4;

transform_::transform_() {
    scale = new vector3(1,1,1);
    position = new vector3(0,0,0);
    rotation = new vector3(0,0,0);
    refresh_axys();
}

void transform_::refresh_axys() {
    cos_x = cos(rotation->getX()*(pi/180));
    sin_x = sin(rotation->getX()*(pi/180));

    cos_y = cos(rotation->getY()*(pi/180));
    sin_y = sin(rotation->getY()*(pi/180));

    cos_z = cos(rotation->getZ()*(pi/180));
    sin_z = sin(rotation->getZ()*(pi/180));

    up =     relative_vector3(new vector3(0, 1, 0));
    right =  relative_vector3(new vector3(1, 0, 0));
    forward = relative_vector3(new vector3(0, 0, 1));
}


vector3* transform_::relative_vector3(vector3* v) {
    double x = v->getX();
    double y = v->getY();
    double z = v->getZ();

    v->setX((cos_y*cos_z*x) - (sin_z*cos_y*y) + (sin_y*z));
    v->setY((sin_x*sin_y*cos_z + sin_z*cos_x)*x + (cos_x*cos_z - sin_z*sin_x*sin_y)*y - (sin_x*cos_y*z));
    v->setZ((-cos_x*sin_y*cos_z)*x + (sin_x*cos_z + sin_z*cos_x*sin_y)*y + (cos_x*cos_y*z));
    return v;
}

std::string transform_::to_string () {
        return ("{\n\tscale: " + scale->to_string() + "\n\tposition: " + position->to_string() +",\n\trotation: " + rotation->to_string() + "\n}");

}
