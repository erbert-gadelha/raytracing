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

    Vector3 M = transform.position + (transform.forward()*distance);  // posição e direção câmera 
    for(int x = initial_x; x < final_x; x++) {
        // SIMULA PRESENCA DE UMA SKYBOX
        double frac = ((double)x)/((double)vertical);
        colorRGB w = colorRGB::WHITE;
        colorRGB GRADIENT = ((ambient_light->color/frac)+(w.clamped() * frac)).clamped() * 0.1;

        for(int y = initial_y; y < final_y; y++) {
            CollisionResult nearest = {this->MAX_DISTANCE, Vector3::UP};
            Vector3 pixel = M - (transform.up()*(x-(vertical/2))) + (transform.right()*(y-(horizontal/2))); 
            Vector3 V = (pixel-transform.position).Normalized(); // cria um vetor da câmera para o pixel

            screen.set(y, x, GRADIENT); // define a cor do pixel 
            Ray ray = Ray(transform.position, V);

            int j = -1;

            for(int i = 0; i < objects.size(); i++) { // verifica cada objeto
                CollisionResult result = objects[i]->cast(ray);
                if(result.t < 0 || result.t > nearest.t)
                    continue;
                j = i;
                nearest = result;
            }

            if(nearest.t != MAX_DISTANCE) {
                colorRGB resultColor = phong(nearest, ray.at(nearest.t), transform.position, objects, lights, ambient_light);

                CollisionResult r_nearest;
                r_nearest.t = MAX_DISTANCE;
                r_nearest.material.color = colorRGB::BLACK;
                Vector3 reflectDir = (nearest.normal*2 - (ray.at(nearest.t)-transform.position).Normalized()).Normalized();
                //Vector3 reflectDir = {ray.direction().x * -1, ray.direction().y, ray.direction().z * -1};
                
                Ray r_ray = Ray(ray.at(nearest.t)+(reflectDir*0.0), reflectDir);
                for (int i = 0; i < objects.size(); i++) {
                    if(i == j)
                        continue;

                    CollisionResult reflection = objects[i]->cast(r_ray);
                    
                    if(reflection.t >= r_nearest.t || reflection.t <= 0)
                        continue;
                    r_nearest = reflection;
                }

                colorRGB r_color = phong(r_nearest, r_ray.at(r_nearest.t), ray.at(nearest.t), objects, lights, ambient_light);
                screen.set(y, x, (resultColor + r_color));
            } else
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



colorRGB Camera::phong(CollisionResult result, Vector3 point, Vector3 observer, std::vector<Object*>objects, std::vector<Light*> lights, Light* ambient_light) {


    colorRGB diffuse = {0, 0, 0};
    colorRGB specular = {0, 0, 0};

    Vector3 viewDir = (observer - point).Normalized();
    
    for (int i = 0; i < lights.size(); i++) {
        Light light = *lights[i];

        double distance = (point - light.transform.position).Magnitude();

        bool isVisible = true;
        for(int j = 0; j < objects.size(); j++) {
            Vector3 dir = (light.transform.position - point).Normalized();
            CollisionResult col = objects[j]->cast(Ray(point, dir));

            if(col.t < 0.0001 || col.t > distance)
                continue;

            isVisible = false;
            break;
        }
        if(!isVisible)
            continue;

        Vector3 lightDir = (light.transform.position - point).Normalized();
        Vector3 reflectDir = ((result.normal *2* Vector3::Product(result.normal, lightDir)) - lightDir).Normalized();

        double diff = std::max(Vector3::Product(result.normal,lightDir), 0.0);
        double spec = std::pow(std::max(Vector3::Product(viewDir,reflectDir), 0.0), result.material.n);

        diffuse += (light.color*light.intensity) * diff;
        specular += (light.color*light.intensity) * spec;
    }


    colorRGB ambient = (result.material.color*ambient_light->color)*ambient_light->intensity;
    ambient = (ambient/255).clamped();

    diffuse = (result.material.color*diffuse);
    diffuse = (diffuse/255).clamped();

    specular = (result.material.specularColor*specular);
    specular = (specular/255).clamped();


    colorRGB finalColor = ambient*result.material.a +
                          diffuse*result.material.d +
                          specular*result.material.s;

    return finalColor.clamped();
}



std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
