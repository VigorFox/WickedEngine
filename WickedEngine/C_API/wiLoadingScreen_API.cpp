#include "wiLoadingScreen_API.h"
#include "../wiECS.h"
#include "../wiHelper.h"
#include "../wiLoadingScreen.h"
#include "../wiScene.h"
#include <mutex>

using namespace wi;
using namespace wi::ecs;
using namespace wi::scene;

extern "C" {

wiLoadingScreen wiLoadingScreen_Create() {
  return (wiLoadingScreen) new LoadingScreen();
}

void wiLoadingScreen_Destroy(wiLoadingScreen screen) {
  if (screen)
    delete (LoadingScreen *)screen;
}

wiRenderPath2D wiLoadingScreen_AsRenderPath2D(wiLoadingScreen screen) {
  return (wiRenderPath2D)screen;
}

struct wiRenderPath_t *wiLoadingScreen_AsRenderPath(wiLoadingScreen screen) {
  return (struct wiRenderPath_t *)screen;
}

void wiLoadingScreen_AddLoadModelTask(wiLoadingScreen screen,
                                      const char *fileName,
                                      wiMatrix transform) {
  if (!screen || !fileName)
    return;
  LoadingScreen *loading = (LoadingScreen *)screen;

  Entity root = CreateEntity();
  XMMATRIX mat = XMLoadFloat4x4((XMFLOAT4X4 *)&transform);
  std::string fname = fileName;

  loading->addLoadingFunction([=](wi::jobsystem::JobArgs args) {
    Scene scene;
    wi::scene::LoadModel2(scene, fname, mat, root);
    std::scoped_lock lck(wi::scene::GetScene().locker);
    wi::scene::GetScene().Merge(scene);
  });
}

// Function removed due to compilation issues with parameter resolution in C API
// void wiLoadingScreen_AddRenderPathActivationTask(...)

bool wiLoadingScreen_IsFinished(wiLoadingScreen screen) {
  if (!screen)
    return false;
  return ((LoadingScreen *)screen)->isFinished();
}

int wiLoadingScreen_GetProgress(wiLoadingScreen screen) {
  if (!screen)
    return 0;
  return ((LoadingScreen *)screen)->getProgress();
}

void wiLoadingScreen_SetBackgroundTexture(wiLoadingScreen screen,
                                          wiTexture texture) {
  if (screen && texture) {
    wi::graphics::Texture tex = ((wi::Resource *)texture)->GetTexture();
    ((LoadingScreen *)screen)->backgroundTexture.SetTexture(tex);
  }
}

wiTexture wiLoadingScreen_GetBackgroundTexture(wiLoadingScreen screen) {
  if (!screen)
    return nullptr;
  return (wiTexture) & ((LoadingScreen *)screen)->backgroundTexture;
}

void wiLoadingScreen_SetBackgroundMode(wiLoadingScreen screen, int mode) {
  if (screen)
    ((LoadingScreen *)screen)->background_mode =
        (LoadingScreen::BackgroundMode)mode;
}

int wiLoadingScreen_GetBackgroundMode(wiLoadingScreen screen) {
  if (!screen)
    return 0;
  return (int)((LoadingScreen *)screen)->background_mode;
}

} // extern "C"
