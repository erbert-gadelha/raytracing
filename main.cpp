#include <iostream>
#include "vector3.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"
#include "transform_.h"
//#include "colorRGB.h"
#include "screen.h"

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

    //screen* screen_ = new screen(1080, 720);
    /*screen* screen_ = new screen(64, 32);
    screen_->set(0, 0, RED);
    screen_->set(1, 0, GREEN);
    screen_->set(2, 0, BLUE);

    saveAsImage(screen_->to_string(), "image.ppm");*/



        // Image
        int image_height = 256;
        int image_width = 256;
        screen* screen_ = new screen(image_width, image_height);

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

        return 0;

}
