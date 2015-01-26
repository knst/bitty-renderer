#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class t> struct Vec2 {
    t x, y;

    Vec2<t>() {}
    Vec2<t>(const t& _x, const t& _y) : x(_x), y(_y) {}

    inline Vec2<t> operator +(const Vec2<t>& v) const { return Vec2<t>(x + v.x, y + v.y); }
    inline Vec2<t> operator -(const Vec2<t>& v) const { return Vec2<t>(x - v.x, y - v.y); }
    inline Vec2<t> operator *(float f)          const { return Vec2<t>(x * f, y * f); }
    template <class > friend std::ostream& operator<<(std::ostream& s, const Vec2<t>& v);
};

template <class t> struct Vec3 {
    t x, y, z;

    Vec3<t>() {}
    Vec3<t>(const t& _x, const t& _y, const t& _z) : x(_x), y(_y), z(_z) {}

    inline Vec3<t> operator +(const Vec3<t>& v) const { return Vec3<t>(x + v.x, y + v.y, z + v.z); }
    inline Vec3<t> operator -(const Vec3<t>& v) const { return Vec3<t>(x - v.x, y - v.y, z - v.z); }
    inline Vec3<t> operator *(float f)          const { return Vec3<t>(x * f, y * f, z * f); }
    inline Vec3<t> operator ^(const Vec3<t>& v) const {
        return Vec3<t>(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
                );
    }
    inline t       operator* (const Vec3<t>& v) const { return x * v.x + y * v.y + z * v.z; }

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3<t>& normalize(t l = 1) {
        *this = (*this) * (l / norm());
        return *this;
    }

    template <class > friend std::ostream& operator<<(std::ostream& s, const Vec3<t>& v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;

template <class t> std::ostream& operator<<(std::ostream& s, const Vec2<t>& v) {
    s << "(" << v.x << ", " << v.y << ")\n";
    return s;
}

template <class t> std::ostream& operator<<(std::ostream& s, const Vec3<t>& v) {
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
    return s;
}

#endif //__GEOMETRY_H__
