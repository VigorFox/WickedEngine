#pragma once
#include "wiMath_API.h"
#include "wiRenderPath_API.h"
#include "wiTexture_API.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiLoadingScreen_t *wiLoadingScreen;

wiLoadingScreen wiLoadingScreen_Create();
void wiLoadingScreen_Destroy(wiLoadingScreen screen);

// Casting to base classes
wiRenderPath2D wiLoadingScreen_AsRenderPath2D(wiLoadingScreen screen);
wiRenderPath wiLoadingScreen_AsRenderPath(wiLoadingScreen screen);

void wiLoadingScreen_AddLoadModelTask(wiLoadingScreen screen,
                                      const char *fileName, wiMatrix transform);
// Note: Lua bind has AddRenderPathActivationTask, but handling RenderPath
// pointers in C needs care. We accept opaque wiRenderPath. fadeType:
// 0=FadeToColor, 1=FadeToBlack
// void wiLoadingScreen_AddRenderPathActivationTask(wiLoadingScreen screen,
//                                                  wiRenderPath path,
//                                                  float fadeSeconds, int r,
//                                                  int g, int b, int fadeType);

bool wiLoadingScreen_IsFinished(wiLoadingScreen screen);
int wiLoadingScreen_GetProgress(wiLoadingScreen screen);

void wiLoadingScreen_SetBackgroundTexture(wiLoadingScreen screen,
                                          wiTexture texture);
wiTexture wiLoadingScreen_GetBackgroundTexture(wiLoadingScreen screen);
// BackgroundMode: 0=Fill, 1=Fit, 2=Stretch
void wiLoadingScreen_SetBackgroundMode(wiLoadingScreen screen, int mode);
int wiLoadingScreen_GetBackgroundMode(wiLoadingScreen screen);

#ifdef __cplusplus
}
#endif
