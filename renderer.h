#ifndef _RENDERER_H__
#define _RENDERER_H__

#include "tgaimage.h"

extern const TGAColor white;
extern const TGAColor red;

extern void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

#endif
