#include <iostream>
#include <vector>

#include "FileWriter.h"
#include "Ray.h"
#include "Vector3.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Transform.h"
#include "Screen.h"


using namespace std;


int main() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};


    //Camera camera = Camera(1080, 1080, 1000);
    Camera camera = Camera(512, 512, 1000);
    //Camera camera = Camera(32, 32, 100);
    camera.transform.position.setZ(-10);

    Object* sphere1 = new Sphere(Vector3().ONE*2, Vector3(0,0,0));
    Object* sphere2 = new Sphere(Vector3().ONE*1, Vector3(1,0.5,0));
    Object* plane1 = new Plane(Vector3().ONE, Vector3(3,0,0), Vector3(5,0,45));
    Object* plane2 = new Plane(Vector3().ONE, Vector3(3,-3,0), Vector3(5,0,0));
    sphere1->color = RED;
    sphere2->color = BLUE;
    plane1->color = YELLOW;
    plane2->color = GREEN;

    vector<Object*> objects;
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(plane1);
    objects.push_back(plane2);


    string image_ppm = camera.render(objects);
    FileWriter::saveAsImage(image_ppm);

    std::cout << "\n===============================\n" << std::endl;
    return 0;
}









