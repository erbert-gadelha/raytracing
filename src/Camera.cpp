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
}

Camera::Camera(int horizontal, int vertical, double distance) {
    this->transform = Transform();
    this->horizontal = horizontal;
    this->vertical = vertical;
    this->screen = Screen(horizontal,vertical);
    this->distance = distance;
}

std::string Camera::render(std::vector<Object*> objects) {
    std::cout << "Rendering <" << objects.size() << "> object(s)";
    auto start = std::chrono::high_resolution_clock::now();

    Vector3 M = transform.position + (transform.forward*distance);



    for(int i = 0; i < objects.size(); i++) {
        for(int h = 0; h < horizontal; h++) {
            for(int v = 0; v < vertical; v++) {
                Vector3 pixel = M + (transform.up*(v-(vertical/2))) + (transform.right*(h-(horizontal/2)));
                Vector3 V = (transform.position - pixel).Normalized();

                std::vector<Vector3> collisions = objects[i]->cast(transform.position, V);
                if(!collisions.empty()) {
                    screen.set(h, v, objects[i]->color);
                    //std::cout << "colidiu.\n";
                } else {
                    //std::cout << "não colidiu.\n";
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << " ~ (Complete in (" << (elapsed_seconds.count()) << ") seconds)." << std::endl;
    return screen.to_string();
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
