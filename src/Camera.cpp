#include "Camera.h"
#include "Screen.h"
#include <string>
#include <vector>

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
    Vector3 M = transform.position + (transform.forward*distance);



    for(int i = 0; i < objects.size(); i++) {
        for(int h = 0; h < horizontal; h++) {
            for(int v = 0; v < vertical; v++) {
                Vector3 pixel = M + (transform.up*v) + (transform.right*h);
                Vector3 V = (transform.position - pixel).Normalized();

                std::cout << V.to_string() << std::endl;
                std::vector<Vector3> collisions = objects[i]->cast(transform.position, transform.forward);
                if(collisions.size() > 0)
                    screen.set(h, v, objects[i]->color);
            }
        }
    }
    return screen.to_string();
}

std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n}");
}
