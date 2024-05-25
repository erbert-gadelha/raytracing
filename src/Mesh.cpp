#include "Mesh.h"


Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<std::tuple<int, int, int>>& faces) {
    this->vertices = vertices;
    this->faces = faces;
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

    std::tuple<int,int,int> face = faces[f];
    Vector3 A, B, C;

    A = vertices[std::get<0>(face)];
    B = vertices[std::get<1>(face)];
    C = vertices[std::get<2>(face)];


    //Vector3 point, Vector3 vector
    Vector3 point = ray.origin(),
            vector = ray.direction();


    Vector3 normal = normal_f(f);
    Vector3 baricenter = (A+B+C)/3;
    Vector3 df = (point - baricenter);

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


    Vector3 PA = (A-baricenter);
    Vector3 PB = (B-baricenter);
    Vector3 PC = (C-baricenter);
    double areaPAB = Vector3::CrossProduct(PA, PB).Magnitude();
    double areaPAC = Vector3::CrossProduct(PA, PC).Magnitude();
    double areaPBC = Vector3::CrossProduct(PB, PC).Magnitude();
    double areaTriangle = areaPAB + areaPAC + areaPBC;


    Vector3 T = ray.at(t);
    Vector3 TA = (A-T);
    Vector3 TB = (B-T);
    Vector3 TC = (C-T);

    double areaTAB = Vector3::CrossProduct(TA, TB).Magnitude();
    double areaTAC = Vector3::CrossProduct(TA, TC).Magnitude();
    double areaTBC = Vector3::CrossProduct(TB, TC).Magnitude();
    double areaTotal = areaTAB + areaTAC + areaTBC;

    /*std::cout << std::endl;
    std::cout << "A  = " << A.to_string() << std::endl;
    std::cout << "B  = " << B.to_string() << std::endl;
    std::cout << "C  = " << C.to_string() << std::endl;
    std::cout << "P  = " << baricenter.to_string() << std::endl;
    std::cout << std::endl;

    std::cout << "PA = " << PA.to_string() << std::endl;
    std::cout << "PB = " << PB.to_string() << std::endl;
    std::cout << "PC = " << PC.to_string() << std::endl;
    std::cout << "PAB = " << areaPAB << std::endl;
    std::cout << "cross PAB: " << Vector3::CrossProduct(PA, PB).to_string() << std::endl;
    std::cout << "magnitude PAB: " << Vector3::CrossProduct(PA, PB).Magnitude() << std::endl;
    std::cout << "PAC = " << areaPAC << std::endl;
    std::cout << "PBC = " << areaPBC << std::endl;
    std::cout << "AREA:" << areaTriangle << std::endl;

    std::cout << std::endl;
    std::cout << "DA = " << TA.to_string() << std::endl;
    std::cout << "DB = " << TB.to_string() << std::endl;
    std::cout << "DC = " << TC.to_string() << std::endl;
    std::cout << "DAB = " << areaTAB << std::endl;
    std::cout << "DAC = " << areaTAC << std::endl;
    std::cout << "DBC = " << areaTBC << std::endl;
    std::cout << "AREA:" << areaTotal << std::endl;*/


    // SUBITRACAO EH FEITA DEVIDA A IMPRECISAO DO PONTO FLUTUANTE
    if((areaTotal-0.00005) > areaTriangle)
        return result;
            


    result.t = t;
    result.color = this->color;
    result.normal = normal;

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


    Vector3 O = Vector3( AB.getY()*AC.getZ() - AB.getZ()*AC.getY(),
                         AB.getZ()*AC.getX() - AB.getX()*AC.getZ(),
                         AB.getX()*AC.getY() - AB.getY()*AC.getX());

    /*std::cout << "A  = " << A.to_string() << std::endl;
    std::cout << "B  = " << B.to_string() << std::endl;
    std::cout << "C  = " << C.to_string() << std::endl;
    std::cout << "AB = " << AB.to_string()<< std::endl;
    std::cout << "AC = " << AC.to_string()<< std::endl;
    std::cout << "O  = " << O.to_string() << std::endl;*/

    return O;

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

