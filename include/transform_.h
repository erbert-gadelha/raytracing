#ifndef TRANSFORM__H
#define TRANSFORM__H
#include "vector3.h"
#include <string>


class transform_
{
    public:
        transform_();
        vector3* rotation;
        vector3* position;
        vector3* scale;

        vector3* up;
        vector3* right;
        vector3* forward;
        void refresh_axys();

        std::string to_string();


    protected:
        vector3*  relative_vector3(vector3* v);

    private:
        double cos_x;
        double sin_x;

        double cos_y;
        double sin_y;


        double cos_z;
        double sin_z;
};

#endif // TRANSFORM__H
