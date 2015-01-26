#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"

#include <string>
#include <vector>

class Model {
public:
    Model(const std::string& filename);
    size_t nverts();
    size_t nfaces();
    Vec3f vert(size_t i);
    std::vector<int> face(size_t idx);

private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<int>> faces;
};

#endif //__MODEL_H__
