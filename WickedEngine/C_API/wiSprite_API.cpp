#include "wiSprite_API.h"
#include "wiSprite.h"

using namespace wi;

struct wiSprite_t {
  Sprite sprite;
};

struct wiImageParams_t {
  wi::image::Params params;
};

extern "C" {

wiSprite wiSprite_Create(const char *image_file, const char *mask_file) {
  wiSprite_t *s = new wiSprite_t();
  s->sprite = Sprite(image_file ? image_file : "", mask_file ? mask_file : "");
  return s;
}

void wiSprite_Destroy(wiSprite sprite) {
  if (sprite)
    delete sprite;
}

wiSpriteAnim wiSprite_GetAnim(wiSprite sprite) {
  // Placeholder: returning nullptr as wiSpriteAnim logic isn't fully exposed or
  // connected to Sprite yet in C API. Or if Sprite has anim, we return it?
  // wi::Sprite has `anim` member which is `SpriteAnim`.
  // But `wiSpriteAnim` handle is opaque pointer.
  // We should return a pointer to the internal member if lifetime is managed by
  // Sprite.
  if (sprite) {
    return (wiSpriteAnim)&sprite->sprite.anim;
  }
  return nullptr;
}

void wiSprite_SetParams(wiSprite sprite, wiImageParams params) {
  if (sprite && params) {
    sprite->sprite.params = params->params;
  }
}

wiImageParams wiSprite_GetParams(wiSprite sprite) {
  if (!sprite)
    return nullptr;
  wiImageParams_t *p = new wiImageParams_t();
  p->params = sprite->sprite.params;
  return p;
}

void wiSprite_SetHidden(wiSprite sprite, bool hidden) {
  if (sprite)
    sprite->sprite.SetHidden(hidden);
}

bool wiSprite_IsHidden(wiSprite sprite) {
  return sprite ? sprite->sprite.IsHidden() : true;
}

} // extern "C"
