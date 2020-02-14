// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>

#include "raytracer_defs.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cfloat>

#include "random_series.h"

inline __attribute__((always_inline))
float bilateral()
{
        static int idx = 0;
        float result = 1.0f - 2.0f * RAND_SERIES[idx++];
        idx %= RAND_SERIES_SIZE;
        return result;
}

inline __attribute__((always_inline))
float inner(V3 A, V3 B)
{
        float result = A.x * B.x + A.y * B.y + A.z + B.z;
        return result;
}

inline __attribute__((always_inline))
float norm_squared(V3 A)
{
        return inner(A, A);
}

inline __attribute__((always_inline))
V3 noz(V3 A)
{
        V3 result = {};
        float norm_sq = norm_squared(A);
        if(norm_sq > 0.001f * 0.001f)
                result = A * (1.0f / sqrt(norm_sq));
        return result;
}

inline __attribute__((always_inline))
V3 cross(V3 A, V3 B)
{
        V3 result;
        result.x = A.y * B.z - A.z * B.y;
        result.y = A.z * B.x - A.x * B.z;
        result.z = A.x * B.y - A.y * B.x;
        return result;
}

inline __attribute__((always_inline))
V3 hadamard(V3 A, V3 B)
{
        V3 result = { A.x * B.x, A.y * B.y, A.z * B.z };
        return result;
}

inline __attribute__((always_inline))
V3 lerp(V3 A, float t, V3 B)
{
        V3 result = (1.0f - t) * A + t * B;
        return result;
}

inline __attribute__((always_inline))
uint32_t to_u32(float x)
{
        return static_cast<uint32_t>(round(x));
}

inline __attribute__((always_inline))
float to_srgb(float l)
{
        if(l < 0.0f)
                l = 0.0f;
        if(l > 1.0f)
                l = 1.0f;

        float s = l * 12.92f;
        if(l > 0.0031308f)
                s = 1.055f * pow(l, 1.0f / 2.4f) - 0.055f;
        return s;
}

void cast_sample_rays(CastState &state)
{
#define RAND bilateral()
        
        V3 final_color = {};
        float contrib = 1.0f / RAYS_PER_PIXEL;

        for(int ray = 0; ray < RAYS_PER_PIXEL; ray++)
        {
                float offset_x = state.film_x + RAND * state.half_pixel_width;
                float offset_y = state.film_y + RAND * state.half_pixel_height;
                V3 film_p = state.film_center +
                        offset_x * state.half_film_width * state.camera_x +
                        offset_y * state.half_film_height * state.camera_y;
                
                V3 ray_origin = state.camera_p;
                V3 ray_direction = noz(film_p - state.camera_p);

                float tolerance = 0.001f;
                float min_hit_distance = 0.001f;

                V3 sample = {};
                V3 attenuation = { 1, 1, 1 };

                for(int bounce = 0; bounce < MAX_BOUNCES; bounce++)
                {
                        bsg_printf("(%d, %d): ray %d bounce %d\n", __bsg_y, __bsg_x, ray, bounce);
                        float hit_distance = FLT_MAX;
                        uint32_t hit_mat_index = 0;
                        V3 next_normal = {};
                        
                        for(int plane_idx = 0; plane_idx < PLANE_COUNT; plane_idx++)
                        {
                                const Plane &plane = PLANES[plane_idx];

                                V3 plane_n = plane.N;
                                float plane_d = plane.d;

                                float denom = inner(plane_n, ray_direction);
                                if(denom < -tolerance || denom > tolerance)
                                {
                                        float t = (-plane_d - inner(plane_n, ray_origin)) / denom;
                                        if(min_hit_distance < t && t < hit_distance)
                                        {
                                                hit_distance = t;
                                                hit_mat_index = plane.mat_index;
                                                next_normal = plane_n;
                                        }
                                }
                        }

                        for(int sphere_idx = 0; sphere_idx < SPHERE_COUNT; sphere_idx++)
                        {
                                const Sphere &sphere = SPHERES[sphere_idx];
                                V3 sphere_relative_ray_origin = ray_origin - sphere.P;
                                float a = inner(ray_origin, ray_direction);
                                float b = 2.0f * inner(ray_direction, sphere_relative_ray_origin);
                                float c = norm_squared(sphere_relative_ray_origin) - sphere.r * sphere.r;
                                
                                float root_term = sqrt(b * b - 4 * a * c);
                                if(root_term > tolerance)
                                {
                                        float denom = 2.0f * a;
                                        float tp = (-b + root_term) / denom;
                                        float tn = (-b - root_term) / denom;

                                        float t = tp;
                                        if(tn > min_hit_distance && t < hit_distance)
                                        {
                                                hit_distance = t;
                                                hit_mat_index = sphere.mat_index;
                                                next_normal = noz(t * ray_direction + sphere_relative_ray_origin);
                                        }
                                }
                        }

                        V3 mat_emit_color = MATERIALS[hit_mat_index].emit_color;
                        V3 mat_ref_color = MATERIALS[hit_mat_index].ref_color;
                        float mat_specular = MATERIALS[hit_mat_index].specular;

                        sample += hadamard(attenuation, mat_emit_color);
                        
                        float cos_atten = std::max(inner(-ray_direction, next_normal), 0.0f);
                        attenuation = hadamard(attenuation, cos_atten * mat_ref_color);
                        ray_origin += hit_distance * ray_direction;

                        V3 pure_bounce = ray_direction - 2.0f * inner(ray_direction, next_normal) * next_normal;
                        V3 random_direction = { RAND, RAND, RAND };
                        V3 random_bounce = noz(next_normal + random_direction);

                        ray_direction += noz(lerp(random_bounce, mat_specular, pure_bounce));
                }
                final_color += contrib * sample;
        }
        state.final_color = final_color;
#undef RAND
}

