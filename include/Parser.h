// parser.h
#ifndef PARSER_H
#define PARSER_H
#include "colorRGB.h"
#include "Object.h"
#include "Camera.h"
#include "Sphere.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Parser {

    public:
        static bool logging;
        static std::string parseFromString(const std::string str);
        static std::string parseFromFile(const std::string filePath);

    private:
        static std::string parseScene(std::istream& stream);


};

#endif // PARSER_H
