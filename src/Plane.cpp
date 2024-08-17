//plane.cpp
#include "Plane.h"
#include "colorRGB.h"
#include <cmath>


Plane::Plane() : Object() {
    this->normal = Vector3::UP;
    this->right = Vector3::RIGHT;
    this->forward = Vector3::FORWARD;
}

Plane::Plane(Vector3 normal) : Object() {
    this->normal = normal.Normalized();


    Vector3 arbitrary(1, 0, 0);
    Vector3 temp = Vector3::CrossProduct(normal, arbitrary);
    if (temp.x == 0 && temp.y == 0 && temp.z == 0)
        arbitrary = Vector3(0, 1, 0);
    this->forward = Vector3::CrossProduct(normal, arbitrary).Normalized() * -1;
    this->right = Vector3::CrossProduct(normal, this->forward).Normalized();

}

Plane::Plane(Vector3 normal, Vector3 position) : Object() {
    this->transform.position = position;

    this->normal = normal.Normalized();
    Vector3 arbitrary(1, 0, 0);
    Vector3 temp = Vector3::CrossProduct(normal, arbitrary);
    if (temp.x == 0 && temp.y == 0 && temp.z == 0)
        arbitrary = Vector3(0, 1, 0);
    this->forward = Vector3::CrossProduct(normal, arbitrary).Normalized() * -1;
    this->right = Vector3::CrossProduct(normal, this->forward).Normalized();

}


CollisionResult Plane::cast(Ray ray) {
    CollisionResult result;

    Vector3 point = ray.origin(),
            vector = ray.direction();

    Vector3 normal = this->normal;
    Vector3 df = (point - transform.position);

    double a = -Vector3::Product(normal, df);
    double b = Vector3::Product(normal, vector);


    double t = a/b;

    if (b == 0 || t < 0)
        return result;

    result.t = t;
    result.material = this->material;
    result.normal = normal;


    // PROJ

    if(this->material.texture.v > 0 && this->material.texture.h > 0) {
        double o = Vector3::Proj(ray.at(t), this->right),
               p = Vector3::Proj(ray.at(t), this->forward);

        o -= std::floor(o);
        p -= std::floor(p);

        int v = floor(o*material.texture.v),
            h = floor(p*material.texture.h);
        
        if(v < 0 || v >= material.texture.v)
            v = material.texture.v;
        else if (h < 0 || h >= material.texture.h)
            h = material.texture.h;
        else
            result.material.color = result.material.color * this->material.texture.image[h][v];
    }


    return result;
}

std::string Plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + material.color.to_string() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
