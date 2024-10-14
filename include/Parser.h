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
        static const char* parseFromString(const std::string str);
        static const char* parseFromFile(const std::string filePath);

    private:
        static const char* parseScene(std::istream& stream);


};

#endif // PARSER_H
