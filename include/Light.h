// Light.h
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "Transform.h"
#include "colorRGB.h"

class Light {

    public:
        Light();
        Light(colorRGB color, Vector3 position);
        Light(colorRGB color, double intensity, Vector3 position);
        
        std::string to_string();
        Transform transform;
        colorRGB color = {128, 128, 128};
        double intensity = 1;

    protected:

    private:
};


#endif // LIGHT_H
