#include "renderer.h"

using namespace std;

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
