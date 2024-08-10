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
#include "Matrix.h"

#include "FileWriter.h"

using namespace std;

Mesh CreateCube(Matrix* transform) {
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


std::vector<Vector3> CreatePoints(Vector3 point) {
    std::vector<Vector3> points = {};

    double gap = 0.4;
    double occur = 1;

    for (double i = -occur; i < occur; i++)
        for (double j = -occur; j < occur; j++)
            for (double k = -occur; k < occur; k++)
                points.push_back(Vector3{i*gap,j*gap,k*gap});


    for(int i = 0; i < points.size(); i++)
        points[i] = points[i] + point;

    return points;
    //return {point};
}



/*

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
}

/// @brief Transformação vetorial aplicada à uma esfera.
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

    sphere->material.color = colorRGB::BLUE;
    plane->material.color = colorRGB::GREEN;

    Light* ambiental =  new Light(colorRGB::WHITE, 1, Vector3::ONE);
    string image_ppm = camera.render({sphere, plane},{},ambiental);
    FileWriter::saveAsImage(image_ppm);
}

/// @brief 1xIcosaedro com luz pontual
void Scene_3(){

    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);

    Object* icosaedro = CreateIcosaedro();
    Object* plane = new Plane(Vector3::ONE, {0,-1,0}, Vector3::ZERO);

    icosaedro->material.a = .1;
    icosaedro->material.s = 2;
    icosaedro->material.d = .5;
    icosaedro->material.n = 200;
    icosaedro->material.color = colorRGB::BLUE;

    plane->material.a = .1;
    plane->material.color = colorRGB::RED;
    Object* s3 = new Sphere({3,3,3},{-2,1.4,7});
    s3->material.a = .1;
    s3->material.s = 2;
    s3->material.d = 1;
    s3->material.n = 100;

    

    Light* ambiental =  new Light(colorRGB::WHITE, 1, Vector3::ONE);
    vector<Light*> lights = { new Light(colorRGB::WHITE, 0.5, {0,1,-1}) };

    string image_ppm = camera.render({icosaedro, plane, s3 }, lights, ambiental);
    FileWriter::saveAsImage(image_ppm);
}*/

/// @brief 3xEsferas, 1xPlano com uma Luz pontual
void Scene_4(){


    int RESOLUTION = 512;
    Camera camera = Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
    camera.transform.position = Vector3(0,2,-10);
    camera.transform.rotation = Vector3(5,0,0);

    Object* s0 = new Sphere({1,1,1},{0,.35,0});
    Object* s1 = new Sphere({.2,.2,.2}, {-1.2, .5, 0});
    Object* s2 = new Sphere({.4,.4,.4}, {1.5, 1, 1});
    Object* s3 = new Sphere({1,1,1},{-.35,1.7,.2});
    Object* s4 = new Sphere({1,1,1},{1,2,.2});
    Object* p = new Plane();
    s0->material.color = colorRGB::RED;
    s1->material.color = colorRGB::YELLOW;
    s2->material.color = colorRGB::GREEN;
    s3->material.color = colorRGB::RED;
    p->material.color = colorRGB::YELLOW;

    s1->material.a = 0.8;
    s1->material.s = 2;
    s1->material.d = 1;
    s1->material.n = 10;

    s3->material.a = .1;
    s3->material.s = 2;
    s3->material.d = 1;
    s3->material.n = 100;

    s4->material.a = .1;
    s4->material.s = .4;
    s4->material.d = .3;
    s4->material.n = 100;
    s4->material.r = 0.1;
    s4->material.color = colorRGB::BLACK;
    s4->material.opacity = 0.1;
    s4->material.ior = 10.8;


    Light* ambiental =  new Light(colorRGB::WHITE, 0.2, {Vector3::ONE});

    vector<Light*> lights = { new Light(colorRGB::WHITE, 1, CreatePoints({-5,1,-1}))};


    string image_ppm = camera.render({s0, s1, s2, s3, s4, p}, lights, ambiental);
    FileWriter::saveAsImage(image_ppm);
}




int main() {
    //Scene_1();
    //Scene_2();
    //Scene_3();
    Scene_4();
    
    return 0;
}









