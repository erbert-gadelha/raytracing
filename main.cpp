#include <iostream>
#include "vector3.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"

#include <math.h>       /* sqrt */

using namespace std;

float distance(int x1, int y1, int x2, int y2) {
    int dx = x1-x2;
    int dy = y1-y2;

    return sqrt((dx*dx)+(dy*dy));
}

int main() {

    /*object** objects = new object*[2];
    objects[0] = new sphere(new vector3(1, 1, 1), new vector3(1, 1, 1));
    objects[1] = new plane(new vector3(1, 1, 1));

    for(int i = 0; i < 2; i++) {
        printf("m%d: %s\n", i, objects[i]->to_string().c_str() );
    }*/



        // Image

        int image_width = 256;
        int image_height = 256;

        // Render

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        int center_x = image_width/2;
        int center_y = image_height/2;

        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                int r = 0;
                int g = 0;
                int b = distance(i,j, center_x, center_y);

                if(distance(i,j, center_x, center_y) < 50)
                    r = 255;


                printf("%d %d %d\n", r, g, b);
            }
        }

}
