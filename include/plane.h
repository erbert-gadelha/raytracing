#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include <string>


class plane : public object
{
    public:
        vector3* scale;
        vector3* position;
        vector3* rotation;
        plane();
        plane(vector3* scale);
        plane(vector3* scale, vector3* position);
        plane(vector3* scale, vector3* position, vector3* rotation);
        //virtual ~plane();
        std::string to_string() override;

    protected:

    private:
};

#endif // PLANE_H
