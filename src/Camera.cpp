#include "Camera.h"
#include "Screen.h"
#include <string>
#include <vector>
#include <chrono>

Camera::Camera() {
    this->transform = Transform();
    this->horizontal = 256;
    this->vertical = 256;
    this->screen = Screen(horizontal,vertical);
    this->distance = 1;
    this->MAX_DISTANCE = 500;
}

Camera::Camera(int horizontal, int vertical, double distance) {
    this->transform = Transform();
    this->horizontal = horizontal;
    this->vertical = vertical;
    this->screen = Screen(horizontal,vertical);
    this->distance = distance;
    this->MAX_DISTANCE = 500;
}

std::string Camera::render(std::vector<Object*> objects) {
  // ===== DEBUG ===== //
    std::cout << "Rendering <" << objects.size() << "> object(s)";
    auto start = std::chrono::high_resolution_clock::now();
  // ===== DEBUG ===== //

    colorRGB SKY_COLOR = {120, 120, 255};
    colorRGB WHITE = {255, 255, 255};
    colorRGB FOG = {124, 133, 148};
    



    Vector3 M = transform.position + (transform.forward()*distance);  // posição e direção câmera 
    for(int v = 0; v < vertical; v++) {
        colorRGB GRADIENT = SKY_COLOR + WHITE*(((double)v)/((double)vertical*2));

        for(int h = 0; h < horizontal; h++) {
            double nearest = this->MAX_DISTANCE;
            Vector3 pixel = M - (transform.up()*(v-(vertical/2))) + (transform.right()*(h-(horizontal/2))); 
            Vector3 V = (pixel-transform.position).Normalized(); // cria um vetor da câmera para o pixel

            screen.set(h, v, GRADIENT); // define a cor do pixel 
            Ray ray = Ray(transform.position, V);

            for(int i = 0; i < objects.size(); i++) { // verifica cada objeto
                CollisionResult result = objects[i]->cast(ray); // verifica a colisão

                if(result.t < 0 || result.t > nearest)
                    continue;

                screen.set(h, v, specular(result, FOG));
                //screen.set(h, v, dephFog(result.color, FOG, result.t));
                nearest = result.t;
            }
            
        }
    }

  // ===== DEBUG ===== //
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << " ~ (Complete in (" << (elapsed_seconds.count()) << ") seconds)." << std::endl;
  // ===== DEBUG ===== //

    return this->screen.to_string();
}



colorRGB Camera::specular(CollisionResult result, colorRGB fog) {
    Vector3 vector3;
    double angle = vector3.Angle(Vector3(0,-1,0),result.normal)+0.2;
    
    return dephFog(result.color*angle, fog, result.t);
}

colorRGB Camera::dephFog(colorRGB color, colorRGB fog, double distance) {
    if(distance > this->MAX_DISTANCE)
        return fog;
    
    double f = distance/this->MAX_DISTANCE;
    return fog*f + color*(1-f);
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
