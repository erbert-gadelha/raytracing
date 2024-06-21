#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "Object.h"
#include "Screen.h"
#include "Light.h"
#include <vector>


class Camera : public Object
{
    public:
        Camera();
        Camera(int horizontal, int vertical, double distance);
        int horizontal;
        int vertical;
        std::string to_string() override;
        Screen screen;
        double distance;
        std::string render(std::vector<Object*>objects,std::vector<Light> lights);
        double MAX_DISTANCE;
        colorRGB Phong(CollisionResult result, colorRGB fog,std::vector<Light> lights,Ray ray,colorRGB cor_ambiente);

    protected:
        colorRGB specular(CollisionResult result, colorRGB fog);
        colorRGB dephFog(colorRGB color, colorRGB fog, double distance);

    private:
};

#endif // CAMERA_H
