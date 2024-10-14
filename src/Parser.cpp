#include "Parser.h"

#include "colorRGB.h"
#include "Object.h"
#include "Plane.h"
#include "Camera.h"
#include "Sphere.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

bool Parser::logging = false;

const char* Parser::parseFromFile(const std::string filePath) {
    std::ifstream sceneStream(filePath);

    if (!sceneStream.is_open()) {
        if(logging)
            std::cerr << "Erro ao abrir o arquivo: (" << filePath << ").\n";
        return "";
    }
    
    std::string result = parseScene(sceneStream);
    sceneStream.close();

    return result.c_str();
}

const char* Parser::parseFromString(const std::string str) {
    std::istringstream sceneStream(str);
    std::string result = parseScene(sceneStream);

    return result.c_str();
}


const char*Parser::parseScene(std::istream& stream) {

    //std::istringstream a("sceneDescription");

    //std::streambuf b = std::istringstream a("sceneDescription");

    //std::ifstream sceneStream(filePath);

    //std::istream* stream = (&sceneStream);

    /*if (!sceneStream.is_open()) {
        if(logging)
            std::cerr << "Erro ao abrir o arquivo: (" << filePath << ").\n";
        return "";
    }*/


    std::string line;
    Camera* camera = nullptr;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Light* ambiental =  new Light(colorRGB::WHITE, 1, {Vector3::ONE});


    while (std::getline(stream, line)) {
        /*if(logging)
            std::cout << line << std::endl;*/

        Object* object = nullptr;
        double m [8];
        double rx, ry, rz;
        double px, py, pz;
        int r, g, b;

        if (line.find("Camera") == 0) {
            int RESOLUTION;
            double rx, ry, rz;
            double px, py, pz;

            std::sscanf(line.c_str(), "Camera (%d) (%lf %lf %lf) (%lf %lf %lf)",
                &RESOLUTION,
                &rx, &ry, &rz,
                &px, &py, &pz);            

            camera = new Camera(RESOLUTION, RESOLUTION, ((double)RESOLUTION/512)*1000);
            camera->transform.position = Vector3(px, py, pz);
            camera->transform.rotation = Vector3(rx, ry, rz);
        } else if (line.find("Ambiental") == 0) {
            double INTENSITY;
            //Ambiental (255 255 255) (1) (0 10 0)
            std::sscanf(line.c_str(), "Ambiental (%d %d %d) (%lf)",
                &r, &g, &b,
                &INTENSITY
            );

            ambiental->color = {r,g,b};
            ambiental->intensity = INTENSITY;
            ambiental->points = {Vector3::ZERO};

        } else if (line.find("Luz") == 0) {
            double INTENSITY;
            //Luz (-2 3 -1) (255 255 255) (0.5)
            std::sscanf(line.c_str(), "Luz (%lf %lf %lf) (%d %d %d) (%lf))",
                &px, &py, &pz,
                &r, &g, &b,
                &INTENSITY
            );

            Light* light = new Light(colorRGB{r, g, b}, INTENSITY, {Vector3(px, py, pz)});
            lights.push_back(light);

        } else if (line.find("Esfera") == 0) {
            // Esfera (1) (0 1 0) (255 255 0) (1 1 1 1 1 1 1 1)
            double RADIUS;
            std::sscanf(line.c_str(), "Esfera (%lf) (%lf %lf %lf) (%d %d %d) (%lf %lf %lf %lf %lf %lf %lf %lf )",
                &RADIUS,
                &px, &py, &pz,
                &r, &g, &b,
                &m[0], &m[1], &m[2], &m[3], 
                &m[4], &m[5], &m[6], &m[7] 
            );

            object = new Sphere(
                Vector3::ONE*RADIUS,
                Vector3(px, py, pz)
            );
        } else if (line.find("Plano") == 0) {
            // Plano (0 0 0) (0 1 0) (128 128 255) (1 1 1 1 1 1 1 1)
            std::sscanf(line.c_str(), "Plano (%lf %lf %lf) (%lf %lf %lf) (%d %d %d) (%lf %lf %lf %lf %lf %lf %lf %lf )",
                &px, &py, &pz,
                &rx, &ry, &rz,
                &r, &g, &b,
                &m[0], &m[1], &m[2], &m[3], 
                &m[4], &m[5], &m[6], &m[7] 
            );

            object = new Plane(
                Vector3(rx, ry, rz),
                Vector3(px, py, pz)
            );

        }

        if(object == nullptr)
            continue;
        

        object->material.color = {r,g,b};
        object->material.d = m[0];
        object->material.s = m[1];
        object->material.a = m[2];
        object->material.r = m[3];
        object->material.t = m[4];
        object->material.n = m[5];
        object->material.opacity = m[6];
        object->material.ior = m[7];

        objects.push_back(object);
    }


    if(logging) {
        std::cout << "Cena carregada com sucesso!\n";
        std::cout << "Objetos: " << objects.size() << "\n";
        std::cout << "Luzes: " << lights.size() << "\n";
        for(int i = 0; i < objects.size(); i++) {
            std::cout << objects[i]->to_string() << "\n";
        }
        for(int i = 0; i < lights.size(); i++) {
            std::cout << lights[i]->to_string() << "\n";
        }
    }
    
    if(camera == nullptr) {
        if(logging)
            std::cerr << "Não foi possível instanciar a camera.\n";
        return "";
    }

    return camera->render(objects, lights, ambiental).c_str();


}