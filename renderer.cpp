#include "geometry.h"
#include "model.h"
#include "renderer.h"

#include <cmath>

using namespace std;

const TGAColor light_white(127, 127, 127, 127);
const TGAColor light_green(127, 255, 127, 255);
const TGAColor light_red  (255, 127, 127, 255);

const TGAColor white(255, 255, 255, 255);
const TGAColor green(  0, 255,   0, 255);
const TGAColor red  (255,   0,   0, 255);

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

    if (x0 < 0) {
        error = derror * x0;
        y += (y1 > y0 ? 1 : -1) * truncf(error);
        error = error - truncf(error);
        x0 = 0;
    }
    x1 = min(x1, -1 + (steep ? image.get_height() : image.get_width()));

    int yMax = steep ? image.get_width() : image.get_height();
    for (int x = x0; x <= x1 && y < yMax; ++x) {
        if (y >= 0) {
            if (steep)
                image.set4(y, x, color);
            else
                image.set4(x, y, color);
        }
        error += derror;
        if (error > 0.5) {
            y +=  (y1 > y0 ? 1 : -1);
            error -= 1.0;
        }
    }
}

void line(Vec2i t0, Vec2i t1, TGAImage& image, TGAColor color) {
    line(t0.x, t0.y, t1.x, t1.y, image, color);
}

void fillTriangle(
    Vec3i t0, Vec3i t1, Vec3i t2,
    TGAImage& image, TGAColor color,
    vector<vector<int>>& zbuffer
) {
    if (t0.y > t1.y)
        swap(t0, t1);
    if (t0.y > t2.y)
        swap(t0, t2);
    if (t1.y > t2.y)
        swap(t1, t2);

    int x0 = t0.x; int y0 = t0.y;
    int x1 = t1.x; int y1 = t1.y;
    int x2 = t2.x; int y2 = t2.y;

    bool reverse = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0) < 0;

    int dy2 = y2 - y0 + 1;
    int dy0 = y1 - y0 + 1;
    int dy1 = y2 - y1 + 1;

    for (int y = y0; y <= y2; ++y) {
        float dl = static_cast<float>(y - y0) / dy2;
        float dr = y <= y1
            ? static_cast<float>(y - y0) / dy0
            : static_cast<float>(y - y1) / dy1;

        int xl = x0 + (x2 - x0) * dl;
        int xr = y <= y1 ? x0 + dr * (x1 - x0) : x1 + dr * (x2 - x1);
        if (reverse)
            swap(xl, xr);

        for (int x = xl; x <= xr; ++x) {
            image.set4(x, y, color);
        }
    }

}

static inline int transform(float a, float base) {
    return (a + 1.0) * base / 2.0;
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color) {
    line(t0, t1, image, color);
    line(t1, t2, image, color);
    line(t2, t0, image, color);
}

void drawModel(const Model& model, const Vec3f& lightDir, TGAImage& image) {
    int width = image.get_width();
    int height = image.get_height();

    vector<vector<int>> zbuffer(width, vector<int>(height));

    for (size_t i = 0; i < model.nfaces(); ++i) {
        const auto& face = model.face(i);
        Vec3i screenCoord[3];
        Vec3f worldCoord[3];
        for (size_t j = 0; j < 3; ++j) {
            worldCoord[j] = model.vert(face[j]);
            screenCoord[j] = Vec3i(transform(worldCoord[j].x, width), transform(worldCoord[j].y, height), worldCoord[j].z);
        }
        Vec3f n = (worldCoord[2] - worldCoord[0]) ^ (worldCoord[1] - worldCoord[0]);
        n.normalize();
        float intensity = n * lightDir;
        if (intensity > 0)
            fillTriangle(
                screenCoord[0], screenCoord[1], screenCoord[2],
                image, TGAColor(intensity * 255, intensity * 255, intensity * 255),
                zbuffer);
    }
}
