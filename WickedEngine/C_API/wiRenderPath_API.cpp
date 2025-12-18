#include "wiRenderPath_API.h"
#include "../wiRenderPath.h"
#include "../wiRenderPath2D.h"
#include "../wiRenderPath3D.h"
#include "../wiTextureHelper.h" // for creating texture wrapper if needed? No, standard logic.
// wiTexture_API.h is included in header

// --- RenderPath Base ---

extern "C" {

uint32_t wiRenderPath_GetLayerMask(wiRenderPath renderPath) {
  if (renderPath)
    return ((wi::RenderPath *)renderPath)->getLayerMask();
  return 0;
}
void wiRenderPath_SetLayerMask(wiRenderPath renderPath, uint32_t mask) {
  if (renderPath)
    ((wi::RenderPath *)renderPath)->setlayerMask(mask);
}

// --- RenderPath2D ---

wiRenderPath wiRenderPath2D_AsRenderPath(wiRenderPath2D renderPath2D) {
  return (wiRenderPath)renderPath2D;
}

void wiRenderPath2D_AddSprite(wiRenderPath2D renderPath, wiSprite sprite,
                              const char *layer) {
  if (renderPath && sprite) {
    if (layer)
      ((wi::RenderPath2D *)renderPath)->AddSprite((wi::Sprite *)sprite, layer);
    else
      ((wi::RenderPath2D *)renderPath)->AddSprite((wi::Sprite *)sprite);
  }
}

void wiRenderPath2D_AddFont(wiRenderPath2D renderPath, wiSpriteFont font,
                            const char *layer) {
  if (renderPath && font) {
    if (layer)
      ((wi::RenderPath2D *)renderPath)->AddFont((wi::SpriteFont *)font, layer);
    else
      ((wi::RenderPath2D *)renderPath)->AddFont((wi::SpriteFont *)font);
  }
}

void wiRenderPath2D_RemoveSprite(wiRenderPath2D renderPath, wiSprite sprite) {
  if (renderPath && sprite)
    ((wi::RenderPath2D *)renderPath)->RemoveSprite((wi::Sprite *)sprite);
}

void wiRenderPath2D_RemoveFont(wiRenderPath2D renderPath, wiSpriteFont font) {
  if (renderPath && font)
    ((wi::RenderPath2D *)renderPath)->RemoveFont((wi::SpriteFont *)font);
}

void wiRenderPath2D_ClearSprites(wiRenderPath2D renderPath) {
  if (renderPath)
    ((wi::RenderPath2D *)renderPath)->ClearSprites();
}

void wiRenderPath2D_ClearFonts(wiRenderPath2D renderPath) {
  if (renderPath)
    ((wi::RenderPath2D *)renderPath)->ClearFonts();
}

int wiRenderPath2D_GetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite) {
  if (renderPath && sprite)
    return ((wi::RenderPath2D *)renderPath)
        ->GetSpriteOrder((wi::Sprite *)sprite);
  return 0;
}

int wiRenderPath2D_GetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font) {
  if (renderPath && font)
    return ((wi::RenderPath2D *)renderPath)
        ->GetFontOrder((wi::SpriteFont *)font);
  return 0;
}

void wiRenderPath2D_AddLayer(wiRenderPath2D renderPath, const char *name) {
  if (renderPath && name)
    ((wi::RenderPath2D *)renderPath)->AddLayer(name);
}

void wiRenderPath2D_SetLayerOrder(wiRenderPath2D renderPath, const char *name,
                                  int order) {
  if (renderPath && name)
    ((wi::RenderPath2D *)renderPath)->SetLayerOrder(name, order);
}

void wiRenderPath2D_SetSpriteOrder(wiRenderPath2D renderPath, wiSprite sprite,
                                   int order) {
  if (renderPath && sprite)
    ((wi::RenderPath2D *)renderPath)
        ->SetSpriteOrder((wi::Sprite *)sprite, order);
}

void wiRenderPath2D_SetFontOrder(wiRenderPath2D renderPath, wiSpriteFont font,
                                 int order) {
  if (renderPath && font)
    ((wi::RenderPath2D *)renderPath)
        ->SetFontOrder((wi::SpriteFont *)font, order);
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
    ((wi::RenderPath3D *)renderPath)->resolutionScale = value;
}

void wiRenderPath3D_SetAO(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setAO((wi::RenderPath3D::AO)value);
}

void wiRenderPath3D_SetAOPower(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setAOPower(value);
}

void wiRenderPath3D_SetAORange(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setAORange(value);
}

void wiRenderPath3D_SetSSREnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setSSREnabled(value);
}

void wiRenderPath3D_SetSSGIEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setSSGIEnabled(value);
}

void wiRenderPath3D_SetRaytracedDiffuseEnabled(wiRenderPath3D renderPath,
                                               bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setRaytracedDiffuseEnabled(value);
}

void wiRenderPath3D_SetRaytracedReflectionsEnabled(wiRenderPath3D renderPath,
                                                   bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setRaytracedReflectionsEnabled(value);
}

void wiRenderPath3D_SetShadowsEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setShadowsEnabled(value);
}

void wiRenderPath3D_SetReflectionsEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setReflectionsEnabled(value);
}

