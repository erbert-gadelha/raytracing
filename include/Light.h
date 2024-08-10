// Light.h
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "Transform.h"
#include "colorRGB.h"
#include <vector>

class Light {

    public:
        Light();
        Light(colorRGB color, std::vector<Vector3> points);
        Light(colorRGB color, double intensity, std::vector<Vector3> points);
        
        std::string to_string();
        //Transform transform;
        std::vector<Vector3> points;
        colorRGB color = {128, 128, 128};
        double intensity = 1;

    protected:

    private:
};


#endif // LIGHT_H
