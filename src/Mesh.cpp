#include "Mesh.h"


std::vector<Vector3> Mesh::cast(Ray ray) {
    Vector3 point = ray.origin(),
            vector = ray.direction();

    std::vector<Vector3> result;
    return result;
}

std::string Mesh::to_string() {
    std::string result = "{\n\tfaces: [";

    for(int i = 0; i < f(); i++){
        std::tuple<int,int,int> face = faces[i];
        int i1 = std::get<0>(face),
            i2 = std::get<1>(face),
            i3 = std::get<2>(face);
        result += ("\n\t(" + std::to_string(i1) + "," + std::to_string(i2) + "," + std::to_string(i3) + "): ");
        result += (" [" + vertices[i1].to_string() + ", " + vertices[i2].to_string() + ", " + vertices[i3].to_string() + "]");
    }
    result += "\n\t]\n}";

    return result;
}


Vector3 Mesh::normal_f(int f) {
    std::tuple<int,int,int> face = faces[f];
    Vector3 A, B, C, AB, AC;

    A = vertices[std::get<0>(face)];
    B = vertices[std::get<1>(face)];
    C = vertices[std::get<2>(face)];
    AB = B-A;
    AC = C-A;

    return Vector3( AB.getY()*AC.getZ() - AB.getZ()*AC.getY(),
                    AB.getZ()*AC.getX() - AB.getX()*AC.getZ(),
                    AB.getX()*AC.getY() - AB.getY()*AC.getX());

}

Vector3 Mesh::normal_v(int v) {
    std::vector<int> faces;

    for(int i = 0; i < f(); i++) {
        std::tuple<int,int,int> face = this->faces[i];
        if(std::get<0>(face) == v)
            faces.push_back(i);
        else if(std::get<1>(face) == v)
            faces.push_back(i);
        else if(std::get<2>(face) == v)
            faces.push_back(i);
    }


    if(faces.empty())
        return Vector3::UP;

    Vector3 mediam = Vector3(0,0,0);
    for(int f = 0; f < faces.size(); f++)
        mediam = mediam + normal_f(f);

    return mediam.Normalized();
}