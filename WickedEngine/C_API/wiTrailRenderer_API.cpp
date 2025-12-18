#include "wiTrailRenderer_API.h"
#include "../wiHelper.h"
#include "../wiMath.h"
#include "../wiResourceManager.h"
#include "../wiTrailRenderer.h"

using namespace DirectX;
#include "wiTrailRenderer_API.h"

struct wiTrailRenderer_t {
  wi::TrailRenderer internal_trail;
};

wiTrailRenderer wiTrailRenderer_Create() { return new wiTrailRenderer_t(); }

void wiTrailRenderer_Destroy(wiTrailRenderer trail) {
  if (trail)
    delete trail;
}

void wiTrailRenderer_AddPoint(wiTrailRenderer trail, wiVector pos, float width,
                              wiVector color, wiVector rotation) {
  if (trail) {
    // Convert wiVector (float4) to XMFLOAT3 for position
    XMFLOAT3 p_pos;
    p_pos.x = pos.x;
    p_pos.y = pos.y;
    p_pos.z = pos.z;

    // Convert wiVector to XMFLOAT4 for color and rotation
    XMFLOAT4 p_col = *(XMFLOAT4 *)&color;
    XMFLOAT4 p_rot = *(XMFLOAT4 *)&rotation;

    trail->internal_trail.AddPoint(p_pos, width, p_col, p_rot);
  }
}

void wiTrailRenderer_Cut(wiTrailRenderer trail, bool loop) {
  if (trail)
    trail->internal_trail.Cut(loop);
}

void wiTrailRenderer_Fade(wiTrailRenderer trail, float amount) {
  if (trail)
    trail->internal_trail.Fade(amount);
}

void wiTrailRenderer_Clear(wiTrailRenderer trail) {
  if (trail)
    trail->internal_trail.Clear();
}

int wiTrailRenderer_GetPointCount(wiTrailRenderer trail) {
  if (trail)
    return (int)trail->internal_trail.points.size();
  return 0;
}

void wiTrailRenderer_GetPoint(wiTrailRenderer trail, int index,
                              wiTrailPoint *outPoint) {
  if (trail && outPoint && index >= 0 &&
      index < (int)trail->internal_trail.points.size()) {
    const auto &p = trail->internal_trail.points[index];

    // Position (XMFLOAT3 -> wiVector)
    outPoint->position.x = p.position.x;
    outPoint->position.y = p.position.y;
    outPoint->position.z = p.position.z;
    outPoint->position.w = 1.0f; // W is typically 1 for pos

    outPoint->width = p.width;

    // Color (XMFLOAT4 -> wiVector)
    *(XMFLOAT4 *)&outPoint->color = p.color;

    // Rotation (XMFLOAT4 -> wiVector)
    *(XMFLOAT4 *)&outPoint->rotation = p.rotation;
  }
}

void wiTrailRenderer_SetPoint(wiTrailRenderer trail, int index,
                              const wiTrailPoint *point) {
  if (trail && point && index >= 0 &&
      index < (int)trail->internal_trail.points.size()) {
    auto &p = trail->internal_trail.points[index];

    p.position.x = point->position.x;
    p.position.y = point->position.y;
    p.position.z = point->position.z;

    p.width = point->width;
    p.color = *(XMFLOAT4 *)&point->color;
    p.rotation = *(XMFLOAT4 *)&point->rotation;
  }
}

void wiTrailRenderer_SetBlendMode(wiTrailRenderer trail,
                                  wiTrailBlendMode blendMode) {
  if (trail)
    trail->internal_trail.blendMode = (wi::enums::BLENDMODE)blendMode;
}

wiTrailBlendMode wiTrailRenderer_GetBlendMode(wiTrailRenderer trail) {
  if (trail)
    return (wiTrailBlendMode)trail->internal_trail.blendMode;
  return WI_TRAIL_BLENDMODE_NORMAL;
}

