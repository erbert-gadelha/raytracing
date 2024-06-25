#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "Object.h"
#include "Screen.h"
#include "Light.h"
#include <vector>
#include <thread>         // std::thread



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
        std::string render(std::vector<Object*>objects, std::vector<Light*>lights, Light* ambient_light);
        double MAX_DISTANCE;

    protected:
        colorRGB specular(CollisionResult result, colorRGB fog);
        colorRGB dephFog(colorRGB color, colorRGB fog, double distance);
        colorRGB phong(CollisionResult collision,Vector3 position, std::vector<Light*>lights, Light* ambient_light);

    private:
    void threadRendering(std::vector<Object*>objects, std::vector<Light*>lights, Light* ambient_light, int initial_x, int final_x, int initial_y, int final_y);
};

#endif // CAMERA_H
