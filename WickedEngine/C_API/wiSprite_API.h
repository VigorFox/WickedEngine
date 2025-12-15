#pragma once
#include "wiC_API.h"
#include "wiImage_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiSprite_t *wiSprite;
typedef struct wiSpriteAnim_t
    *wiSpriteAnim; // Placeholder, need struct definition if using Anim

wiSprite wiSprite_Create(const char *image_file,
                         const char *mask_file); // args can be null
void wiSprite_Destroy(wiSprite sprite);

void wiSprite_SetParams(wiSprite sprite, wiImageParams params);
wiImageParams
wiSprite_GetParams(wiSprite sprite); // Returns copy or pointer? internal one.
// Note: wiSprite has "params" member. Direct access or copy?
// C API usually prefers handles. We can return a handle to the internal params.
// (Careful with lifetime) Or we pass values. Implementing: wiSprite_GetParams
// returns a NEW handle to a COPY? Or the internal pointer? Internal pointer is
// risky if Sprite moves or reallocs, but for a single object it's okay. Let's
// say it updates the sprite's internal params from the provided handle in
// SetParams. GetParams fills a handle? Simpler: Set/Get individual properties
// on Sprite directly or expose Sprite's Params member as a handle.

// For now, let's copy params in SetParams.
// And GetParams returns a pointer to the internal params (Handle).

void wiSprite_SetHidden(wiSprite sprite, bool hidden);
bool wiSprite_IsHidden(wiSprite sprite);

// Textures
// Need wiTexture_API.h for texture handles?
// For now, loading by string in Create coverage is "SetTexture" equivalent.

#ifdef __cplusplus
}
#endif
