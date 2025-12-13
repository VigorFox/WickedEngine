#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

// Options
void wiRenderer_SetGameSpeed(float speed);
float wiRenderer_GetGameSpeed();
void wiRenderer_SetShadowProps2D(int resolution);
void wiRenderer_SetShadowPropsCube(int resolution);
void wiRenderer_SetDebugPartitionTreeEnabled(bool enabled);
void wiRenderer_SetDebugBonesEnabled(bool enabled);
void wiRenderer_SetDebugEmittersEnabled(bool enabled);
void wiRenderer_SetDebugEnvProbesEnabled(bool enabled);
void wiRenderer_SetDebugForceFieldsEnabled(bool enabled);
void wiRenderer_SetDebugCamerasEnabled(bool enabled);
void wiRenderer_SetDebugCollidersEnabled(bool enabled);
void wiRenderer_SetGridHelperEnabled(bool enabled);
void wiRenderer_SetDDGIDebugEnabled(bool enabled);
void wiRenderer_SetDDGIEnabled(bool enabled);
void wiRenderer_SetDebugLightCulling(bool enabled);
void wiRenderer_SetOcclusionCullingEnabled(bool enabled);
void wiRenderer_SetTemporalAAEnabled(bool enabled);
void wiRenderer_SetRaytracedShadowsEnabled(bool enabled);
void wiRenderer_SetMeshShaderAllowed(bool enabled);
void wiRenderer_SetMeshletOcclusionCullingEnabled(bool enabled);
void wiRenderer_SetCapsuleShadowEnabled(bool enabled);
void wiRenderer_SetCapsuleShadowFade(float fade);
void wiRenderer_SetCapsuleShadowAngle(float angle);
void wiRenderer_SetShadowLODOverrideEnabled(bool enabled);

// Drawing Helper Structs
typedef struct wiRenderableLine_t {
  wiVector start;
  wiVector end;
  wiColor color_start;
  wiColor color_end;
} wiRenderableLine;

typedef struct wiRenderablePoint_t {
  wiVector position;
  float size;
  wiColor color;
} wiRenderablePoint;

typedef struct wiRenderableBox_t {
  wiMatrix transform; // contains position, rotation, scale
  wiColor color;
} wiRenderableBox;

typedef struct wiRenderableSphere_t {
  wiVector center;
  float radius;
  wiColor color;
} wiRenderableSphere;

typedef struct wiRenderableCapsule_t {
  wiVector base;
  wiVector tip;
  float radius;
  wiColor color;
} wiRenderableCapsule;

// Drawing Functions
void wiRenderer_DrawLine(wiRenderableLine *line, bool depth);
void wiRenderer_DrawPoint(wiRenderablePoint *point, bool depth);
void wiRenderer_DrawBox(wiRenderableBox *box, bool depth);
void wiRenderer_DrawSphere(wiRenderableSphere *sphere, bool depth);
void wiRenderer_DrawCapsule(wiRenderableCapsule *capsule, bool depth);

// Debug Text
typedef struct wiDebugTextParams_t {
  wiVector position; // xyz
  wiColor color;
  float scaling;
  int flags; // see wiRenderer::DebugTextParams::Flags in C++
} wiDebugTextParams;

void wiRenderer_DrawDebugText(const char *text, wiDebugTextParams *params);

#ifdef __cplusplus
}
#endif