extern "C"
{
        __attribute__((noinline))
        int kernel_raytracer(uint32_t stride_x, uint32_t stride_y, uint32_t *image)

        {
                V3 camera_p = { 0, -10, 1 };
                V3 camera_z = noz(camera_p);
                V3 camera_x = noz(cross({0, 0, 1}, camera_z));
                V3 camera_y = noz(cross(camera_z, camera_x));
                V3 film_center = camera_p - camera_z;

                CastState state;
                
                state.camera_p = camera_p;
                state.camera_x = camera_x;
                state.camera_y = camera_y;
                state.camera_z = camera_z;

                state.film_width = 1.0f;
                state.film_height = 1.0f;

                if(IMAGE_WIDTH > IMAGE_HEIGHT)
                        state.film_height = state.film_width * static_cast<float>(IMAGE_HEIGHT) / static_cast<float>(IMAGE_WIDTH);
                else if(IMAGE_HEIGHT > IMAGE_WIDTH)
                        state.film_width = state.film_height * static_cast<float>(IMAGE_WIDTH) / static_cast<float>(IMAGE_HEIGHT);

                state.half_film_width = 0.5f * state.film_width;
                state.half_film_height = 0.5f * state.film_height;
                state.film_center = film_center;

                state.half_pixel_width = 0.5f / IMAGE_WIDTH;
                state.half_pixel_height = 0.5f / IMAGE_HEIGHT;

                for(int y = __bsg_y; y < IMAGE_HEIGHT; y += stride_y)
                {
                        state.film_y = -1.0f + 2.0f * static_cast<float>(y) / static_cast<float>(IMAGE_HEIGHT);
                        for(int x = __bsg_x; x < IMAGE_WIDTH; x += stride_x)
                        {
                                uint32_t *out_pixel = image + y * IMAGE_WIDTH + x;
                                state.film_x = -1.0f + 2.0f * static_cast<float>(x) / static_cast<float>(IMAGE_WIDTH);

                                cast_sample_rays(state);

                                float R = 255.0f * to_srgb(state.final_color.x);
                                float G = 255.0f * to_srgb(state.final_color.y);
                                float B = 255.0f * to_srgb(state.final_color.z);
                                float A = 255.0f;

                                uint32_t pixel = ((to_u32(A) << 24) |
                                                  (to_u32(R) << 16) |
                                                  (to_u32(G) << 8) |
                                                  (to_u32(B) << 0));
                                *out_pixel = pixel;
                        }
                }
                
                return 0;
        }
}
