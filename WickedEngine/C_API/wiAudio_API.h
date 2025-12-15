#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum wiAudio_SubmixType {
  WI_AUDIO_SUBMIX_SOUNDEFFECT = 0,
  WI_AUDIO_SUBMIX_MUSIC = 1,
  WI_AUDIO_SUBMIX_USER0 = 2,
  WI_AUDIO_SUBMIX_USER1 = 3,
  WI_AUDIO_SUBMIX_COUNT = 4
} wiAudio_SubmixType;

typedef enum wiAudio_ReverbPreset {
  WI_AUDIO_REVERB_DEFAULT = 0,
  WI_AUDIO_REVERB_GENERIC = 1,
  WI_AUDIO_REVERB_FOREST =
      2, // ... others skipped for brevity, matching enum order
  WI_AUDIO_REVERB_CAVE = 10,
  WI_AUDIO_REVERB_UNDERWATER = 23,
  // Add full list if needed, essential ones for now
} wiAudio_ReverbPreset;

// Opaque types
typedef struct wiSound_t *wiSound;
typedef struct wiSoundInstance_t *wiSoundInstance;

// Sound
wiSound wiAudio_CreateSound(const char *filename);
wiSound wiAudio_CreateSoundFromData(const uint8_t *data, size_t size);
// Note: Sound destruction is handled by resource manager or we need a Release
// if we allocate wrapper? wiSound is likely a wrapper around Resource, or just
// the Resource pointer? In Lua binding: soundResource is stored. We should
// probably just return an opaque pointer to a new'd C++ object or use the
// Resource pointer. Since C API lacks C++ smart pointers, we might need manual
// management or stick to Resource Handles. For simplicity, let's treat wiSound
// as a handle. But we need a way to clean up if we alloc. If we return raw
// pointer to a struct we allocate, the user must free it.
void wiAudio_DestroySound(wiSound sound);

// SoundInstance
wiSoundInstance wiAudio_CreateSoundInstance(wiSound sound);
void wiAudio_DestroySoundInstance(wiSoundInstance instance);

// Playback
void wiAudio_Play(wiSoundInstance instance);
void wiAudio_Pause(wiSoundInstance instance);
void wiAudio_Stop(wiSoundInstance instance);
void wiAudio_ExitLoop(wiSoundInstance instance);
bool wiAudio_IsEnded(wiSoundInstance instance);

// Properties
void wiAudio_SetVolume(
    float volume, wiSoundInstance instance); // instance nullable for global?
                                             // No, C++ func has default nullptr
float wiAudio_GetVolume(wiSoundInstance instance);
void wiAudio_SetSubmixType(wiSoundInstance instance, wiAudio_SubmixType type);
void wiAudio_SetLooped(wiSoundInstance instance, bool looped);

// Global
void wiAudio_SetSubmixVolume(wiAudio_SubmixType type, float volume);
float wiAudio_GetSubmixVolume(wiAudio_SubmixType type);
void wiAudio_SetReverb(wiAudio_ReverbPreset preset);

#ifdef __cplusplus
}
#endif
