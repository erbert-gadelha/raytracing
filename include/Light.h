#ifndef LIGHT_H
#define LIGHT_H
#include "colorRGB.h"
#include "Vector3.h"
#include "Transform.h"
class Light
{
private:
    /* data */
public:
    Light(/* args */);
    colorRGB color;
    Transform transform;
    
    Light(colorRGB color,Vector3 position);
};


#endif // LIGHT_H