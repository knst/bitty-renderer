#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float d = 0; d < 1; d += 0.001) {
        int x = x0 * (1 - d) + x1 * d;
        int y = y0 * (1 - d) + y1 * d;
        image.set(x, y, color);
    }
}

int main(int , char** ) {
    TGAImage image(100, 100, TGAImage::RGB);
    image.set(52, 41, red);
    line(0, 0, 100, 100, image, white);
    line(0, 100, 100, 0, image, white);
    line(100, 0, 0, 100, image, red);


    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
