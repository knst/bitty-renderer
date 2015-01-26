#include "renderer.h"
#include "model.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Run as: " << argv[0] << " Model.obj" << endl;
        return 1;
    }

    Model model(argv[1]);
    TGAImage image(800, 800, TGAImage::RGBA);
    for (size_t i = 0; i < model.nfaces(); ++i) {
        drawFace(model, model.face(i), image);
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
