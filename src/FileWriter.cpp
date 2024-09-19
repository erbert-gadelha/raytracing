#include "FileWriter.h"


std::string FileWriter::saveAsImage (std::string image, std::string targetDirectory) {

    time_t seconds = time (NULL);
    std::string fileName = ("image_" + std::to_string(seconds) + ".ppm");
    std::ofstream outputFile(targetDirectory + fileName);

    if (!outputFile.is_open())
        return "";

    outputFile << image;
    outputFile.close();
    return fileName;
}