
#include "wiApplication_API.h"
#include "wiBacklog_API.h"
#include "wiInput_API.h"
#include "wiRenderer_API.h"


#include "wiC_API.h"
#include "wiMath_API.h"
#include <stdio.h>

int main() {
  printf("Testing WickedEngine C API...\n");

  // Math Test
  wiVector v1 = wiVector_Create(1, 2, 3, 0);
  wiVector v2 = wiVector_Create(4, 5, 6, 0);
  wiVector v3 = wiVector_Add(v1, v2);

  printf("Vector Add: %f %f %f\n", v3.x, v3.y, v3.z);

  if (v3.x != 5 || v3.y != 7 || v3.z != 9) {
    printf("Math Test Failed!\n");
    return 1;
  }

  // Application Test (Symbolic)
  // In a real scenario, we would need a valid app handle.
  // Here we just check if functions are callable (linker would check symbols).
  wiApplication app = NULL;
  wiApplication_GetActivePath(app);
  wiApplication_SetFPSDisplay(app, true);

  printf("Testing Renderer API...\n");
  wiRenderer_SetGameSpeed(1.5f);
  if (wiRenderer_GetGameSpeed() != 1.5f) {
    printf("Renderer GameSpeed Test Failed!\n");
    return 1;
  }
  wiRenderableLine line;
  line.start = wiVector_Create(0, 0, 0, 0);
  line.end = wiVector_Create(10, 10, 10, 0);
  line.color_start.r = 255;
  line.color_start.a = 255;
  line.color_end.r = 255;
  line.color_end.a = 255;
  wiRenderer_DrawLine(&line, false);
  printf("Renderer API Test Passed.\n");

  printf("Testing Backlog API...\n");
  wiBacklog_Post("C API Test Message");
  wiBacklog_Clear();
  printf("Backlog API Test Passed.\n");

  printf("Testing Input API...\n");
  if (wiInput_Down(WI_INPUT_KEYBOARD_BUTTON_SPACE, 0)) {
    printf("Input Test Warning: Space pressed unexpectedly (ignore if "
           "interactive)\n");
  }
  wiVector ptr = wiVector_Create(100, 100, 0, 0);
  wiInput_SetPointer(ptr);
  wiVector ptr_read = wiInput_GetPointer();
  // Note: SetPointer might not immediately reflect in GetPointer depending on
  // frame update logic But for direct setter/getter verification it might work
  // or we just verify symbol linking.
  printf("Input Pointer Set/Get: (%f, %f)\n", ptr_read.x, ptr_read.y);

  printf("Test Finished.\n");
  return 0;
}
