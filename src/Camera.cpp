#include "Camera.h"
#include "Screen.h"
#include <string>
#include <vector>
#include <chrono>
#include <Material.h>
#include <math.h>
#include <algorithm>

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


            for(int i = 0; i < objects.size(); i++) { // verifica cada objeto
                CollisionResult result = objects[i]->cast(ray);
                if(result.t < 0 || result.t > nearest.t)
                    continue;
                nearest = result;
            }

            if(nearest.t != MAX_DISTANCE) {
                colorRGB resultColor = phong(nearest, ray, objects, lights, ambient_light);
                colorRGB refracao_color = reflection(nearest, ray, objects, lights, ambient_light, GRADIENT);
                colorRGB reflexao_color = refract(nearest, ray, objects, lights, ambient_light);

                screen.set(y, x, (resultColor + refracao_color + reflexao_color));
            } else {
                screen.set(y, x, GRADIENT);
            }
            
        }
    }

}


std::string Camera::render(std::vector<Object*> objects, std::vector<Light*> lights, Light* ambient_light) {
    // ===== DEBUG ===== //
    /*std::cout << "Rendering <" << objects.size() << "> object(s)";
    auto start = std::chrono::high_resolution_clock::now();*/
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
    /*auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << " ~ (Complete in (" << (elapsed_seconds.count()) << ") seconds)." << std::endl;*/
    // ===== DEBUG ===== //

    return this->screen.to_string();
}



colorRGB Camera::phong(CollisionResult result, Ray ray, std::vector<Object*>objects, std::vector<Light*> lights, Light* ambient_light) {


    colorRGB diffuse = {0, 0, 0};
    colorRGB specular = {0, 0, 0};

    //Vector3 viewDir = (observer - point).Normalized();
    Vector3 viewDir = ray.direction();
    
    for (int i = 0; i < lights.size(); i++) {
        Light light = *lights[i];
        Vector3 lightCenter = light.points[lights.size()/2];

        Vector3 point = ray.at(result.t);
        double distance = (point - lightCenter).Magnitude();

        int visiblePoints = 0;
        double ratio;



        for(int k = 0; k < light.points.size(); k++) {

            int visible = 1;
            for(int j = 0; j < objects.size(); j++) {

                Vector3 dir = (light.points[k] - point).Normalized();
                CollisionResult col = objects[j]->cast(Ray(point, dir));

                if(col.t > 0.0001 && col.t < distance) {
                    visible = 0;
                }
            }
            
            visiblePoints+=visible;
        }        

        if(visiblePoints == 0)
            continue;
        
        ratio = ((double)visiblePoints)/light.points.size();

        Vector3 lightDir = (lightCenter - point).Normalized();
        Vector3 reflectDir = (lightDir - (result.normal * 2 * Vector3::Product(result.normal,lightDir))).Normalized();


        double diff = std::max(Vector3::Product(result.normal,lightDir), 0.0);
        double spec = std::pow(std::max(Vector3::Product(viewDir,reflectDir), 0.0), result.material.n);

        diffuse += (light.color*light.intensity) * diff * ratio;
        specular += (light.color*light.intensity) * spec * ratio;
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

colorRGB Camera::reflection(CollisionResult collision, Ray ray, std::vector<Object*>objects, std::vector<Light*>lights, Light* ambient_light, colorRGB defaultColor) {
    colorRGB r_color = colorRGB::BLACK;

    double coeficiente_r = collision.material.r;
    collision.material.color = defaultColor;
    for(int r = 0; r < 3; r++) { // NUMERO DE RECURSÕES DESEJADAS
        Vector3 reflectDir = (ray.direction() - (collision.normal * 2 * Vector3::Product(collision.normal,ray.direction()))).Normalized();
        Ray r_ray = Ray(ray.at(collision.t)+(reflectDir*0.0), reflectDir);

        collision.t = MAX_DISTANCE;
        CollisionResult nearest;
        nearest.t = MAX_DISTANCE;
        for (int i = 0; i < objects.size(); i++) {
            CollisionResult temp = objects[i]->cast(r_ray);
            if(temp.t >= nearest.t || temp.t <= 0.0001)
                continue;
            nearest = temp;
        }

        if(nearest.t == MAX_DISTANCE)
            break;

        r_color = r_color + phong(nearest, r_ray, objects, lights, ambient_light)*coeficiente_r;
        collision = nearest;
    }

    return r_color.clamped();
}

colorRGB Camera::refract(CollisionResult collision, Ray ray, std::vector<Object*>objects, std::vector<Light*>lights, Light* ambient_light) {
    double opacity = collision.material.opacity;
    double cosi = std::clamp((double)Vector3::Product(collision.normal, ray.direction()), (double)1, (double)2);
    double etai = 1, etat = collision.material.ior;
    Vector3 n = collision.normal;

    if (cosi < 0) {
        cosi = -cosi;
        std::swap(etai, etat);
        n = collision.normal* -1;
    }

    double etaRatio = etai / etat;
    double k = 1 - etaRatio * etaRatio * (1 - cosi * cosi);

    Vector3 refract;
    if (k < 0)
        refract = {0,0,0}; // Total internal reflection
    else
        refract =  {ray.direction() * etaRatio + n*(cosi*etaRatio - std::sqrt(k))};
    


    Vector3 point = ray.at(collision.t);
    Ray ray2 = Ray(point, refract);
    collision.t = MAX_DISTANCE;
    for(int i = 0; i < objects.size(); i++) {
        CollisionResult temp = objects[i]->cast(ray2);
        if(temp.t >= collision.t || temp.t <= 0.0001)
            continue;
        collision = temp;
    }

    if(collision.t == MAX_DISTANCE)
        return colorRGB::BLACK;
    
    return phong(collision, ray2, objects, lights, ambient_light) * (1-opacity);
    //return collision.material.color * (1-opacity);
}



std::string Camera::to_string() {
    return ("{\n\tmesh: camera,\n\ttransform: " + this->transform.to_string() + "\n\tdistance: " + std::to_string(distance) + "}");
}
