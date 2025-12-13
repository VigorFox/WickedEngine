#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

// Application Handle
// Note: wiApplication is defined in wiC_API.h

void wiApplication_SetActivePath(wiApplication app, wiRenderPath path);
void wiApplication_SetActivePathFade(wiApplication app, wiRenderPath path, float fadeSeconds, wiColor fadeColor, wiFadeType fadeType);
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
void wiApplication_SetHeapAllocationCountDisplay(wiApplication app, bool active);
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
