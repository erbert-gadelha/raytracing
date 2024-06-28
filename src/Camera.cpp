#include "Camera.h"
#include "Screen.h"
#include <string>
#include <vector>
#include <chrono>
#include <Material.h>
#include <math.h>

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
        colorRGB GRADIENT = WHITE;

        for(int y = initial_y; y < final_y; y++) {
            //CollisionResult nearest = {this->MAX_DISTANCE, Vector3::UP, GRADIENT};
            CollisionResult nearest = {this->MAX_DISTANCE, Vector3::UP};
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

            if(nearest.t != MAX_DISTANCE)
                screen.set(y, x, phong(nearest, ray.at(nearest.t), transform.position, lights, ambient_light));
            else
                screen.set(y, x, GRADIENT);
            
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



colorRGB Camera::phong(CollisionResult result, Vector3 point, Vector3 observer, std::vector<Light*> lights, Light* ambient_light) {


    colorRGB diffuse = {0, 0, 0};
    colorRGB specular = {0, 0, 0};

    Vector3 viewDir = (observer - point).Normalized();
    
    for (int i = 0; i < lights.size(); i++) {
        Light light = *lights[i];
        Vector3 lightDir = (light.transform.position - point).Normalized();
        Vector3 reflectDir = ((result.normal *2* Vector3::Product(result.normal, lightDir)) - lightDir).Normalized();
        
        // Difusa
        double diff = std::max(Vector3::Product(result.normal,lightDir), 0.0);
        diffuse += (light.color*light.intensity) * diff;
        
        // Especular
        double spec = std::pow(std::max(Vector3::Product(viewDir,reflectDir), 0.0), 2);
        specular += (light.color*light.intensity) * spec;
    }


    colorRGB ambient = (result.material.color*ambient_light->color)*ambient_light->intensity;
    ambient = (ambient/255).clamped();

    diffuse = (result.material.color*diffuse);
    diffuse = (diffuse/255).clamped();

    specular = (result.material.color*specular);
    specular = (specular/255).clamped();


    colorRGB finalColor = ambient*result.material.a +
                          diffuse*result.material.d +
                          specular*result.material.s;

    return finalColor.clamped();
}



std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
