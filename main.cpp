#include <iostream>
#include <vector>
#include <tuple>


#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix.h"

#include "FileWriter.h"
#include "TransformAfim.h"

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

    return new Mesh(vertices, faces);
}

void Scene_1() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    int RESOLUTION = 1080;
    Camera camera = Camera(RESOLUTION, RESOLUTION, (RESOLUTION/512)*1000);
    camera.transform.position = Vector3(-5,5,-10);
    camera.transform.rotation = Vector3(10,25,0);




    Object* sphere = new Sphere(Vector3().ONE*1, Vector3(2,1.5,0.25));
    Object* mesh = new Mesh({Vector3(0,2,0),Vector3(0,0,0),Vector3(2,0,0),Vector3(2,2,0)}, {{1,2,3}});
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));
    Object* cube = CreateCube();

    // Transformação 

    // std::vector<Vector3> vertices = {
    //     {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
    //     {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    // };

    // std::vector<std::tuple<int, int, int>> faces = {
    //     {0, 1, 2}, {2, 3, 0},{4, 5, 6}, {6, 7, 4}, 
    //     {0, 1, 5}, {5, 4, 0},{2, 3, 7}, {7, 6, 2},
    //     {1, 2, 6}, {6, 5, 1},{0, 3, 7}, {7, 4, 0} 
    // };
    // std::vector<Vector3> newVertices;

    // for (int i = 0; i < vertices.size(); i++) {
    //     TransformAfim transform = TransformAfim("rotY", 90, vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    //     std::vector<double> coord = transform.getCoord();
    //     newVertices.push_back({coord[0], coord[1], coord[2]});

    // }
    // cube = new Mesh(newVertices, faces);


    sphere->color = BLUE;
    plane->color = GREEN;
    mesh->color = RED;
    cube->color = YELLOW;

    vector<Object*> objects;
    objects.push_back(sphere);
    objects.push_back(plane);
    objects.push_back(mesh);
    objects.push_back(cube);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_2() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

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

    Object* sphere = new Sphere(Vector3().ONE*1, (translate*m_cord).to_vector());
    Object* plane = new Plane(Vector3().ONE, Vector3(0,0,0), Vector3(0,0,0));

    sphere->color = BLUE;
    plane->color = GREEN;

    vector<Object*> objects;
    objects.push_back(sphere);
    objects.push_back(plane);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

int main() {
    //Scene_1();
    Scene_2();
    
    std::cout << "\n===============================\n" << std::endl;
    return 0;
}









