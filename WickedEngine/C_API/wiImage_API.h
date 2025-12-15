#pragma once
#include "wiC_API.h"

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

// Enums for Stencil, Blend, etc. can be added as needed.
// For now covering basics.

#ifdef __cplusplus
}
#endif
