#include "wiRenderPath_API.h"
#include "../wiRenderPath2D.h"
#include "../wiRenderPath3D.h"
#include "../wiSprite.h"
#include "../wiSpriteFont.h"

using namespace wi;

// We assume the opaque pointers map directly to the classes.
// Since we don't have safe type checking in C, we rely on the user passing
// correct pointers. However, internally we can treat them as their appropriate
// C++ classes.

extern "C" {

// --- RenderPath Base ---
uint32_t wiRenderPath_GetLayerMask(wiRenderPath renderPath) {
  if (!renderPath)
    return 0;
  return ((RenderPath *)renderPath)->getLayerMask();
}

void wiRenderPath_SetLayerMask(wiRenderPath renderPath, uint32_t mask) {
  if (renderPath) {
    ((RenderPath *)renderPath)->setlayerMask(mask);
  }
}

// --- RenderPath2D ---
wiRenderPath wiRenderPath2D_AsRenderPath(wiRenderPath2D renderPath2D) {
  return (wiRenderPath)renderPath2D;
}

void wiRenderPath2D_AddSprite(wiRenderPath2D renderPath, wiSprite sprite,
                              const char *layer) {
  if (renderPath && sprite) {
    if (layer)
      ((RenderPath2D *)renderPath)->AddSprite((Sprite *)sprite, layer);
    else
      ((RenderPath2D *)renderPath)->AddSprite((Sprite *)sprite);
  }
}

void wiRenderPath2D_AddFont(wiRenderPath2D renderPath, wiSpriteFont font,
                            const char *layer) {
  if (renderPath && font) {
    if (layer)
      ((RenderPath2D *)renderPath)->AddFont((SpriteFont *)font, layer);
    else
      ((RenderPath2D *)renderPath)->AddFont((SpriteFont *)font);
  }
}

void wiRenderPath2D_RemoveSprite(wiRenderPath2D renderPath, wiSprite sprite) {
  if (renderPath && sprite)
    ((RenderPath2D *)renderPath)->RemoveSprite((Sprite *)sprite);
}

void wiRenderPath2D_RemoveFont(wiRenderPath2D renderPath, wiSpriteFont font) {
  if (renderPath && font)
    ((RenderPath2D *)renderPath)->RemoveFont((SpriteFont *)font);
}

void wiRenderPath2D_ClearSprites(wiRenderPath2D renderPath) {
  if (renderPath)
    ((RenderPath2D *)renderPath)->ClearSprites();
}

void wiRenderPath2D_ClearFonts(wiRenderPath2D renderPath) {
  if (renderPath)
    ((RenderPath2D *)renderPath)->ClearFonts();
}

int wiRenderPath2D_GetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite) {
  if (renderPath && sprite)
    return ((RenderPath2D *)renderPath)->GetSpriteOrder((Sprite *)sprite);
  return 0;
}

int wiRenderPath2D_GetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font) {
  if (renderPath && font)
    return ((RenderPath2D *)renderPath)->GetFontOrder((SpriteFont *)font);
  return 0;
}

void wiRenderPath2D_AddLayer(wiRenderPath2D renderPath, const char *name) {
  if (renderPath && name)
    ((RenderPath2D *)renderPath)->AddLayer(name);
}

void wiRenderPath2D_SetLayerOrder(wiRenderPath2D renderPath, const char *name,
                                  int order) {
  if (renderPath && name)
    ((RenderPath2D *)renderPath)->SetLayerOrder(name, order);
}

void wiRenderPath2D_SetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite,
                                   int order) {
  if (renderPath && sprite)
    ((RenderPath2D *)renderPath)->SetSpriteOrder((Sprite *)sprite, order);
}

void wiRenderPath2D_SetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font,
                                 int order) {
  if (renderPath && font)
    ((RenderPath2D *)renderPath)->SetFontOrder((SpriteFont *)font, order);
}

// --- RenderPath3D ---
wiRenderPath wiRenderPath3D_AsRenderPath(wiRenderPath3D renderPath3D) {
  return (wiRenderPath)renderPath3D;
}
wiRenderPath2D wiRenderPath3D_AsRenderPath2D(wiRenderPath3D renderPath3D) {
  return (wiRenderPath2D)renderPath3D;
}

void wiRenderPath3D_SetResolutionScale(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->resolutionScale = value;
}

void wiRenderPath3D_SetAO(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setAO((RenderPath3D::AO)value);
}

void wiRenderPath3D_SetAOPower(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setAOPower(value);
}

void wiRenderPath3D_SetAORange(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setAORange(value);
}

void wiRenderPath3D_SetSSREnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setSSREnabled(value);
}

void wiRenderPath3D_SetSSGIEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setSSGIEnabled(value);
}

void wiRenderPath3D_SetRaytracedDiffuseEnabled(wiRenderPath3D renderPath,
                                               bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setRaytracedDiffuseEnabled(value);
}

void wiRenderPath3D_SetRaytracedReflectionsEnabled(wiRenderPath3D renderPath,
                                                   bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setRaytracedReflectionsEnabled(value);
}

void wiRenderPath3D_SetShadowsEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setShadowsEnabled(value);
}

void wiRenderPath3D_SetReflectionsEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setReflectionsEnabled(value);
}

void wiRenderPath3D_SetFXAAEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setFXAAEnabled(value);
}

void wiRenderPath3D_SetBloomEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setBloomEnabled(value);
}

void wiRenderPath3D_SetBloomThreshold(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setBloomThreshold(value);
}

void wiRenderPath3D_SetColorGradingEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setColorGradingEnabled(value);
}

void wiRenderPath3D_SetVolumeLightsEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setVolumeLightsEnabled(value);
}

void wiRenderPath3D_SetLightShaftsEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setLightShaftsEnabled(value);
}

void wiRenderPath3D_SetLensFlareEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setLensFlareEnabled(value);
}

void wiRenderPath3D_SetMotionBlurEnabled(wiRenderPath3D renderPath,
                                         bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setMotionBlurEnabled(value);
}

void wiRenderPath3D_SetDitherEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setDitherEnabled(value);
}

void wiRenderPath3D_SetDepthOfFieldEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setDepthOfFieldEnabled(value);
}

void wiRenderPath3D_SetEyeAdaptionEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setEyeAdaptionEnabled(value);
}

void wiRenderPath3D_SetMSAASampleCount(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setMSAASampleCount((uint32_t)value);
}

void wiRenderPath3D_SetSharpenFilterEnabled(wiRenderPath3D renderPath,
                                            bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setSharpenFilterEnabled(value);
}

void wiRenderPath3D_SetSharpenFilterAmount(wiRenderPath3D renderPath,
                                           float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setSharpenFilterAmount(value);
}

void wiRenderPath3D_SetExposure(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setExposure(value);
}

void wiRenderPath3D_SetMotionBlurStrength(wiRenderPath3D renderPath,
                                          float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setMotionBlurStrength(value);
}

void wiRenderPath3D_SetDepthOfFieldStrength(wiRenderPath3D renderPath,
                                            float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setDepthOfFieldStrength(value);
}

void wiRenderPath3D_SetLightShaftsStrength(wiRenderPath3D renderPath,
                                           float value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setLightShaftsStrength(value);
}

void wiRenderPath3D_SetFSR2Enabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)->setFSR2Enabled(value);
}

void wiRenderPath3D_SetFSR2Preset(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((RenderPath3D *)renderPath)
        ->setFSR2Preset((RenderPath3D::FSR2_Preset)value);
}

} // extern "C"