void wiTrailRenderer_SetSubdivision(wiTrailRenderer trail,
                                    uint32_t subdivision) {
  if (trail)
    trail->internal_trail.subdivision = subdivision;
}

uint32_t wiTrailRenderer_GetSubdivision(wiTrailRenderer trail) {
  if (trail)
    return trail->internal_trail.subdivision;
  return 0;
}

void wiTrailRenderer_SetWidth(wiTrailRenderer trail, float width) {
  if (trail)
    trail->internal_trail.width = width;
}

float wiTrailRenderer_GetWidth(wiTrailRenderer trail) {
  if (trail)
    return trail->internal_trail.width;
  return 0.0f;
}

void wiTrailRenderer_SetColor(wiTrailRenderer trail, wiVector color) {
  if (trail)
    trail->internal_trail.color = *(XMFLOAT4 *)&color;
}

wiVector wiTrailRenderer_GetColor(wiTrailRenderer trail) {
  wiVector v = {0};
  if (trail)
    *(XMFLOAT4 *)&v = trail->internal_trail.color;
  return v;
}

void wiTrailRenderer_SetTexture(wiTrailRenderer trail, wiTexture texture) {
  if (trail && texture) {
    trail->internal_trail.texture = ((wi::Resource *)texture)->GetTexture();
  }
}

wiTexture wiTrailRenderer_GetTexture(wiTrailRenderer trail) {
  if (trail) {
    // Returning a new Resource pointer wrapping the texture object is risky
    // because it ownership is unclear. But C API handles usually imply
    // references. However, trail->texture is a Texture object (value).
    // wiTexture MUST be a pointer to a Resource.
    // Creating 'new Resource' here means we leak it if user doesn't destroy it.
    // But wiTexture handle usually refers to a managed resource.
    // NOTE: TrailRenderer holds Texture BY VALUE `wi::graphics::Texture
    // texture;`. We cannot return a pointer to internal member easily if we
    // want to treat it as generic Resource handle? Actually we can:
    // `(wiTexture)&trail->internal_trail.texture`. Because Texture inherits
    // Resource? Let's check wiGraphicsDevice.h or similar.
    // wi::graphics::Texture final : public Resource.
    // So YES, we can return address.
    return (wiTexture)&trail->internal_trail.texture;
  }
  return nullptr;
}

void wiTrailRenderer_SetTexture2(wiTrailRenderer trail, wiTexture texture) {
  if (trail && texture) {
    trail->internal_trail.texture2 = ((wi::Resource *)texture)->GetTexture();
  }
}

wiTexture wiTrailRenderer_GetTexture2(wiTrailRenderer trail) {
  if (trail) {
    return (wiTexture)&trail->internal_trail.texture2;
  }
  return nullptr;
}

void wiTrailRenderer_SetTexMulAdd(wiTrailRenderer trail, wiVector value) {
  if (trail)
    trail->internal_trail.texMulAdd = *(XMFLOAT4 *)&value;
}

wiVector wiTrailRenderer_GetTexMulAdd(wiTrailRenderer trail) {
  wiVector v = {0};
  if (trail)
    *(XMFLOAT4 *)&v = trail->internal_trail.texMulAdd;
  return v;
}

void wiTrailRenderer_SetTexMulAdd2(wiTrailRenderer trail, wiVector value) {
  if (trail)
    trail->internal_trail.texMulAdd2 = *(XMFLOAT4 *)&value;
}

wiVector wiTrailRenderer_GetTexMulAdd2(wiTrailRenderer trail) {
  wiVector v = {0};
  if (trail)
    *(XMFLOAT4 *)&v = trail->internal_trail.texMulAdd2;
  return v;
}

void wiTrailRenderer_SetDepthSoften(wiTrailRenderer trail, float value) {
  if (trail)
    trail->internal_trail.depth_soften = value;
}

void wiTrailRenderer_Update(wiTrailRenderer trail, float dt) {
  // No-op or implementation if needed.
  (void)trail;
  (void)dt;
}
