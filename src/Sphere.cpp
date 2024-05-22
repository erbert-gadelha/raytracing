// sphere.cpp
#include "Sphere.h"
#include <iostream>
#include "Transform.h"
#include "Vector3.h"
#include <math.h>       /* sqrt */
#include <vector>

Sphere::Sphere() : Object() {
    this->transform = Transform();
}

Sphere::Sphere(Vector3 scale) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
}

Sphere::Sphere(Vector3 scale, Vector3 position) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
}

Sphere::Sphere(Vector3 scale, Vector3 position, Vector3 rotation ) : Object() {
    this->transform = Transform();
    this->transform.scale = scale;
    this->transform.position = position;
    this->transform.rotation = rotation;
}




std::vector<Vector3> Sphere::cast(Ray ray) {
    std::vector<Vector3> result;

    //Vector3 point, Vector3 vector
    Vector3 point = ray.origin(),
            vector = ray.direction();

    Vector3 df = point - transform.position;
    double x = vector.getX(); // VETOR DIRETOR DA RETA
    double y = vector.getY(); // VETOR DIRETOR DA RETA
    double z = vector.getZ(); // VETOR DIRETOR DA RETA
    double xc = df.getX();    // DIFERENCA DAS COORDENADAS
    double yc = df.getY();    // DIFERENCA DAS COORDENADAS
    double zc = df.getZ();    // DIFERENCA DAS COORDENADAS
    double radius = this->transform.scale.getX()/2;    // RAIO DA ESFERA

    double a = (x*x) + (y*y) + (z*z);
    double b = (-2)*((x*xc)+(y*yc)+(z*zc));
    double c = (xc*xc)+(yc*yc)+(zc*zc) - (radius*radius);
    double delta = (b*b)-(4*a*c);


    if(delta < 0)
        return result;

    double square_root = sqrt(delta);
    double t1 = (-b+square_root)/(2*a);
    double t2 = (-b-square_root)/(2*a);

  //////////// DEBUG ////////////
    /*std::cout << "casting : {\n";
    std::cout << "   sphere: { radius: " << radius << ", position: " << this->transform.position.getX() << ',' << this->transform.position.getY() << ',' << this->transform.position.getZ() << ") }\n";
    std::cout << "   line: { point: (" << point.getX() << ',' << point.getY() << ',' <<  point.getZ() << "), vector: (" << x << ',' << y << ',' <<  z << ") }\n";
    std::cout << "};\n";
    printf("{\n   a: %f\n   b: %f\n   c: %f\n   delta:%f\n};\n", a, b, c, delta);
    std::cout << "   raiz [1]: " << t1 << ";\n";
    std::cout << "   raiz [2]: " << t2 << ";\n";*/
  //////////// DEBUG ////////////


    result.push_back( point + (vector*t1));
    if (delta == 0)
        return result;
    result.push_back( point + (vector*t2));
    return result;
}



std::string Sphere::to_string() {
    return ("{\n\tmesh: sphere,\n\tcolor: (" + getColor() + ")\n\ttransform: " + this->transform.to_string() + "\n}");
}
