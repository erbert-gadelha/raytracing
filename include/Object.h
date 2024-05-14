// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Transform.h"
#include "colorRGB.h"
#include <vector>

class Object {

    public:
        Object();
        virtual ~Object();
        virtual std::string to_string();
        virtual std::vector<Vector3> cast(Vector3 point, Vector3 vector);
        Transform transform;
        colorRGB color;

        void setColor(int r, int g, int b);
        std::string getColor();


    protected:
        /*object(vector3* scale);
        object(vector3* scale, vector3* position);
        object(vector3* scale, vector3* position, vector3* rotation);*/

    private:
};

#endif // OBJECT_H
