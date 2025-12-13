#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

// Log Levels? wiBacklog just takes strings usually.

void wiBacklog_Post(const char *text);
void wiBacklog_Clear();
void wiBacklog_SetBackground(
    wiTexture *texture); // Texture type needed? or just pass generic?
// Wait, wiTexture is not exposed yet. Let's skip SetBackground for now or use
// opaque pointer.
void wiBacklog_SetFontSize(int value);
// void wiBacklog_SetFont(wiSpriteFont font); // skipping struct dep for now

#ifdef __cplusplus
}
#endif
