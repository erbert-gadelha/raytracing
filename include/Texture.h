#ifndef TEXTURE_H
#define TEXTURE_H
#include "colorRGB.h"

struct Texture {
    colorRGB** image;
    int h = 0;
    int v = 0;

};

#endif // TEXTURE_H
