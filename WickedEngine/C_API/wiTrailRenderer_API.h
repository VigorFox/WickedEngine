#pragma once
#include "wiC_API.h"
#include "wiMath_API.h"
#include "wiTexture_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiTrailRenderer_t *wiTrailRenderer;

// TrailPoint structure mirroring the one in wiTrailRenderer
typedef struct wiTrailPoint_t {
  wiVector position;
  float width;
  wiVector color;
  wiVector rotation;
} wiTrailPoint;

wiTrailRenderer wiTrailRenderer_Create();
void wiTrailRenderer_Destroy(
    wiTrailRenderer trail); // Note: TrailRenderer is often a member, but if we
                            // create it on heap we need destroy.

void wiTrailRenderer_AddPoint(wiTrailRenderer trail, wiVector pos, float width,
                              wiVector color, wiVector rotation);
void wiTrailRenderer_Cut(wiTrailRenderer trail, bool loop);
void wiTrailRenderer_Fade(wiTrailRenderer trail, float amount);
void wiTrailRenderer_Clear(wiTrailRenderer trail);
int wiTrailRenderer_GetPointCount(wiTrailRenderer trail);
void wiTrailRenderer_GetPoint(wiTrailRenderer trail, int index,
                              wiTrailPoint *outPoint);
void wiTrailRenderer_SetPoint(wiTrailRenderer trail, int index,
                              const wiTrailPoint *point);

// Settings
typedef enum wiTrailBlendMode {
  WI_TRAIL_BLENDMODE_NORMAL = 0,
  WI_TRAIL_BLENDMODE_ADDITIVE = 1,
  WI_TRAIL_BLENDMODE_SOFT_ADDITIVE = 2,
  WI_TRAIL_BLENDMODE_NULTIPLICATIVE = 3,
} wiTrailBlendMode;

void wiTrailRenderer_SetBlendMode(wiTrailRenderer trail,
                                  wiTrailBlendMode blendMode);
wiTrailBlendMode wiTrailRenderer_GetBlendMode(wiTrailRenderer trail);
void wiTrailRenderer_SetSubdivision(wiTrailRenderer trail,
                                    uint32_t subdivision);
uint32_t wiTrailRenderer_GetSubdivision(wiTrailRenderer trail);
void wiTrailRenderer_SetWidth(wiTrailRenderer trail, float width);
float wiTrailRenderer_GetWidth(wiTrailRenderer trail);
void wiTrailRenderer_SetColor(wiTrailRenderer trail, wiVector color);
wiVector wiTrailRenderer_GetColor(wiTrailRenderer trail);
void wiTrailRenderer_SetTexture(wiTrailRenderer trail, wiTexture texture);
wiTexture wiTrailRenderer_GetTexture(
    wiTrailRenderer trail); // Returns pointer, verify validity
void wiTrailRenderer_SetTexture2(wiTrailRenderer trail, wiTexture texture);
wiTexture wiTrailRenderer_GetTexture2(wiTrailRenderer trail);
void wiTrailRenderer_SetTexMulAdd(wiTrailRenderer trail, wiVector value);
wiVector wiTrailRenderer_GetTexMulAdd(wiTrailRenderer trail);
void wiTrailRenderer_SetTexMulAdd2(wiTrailRenderer trail, wiVector value);
wiVector wiTrailRenderer_GetTexMulAdd2(wiTrailRenderer trail);
void wiTrailRenderer_SetDepthSoften(wiTrailRenderer trail, float value);

void wiTrailRenderer_Update(wiTrailRenderer trail, float dt);
void wiTrailRenderer_Draw(
    wiTrailRenderer trail,
    wiCanvas canvas); // Assuming we might need to draw it manually? API usage
                      // in Lua suggests it's usually part of something else or
                      // drawn manually. Lua binds Draw but C API usually relies
                      // on Scene unless it's a standalone helper. Lua binds
                      // Draw? Checked lua bindings: No Draw method bound in
                      // methods[] list. It seems it is just data container or
                      // managed by scene? Wait, TrailRenderer is a class in
                      // wiTrailRenderer.h. Let's check if it has Draw.
// Re-checking lua bindings for Draw...
// methods[]: AddPoint, Cut, Fade, Clear... No Draw.
// It seems TrailRenderer is usually used by components or manually drawn in
// C++. The lua binding seems to be modifying a global or specific instance
// attached to something? Actually the Lua binding shows `trail` as a member
// `TrailRenderer trail;` inside the binding class? No, `TrailRenderer_BindLua`
// wraps `TrailRenderer trail;` BY VALUE? Checked wiTrailRenderer_BindLua.h? No
// source provided for .h. In cpp: `TrailRenderer trail;` is a member of
// `TrailRenderer_BindLua` probably. Wait, if it's a binding of a standalone
// object, users create it `local t = TrailRenderer()`. Then they probably call
// `wi.DrawTrail(t)`? or something? Let's assume for now we expose the object
// and its methods.

#ifdef __cplusplus
}
#endif
