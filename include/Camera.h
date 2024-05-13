#ifndef CAMERA_H
#define CAMERA_H

#include <Object.h>
#include <string>
#include <Screen.h>


class Camera : public Object
{
    public:
        Camera();
        Camera(int w, int h, double distance);
        std::string to_string() override;
        Screen* screen;
        double distance;

    protected:

    private:
};

#endif // CAMERA_H
