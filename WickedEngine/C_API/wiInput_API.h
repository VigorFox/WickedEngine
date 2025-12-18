#pragma once
#include "wiMath_API.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Constants directly mirrored from wiInput.h
// Note: We prepend WI_INPUT_ to avoid collisions
typedef enum wiInput_Button {
  WI_INPUT_BUTTON_NONE = 0,

  // Keyboard digits/letters reserved ranges skipped for brevity, mapping direct
  // codes if needed Assuming standard usage via helper functions or direct
  // casts if header matches But for C API we often want explicit enums.

  WI_INPUT_GAMEPAD_BUTTON_UP =
      21, // Mapped to internal IDs if they match, or we need conversion map
  // Actually, wiInput.h enums are specific integers.
  // Let's rely on the user passing integers or provide a specific set of
  // commonly used ones.

  // Simplification: Allow user to pass integer codes, but provide useful
  // constants. We will assume the user has access to these constants.

  WI_INPUT_MOUSE_BUTTON_LEFT = 85,
  WI_INPUT_MOUSE_BUTTON_RIGHT = 86,
  WI_INPUT_MOUSE_BUTTON_MIDDLE = 87,

  WI_INPUT_KEYBOARD_BUTTON_UP = 93,
  WI_INPUT_KEYBOARD_BUTTON_DOWN = 94,
  WI_INPUT_KEYBOARD_BUTTON_LEFT = 95,
  WI_INPUT_KEYBOARD_BUTTON_RIGHT = 96,
  WI_INPUT_KEYBOARD_BUTTON_SPACE = 97,
  WI_INPUT_KEYBOARD_BUTTON_ESCAPE = 113,
  WI_INPUT_KEYBOARD_BUTTON_ENTER = 112,
} wiInput_Button;

typedef enum wiInput_GamepadAnalog {
  WI_INPUT_GAMEPAD_ANALOG_THUMBSTICK_L = 0,
  WI_INPUT_GAMEPAD_ANALOG_THUMBSTICK_R = 1,
  WI_INPUT_GAMEPAD_ANALOG_TRIGGER_L = 2,
  WI_INPUT_GAMEPAD_ANALOG_TRIGGER_R = 3,
} wiInput_GamepadAnalog;

typedef struct wiInput_ControllerFeedback_t {
  float vibration_left;
  float vibration_right;
  wiColor led_color;
} wiInput_ControllerFeedback;

// Functions
bool wiInput_Down(int button, int playerindex);
bool wiInput_Press(int button, int playerindex);
bool wiInput_Release(int button, int playerindex);
bool wiInput_Hold(int button, uint32_t frames, bool continuous,
                  int playerIndex);

wiVector wiInput_GetPointer();
void wiInput_SetPointer(wiVector props);
void wiInput_HidePointer(bool value);

wiVector wiInput_GetAnalog(wiInput_GamepadAnalog analog, int playerIndex);
void wiInput_SetControllerFeedback(wiInput_ControllerFeedback output,
                                   int playerindex);

#ifdef __cplusplus
}
#endif
