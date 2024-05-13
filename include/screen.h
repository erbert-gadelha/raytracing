#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <colorRGB.h>


class screen {
    public:
        screen(int w, int h);
        int width();
        int height();
        colorRGB get(int x, int y);
        void set(int x, int y, colorRGB color);
        std::string to_string();
        ~screen();

    protected:
        int w;
        int h;
        colorRGB** pixels;
    private:
};

#endif // SCREEN_H
