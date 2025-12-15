#include "wiSprite_API.h"
#include "wiSprite.h"

using namespace wi;

struct wiSprite_t {
  Sprite sprite;
};

// We need to define wiImageParams_t here to cast it (or include internal
// header?) Since it's opaque in header, we need to know what it is in
// implementation. It was defined in wiImage_API.cpp. We should move struct
// definition to a common internal header or redefine it compatible. Better:
// wiImage_API.h only declares it. We can define a shared private header
// `wiC_API_Internal.h` or just copy definition (BAD). Or include wiImage.h and
// cast. wiImageParams_t is just a wrapper around wi::image::Params. Let's
// assume we can include `wiImage_API.cpp`? No. We will just cast to
// `wi::image::Params*` assuming we know the layout or access it via a helper?
// We can expose a helper in wiImage_API.cpp?
// Or we just redefine struct wiImageParams_t { wi::image::Params params; };
// here. It's correct as long as it matches.

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

void wiSprite_SetParams(wiSprite sprite, wiImageParams params) {
  if (sprite && params) {
    sprite->sprite.params = params->params;
  }
}

wiImageParams wiSprite_GetParams(wiSprite sprite) {
  if (!sprite)
    return nullptr;
  // We return a pointer to the internal params?
  // Types mismatch: wiImageParams is `wiImageParams_t*`.
  // sprite->sprite.params is `wi::image::Params`.
  // We can't just return &sprite->sprite.params because it's not wrapped in a
  // `wiImageParams_t`. We need to wrap it? But then we leak memory if user
  // doesn't free it. Or we return a persistent wrapper? C API Design choice:
  // Getters usually return copies for structs, or we use separate GetParamX
  // functions. If we want to return a Handle, we must allocate a wrapper. Let's
  // allocate a wrapper copy. User must destroy it. "GetParams" implies getting
  // the state.
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
