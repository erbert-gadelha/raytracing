// Light.h
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "Transform.h"
#include "colorRGB.h"

class Light {

    public:
        Light();
        Light(Vector3 position, colorRGB color);
        
        std::string to_string();
        Transform transform;
        colorRGB color;

    protected:

    private:
};


#endif // LIGHT_H
