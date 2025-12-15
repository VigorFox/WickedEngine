#pragma once
#include "wiC_API.h"
#include "wiMath_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiTexture_t *wiTexture;

// Helper struct for texture descriptions/info if needed,
// but for now we expose specific getters.

wiTexture wiTexture_GetLogo();
wiTexture wiTexture_CreateGradientTexture(
    int gradient_type, // 0: Linear, 1: Circular, 2: Angular
    uint32_t width, uint32_t height, wiVector uv_start, wiVector uv_end,
    int gradient_flags, // 1<<0: Inverse, 1<<1: Smoothstep, 1<<2: PerlinNoise
    float perlin_scale, uint32_t perlin_seed, int perlin_octaves,
    float perlin_persistence);

bool wiTexture_IsValid(wiTexture texture);
int wiTexture_GetWidth(wiTexture texture);
int wiTexture_GetHeight(wiTexture texture);
int wiTexture_GetDepth(wiTexture texture);
int wiTexture_GetArraySize(wiTexture texture);

void wiTexture_Save(wiTexture texture, const char *filename);

#ifdef __cplusplus
}
#endif
