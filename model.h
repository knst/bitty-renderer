#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"

#include <string>
#include <vector>

class Model {
public:
    Model(const std::string& filename);
    size_t nverts() const;
    size_t nfaces() const;
    Vec3f vert(size_t i) const;
    std::vector<int> face(size_t idx) const;

private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<int>> faces;
};

#endif //__MODEL_H__
