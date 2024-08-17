#ifndef MATERIAL_H
#define MATERIAL_H
#include "colorRGB.h"
#include "Texture.h"

/** coeficiente
 * @tparam double d, coeficiente difuso
 * @tparam double s, coeficiente especular
 * @tparam double a, coeficiente ambiental
 * @tparam double r, coeficiente de reflexão
 * @tparam double t, coeficiente de transmissão
 * @tparam double n, coeficiente de rugosidade
 * */ 
struct Material {
    double d = 1;   // coeficiente difuso
    double s = 0.1;   // coeficiente especular
    double a = 1;   // coeficiente ambiental
    double r = 1;   // coeficiente de reflexao
    double t = 1;   // coeficiente de transmissão
    double n = 10;   // coeficiente de rugosidade
    colorRGB color = {128,128,128};
    colorRGB specularColor = {255,255,255};
    double opacity = 1;
    double ior = 1;
    Texture texture;
};

#endif // MATERIAL_H
