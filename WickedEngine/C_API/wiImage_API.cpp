#include "wiImage_API.h"
#include "wiHelper.h"
#include "wiImage.h"
#include "wiMath_API.h" // Explicit include


using namespace wi::image;
using namespace DirectX; // for XMFLOAT conversions if needed

struct wiImageParams_t {
  Params params;
};

extern "C" {

wiImageParams wiImageParams_Create(float x, float y, float w, float h) {
  wiImageParams_t *p = new wiImageParams_t();
  p->params = Params(x, y, w, h);
  return p;
}

void wiImageParams_Destroy(wiImageParams params) {
  if (params)
    delete params;
}

void wiImageParams_SetPos(wiImageParams params, wiVector pos) {
  if (params)
    params->params.pos = XMFLOAT3(pos.x, pos.y, pos.z);
}

void wiImageParams_SetSize(wiImageParams params, wiVector size) {
  if (params)
    params->params.siz = XMFLOAT2(size.x, size.y);
}

void wiImageParams_SetPivot(wiImageParams params, wiVector pivot) {
  if (params)
    params->params.pivot = XMFLOAT2(pivot.x, pivot.y);
}

void wiImageParams_SetColor(wiImageParams params, wiColor color) {
  if (params)
    params->params.color =
        XMFLOAT4((float)color.r / 255.0f, (float)color.g / 255.0f,
                 (float)color.b / 255.0f, (float)color.a / 255.0f);
}

void wiImageParams_SetOpacity(wiImageParams params, float opacity) {
  if (params)
    params->params.opacity = opacity;
}

void wiImageParams_SetRotation(wiImageParams params, float rotation) {
  if (params)
    params->params.rotation = rotation;
}

void wiImageParams_SetFade(wiImageParams params, float fade) {
  if (params)
    params->params.fade = fade;
}

wiVector wiImageParams_GetPos(wiImageParams params) {
  wiVector v = {0, 0, 0, 0};
  if (params) {
    v.x = params->params.pos.x;
    v.y = params->params.pos.y;
    v.z = params->params.pos.z;
  }
  return v;
}

wiVector wiImageParams_GetSize(wiImageParams params) {
  wiVector v = {0, 0, 0, 0};
  if (params) {
    v.x = params->params.siz.x;
    v.y = params->params.siz.y;
  }
  return v;
}

wiVector wiImageParams_GetPivot(wiImageParams params) {
  wiVector v = {0, 0, 0, 0};
  if (params) {
    v.x = params->params.pivot.x;
    v.y = params->params.pivot.y;
  }
  return v;
}

wiColor wiImageParams_GetColor(wiImageParams params) {
  wiColor c = {0, 0, 0, 0};
  if (params) {
    c.r = (uint8_t)(params->params.color.x * 255);
    c.g = (uint8_t)(params->params.color.y * 255);
    c.b = (uint8_t)(params->params.color.z * 255);
    c.a = (uint8_t)(params->params.color.w * 255);
  }
  return c;
}

float wiImageParams_GetOpacity(wiImageParams params) {
  return params ? params->params.opacity : 0.0f;
}

float wiImageParams_GetRotation(wiImageParams params) {
  return params ? params->params.rotation : 0.0f;
}

} // extern "C"
