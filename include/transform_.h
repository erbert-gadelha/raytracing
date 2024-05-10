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

        std::string to_string();


    protected:

    private:
};

#endif // TRANSFORM__H
