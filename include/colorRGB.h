#ifndef COLORRGB_H
#define COLORRGB_H
#include <string>
#include <algorithm>
#include <math.h>

struct colorRGB {

    static const colorRGB RED;
    static const colorRGB GREEN;
    static const colorRGB BLUE;
    static const colorRGB YELLOW;
    static const colorRGB WHITE;
    static const colorRGB BLACK;

    int red;
    int green;
    int blue;

    std::string to_string() {
        return (std::to_string(red) + ' ' + std::to_string(green) + ' ' + std::to_string(blue));
    }


    inline colorRGB operator=(colorRGB c) {
        red=c.red;
        green=c.green;
        blue=c.blue;
        return c;
    }

    inline colorRGB operator+(colorRGB c) {
        return {red+c.red, 
                green+c.green,
                blue+c.blue
            };
    }

    inline void operator+=(colorRGB c) {
        red   = red  +c.red;
        green = green+c.green;
        blue  = blue +c.blue;
    }

    inline void operator-=(colorRGB c) {
        red   = red  -c.red;
        green = green-c.green;
        blue  = blue -c.blue;
    }
    inline void operator*=(double t) {
        red   = (int)(red*t);
        green = (int)(green*t);
        blue  = (int)(blue*t);
    }
    inline bool operator==(colorRGB c) {
        return (c.red==red && c.green==green && c.blue==blue);
    }
    inline colorRGB operator*(double t) {
        return {(int)(red*t), (int)(green*t), (int)(blue*t)};
    }
    inline colorRGB operator/(double t) {
        return {(int)(red/t), (int)(green/t), (int)(blue/t)};
    }
    inline colorRGB operator*(colorRGB c) {
        return {red*c.red, green*c.green, blue*c.blue};
    }

    static colorRGB Clamp(colorRGB c) {
        return {colorRGB::clamp((int)(c.red),0,255),
                colorRGB::clamp((int)(c.green),0,255),
                colorRGB::clamp((int)(c.blue),0,255)};
    }


    
    colorRGB clamped() {
        return Clamp(*this);
    }

    //private:
        static int clamp(int value, int min, int max) {
            if(value > max)
                return value;
            if(value < min)
                return min;
            
            return value;

        }
};

#endif // COLORRGB_H
