#ifndef MESH_H
#define MESH_H
#include <string>
#include "vector3.h"

class mesh
{
    public:
        virtual ~mesh();
        //virtual ~mesh(vector3* position);
        //virtual ~mesh();
        vector3* position;
        virtual  std::string to_string();

    protected:
        mesh() {}

    private:
};

#endif // MESH_H
