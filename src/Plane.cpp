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

double Plane::getD() {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return (normal.getX()*pos.getX()) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ());
}

double Plane::contains (Vector3 point) {
    Vector3 normal = transform.up();
    Vector3 pos = transform.position;
    return ((normal.getX()*pos.getX()) + (normal.getY()*pos.getY()) + (normal.getZ()*pos.getZ()) - this->getD());
}


std::vector<Vector3> Plane::cast(Vector3 point, Vector3 vector) {
    std::vector<Vector3> result;

    Vector3 normal = transform.up();
    Vector3 df = (point - transform.position);

    double xc = df.getX();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double yc = df.getY();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double zc = df.getZ();  // VETOR (PONTO RETA) - (PONTO PLANO)
    double xn = normal.getX();   // VETOR NORMAL AO PLANO
    double yn = normal.getY();   // VETOR NORMAL AO PLANO
    double zn = normal.getZ();   // VETOR NORMAL AO PLANO
    double x = vector.getX();   // VETOR DIRETOR DA RETA
    double y = vector.getY();   // VETOR DIRETOR DA RETA
    double z = vector.getZ();   // VETOR DIRETOR DA RETA
    double a = -(xn*xc + yn*yc + zn*zc);
    double b = (xn*x + yn*y + zn*z);

    if(a == 0 || b == 0)
        return result;

    if(a < 0) a*= -1;
    if(b < 0) b*= -1;

    result.push_back(point + (vector*(a/b)));
    return result;
}

std::string Plane::to_string() {
    return ("{\n\tmesh: plane,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
