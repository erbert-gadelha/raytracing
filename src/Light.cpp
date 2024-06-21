#include "Light.h"

Light::Light()
{
}
Light::Light(colorRGB color,Vector3 position){
    this->color = color;
    this->transform.position = position;
}
