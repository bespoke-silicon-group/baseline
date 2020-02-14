#ifndef RAYTRACER_DEFS_H
#define RAYTRACER_DEFS_H

#include <cstdint>

constexpr int RAYS_PER_PIXEL = 4;
constexpr int MAX_BOUNCES = 2;
constexpr uint32_t IMAGE_WIDTH = 4;
constexpr uint32_t IMAGE_HEIGHT = 4;

struct V3
{
        float x, y, z;
};

inline __attribute__((always_inline))
V3 operator *(float A, V3 B)
{
        V3 result = { A * B.x, A * B.y, A * B.z };
        return result;
}

inline __attribute__((always_inline))
V3 operator *(V3 B, float A)
{
        return A * B;
}

inline __attribute__((always_inline))
V3 &operator *=(V3 &B, float A)
{
        B = A * B;
        return B;
}

inline __attribute__((always_inline))
V3 operator +(V3 A, V3 B)
{
        V3 result = { A.x + B.x, A.y + B.y, A.z + B.z };
        return result;
}

inline __attribute__((always_inline))
V3 operator -(V3 A, V3 B)
{
        V3 result = { A.x - B.x, A.y - B.y, A.z - B.z };
        return result;
}

inline __attribute__((always_inline))
V3 operator -(V3 A)
{
        return -1.0f * A;
}

inline __attribute__((always_inline))
V3 &operator +=(V3 &A, V3 B)
{
        A = A + B;
        return A;
}

struct Material
{
        float specular;
        V3 ref_color;
        V3 emit_color;
};

struct Plane
{
        V3 N;
        float d;
        uint32_t mat_index;
};

struct Sphere
{
        V3 P;
        float r;
        uint32_t mat_index;
};

struct CastState
{
        V3 camera_p, camera_x, camera_y, camera_z;

        float film_width, film_height, half_film_width, half_film_height;

        V3 film_center;

        float half_pixel_width, half_pixel_height;
        float film_x, film_y;

        V3 final_color;
};

Material MATERIALS[] =
{
        {    0, {                   }, {0.3f, 0.4f, 0.5f}},
        {    0, { 0.5f,  0.5f,  0.5f}, {                }},
        {    0, { 0.7f,  0.5f,  0.3f}, {                }},
        {    0, {                   }, {4.0f, 0.0f, 0.0f}},
        { 0.7f, { 0.2f,  0.8f,  0.2f}, {                }},
        {0.85f, { 0.4f,  0.8f,  0.9f}, {                }},
        { 1.0f, {0.95f, 0.95f, 0.95f}, {                }},
        { 0.98f, {0.95f, 0.95f, 0.95f}, {               }},
};

constexpr uint32_t MATERIAL_COUNT = sizeof(MATERIALS) / sizeof(MATERIALS[0]);
Plane PLANES[] =
{
        {{0, 0, 1}, 0, 7},
};
constexpr uint32_t PLANE_COUNT = sizeof(PLANES) / sizeof(PLANES[0]);
        
Sphere SPHERES[] =
{
        {{ 0,  0, 0}, 1.0f, 2},
        {{ 3, 2, 0}, 1.0f, 3},
        {{-2, -1, 2}, 1.0f, 4},
        {{ 1, -1, 2}, 1.0f, 5},
        {{-2,  3, 0}, 2.0f, 6},
};
constexpr uint32_t SPHERE_COUNT = sizeof(SPHERES) / sizeof(SPHERES[0]);

#endif
