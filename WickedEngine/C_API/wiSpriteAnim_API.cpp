#include "wiSpriteAnim_API.h"
#include "../wiMath.h"
#include "../wiSprite.h"


using namespace DirectX;

// wiSpriteAnim is a pointer to wi::Sprite::Anim
// We assume it is passed from wiSprite_GetAnim

extern "C" {

void wiSpriteAnim_SetRot(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->rot = val;
}
float wiSpriteAnim_GetRot(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->rot;
  return 0.0f;
}

void wiSpriteAnim_SetRotation(wiSpriteAnim anim, float val) {
  wiSpriteAnim_SetRot(anim, val);
}
float wiSpriteAnim_GetRotation(wiSpriteAnim anim) {
  return wiSpriteAnim_GetRot(anim);
}

void wiSpriteAnim_SetOpacity(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->opa = val;
}
float wiSpriteAnim_GetOpacity(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->opa;
  return 0.0f;
}

void wiSpriteAnim_SetFade(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->fad = val;
}
float wiSpriteAnim_GetFade(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->fad;
  return 0.0f;
}

void wiSpriteAnim_SetRepeatable(wiSpriteAnim anim, bool val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->repeatable = val;
}
bool wiSpriteAnim_GetRepeatable(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->repeatable;
  return false;
}

void wiSpriteAnim_SetVelocity(wiSpriteAnim anim, wiVector val) {
  if (anim) {
    XMStoreFloat3(&((wi::Sprite::Anim *)anim)->vel,
                  XMLoadFloat4((XMFLOAT4 *)&val));
  }
}
wiVector wiSpriteAnim_GetVelocity(wiSpriteAnim anim) {
  wiVector v = {0};
  if (anim) {
    XMStoreFloat4((XMFLOAT4 *)&v,
                  XMLoadFloat3(&((wi::Sprite::Anim *)anim)->vel));
  }
  return v;
}

void wiSpriteAnim_SetScaleX(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->scaleX = val;
}
float wiSpriteAnim_GetScaleX(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->scaleX;
  return 0.0f;
}

void wiSpriteAnim_SetScaleY(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->scaleY = val;
}
float wiSpriteAnim_GetScaleY(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->scaleY;
  return 0.0f;
}

void wiSpriteAnim_SetMovingTexAnimSpeedX(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->movingTexAnim.speedX = val;
}
float wiSpriteAnim_GetMovingTexAnimSpeedX(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->movingTexAnim.speedX;
  return 0.0f;
}

void wiSpriteAnim_SetMovingTexAnimSpeedY(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->movingTexAnim.speedY = val;
}
float wiSpriteAnim_GetMovingTexAnimSpeedY(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->movingTexAnim.speedY;
  return 0.0f;
}

void wiSpriteAnim_SetDrawRectAnimFrameRate(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->drawRectAnim.frameRate = val;
}
float wiSpriteAnim_GetDrawRectAnimFrameRate(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->drawRectAnim.frameRate;
  return 0.0f;
}

void wiSpriteAnim_SetDrawRectAnimFrameCount(wiSpriteAnim anim, int val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->drawRectAnim.frameCount = val;
}
int wiSpriteAnim_GetDrawRectAnimFrameCount(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->drawRectAnim.frameCount;
  return 0;
}

void wiSpriteAnim_SetDrawRectAnimHorizontalFrameCount(wiSpriteAnim anim,
                                                      int val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->drawRectAnim.horizontalFrameCount = val;
}
int wiSpriteAnim_GetDrawRectAnimHorizontalFrameCount(wiSpriteAnim anim) {
  if (anim)
    return ((wi::Sprite::Anim *)anim)->drawRectAnim.horizontalFrameCount;
  return 0;
}

void wiSpriteAnim_SetWobbleAnimAmount(wiSpriteAnim anim, float x, float y) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->wobbleAnim.amount = XMFLOAT2(x, y);
}

void wiSpriteAnim_SetWobbleAnimSpeed(wiSpriteAnim anim, float val) {
  if (anim)
    ((wi::Sprite::Anim *)anim)->wobbleAnim.speed = val;
}
}
