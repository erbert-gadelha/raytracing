#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>
#include <algorithm>

/** coeficiente
 * @tparam double d, coeficiente difuso
 * @tparam double s, coeficiente especular
 * @tparam double a, coeficiente ambiental
 * @tparam double r, coeficiente de reflexão
 * @tparam double t, coeficiente de transmissão
 * @tparam double n, coeficiente de rugosidade
 * */ 
struct Material {
    double d;   // coeficiente difuso
    double s;   // coeficiente especular
    double a;   // coeficiente ambiental
    double r;   // coeficiente de reflexao
    double t;   // coeficiente de transmissão
    double n;   // coeficiente de rugosidade
};

#endif // MATERIAL_H