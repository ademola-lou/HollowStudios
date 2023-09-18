#pragma once

#include <sstream>
#include <iomanip>

namespace MathUtils {
    template<typename T>
    struct Vec3 {
        T x, y, z;
        Vec3(T x, T y, T z): x(x), y(y), z(z) {};
        Vec3(): x(0), y(0), z(0) {};
        Vec3 operator+(const Vec3& v) {
            return Vec3(x + v.x, y + v.y, z + v.z);
        };
    };

    uint32_t rgbToHex(float r, float g, float b) {
        uint32_t ir = static_cast<uint32_t>(r * 255.0 + 0.5) & 0xFF;
        uint32_t ig = static_cast<uint32_t>(g * 255.0 + 0.5) & 0xFF;
        uint32_t ib = static_cast<uint32_t>(b * 255.0 + 0.5) & 0xFF;

        return (ir << 16) | (ig << 8) | ib;
    }
}