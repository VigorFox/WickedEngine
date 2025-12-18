#pragma once
#include "wiMath_API.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// wiImageParams wrapper
typedef struct wiImageParams_t *wiImageParams;

wiImageParams wiImageParams_Create(float x, float y, float w, float h);
void wiImageParams_Destroy(wiImageParams params);

void wiImageParams_SetPos(wiImageParams params, wiVector pos);
void wiImageParams_SetSize(wiImageParams params, wiVector size);
void wiImageParams_SetPivot(wiImageParams params, wiVector pivot);
void wiImageParams_SetColor(wiImageParams params, wiColor color);
void wiImageParams_SetOpacity(wiImageParams params, float opacity);
void wiImageParams_SetRotation(wiImageParams params, float rotation);
void wiImageParams_SetFade(wiImageParams params, float fade);

// Getters
wiVector wiImageParams_GetPos(wiImageParams params);
wiVector wiImageParams_GetSize(wiImageParams params);
wiVector wiImageParams_GetPivot(wiImageParams params);
wiColor wiImageParams_GetColor(wiImageParams params);
float wiImageParams_GetOpacity(wiImageParams params);
float wiImageParams_GetRotation(wiImageParams params);

// Blend Modes
typedef enum wiBlendMode {
  WI_BLENDMODE_NORMAL,
  WI_BLENDMODE_ADDITIVE,
  WI_BLENDMODE_MULTIPLY,
  WI_BLENDMODE_PREMULTIPLIED
} wiBlendMode;

void wiImageParams_SetBlendMode(wiImageParams params, wiBlendMode mode);
wiBlendMode wiImageParams_GetBlendMode(wiImageParams params);

#ifdef __cplusplus
}
#endif
