#pragma once
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Common Types
typedef struct wiApplication_t *wiApplication;
typedef struct wiCanvas_t *wiCanvas;
typedef struct wiRenderPath_t *wiRenderPath;
typedef struct wiRenderPath2D_t *wiRenderPath2D;
typedef struct wiRenderPath3D_t *wiRenderPath3D;
typedef struct wiLoadingScreen_t *wiLoadingScreen;
typedef struct wiTexture_t *wiTexture;

// Math Types
typedef struct wiVector {
  float x, y, z, w;
} wiVector;

typedef struct wiMatrix {
  float m[4][4];
} wiMatrix;

typedef struct wiColor {
  uint8_t r, g, b, a;
} wiColor;

// Enums
typedef enum wiFadeType {
  wiFadeType_FadeToColor = 0,
  wiFadeType_CrossFade = 1,
} wiFadeType;

#ifdef __cplusplus
}
#endif
