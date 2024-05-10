#ifndef COLORRGB_H
#define COLORRGB_H
#include <string>

class colorRGB
{
    public:
        colorRGB();
        colorRGB(int red, int green, int blue);
        int r;
        int g;
        int b;
        std::string to_string();

    protected:

    private:
};

#endif // COLORRGB_H
