#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <fstream>
#include <stdexcept>

#pragma pack(push,1)
struct TGA_Header {
    char idlength;
    char colormaptype;
    char datatypecode;
    short colormaporigin;
    short colormaplength;
    char colormapdepth;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char  bitsperpixel;
    char  imagedescriptor;
};
#pragma pack(pop)



struct TGAColor {
    union {
        struct {
            uint8_t b, g, r, a;
        } parts;
        uint8_t raw[4];
        uint32_t val;
    };

    int bytespp;

    TGAColor() : val(0), bytespp(1) {
    }

    TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255) : parts{B, G, R, A}, bytespp(4) {
    }

    TGAColor(int v, int bpp) : val(v), bytespp(bpp) {
    }

    TGAColor(const TGAColor &c) : val(c.val), bytespp(c.bytespp) {
    }

    TGAColor(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
        for (int i=0; i<bpp; i++) {
            raw[i] = p[i];
        }
        if (bpp < 1 || bpp > 4)
            throw std::logic_error("bpp can be only 1, 2, 3 or 4");
    }

    TGAColor & operator =(const TGAColor &c) {
        if (this != &c) {
            bytespp = c.bytespp;
            val = c.val;
        }
        return *this;
    }
};


class TGAImage {
protected:
    int width;
    int height;
    int bytespp;
    uint8_t* data;

    bool   load_rle_data(std::ifstream &in);
    bool unload_rle_data(std::ofstream &out);
public:
    enum Format {
        GRAYSCALE=1, RGB=3, RGBA=4
    };

    TGAImage(int w, int h, int bpp);
    TGAImage(const TGAImage &img);
    bool read_tga_file(const char *filename);
    bool write_tga_file(const char *filename, bool rle=true);
    void flip_horizontally();
    void flip_vertically();
    bool scale(int w, int h);
    TGAColor safeGet(int x, int y);
    bool safeSet(int x, int y, const TGAColor& c);
    void set1(int x, int y, const TGAColor& c);
    void set2(int x, int y, const TGAColor& c);
    void set4(int x, int y, const TGAColor& c);
    ~TGAImage();
    TGAImage & operator =(const TGAImage &img);
    int get_width();
    int get_height();
    int get_bytespp();
    uint8_t *buffer();
    void clear();
};

#endif //__IMAGE_H__
