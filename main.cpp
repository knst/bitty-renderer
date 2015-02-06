#include "renderer.h"
#include "model.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Run as: " << argv[0] << " Model.obj" << endl;
        return 1;
    }

    for (size_t test = 0; test < 1; ++test) {
        TGAImage image(800, 800, TGAImage::RGBA);

        Model model(argv[1]);
        drawModel(model, {0, 0, -1}, image);

        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
    }
    return 0;
}
