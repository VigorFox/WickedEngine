#pragma once
#include "wiMath_API.h"       // for wiColor
#include "wiRenderPath_API.h" // for wiRenderPath
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Application Handle
// Application Handle
typedef struct wiApplication_t *wiApplication;
typedef struct wiCanvas_t *wiCanvas;

typedef enum wiFadeType_t {
  WI_FADE_TO_COLOR = 0,
  WI_FADE_TO_BLACK = 1
} wiFadeType;

void wiApplication_SetActivePath(wiApplication app, wiRenderPath path);
void wiApplication_SetActivePathFade(wiApplication app, wiRenderPath path,
                                     float fadeSeconds, wiColor fadeColor,
                                     wiFadeType fadeType);
wiRenderPath wiApplication_GetActivePath(wiApplication app);

void wiApplication_SetFrameSkip(wiApplication app, bool enabled);
void wiApplication_SetFullScreen(wiApplication app, bool enabled);
void wiApplication_SetTargetFrameRate(wiApplication app, float value);
void wiApplication_SetFrameRateLock(wiApplication app, bool enabled);
void wiApplication_SetInfoDisplay(wiApplication app, bool active);
void wiApplication_SetWatermarkDisplay(wiApplication app, bool active);
void wiApplication_SetFPSDisplay(wiApplication app, bool active);
void wiApplication_SetResolutionDisplay(wiApplication app, bool active);
void wiApplication_SetLogicalSizeDisplay(wiApplication app, bool active);
void wiApplication_SetColorSpaceDisplay(wiApplication app, bool active);
void wiApplication_SetPipelineCountDisplay(wiApplication app, bool active);
void wiApplication_SetHeapAllocationCountDisplay(wiApplication app,
                                                 bool active);
void wiApplication_SetVRAMUsageDisplay(wiApplication app, bool active);
void wiApplication_SetColorGradingHelper(wiApplication app, bool active);

bool wiApplication_IsHDRSupported(wiApplication app);
void wiApplication_SetHDR(wiApplication app, bool enabled);

wiCanvas wiApplication_GetCanvas(wiApplication app);
void wiApplication_SetCanvas(wiApplication app, wiCanvas canvas);

void wiApplication_Exit(wiApplication app);

#ifdef __cplusplus
}
#endif
