#ifndef MATERIAL_H
#define MATERIAL_H
#include "colorRGB.h"

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
    double s = 1;   // coeficiente especular
    double a = 1;   // coeficiente ambiental
    double r = 1;   // coeficiente de reflexao
    double t = 1;   // coeficiente de transmissão
    double n = 1;   // coeficiente de rugosidade
    colorRGB color = {128,128,128};
};

#endif // MATERIAL_H
