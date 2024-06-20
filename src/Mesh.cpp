#include "Mesh.h"
#include "Matrix.h"


Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<std::tuple<int, int, int>>& faces) {
    this->vertices = vertices;
    this->faces = faces;

    this->face_areas = std::vector<double>(this->faces.size());
    this->face_barycenters = std::vector<Vector3>(this->faces.size());
    this->face_normal = std::vector<Vector3>(this->faces.size());
    for(int i = 0; i < this->faces.size(); i++) {
        this->face_normal[i] = normal_f(i);

        std::tuple<int,int,int> face = this->faces[i];
        Vector3 A = vertices[std::get<0>(face)],
                B = vertices[std::get<1>(face)],
                C = vertices[std::get<2>(face)];

        Vector3 barycenter = (A+B+C)/3;
        this->face_barycenters[i] = barycenter;
        this->face_areas[i] = Vector3::CrossProduct(A-barycenter, B-barycenter).Magnitude() * 3;
    }

    this->vertice_normal = std::vector<Vector3>(this->vertices.size());
    for(int j = 0; j < this->vertices.size(); j++) {
        this->vertice_normal[j] = normal_v(j);
    }
    
}


CollisionResult Mesh::cast(Ray ray) {
    Vector3 point = ray.origin(),
            vector = ray.direction();

    CollisionResult result;
    result.t = 1000000;

    for(int i = 0; i < f(); i++) {
        CollisionResult result_ = cast_face(ray, i);

        if(result_.t < 0)
            continue;

        if(result_.t < result.t)
            result = result_;
    }

    return result;
}












CollisionResult Mesh::cast_face(Ray ray, int f) {

    Vector3 point = ray.origin(),
            vector = ray.direction();

    std::tuple<int,int,int> face = faces[f];
    Vector3 A = vertices[std::get<0>(face)],
            B = vertices[std::get<1>(face)],
            C = vertices[std::get<2>(face)];




    Vector3 normal = face_normal[f];
    Vector3 df = (point - this->face_barycenters[f]);

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



    CollisionResult result;
    double t = std::abs (a/b);
    //double t = -a/b;
    
    if (b == 0 || t < 0)
        return result;


    Vector3 T = ray.at(t);
    Vector3 TA = (A-T); // A - faces[f][0]
    Vector3 TB = (B-T); // B - faces[f][1]
    Vector3 TC = (C-T); // C - faces[f][2]
    double areaTAB = Vector3::CrossProduct(TA, TB).Magnitude();
    double areaTAC = Vector3::CrossProduct(TA, TC).Magnitude();
    double areaTBC = Vector3::CrossProduct(TB, TC).Magnitude();
    double areaTotal = areaTAB + areaTAC + areaTBC;

    //double areaTriangle = Vector3::CrossProduct(A-barycenter, B-barycenter).Magnitude() * 3;
    double areaTriangle = this->face_areas[f];

    // SUBITRACAO EH FEITA DEVIDA A IMPRECISAO DO PONTO FLUTUANTE
    if((areaTotal-0.00005) > areaTriangle)
        return result;
            


    result.t = t;
    result.color = this->color;
    //result.normal = normal;

    /*result.normal = normal_v(std::get<0>(face))*areaTAB +
                    normal_v(std::get<1>(face))*areaTAC +
                    normal_v(std::get<2>(face))*areaTBC;*/

    /*result.normal = normal_v(std::get<0>(face))*areaTAB + 
                    normal_v(std::get<2>(face))*areaTAC +
                    normal_v(std::get<1>(face))*areaTBC;*/

    /*result.normal = normal_v(std::get<1>(face))*areaTAB +
                    normal_v(std::get<2>(face))*areaTAC +
                    normal_v(std::get<0>(face))*areaTBC;*/

    result.normal = (normal_v(std::get<1>(face))*areaTAB +
                    normal_v(std::get<0>(face))*areaTAC +
                    normal_v(std::get<2>(face))*areaTBC)/3;

    /*result.normal = normal_v(std::get<2>(face))*areaTAB +
                    normal_v(std::get<0>(face))*areaTAC +
                    normal_v(std::get<1>(face))*areaTBC;*/

    /*result.normal = normal_v(std::get<2>(face))*areaTAB +
                    normal_v(std::get<1>(face))*areaTAC +
                    normal_v(std::get<0>(face))*areaTBC;*/

    result.normal = vertice_normal[std::get<0>(face)]*areaTAB +
                    vertice_normal[std::get<1>(face)]*areaTAC +
                    vertice_normal[std::get<2>(face)]*areaTBC;

    std::cout << "["<<areaTAB<<", " << areaTAC << ", " << areaTBC << "]" << std::endl;
    //std::cout << result.normal.to_string() << std::endl;

    //result.normal = Vector3::RIGHT*(1);

    return result;
}












Vector3 Mesh::normal_f(int f) {

    std::tuple<int,int,int> face = faces[f];
    Vector3 A = vertices[std::get<0>(face)];
    Vector3 B = vertices[std::get<1>(face)];
    Vector3 C = vertices[std::get<2>(face)];
    Vector3 AB = B-A;
    Vector3 AC = C-A;
    
    Matrix mAB, mAC;
    mAB = mAB.vectorToMatrix(AB);
    mAC = mAC.vectorToMatrix(AC);

    /*Vector3 O = Vector3( AB.getY()*AC.getZ() - AB.getZ()*AC.getY(),
                         AB.getZ()*AC.getX() - AB.getX()*AC.getZ(),
                         AB.getX()*AC.getY() - AB.getY()*AC.getX());
    return O;*/
    return mAB.dotProduct(mAC).to_vector().Normalized();

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

    Vector3 mediam = face_normal[0];
    for(int f = 1; f < faces.size(); f++)
        mediam = mediam + face_normal[f].Normalized();    

    return mediam.Normalized();
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
