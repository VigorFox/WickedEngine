#include "wiAudio_API.h"
#include "wiAudio.h"
#include "wiResourceManager.h"

using namespace wi::audio;

struct wiSound_t {
  wi::Resource resource;
};

struct wiSoundInstance_t {
  SoundInstance instance;
};

extern "C" {

wiSound wiAudio_CreateSound(const char *filename) {
  wiSound_t *s = new wiSound_t();
  s->resource = wi::resourcemanager::Load(filename);
  if (!s->resource.IsValid()) {
    delete s;
    return nullptr;
  }
  return s;
}

// CreateSoundFromData requires slightly more complex handling as
// ResourceManager usually takes files. But wi::audio::CreateSound overload
// takes data. Creating a "Sound" struct directly not via Resource? The Lua
// binding uses SoundResource. wi::audio::CreateSound(data, size, &sound); This
// populates the Sound struct. We need to wrap that. Our wiSound_t uses
// wi::Resource to match the common usage, but direct Sound struct is also
// valid. Refactoring wiSound_t to hold Sound object directly might be better if
// we support raw data. But Load() returns Resource. Let's support file only for
// now as per Lua binding preference, or check if Lua supports data? Lua binding
// only `CreateSound(string)`. So we stick to file.

void wiAudio_DestroySound(wiSound sound) {
  if (sound)
    delete sound;
}

wiSoundInstance wiAudio_CreateSoundInstance(wiSound sound) {
  if (!sound || !sound->resource.IsValid())
    return nullptr;
  const Sound *s_internal = &sound->resource.GetSound();
  if (!s_internal->IsValid())
    return nullptr;

  wiSoundInstance_t *inst = new wiSoundInstance_t();
  if (CreateSoundInstance(s_internal, &inst->instance)) {
    return inst;
  }
  delete inst;
  return nullptr;
}

void wiAudio_DestroySoundInstance(wiSoundInstance instance) {
  if (instance)
    delete instance;
}

void wiAudio_Play(wiSoundInstance instance) {
  if (instance)
    Play(&instance->instance);
}

void wiAudio_Pause(wiSoundInstance instance) {
  if (instance)
    Pause(&instance->instance);
}

void wiAudio_Stop(wiSoundInstance instance) {
  if (instance)
    Stop(&instance->instance);
}

void wiAudio_ExitLoop(wiSoundInstance instance) {
  if (instance)
    ExitLoop(&instance->instance);
}

bool wiAudio_IsEnded(wiSoundInstance instance) {
  if (instance)
    return IsEnded(&instance->instance);
  return true;
}

void wiAudio_SetVolume(float volume, wiSoundInstance instance) {
  SetVolume(volume, instance ? &instance->instance : nullptr);
}

float wiAudio_GetVolume(wiSoundInstance instance) {
  return GetVolume(instance ? &instance->instance : nullptr);
}

void wiAudio_SetSubmixType(wiSoundInstance instance, wiAudio_SubmixType type) {
  if (instance)
    instance->instance.type = (SUBMIX_TYPE)type;
}

void wiAudio_SetLooped(wiSoundInstance instance, bool looped) {
  if (instance)
    instance->instance.SetLooped(looped);
}

void wiAudio_SetSubmixVolume(wiAudio_SubmixType type, float volume) {
  SetSubmixVolume((SUBMIX_TYPE)type, volume);
}

float wiAudio_GetSubmixVolume(wiAudio_SubmixType type) {
  return GetSubmixVolume((SUBMIX_TYPE)type);
}

void wiAudio_SetReverb(wiAudio_ReverbPreset preset) {
  SetReverb((REVERB_PRESET)preset);
}

} // extern "C"
