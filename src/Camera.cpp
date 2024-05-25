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
    this->MAX_DISTANCE = 10000;
}

Camera::Camera(int horizontal, int vertical, double distance) {
    this->transform = Transform();
    this->horizontal = horizontal;
    this->vertical = vertical;
    this->screen = Screen(horizontal,vertical);
    this->distance = distance;
    this->MAX_DISTANCE = 10000;
}

std::string Camera::render(std::vector<Object*> objects) {
  // ===== DEBUG ===== //
    std::cout << "Rendering <" << objects.size() << "> object(s)";
    auto start = std::chrono::high_resolution_clock::now();
  // ===== DEBUG ===== //

    colorRGB SKY_COLOR = {120, 120, 255};
    colorRGB WHITE = {255, 255, 255};



    Vector3 M = transform.position + (transform.forward()*distance);
    for(int v = 0; v < vertical; v++) {
        colorRGB GRADIENT = SKY_COLOR + WHITE*(((double)v)/((double)vertical*2));

        for(int h = 0; h < horizontal; h++) {
            double nearest = this->MAX_DISTANCE;
            Vector3 pixel = M - (transform.up()*(v-(vertical/2))) + (transform.right()*(h-(horizontal/2)));
            Vector3 V = (pixel-transform.position).Normalized();

            screen.set(h, v, GRADIENT);
            Ray ray = Ray(transform.position, V);

            for(int i = 0; i < objects.size(); i++) {
                CollisionResult result = objects[i]->cast(ray);

                if(result.t < 0 || result.t > nearest)
                    continue;

                screen.set(h, v, dephFog(result.color, WHITE, result.t));
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



colorRGB Camera::dephFog(colorRGB color, colorRGB fog, double distance) {
    return ( color*(50/distance) + fog*(distance/50));
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
