#ifndef SPHcolorERE_H
#define SPHERE_H

#include "object.h"
#include <string>


class sphere : public object
{
    public:
        sphere();
        sphere(vector3* scale);
        sphere(vector3* scale, vector3* position);
        sphere(vector3* scale, vector3* position, vector3* rotation);
        std::string to_string() override;

    protected:

    private:
};

#endif // SPHERE_H
