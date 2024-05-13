#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include <string>


class Plane : public Object
{
    public:
        Plane();
        Plane(Vector3* scale);
        Plane(Vector3* scale, Vector3* position);
        Plane(Vector3* scale, Vector3* position, Vector3* rotation);
        std::string to_string() override;

    protected:

    private:
};

#endif // PLANE_H
