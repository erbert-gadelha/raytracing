#ifndef CAMERA_H
#define CAMERA_H

#include <object.h>


class camera : public object
{
    public:
        camera();
        camera(vector3* position);
        camera(vector3* position, vector3* rotation);
        std::string to_string() override;

    protected:

    private:
};

#endif // CAMERA_H
