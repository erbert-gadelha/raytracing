#ifndef SPHcolorERE_H
#define SPHERE_H

#include "Object.h"
#include <string>


class Sphere : public Object
{
    public:
        Sphere();
        Sphere(Vector3* scale);
        Sphere(Vector3* scale, Vector3* position);
        Sphere(Vector3* scale, Vector3* position, Vector3* rotation);
        std::string to_string() override;

    protected:

    private:
};

#endif // SPHERE_H
