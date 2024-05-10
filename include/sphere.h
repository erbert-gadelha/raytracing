#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include <string>


class sphere : public object
{
    public:
        vector3* scale;
        vector3* position;
        vector3* rotation;
        sphere();
        sphere(vector3* scale);
        sphere(vector3* scale, vector3* position);
        sphere(vector3* scale, vector3* position, vector3* rotation);
        //virtual ~sphere();
        std::string to_string() override;

    protected:

    private:
};

#endif // SPHERE_H
