#include "wiVideo_API.h"
#include "../wiResourceManager.h"
#include "../wiVideo.h"

using namespace wi::video;

extern "C" {

// --- wiVideo ---
// wiVideo wraps wi::Resource
wiVideo wiVideo_Load(const char *filename) {
  if (!filename)
    return nullptr;
  wi::Resource *res = new wi::Resource();
  *res = wi::resourcemanager::Load(filename);
  return (wiVideo)res;
}

// Helper to clean up the resource wrapper if we decide to expose it.
// Plan didn't specifying destroying wiVideo (Resource), but usually Resources
// are managed. If we allocate 'new wi::Resource', we should delete it.
void wiVideo_Destroy(wiVideo video) {
  if (video)
    delete (wi::Resource *)video;
}

bool wiVideo_IsValid(wiVideo video) {
  if (!video)
    return false;
  wi::Resource *res = (wi::Resource *)video;
  return res->IsValid() && res->GetVideo().IsValid();
}

float wiVideo_GetDuration(wiVideo video) {
  if (!wiVideo_IsValid(video))
    return 0.0f;
  return ((wi::Resource *)video)->GetVideo().duration_seconds;
}

// --- wiVideoInstance ---
wiVideoInstance wiVideoInstance_Create(wiVideo video) {
  if (!wiVideo_IsValid(video))
    return nullptr;
  VideoInstance *instance = new VideoInstance();
  const Video &v = ((wi::Resource *)video)->GetVideo();
  CreateVideoInstance(&v, instance);
  return (wiVideoInstance)instance;
}

void wiVideoInstance_Destroy(wiVideoInstance instance) {
  if (instance)
    delete (VideoInstance *)instance;
}

bool wiVideoInstance_IsValid(wiVideoInstance instance) {
  if (!instance)
    return false;
  return ((VideoInstance *)instance)->IsValid();
}

void wiVideoInstance_Play(wiVideoInstance instance) {
  if (instance)
    ((VideoInstance *)instance)->flags |= VideoInstance::Flags::Playing;
}

void wiVideoInstance_Pause(wiVideoInstance instance) {
  if (instance)
    ((VideoInstance *)instance)->flags &= ~VideoInstance::Flags::Playing;
}

void wiVideoInstance_Stop(wiVideoInstance instance) {
  if (instance) {
    ((VideoInstance *)instance)->flags &= ~VideoInstance::Flags::Playing;
    Seek((VideoInstance *)instance, 0);
  }
}

void wiVideoInstance_SetLooped(wiVideoInstance instance, bool looped) {
  if (instance) {
    if (looped)
      ((VideoInstance *)instance)->flags |= VideoInstance::Flags::Looped;
    else
      ((VideoInstance *)instance)->flags &= ~VideoInstance::Flags::Looped;
  }
}

void wiVideoInstance_Seek(wiVideoInstance instance, float time) {
  if (instance)
    Seek((VideoInstance *)instance, time);
}

float wiVideoInstance_GetCurrentTime(wiVideoInstance instance) {
  if (instance)
    return ((VideoInstance *)instance)->current_time;
  return 0.0f;
}

bool wiVideoInstance_IsEnded(wiVideoInstance instance) {
  if (!instance)
    return true;
  auto *inst = (VideoInstance *)instance;
  return inst->video && inst->current_time >= inst->video->duration_seconds;
}

} // extern "C"
