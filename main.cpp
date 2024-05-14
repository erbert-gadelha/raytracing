#include <iostream>
#include "Vector3.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Transform.h"
#include "Screen.h"

#include <math.h>       /* sqrt */
#include <fstream>
#include <vector>


using namespace std;

void saveAsImage (std::string image, std::string fileName) {
    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    outputFile << image;
    outputFile.close();
    std::cout << "Arquivo gerado com sucesso." << std::endl;
}



int main() {
    colorRGB RED   = {255,0,0};
    colorRGB GREEN = {0,255,0};
    colorRGB BLUE  = {0,0,255};
    colorRGB YELLOW  = {255,255,0};

    Camera camera = Camera(512, 512, 1000);
    camera.transform.position.setZ(-10);

    Sphere sphere1 = Sphere(Vector3().ONE*2, Vector3(0,0,0));
    sphere1.color = RED;
    Sphere sphere2 = Sphere(Vector3().ONE*1, Vector3(1,2,0));
    sphere2.color = BLUE;

    vector<Object*> objects;
    objects.push_back(&sphere1);
    objects.push_back(&sphere2);
    saveAsImage(camera.render(objects), "image.ppm");

    return 0;
}









