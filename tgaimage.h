#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <fstream>

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
        uint8_t raw[4];
        uint32_t val;
    };

    int bytespp;

    inline uint8_t& b() { return raw[0]; }
    inline uint8_t& g() { return raw[1]; }
    inline uint8_t& r() { return raw[2]; }
    inline uint8_t& a() { return raw[3]; }

    TGAColor() : val(0), bytespp(1) {
    }

    TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : raw{B, G, R, A}, bytespp(4) {
    }

    TGAColor(int v, int bpp) : val(v), bytespp(bpp) {
    }

    TGAColor(const TGAColor &c) : val(c.val), bytespp(c.bytespp) {
    }

    TGAColor(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
        for (int i=0; i<bpp; i++) {
            raw[i] = p[i];
        }
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
    unsigned char* data;
    int width;
    int height;
    int bytespp;

    bool   load_rle_data(std::ifstream &in);
    bool unload_rle_data(std::ofstream &out);
public:
    enum Format {
        GRAYSCALE=1, RGB=3, RGBA=4
    };

    TGAImage();
    TGAImage(int w, int h, int bpp);
    TGAImage(const TGAImage &img);
    bool read_tga_file(const char *filename);
    bool write_tga_file(const char *filename, bool rle=true);
    bool flip_horizontally();
    bool flip_vertically();
    bool scale(int w, int h);
    TGAColor get(int x, int y);
    bool set(int x, int y, TGAColor c);
    ~TGAImage();
    TGAImage & operator =(const TGAImage &img);
    int get_width();
    int get_height();
    int get_bytespp();
    unsigned char *buffer();
    void clear();
};

#endif //__IMAGE_H__
