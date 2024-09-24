#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <string>


#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Camera.h"
#include "Matrix.h"
#include "Texture.h"
#include <fstream>

#include "Parser.h"

using namespace std;

/*Mesh CreateCube(Matrix* transform) {
    std::vector<Vector3> vertices = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    };

    std::vector<std::tuple<int, int, int>> faces = {
        {0, 1, 2}, {2, 3, 0},{4, 5, 6}, {6, 7, 4}, 
        {0, 1, 5}, {5, 4, 0},{2, 3, 7}, {7, 6, 2},
        {1, 2, 6}, {6, 5, 1},{0, 3, 7}, {7, 4, 0} 
    };

    if(transform != nullptr) {
        for (int i = 0; i < vertices.size(); i++) {
            Matrix cord = transform->vectorToMatrix(vertices[i]);
            vertices[i] = (*transform * cord).to_vector();
        }
    }

    return Mesh(vertices, faces);
}


Object* CreateIcosaedro() {
    const double t = (1.0 + std::sqrt(5.0)) / 2.0;
    std::vector<Vector3> vertices = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };

    std::vector<std::tuple<int, int, int>> faces = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };


    Matrix matrix, translate, rotateY, scale;
    int angle = 0;
    double c = std::cos(angle),
           s = std::sin(angle);
    rotateY.values = {{ c,0,s,0},
                      { 0,1,0,0},
                      {-s,0,c,0},
                      { 0,0,0,1}
    };
    translate.values = {{1,0,0,0},
                        {0,1,0,0.5},
                        {0,0,1,5},
                        {0,0,0,1}
    };
    scale.values = {{0.5,0,0,0},
                    {0,0.5,0,0},
                    {0,0,0.5,0},
                    {0,0,0,1}
    };
    
    matrix = translate*scale*rotateY;
    for (int i = 0; i < vertices.size(); i++) {
        Matrix cord = matrix.vectorToMatrix(vertices[i]);
        vertices[i] = (matrix * cord).to_vector();
    }


    return new Mesh(vertices, faces);
}


/// @brief 1xEsfera, 1xRetangulo, 1xCubo e 1xPlano com iluminação ambiental.
void Scene_1() {
    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = {0,1,-10};
    camera.transform.rotation = {4,0,0};



    Object* sphere = new Sphere(Vector3::ONE, {2,1.5,0.25});
    Object* mesh = new Mesh({ {0,2,0},{0,0,0},{2,0,0},{2,2,0}}, {{1,2,3}});
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));



    Matrix matrix, translate, rotateY;
    int angle = -30;
    double c = std::cos(angle),
           s = std::sin(angle);
    rotateY.values = {{ c,0,s,0},
                      { 0,1,0,0},
                      {-s,0,c,0},
                      { 0,0,0,1}
    };
    translate.values = {{1,0,0,0},
                        {0,1,0,0.5},
                        {0,0,1,0},
                        {0,0,0,1}
    };

    matrix = translate*rotateY;
    Mesh cube = CreateCube(&matrix);


    sphere->material = { 1, 5, 1, 1, 1, 100, colorRGB::BLUE};
    plane->material = { 1, 5, 1, 1, 1, 100, colorRGB::GREEN};
    mesh->material = { 1, 4, 1, 1, 1, 1000, colorRGB::RED};
    cube.material = { 1, 5, 1, 1, 1, 100, colorRGB::YELLOW};

    vector<Object*> objects = {
        sphere,
        plane,
        mesh,
        &cube
    };


    Light* ambiental =  new Light(colorRGB::WHITE, .2, Vector3::ONE);
    vector<Light*> lights = { new Light(colorRGB::WHITE, 1, {0,.5,-5})};

    string image_ppm = camera.render(objects,lights,ambiental);
    FileWriter::saveAsImage(image_ppm);
}*/


void replaceNewlines(std::string& str) {
    std::string target = "\\n"; // Isso é o que você espera como entrada
    std::string replacement = "\n"; // Isso é o que você quer na string
    
    // Substituindo todas as ocorrências de "\\n" por "\n"
    size_t pos = 0;
    while ((pos = str.find(target, pos)) != std::string::npos) {
        str.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }
}

int main(int argc, char* argv[]) {

    if(argc == 3) {

        Parser::logging = false;

        string v0 = argv[1];
        string v1 = argv[2];
        string image_ppm;

        if (v0[0] == '1') {
            replaceNewlines(v1);
            try {
                image_ppm = Parser::parseFromString(v1);
            } catch (exception e) {
                cout << "Error\n";
            }
        }
        
        if(!image_ppm.empty()) {
            cout << image_ppm << std::endl;
            return 0;
        } else {
            //cout << "EMPTY";
        }
    }

    cout << "NOOP" << std::endl;    
    return -1;
}









