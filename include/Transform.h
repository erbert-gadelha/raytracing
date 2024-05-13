#ifndef TRANSFORM__H
#define TRANSFORM__H
#include "Vector3.h"
#include <string>


class Transform
{
    public:
        Transform();
        Vector3* rotation;
        Vector3* position;
        Vector3* scale;

        Vector3* up;
        Vector3* right;
        Vector3* forward;
        void refresh_axys();

        std::string to_string();


    protected:
        Vector3*  relative_vector3(Vector3* v);

    private:
        double cos_x;
        double sin_x;

        double cos_y;
        double sin_y;


        double cos_z;
        double sin_z;
};

#endif // TRANSFORM__H
