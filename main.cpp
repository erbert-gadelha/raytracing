#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>


#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix.h"

#include "FileWriter.h"

using namespace std;

Object* CreateCube() {
    std::vector<Vector3> vertices = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    };

    std::vector<std::tuple<int, int, int>> faces = {
        {0, 1, 2}, {2, 3, 0},{4, 5, 6}, {6, 7, 4}, 
        {0, 1, 5}, {5, 4, 0},{2, 3, 7}, {7, 6, 2},
        {1, 2, 6}, {6, 5, 1},{0, 3, 7}, {7, 4, 0} 
    };

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
    for (int i = 0; i < vertices.size(); i++) {
        Matrix cord = matrix.vectorToMatrix(vertices[i]);
        vertices[i] = (matrix * cord).to_vector();
    }
    

    return new Mesh(vertices, faces);
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

void Scene_1() {
    int RESOLUTION = 1080;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = {-5,5,-10};
    camera.transform.rotation = {10,25,0};



    Object* sphere = new Sphere(Vector3::ONE, {2,1.5,0.25});
    Object* mesh = new Mesh({ {0,2,0},{0,0,0},{2,0,0},{2,2,0}}, {{1,2,3}});
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));
    Object* cube = CreateCube();


    sphere->color = colorRGB::BLUE;
    plane->color = colorRGB::GREEN;
    mesh->color = colorRGB::RED;
    cube->color = colorRGB::YELLOW;

    vector<Object*> objects = {
        sphere,
        plane,
        mesh,
        cube
    };

    string image_ppm = camera.render(objects,{},nullptr);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_2() {
    
    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = Vector3(-5,5,-10);
    camera.transform.rotation = Vector3(10,25,0);

    Vector3 v_cord = Vector3(0,0,0);
    Matrix m_cord = Matrix().vectorToMatrix(v_cord);
    Matrix translate = {{{ 1, 0, 0,   2},
                         { 0, 1, 0, 1.5},
                         { 0, 0, 1, 0.25},
                         { 0, 0, 0,   1}
    }};

    Object* sphere = new Sphere(Vector3::ONE, (translate*m_cord).to_vector());
    Object* plane = new Plane(Vector3::ONE, Vector3::ZERO, Vector3::ZERO);

    sphere->color = colorRGB::BLUE;
    plane->color = colorRGB::GREEN;

    vector<Object*> objects = {sphere, plane};

    string image_ppm = camera.render(objects,{},nullptr);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_3(){

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);

    Object* icosaedro = CreateIcosaedro();
    icosaedro->color = colorRGB::RED;

    string image_ppm = camera.render({icosaedro},{},nullptr);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_4(){

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = {0,0,-5};
    camera.transform.rotation = {0,0,0};

    Vector3 lightPosition = {0,1,-.5};


    Object* sphere = new Sphere();
    Object* sphere2 = new Sphere(Vector3::ONE*0.2, lightPosition);
    Object* plane = new Plane(Vector3::ONE, Vector3::UP*(-1));
    sphere->color = colorRGB::YELLOW;
    plane->color = colorRGB::RED;


    sphere2->color = colorRGB::YELLOW;

    vector<Light*> lights = { new Light(lightPosition, colorRGB::WHITE) };

    string image_ppm = camera.render({sphere, plane, sphere2},lights, new Light(Vector3::UP*(-1), colorRGB::WHITE));
    FileWriter::saveAsImage(image_ppm);
}


int main() {
    //Scene_1();
    //Scene_2();
    //Scene_3();
    Scene_4();
    
    std::cout << "\n===============================\n" << std::endl;
    return 0;
}









