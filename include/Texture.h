#ifndef TEXTURE_H
#define TEXTURE_H
#include "colorRGB.h"

struct Texture {
    colorRGB** image;
    int h = 0;
    int v = 0;

    static Texture CreateTexture() {
        Texture t;
        t.h = 3;
        t.v = 3;

        t.image = new colorRGB*[t.h];
        for(int i = 0; i < t.h; i++)
            t.image[i] = new colorRGB[t.v];
        
        t.image[0][0] = colorRGB::RED;
        t.image[0][1] = colorRGB::GREEN;
        t.image[0][2] = colorRGB::BLUE;

        t.image[1][0] = colorRGB::WHITE;
        t.image[1][1] = colorRGB::BLACK;
        t.image[1][2] = colorRGB::YELLOW;

        t.image[2][0] = colorRGB::GREEN;
        t.image[2][1] = colorRGB::BLUE;
        t.image[2][2] = colorRGB::RED;

        return t;
    }

    static Texture CreateTexture_heart() {
        Texture t;
        t.h = 8;
        t.v = 8;

        t.image = new colorRGB*[t.h];
        for(int i = 0; i < t.h; i++)
            t.image[i] = new colorRGB[t.v];

        colorRGB background = colorRGB::BLACK;
        colorRGB fill = colorRGB::WHITE;
        
        t.image[7][0] = background;
        t.image[7][1] = background;
        t.image[7][2] = background;
        t.image[7][3] = background;
        t.image[7][4] = background;
        t.image[7][5] = background;
        t.image[7][6] = background;
        t.image[7][7] = fill;

        t.image[6][0] = background;
        t.image[6][1] = background;
        t.image[6][2] = background;
        t.image[6][3] = background;
        t.image[6][4] = background;
        t.image[6][5] = background;
        t.image[6][6] = background;
        t.image[6][2] = background;
        t.image[6][7] = background;

        t.image[5][0] = background;
        t.image[5][1] = background;
        t.image[5][2] = fill;
        t.image[5][3] = background;
        t.image[5][4] = fill;
        t.image[5][5] = background;
        t.image[5][6] = background;
        t.image[5][7] = background;

        t.image[4][0] = background;
        t.image[4][1] = background;
        t.image[4][2] = fill;
        t.image[4][3] = fill;
        t.image[4][4] = fill;
        t.image[4][5] = background;
        t.image[4][6] = background;
        t.image[4][7] = background;

        t.image[3][0] = background;
        t.image[3][1] = background;
        t.image[3][2] = background;
        t.image[3][3] = fill;
        t.image[3][4] = background;
        t.image[3][5] = background;
        t.image[3][6] = background;
        t.image[3][7] = background;

        t.image[2][0] = background;
        t.image[2][1] = background;
        t.image[2][2] = background;
        t.image[2][3] = background;
        t.image[2][4] = background;
        t.image[2][5] = background;
        t.image[2][6] = background;
        t.image[2][7] = background;

        t.image[1][0] = fill;
        t.image[1][1] = background;
        t.image[1][2] = background;
        t.image[1][3] = background;
        t.image[1][4] = background;
        t.image[1][5] = background;
        t.image[1][6] = fill;
        t.image[1][7] = background;

        t.image[0][0] = fill;
        t.image[0][1] = background;
        t.image[0][2] = background;
        t.image[0][3] = background;
        t.image[0][4] = background;
        t.image[0][5] = background;
        t.image[0][6] = fill;
        t.image[0][7] = fill;

        return t;
    }

    static Texture CreateTexture_creeper() {
        Texture t;
        t.h = 8;
        t.v = 8;

        t.image = new colorRGB*[t.h];
        for(int i = 0; i < t.h; i++)
            t.image[i] = new colorRGB[t.v];

        colorRGB background_0 = {255,255,255};
        colorRGB background_1 = {230,230,230};
        colorRGB fill = colorRGB::BLACK;
        
        t.image[7][0] = background_0;
        t.image[7][1] = background_1;
        t.image[7][2] = background_0;
        t.image[7][3] = background_1;
        t.image[7][4] = background_0;
        t.image[7][5] = background_1;
        t.image[7][6] = background_0;
        t.image[7][7] = background_1;

        t.image[6][0] = background_1;
        t.image[6][1] = background_0;
        t.image[6][2] = background_1;
        t.image[6][3] = background_0;
        t.image[6][4] = background_1;
        t.image[6][5] = background_0;
        t.image[6][6] = background_1;
        t.image[6][2] = background_0;
        t.image[6][7] = background_1;

        t.image[5][0] = background_0;
        t.image[5][1] = fill;
        t.image[5][2] = fill;
        t.image[5][3] = background_1;
        t.image[5][4] = background_0;
        t.image[5][5] = fill;
        t.image[5][6] = fill;
        t.image[5][7] = background_1;

        t.image[4][0] = background_1;
        t.image[4][1] = fill;
        t.image[4][2] = fill;
        t.image[4][3] = background_0;
        t.image[4][4] = background_1;
        t.image[4][5] = fill;
        t.image[4][6] = fill;
        t.image[4][7] = background_0;

        t.image[3][0] = background_0;
        t.image[3][1] = background_1;
        t.image[3][2] = background_0;
        t.image[3][3] = fill;
        t.image[3][4] = fill;
        t.image[3][5] = background_1;
        t.image[3][6] = background_0;
        t.image[3][7] = background_1;

        t.image[2][0] = background_1;
        t.image[2][1] = background_0;
        t.image[2][2] = fill;
        t.image[2][3] = background_0;
        t.image[2][4] = background_1;
        t.image[2][5] = fill;
        t.image[2][6] = background_1;
        t.image[2][7] = background_0;

        t.image[1][0] = background_0;
        t.image[1][1] = background_1;
        t.image[1][2] = fill;
        t.image[1][3] = background_1;
        t.image[1][4] = background_0;
        t.image[1][5] = fill;
        t.image[1][6] = background_0;
        t.image[1][7] = background_1;

        t.image[0][0] = background_1;
        t.image[0][1] = background_0;
        t.image[0][2] = background_1;
        t.image[0][3] = background_0;
        t.image[0][4] = background_1;
        t.image[0][5] = background_0;
        t.image[0][6] = background_1;
        t.image[0][7] = background_0;

        return t;
    }


};

#endif // TEXTURE_H