void wiRenderPath3D_SetFXAAEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setFXAAEnabled(value);
}

void wiRenderPath3D_SetBloomEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setBloomEnabled(value);
}

void wiRenderPath3D_SetBloomThreshold(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setBloomThreshold(value);
}

void wiRenderPath3D_SetColorGradingEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setColorGradingEnabled(value);
}

void wiRenderPath3D_SetVolumeLightsEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setVolumeLightsEnabled(value);
}

void wiRenderPath3D_SetLightShaftsEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setLightShaftsEnabled(value);
}

void wiRenderPath3D_SetLensFlareEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setLensFlareEnabled(value);
}

void wiRenderPath3D_SetMotionBlurEnabled(wiRenderPath3D renderPath,
                                         bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setMotionBlurEnabled(value);
}

void wiRenderPath3D_SetDitherEnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setDitherEnabled(value);
}

void wiRenderPath3D_SetDepthOfFieldEnabled(wiRenderPath3D renderPath,
                                           bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setDepthOfFieldEnabled(value);
}

void wiRenderPath3D_SetEyeAdaptionEnabled(wiRenderPath3D renderPath,
                                          bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setEyeAdaptionEnabled(value);
}

void wiRenderPath3D_SetMSAASampleCount(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setMSAASampleCount(value);
}

void wiRenderPath3D_SetSharpenFilterEnabled(wiRenderPath3D renderPath,
                                            bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setSharpenFilterEnabled(value);
}

void wiRenderPath3D_SetSharpenFilterAmount(wiRenderPath3D renderPath,
                                           float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setSharpenFilterAmount(value);
}

void wiRenderPath3D_SetExposure(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setExposure(value);
}

void wiRenderPath3D_SetMotionBlurStrength(wiRenderPath3D renderPath,
                                          float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setMotionBlurStrength(value);
}

void wiRenderPath3D_SetDepthOfFieldStrength(wiRenderPath3D renderPath,
                                            float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setDepthOfFieldStrength(value);
}

void wiRenderPath3D_SetLightShaftsStrength(wiRenderPath3D renderPath,
                                           float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setLightShaftsStrength(value);
}

void wiRenderPath3D_SetFSR2Enabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setFSR2Enabled(value);
}

void wiRenderPath3D_SetFSR2Preset(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)
        ->setFSR2Preset((wi::RenderPath3D::FSR2_Preset)value);
}

// New implementations
void wiRenderPath3D_SetDistortionOverlay(wiRenderPath3D renderPath,
                                         wiTexture texture) {
  if (renderPath) {
    if (texture) {
      // Unwrapping wiTexture (Resource*) -> texture
      ((wi::RenderPath3D *)renderPath)->distortion_overlay =
          ((wi::Resource *)texture)->GetTexture();
    } else {
      ((wi::RenderPath3D *)renderPath)->distortion_overlay =
          wi::graphics::Texture();
    }
  }
}

void wiRenderPath3D_SetChromaticAberrationEnabled(wiRenderPath3D renderPath,
                                                  bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setChromaticAberrationEnabled(value);
}

void wiRenderPath3D_SetChromaticAberrationAmount(wiRenderPath3D renderPath,
                                                 float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setChromaticAberrationAmount(value);
}

void wiRenderPath3D_SetHDRCalibration(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setHDRCalibration(value);
}

void wiRenderPath3D_SetVisibilityComputeShadingEnabled(
    wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setVisibilityComputeShadingEnabled(value);
}

void wiRenderPath3D_SetTonemap(wiRenderPath3D renderPath, int value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setTonemap((wi::renderer::Tonemap)value);
}

void wiRenderPath3D_SetCropLeft(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->crop_left = value;
}
void wiRenderPath3D_SetCropRight(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->crop_right = value;
}
void wiRenderPath3D_SetCropTop(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->crop_top = value;
}
void wiRenderPath3D_SetCropBottom(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->crop_bottom = value;
}

void wiRenderPath3D_SetFSREnabled(wiRenderPath3D renderPath, bool value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setFSREnabled(value);
}
void wiRenderPath3D_SetFSRSharpness(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setFSRSharpness(value);
}
void wiRenderPath3D_SetFSR2Sharpness(wiRenderPath3D renderPath, float value) {
  if (renderPath)
    ((wi::RenderPath3D *)renderPath)->setFSR2Sharpness(value);
}

wiTexture wiRenderPath3D_GetLastPostProcessRT(wiRenderPath3D renderPath) {
  if (renderPath) {
    const wi::graphics::Texture *tex =
        ((wi::RenderPath3D *)renderPath)->GetLastPostprocessRT();
    if (tex) {
      // Need to return a wiTexture (Resource*).
      // This texture is internal to RenderPath3D (owned by it usually, or
      // temporary). Creating a new Resource wrapper on heap to prevent leak of
      // internal pointer? "GetLastPostProcessRT" returns pointer to internal
      // member usually. If we wrap it in new Resource, Resource destructor
      // might not own the textrue (Texture struct has shared_ptr, so it
      // increases ref count). So copying it to a new Resource is safe (it just
      // shares reference).
      wi::Resource *res = new wi::Resource();
      res->SetTexture(*tex);
      return (wiTexture)res;
    }
  }
  return nullptr;
}
}
