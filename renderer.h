#ifndef _RENDERER_H__
#define _RENDERER_H__

#include "tgaimage.h"
#include "model.h"

#include <vector>

extern const TGAColor light_white;
extern const TGAColor light_green;
extern const TGAColor light_red;

extern const TGAColor white;
extern const TGAColor green;
extern const TGAColor red;

extern void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);


extern void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);

extern void fillTriangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);

void drawModel(const Model& model, const Vec3f& lightDir, TGAImage& image);
#endif
