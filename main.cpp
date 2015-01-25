#include "tgaimage.h"
#include <cmath>

using namespace std;

const TGAColor white(255, 255, 255, 255);
const TGAColor red  (255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (abs(x1 - x0) < abs(y1 - y0)) {
        swap(x1, y1);
        swap(x0, y0);
        steep = true;
    }
    if (x1 < x0) {
        swap(x1, x0);
        swap(y1, y0);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(static_cast<float>(dy) / dx);
    float error = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x) {
        if (steep)
            image.set4(y, x, color);
        else
            image.set4(x, y, color);
        error += derror;
        if (error > 0.5) {
            y +=  (y1 > y0 ? 1 : -1);
            error -= 1.0;
        }
    }
}

int main(int , char** ) {
    TGAImage image(100, 100, TGAImage::RGBA);
    image.safeSet(52, 41, red);
    for (size_t i = 0;i < 1000 * 1000; ++i) {
//        line(13, 20, 80, 40, image, white);
//        line(20, 13, 40, 80, image, red);
//        line(80, 40, 13, 20, image, red);
        line(0, 0, 99, 99, image, white);
        line(0, 99, 99, 0, image, white);
        line(99, 0, 0, 99, image, red);


    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
