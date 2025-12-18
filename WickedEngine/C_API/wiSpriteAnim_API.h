#pragma once
#include "wiC_API.h"
#include "wiMath_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiSpriteAnim_t *wiSpriteAnim;

// Functions to manipulate wiSpriteAnim handles.
// Use wiSprite_GetAnim(sprite) to get a handle to a sprite's animation.

void wiSpriteAnim_SetRot(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetRot(wiSpriteAnim anim);

void wiSpriteAnim_SetRotation(wiSpriteAnim anim, float val); // Alias for Rot
float wiSpriteAnim_GetRotation(wiSpriteAnim anim);

void wiSpriteAnim_SetOpacity(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetOpacity(wiSpriteAnim anim);

void wiSpriteAnim_SetFade(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetFade(wiSpriteAnim anim);

void wiSpriteAnim_SetRepeatable(wiSpriteAnim anim, bool val);
bool wiSpriteAnim_GetRepeatable(wiSpriteAnim anim);

void wiSpriteAnim_SetVelocity(wiSpriteAnim anim, wiVector val);
wiVector wiSpriteAnim_GetVelocity(wiSpriteAnim anim);

void wiSpriteAnim_SetScaleX(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetScaleX(wiSpriteAnim anim);

void wiSpriteAnim_SetScaleY(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetScaleY(wiSpriteAnim anim);

// Complex substructs: MovingTexAnim, DrawRectAnim, WobbleAnim
// We can flatten them or expose separate handles.
// Flattening is easier for straightforward C API unless they are reused.
// Lua binds them as properties.
// Let's flatten common ones or provide specific setters.

// MovingTexAnim
void wiSpriteAnim_SetMovingTexAnimSpeedX(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetMovingTexAnimSpeedX(wiSpriteAnim anim);
void wiSpriteAnim_SetMovingTexAnimSpeedY(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetMovingTexAnimSpeedY(wiSpriteAnim anim);

// DrawRectAnim
void wiSpriteAnim_SetDrawRectAnimFrameRate(wiSpriteAnim anim, float val);
float wiSpriteAnim_GetDrawRectAnimFrameRate(wiSpriteAnim anim);
void wiSpriteAnim_SetDrawRectAnimFrameCount(wiSpriteAnim anim, int val);
int wiSpriteAnim_GetDrawRectAnimFrameCount(wiSpriteAnim anim);
void wiSpriteAnim_SetDrawRectAnimHorizontalFrameCount(wiSpriteAnim anim,
                                                      int val);
int wiSpriteAnim_GetDrawRectAnimHorizontalFrameCount(wiSpriteAnim anim);

// WobbleAnim (Lua bind showed SetWobbleAnimAmount/Speed)
void wiSpriteAnim_SetWobbleAnimAmount(wiSpriteAnim anim, float x, float y);
// getter for amount?
void wiSpriteAnim_SetWobbleAnimSpeed(wiSpriteAnim anim, float val);

#ifdef __cplusplus
}
#endif
