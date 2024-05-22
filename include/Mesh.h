#ifndef MESH_H
#define MESH_H

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "Transform.h"
#include "colorRGB.h"
#include <vector>
#include <tuple>


class Mesh : public Object {

    public:
        Mesh() {};
        Mesh(const std::vector<Vector3>& vertices, const std::vector<std::tuple<int, int, int>>& faces) : vertices(vertices), faces(faces) {};
        std::string to_string() override;
        std::vector<Vector3> cast(Ray ray) override;
        colorRGB color;

        int v() {return vertices.size();}
        int f() {return faces.size();}



    protected:
        std::vector<Vector3> vertices;
        std::vector<std::tuple<int, int, int>> faces;
};

#endif // MESH_H
