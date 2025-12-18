#ifndef WI_TYPEDEFS_H
#define WI_TYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiVector_t {
  float x, y, z, w;
} wiVector;

typedef struct wiMatrix_t {
  float data[4][4];
} wiMatrix;

#ifdef __cplusplus
}
#endif

#endif // WI_TYPEDEFS_H
