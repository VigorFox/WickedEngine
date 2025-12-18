#include "wiLoadingScreen_API.h"
#include "../wiLoadingScreen.h"
#include "../wiScene.h"
#include <mutex>

using namespace wi;

extern "C" {

wiLoadingScreen wiLoadingScreen_Create(void) {
  return (wiLoadingScreen) new LoadingScreen();
}

void wiLoadingScreen_Destroy(wiLoadingScreen loadingScreen) {
  if (loadingScreen) {
    delete ((LoadingScreen *)loadingScreen);
  }
}

void wiLoadingScreen_Start(wiLoadingScreen loadingScreen) {
  if (loadingScreen) {
    ((LoadingScreen *)loadingScreen)->Start();
  }
}

void wiLoadingScreen_AddLoadModelTask(wiLoadingScreen loadingScreen,
                                      const char *fileName) {
  if (loadingScreen && fileName) {
    LoadingScreen *loading = (LoadingScreen *)loadingScreen;
    std::string file = fileName;
    // Helper to load into global scene
    loading->addLoadingFunction([file](wi::jobsystem::JobArgs args) {
      wi::scene::Scene scene;             // Local temporary scene
      wi::scene::LoadModel2(scene, file); // Load into temp scene

      // Merchant merge into global
      // Note: locking global scene is good practice here
      std::scoped_lock lck(wi::scene::GetScene().locker);
      wi::scene::GetScene().Merge(scene);
    });
  }
}

void wiLoadingScreen_AddLoadModelTaskToScene(wiLoadingScreen loadingScreen,
                                             wiScene scene,
                                             const char *fileName) {
  if (loadingScreen && scene && fileName) {
    LoadingScreen *loading = (LoadingScreen *)loadingScreen;
    wi::scene::Scene *targetScene = (wi::scene::Scene *)scene;
    std::string file = fileName;

    loading->addLoadingFunction(
        [file, targetScene](wi::jobsystem::JobArgs args) {
          wi::scene::Scene tempScene;
          wi::scene::LoadModel2(tempScene, file);

          std::scoped_lock lck(targetScene->locker);
          targetScene->Merge(tempScene);
        });
  }
}

bool wiLoadingScreen_IsFinished(wiLoadingScreen loadingScreen) {
  if (loadingScreen) {
    return ((LoadingScreen *)loadingScreen)->isFinished();
  }
  return true; // If null, considered finished/inactive
}

int wiLoadingScreen_GetProgress(wiLoadingScreen loadingScreen) {
  if (loadingScreen) {
    return ((LoadingScreen *)loadingScreen)->getProgress();
  }
  return 100;
}

void wiLoadingScreen_SetBackgroundTexture(wiLoadingScreen loadingScreen,
                                          wiTexture texture) {
  if (loadingScreen && texture) {
    // texture is wi::Resource*
    ((LoadingScreen *)loadingScreen)->backgroundTexture =
        *((wi::Resource *)texture);
  }
}
}
