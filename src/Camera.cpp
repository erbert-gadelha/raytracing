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

void Camera::threadRendering(std::vector<Object*> objects, std::vector<Light*>lights, Light* ambient_light, int initial_x, int final_x, int initial_y, int final_y) {
    colorRGB SKY_COLOR = {120, 120, 255};
    colorRGB WHITE = {255, 255, 255};
    //colorRGB FOG = {124, 133, 148};

    Vector3 M = transform.position + (transform.forward()*distance);  // posição e direção câmera 
    for(int x = initial_x; x < final_x; x++) {
        // SIMULA PRESENCA DE UMA SKYBOX
        //colorRGB GRADIENT = SKY_COLOR + WHITE*(((double)x)/((double)vertical*2));
        colorRGB GRADIENT = WHITE*0;

        for(int y = initial_y; y < final_y; y++) {
            //CollisionResult nearest = {this->MAX_DISTANCE, Vector3::UP, GRADIENT};
            CollisionResult nearest = {this->MAX_DISTANCE, Vector3::UP, GRADIENT};
            Vector3 pixel = M - (transform.up()*(x-(vertical/2))) + (transform.right()*(y-(horizontal/2))); 
            Vector3 V = (pixel-transform.position).Normalized(); // cria um vetor da câmera para o pixel

            screen.set(y, x, GRADIENT); // define a cor do pixel 
            Ray ray = Ray(transform.position, V);

            for(int i = 0; i < objects.size(); i++) { // verifica cada objeto
                CollisionResult result = objects[i]->cast(ray);
                if(result.t < 0 || result.t > nearest.t)
                    continue;
                nearest = result;
            }

            screen.set(y, x, phong(nearest, ray.at(nearest.t), lights, ambient_light));
            
        }
    }

}


std::string Camera::render(std::vector<Object*> objects, std::vector<Light*> lights, Light* ambient_light) {
    // ===== DEBUG ===== //
    std::cout << "Rendering <" << objects.size() << "> object(s)";
    auto start = std::chrono::high_resolution_clock::now();
    // ===== DEBUG ===== //
    


    // ===== CRIANDO THREADS ===== //
    int cores = 8;
    int chunck = vertical/cores;
    std::thread threads [cores];
    for(int i = 0; i < cores; i++)
        threads[i] = std::thread ([this](std::vector<Object*> objects, std::vector<Light*>lights, Light* ambient_light, int initial_x, int final_x, int initial_y, int final_y) { this->threadRendering(objects, lights, ambient_light, initial_x, final_x, initial_y, final_y); }, objects, lights, ambient_light,  0, horizontal, chunck*i, chunck*(i+1));
    for(int i = 0; i < cores; i++)
        threads[i].join();
    // ===== CRIANDO THREADS ===== //



    // ===== DEBUG ===== //
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << " ~ (Complete in (" << (elapsed_seconds.count()) << ") seconds)." << std::endl;
    // ===== DEBUG ===== //

    return this->screen.to_string();
}



colorRGB Camera::specular(CollisionResult result, colorRGB fog) {
    Vector3 vector3;
    double angle = vector3.Angle(Vector3(0,-1,0),result.normal)/*+0.2*/;
    
    return dephFog(result.color*angle, fog, result.t);
}

colorRGB Camera::dephFog(colorRGB color, colorRGB fog, double distance) {
    if(distance > this->MAX_DISTANCE)
        return fog;
    
    double f = distance/this->MAX_DISTANCE;
    return fog*f + color*(1-f);
}


colorRGB Camera::phong(CollisionResult result, Vector3 position, std::vector<Light*>lights, Light* ambient_light) {

    colorRGB I = {255, 0, 0};
    
    double d = this->MAX_DISTANCE;

    /*for(int i = 0; i < lights.size(); i++) {
        Vector3 v = position - ambient_light->transform.position;
        d = v.Magnitude();

        double angle = Vector3::Angle(v, result.normal);
    }*/
    
    return result.color*I;
}



std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
