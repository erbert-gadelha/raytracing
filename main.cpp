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


    Object* sphere = new Sphere();
    std::cout<< sphere->cast(new Vector3(0,0,-10), new Vector3(0,0,1)) << std::endl;


    return 0;

    // Image
    int image_height = 256;
    int image_width = 256;
    Screen* screen_ = new Screen(image_width, image_height);

    // Render

    int center_x = image_width/2;
    int center_y = image_height/2;

    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            if(y > center_y)
                if(x > center_x)
                    screen_->set(x, y, GREEN);
                else
                    screen_->set(x, y, BLUE);
            else
                if(x > center_x)
                    screen_->set(x, y, RED);
                else
                    screen_->set(x, y, YELLOW);
        }
    }

    saveAsImage(screen_->to_string(), "image.ppm");


}
