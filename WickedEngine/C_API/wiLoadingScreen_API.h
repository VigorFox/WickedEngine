#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiLoadingScreen_t *wiLoadingScreen;
typedef struct wiScene_t *wiScene;

// Lifecycle
wiLoadingScreen wiLoadingScreen_Create(void);
void wiLoadingScreen_Destroy(wiLoadingScreen loadingScreen);

// Start the loading screen (activates it)
void wiLoadingScreen_Start(wiLoadingScreen loadingScreen);

// Task Management
// Adds a task to load a model file into the global scene
void wiLoadingScreen_AddLoadModelTask(wiLoadingScreen loadingScreen,
                                      const char *fileName);
// Adds a task to load a model file into a specific scene
void wiLoadingScreen_AddLoadModelTaskToScene(wiLoadingScreen loadingScreen,
                                             wiScene scene,
                                             const char *fileName);

// Status
bool wiLoadingScreen_IsFinished(wiLoadingScreen loadingScreen);
int wiLoadingScreen_GetProgress(wiLoadingScreen loadingScreen);

// Customization
void wiLoadingScreen_SetBackgroundTexture(wiLoadingScreen loadingScreen,
                                          wiTexture texture);

#ifdef __cplusplus
}
#endif
