//plane.cpp
#include "Plane.h"
#include "colorRGB.h"

Plane::Plane() : Object() {
    this->transform = Transform();
}

Plane::Plane(Vector3 scale) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
}

Plane::Plane(Vector3 scale, Vector3 position) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
}

Plane::Plane(Vector3 scale, Vector3 position, Vector3 rotation ) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
    this->transform.rotation = rotation;
}

/*double Plane::getD() {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return (normal.getX()*pos.getX()) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ());
}*/

/*double Plane::contains (Vector3 point) {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return ((normal.x*pos.x) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ()) - this->getD());
}*/

CollisionResult Plane::cast(Ray ray) {
    CollisionResult result;

    //Vector3 point, Vector3 vector
    Vector3 point = ray.origin(),
            vector = ray.direction();

    Vector3 normal = transform.up();
    Vector3 df = (point - transform.position);

    double a = -Vector3::Product(normal, df);
    double b = Vector3::Product(normal, vector);


    double t = a/b;

    if (b == 0 || t < 0)
        return result;

    result.t = t;
    result.material = this->material;
    result.normal = normal;

    return result;
}

std::string Plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + material.color.to_string() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
