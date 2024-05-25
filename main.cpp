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

    return new Mesh(vertices, faces);
}

void Scene_1() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    //Camera camera = Camera(1080, 1080, 1000);
    Camera camera = Camera(512, 512, 1000);
    //Camera camera = Camera(32, 32, 100);
    camera.transform.position.setZ(-10);




    Object* sphere = new Sphere(Vector3().ONE*1, Vector3(2,1.5,0.25));
    Object* mesh = new Mesh({Vector3(0,2,0),Vector3(0,0,0),Vector3(2,0,0),Vector3(2,2,0)}, {{1,2,3}});
    Object* plane = new Plane(Vector3().ONE, Vector3(3,-1,0), Vector3(0,0,0));
    Object* cube = CreateCube();
    sphere->color = BLUE;
    plane->color = GREEN;
    mesh->color = YELLOW;
    cube->color = RED;

    vector<Object*> objects;
    objects.push_back(sphere);
    objects.push_back(plane);
    objects.push_back(mesh);
    objects.push_back(cube);

    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);
}

void Scene_2() {
    Mesh mesh = Mesh({Vector3(3,0,0),Vector3(0,0,0),Vector3(0,3,0),Vector3(2,2,0)}, {{0,1,2}});
    mesh.cast(Ray(Vector3(0,0,-10), Vector3(0.01,0,0.9)));
}

int main() {
    Scene_1();
    //Scene_2();
    
    std::cout << "\n===============================\n" << std::endl;
    return 0;
}









