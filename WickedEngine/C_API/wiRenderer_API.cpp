#include "wiRenderer_API.h"
#include "wiHelper.h"
#include "wiRenderer.h"


using namespace wi::renderer;
using namespace wi::graphics;

extern "C" {

void wiRenderer_SetGameSpeed(float speed) { SetGameSpeed(speed); }

float wiRenderer_GetGameSpeed() { return GetGameSpeed(); }

void wiRenderer_SetShadowProps2D(int resolution) {
  SetShadowProps2D(resolution);
}

void wiRenderer_SetShadowPropsCube(int resolution) {
  SetShadowPropsCube(resolution);
}

void wiRenderer_SetDebugPartitionTreeEnabled(bool enabled) {
  SetToDrawDebugPartitionTree(enabled);
}

void wiRenderer_SetDebugBonesEnabled(bool enabled) {
  SetToDrawDebugBoneLines(enabled);
}

void wiRenderer_SetDebugEmittersEnabled(bool enabled) {
  SetToDrawDebugEmitters(enabled);
}

void wiRenderer_SetDebugEnvProbesEnabled(bool enabled) {
  SetToDrawDebugEnvProbes(enabled);
}

void wiRenderer_SetDebugForceFieldsEnabled(bool enabled) {
  SetToDrawDebugForceFields(enabled);
}

void wiRenderer_SetDebugCamerasEnabled(bool enabled) {
  SetToDrawDebugCameras(enabled);
}

void wiRenderer_SetDebugCollidersEnabled(bool enabled) {
  SetToDrawDebugColliders(enabled);
}

void wiRenderer_SetGridHelperEnabled(bool enabled) {
  SetToDrawGridHelper(enabled);
}

void wiRenderer_SetDDGIDebugEnabled(bool enabled) {
  SetDDGIDebugEnabled(enabled);
}

void wiRenderer_SetDDGIEnabled(bool enabled) { SetDDGIEnabled(enabled); }

void wiRenderer_SetDebugLightCulling(bool enabled) {
  SetDebugLightCulling(enabled);
}

void wiRenderer_SetOcclusionCullingEnabled(bool enabled) {
  SetOcclusionCullingEnabled(enabled);
}

void wiRenderer_SetTemporalAAEnabled(bool enabled) {
  SetTemporalAAEnabled(enabled);
}

void wiRenderer_SetRaytracedShadowsEnabled(bool enabled) {
  SetRaytracedShadowsEnabled(enabled);
}

void wiRenderer_SetMeshShaderAllowed(bool enabled) {
  SetMeshShaderAllowed(enabled);
}

void wiRenderer_SetMeshletOcclusionCullingEnabled(bool enabled) {
  SetMeshletOcclusionCullingEnabled(enabled);
}

void wiRenderer_SetCapsuleShadowEnabled(bool enabled) {
  SetCapsuleShadowEnabled(enabled);
}

void wiRenderer_SetCapsuleShadowFade(float fade) { SetCapsuleShadowFade(fade); }

void wiRenderer_SetCapsuleShadowAngle(float angle) {
  SetCapsuleShadowAngle(angle);
}

void wiRenderer_SetShadowLODOverrideEnabled(bool enabled) {
  SetShadowLODOverrideEnabled(enabled);
}

void wiRenderer_DrawLine(wiRenderableLine *line, bool depth) {
  RenderableLine l;
  l.start = XMFLOAT3(line->start.x, line->start.y, line->start.z);
  l.end = XMFLOAT3(line->end.x, line->end.y, line->end.z);
  l.color_start = XMFLOAT4(
      (float)line->color_start.r / 255.0f, (float)line->color_start.g / 255.0f,
      (float)line->color_start.b / 255.0f, (float)line->color_start.a / 255.0f);
  l.color_end = XMFLOAT4(
      (float)line->color_end.r / 255.0f, (float)line->color_end.g / 255.0f,
      (float)line->color_end.b / 255.0f, (float)line->color_end.a / 255.0f);
  DrawLine(l, depth);
}

void wiRenderer_DrawPoint(wiRenderablePoint *point, bool depth) {
  RenderablePoint p;
  p.position =
      XMFLOAT3(point->position.x, point->position.y, point->position.z);
  p.size = point->size;
  p.color =
      XMFLOAT4((float)point->color.r / 255.0f, (float)point->color.g / 255.0f,
               (float)point->color.b / 255.0f, (float)point->color.a / 255.0f);
  DrawPoint(p, depth);
}

void wiRenderer_DrawBox(wiRenderableBox *box, bool depth) {
  XMFLOAT4X4 mat;
  memcpy(&mat, &box->transform, sizeof(mat));
  XMFLOAT4 col =
      XMFLOAT4((float)box->color.r / 255.0f, (float)box->color.g / 255.0f,
               (float)box->color.b / 255.0f, (float)box->color.a / 255.0f);
  DrawBox(mat, col, depth);
}

void wiRenderer_DrawSphere(wiRenderableSphere *sphere, bool depth) {
  wi::primitive::Sphere s;
  s.center = XMFLOAT3(sphere->center.x, sphere->center.y, sphere->center.z);
  s.radius = sphere->radius;
  XMFLOAT4 col = XMFLOAT4(
      (float)sphere->color.r / 255.0f, (float)sphere->color.g / 255.0f,
      (float)sphere->color.b / 255.0f, (float)sphere->color.a / 255.0f);
  DrawSphere(s, col, depth);
}

void wiRenderer_DrawCapsule(wiRenderableCapsule *capsule, bool depth) {
  wi::primitive::Capsule c;
  c.base = XMFLOAT3(capsule->base.x, capsule->base.y, capsule->base.z);
  c.tip = XMFLOAT3(capsule->tip.x, capsule->tip.y, capsule->tip.z);
  c.radius = capsule->radius;
  XMFLOAT4 col = XMFLOAT4(
      (float)capsule->color.r / 255.0f, (float)capsule->color.g / 255.0f,
      (float)capsule->color.b / 255.0f, (float)capsule->color.a / 255.0f);
  DrawCapsule(c, col, depth);
}

void wiRenderer_DrawDebugText(const char *text, wiDebugTextParams *params) {
  DebugTextParams p;
  p.position =
      XMFLOAT3(params->position.x, params->position.y, params->position.z);
  p.color = XMFLOAT4(
      (float)params->color.r / 255.0f, (float)params->color.g / 255.0f,
      (float)params->color.b / 255.0f, (float)params->color.a / 255.0f);
  p.scaling = params->scaling;
  p.flags = params->flags;
  DrawDebugText(text, p);
}

} // extern "C"
