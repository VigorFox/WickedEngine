#pragma once
#include "wiC_API.h"
#include "wiImage_API.h"
#include "wiSpriteFont_API.h"
#include "wiSprite_API.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiRenderPath_t *wiRenderPath;
typedef struct wiRenderPath2D_t *wiRenderPath2D;
typedef struct wiRenderPath3D_t *wiRenderPath3D;

// --- RenderPath Base ---
uint32_t wiRenderPath_GetLayerMask(wiRenderPath renderPath);
void wiRenderPath_SetLayerMask(wiRenderPath renderPath, uint32_t mask);

// --- RenderPath2D ---
// Casting helpers (C-side only reinterpretation of pointer, assumes valid
// object)
wiRenderPath wiRenderPath2D_AsRenderPath(wiRenderPath2D renderPath2D);

void wiRenderPath2D_AddSprite(wiRenderPath2D renderPath, wiSprite sprite,
                              const char *layer);
void wiRenderPath2D_AddFont(wiRenderPath2D renderPath, wiSpriteFont font,
                            const char *layer);
void wiRenderPath2D_RemoveSprite(wiRenderPath2D renderPath, wiSprite sprite);
void wiRenderPath2D_RemoveFont(wiRenderPath2D renderPath, wiSpriteFont font);
void wiRenderPath2D_ClearSprites(wiRenderPath2D renderPath);
void wiRenderPath2D_ClearFonts(wiRenderPath2D renderPath);
int wiRenderPath2D_GetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite);
int wiRenderPath2D_GetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font);
void wiRenderPath2D_AddLayer(wiRenderPath2D renderPath, const char *name);
void wiRenderPath2D_SetLayerOrder(wiRenderPath2D renderPath, const char *name,
                                  int order);
void wiRenderPath2D_SetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite,
                                   int order);
void wiRenderPath2D_SetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font,
                                 int order);

// --- RenderPath3D ---
wiRenderPath wiRenderPath3D_AsRenderPath(wiRenderPath3D renderPath3D);
wiRenderPath2D wiRenderPath3D_AsRenderPath2D(wiRenderPath3D renderPath3D);

void wiRenderPath3D_SetResolutionScale(wiRenderPath3D renderPath, float value);
void wiRenderPath3D_SetAO(
    wiRenderPath3D renderPath,
    int value); // 0: Disabled, 1: SSAO, 2: HBAO, 3: MSAO, 4: RTAO
void wiRenderPath3D_SetAOPower(wiRenderPath3D renderPath, float value);
void wiRenderPath3D_SetAORange(wiRenderPath3D renderPath, float value);
void wiRenderPath3D_SetSSREnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetSSGIEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetRaytracedDiffuseEnabled(wiRenderPath3D renderPath,
                                               bool value);
void wiRenderPath3D_SetRaytracedReflectionsEnabled(wiRenderPath3D renderPath,
                                                   bool value);
void wiRenderPath3D_SetShadowsEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetReflectionsEnabled(wiRenderPath3D renderPath,
                                          bool value);
void wiRenderPath3D_SetFXAAEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetBloomEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetBloomThreshold(wiRenderPath3D renderPath, float value);
void wiRenderPath3D_SetColorGradingEnabled(wiRenderPath3D renderPath,
                                           bool value);
void wiRenderPath3D_SetVolumeLightsEnabled(wiRenderPath3D renderPath,
                                           bool value);
void wiRenderPath3D_SetLightShaftsEnabled(wiRenderPath3D renderPath,
                                          bool value);
void wiRenderPath3D_SetLensFlareEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetMotionBlurEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetDitherEnabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetDepthOfFieldEnabled(wiRenderPath3D renderPath,
                                           bool value);
void wiRenderPath3D_SetEyeAdaptionEnabled(wiRenderPath3D renderPath,
                                          bool value);
void wiRenderPath3D_SetMSAASampleCount(wiRenderPath3D renderPath, int value);
void wiRenderPath3D_SetSharpenFilterEnabled(wiRenderPath3D renderPath,
                                            bool value);
void wiRenderPath3D_SetSharpenFilterAmount(wiRenderPath3D renderPath,
                                           float value);
void wiRenderPath3D_SetExposure(wiRenderPath3D renderPath, float value);
void wiRenderPath3D_SetMotionBlurStrength(wiRenderPath3D renderPath,
                                          float value);
void wiRenderPath3D_SetDepthOfFieldStrength(wiRenderPath3D renderPath,
                                            float value);
void wiRenderPath3D_SetLightShaftsStrength(wiRenderPath3D renderPath,
                                           float value);
void wiRenderPath3D_SetFSR2Enabled(wiRenderPath3D renderPath, bool value);
void wiRenderPath3D_SetFSR2Preset(
    wiRenderPath3D renderPath,
    int value); // 0: Quality, 1: Balanced, 2: Performance, 3: UltraPerf

#ifdef __cplusplus
}
#endif
