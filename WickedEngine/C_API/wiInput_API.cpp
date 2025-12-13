#include "wiInput_API.h"
#include "wiInput.h"

using namespace wi::input;

extern "C" {

bool wiInput_Down(int button, int playerindex) {
  return Down((BUTTON)button, playerindex);
}

bool wiInput_Press(int button, int playerindex) {
  return Press((BUTTON)button, playerindex);
}

bool wiInput_Release(int button, int playerindex) {
  return Release((BUTTON)button, playerindex);
}

bool wiInput_Hold(int button, uint32_t frames, bool continuous,
                  int playerIndex) {
  return Hold((BUTTON)button, frames, continuous, playerIndex);
}

wiVector wiInput_GetPointer() {
  XMFLOAT4 p = GetPointer();
  wiVector v;
  v.x = p.x;
  v.y = p.y;
  v.z = p.z;
  v.w = p.w;
  return v;
}

void wiInput_SetPointer(wiVector props) {
  SetPointer(XMFLOAT4(props.x, props.y, props.z, props.w));
}

void wiInput_HidePointer(bool value) { HidePointer(value); }

wiVector wiInput_GetAnalog(wiInput_GamepadAnalog analog, int playerIndex) {
  XMFLOAT4 a = GetAnalog((GAMEPAD_ANALOG)analog, playerIndex);
  wiVector v;
  v.x = a.x;
  v.y = a.y;
  v.z = a.z;
  v.w = a.w;
  return v;
}

void wiInput_SetControllerFeedback(wiInput_ControllerFeedback output,
                                   int playerindex) {
  ControllerFeedback fb;
  fb.vibration_left = output.vibration_left;
  fb.vibration_right = output.vibration_right;
  fb.led_color = wi::Color(output.led_color.r, output.led_color.g,
                           output.led_color.b, output.led_color.a);
  SetControllerFeedback(fb, playerindex);
}

} // extern "C"
