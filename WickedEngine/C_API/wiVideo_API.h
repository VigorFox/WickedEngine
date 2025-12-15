#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiVideo_t *wiVideo;
typedef struct wiVideoInstance_t *wiVideoInstance;

// --- wiVideo ---
wiVideo wiVideo_Load(const char *filename);
void wiVideo_Destroy(wiVideo video);
bool wiVideo_IsValid(wiVideo video);
float wiVideo_GetDuration(wiVideo video);

// --- wiVideoInstance ---
wiVideoInstance wiVideoInstance_Create(wiVideo video);
void wiVideoInstance_Destroy(wiVideoInstance instance);

bool wiVideoInstance_IsValid(wiVideoInstance instance);
void wiVideoInstance_Play(wiVideoInstance instance);
void wiVideoInstance_Pause(wiVideoInstance instance);
void wiVideoInstance_Stop(wiVideoInstance instance);
void wiVideoInstance_SetLooped(wiVideoInstance instance, bool looped);
void wiVideoInstance_Seek(wiVideoInstance instance, float time);
float wiVideoInstance_GetCurrentTime(wiVideoInstance instance);
bool wiVideoInstance_IsEnded(wiVideoInstance instance);

#ifdef __cplusplus
}
#endif
