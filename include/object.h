// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "vector3.h"

class object {

    public:
        // Construtor com parâmetro position
        virtual ~object();
        virtual std::string to_string();
        vector3* scale;
        vector3* position;
        vector3* rotation;
        object();

    protected:
        object(vector3* scale);
        object(vector3* scale, vector3* position);
        object(vector3* scale, vector3* position, vector3* rotation);

    private:
};

#endif // OBJECT_H
