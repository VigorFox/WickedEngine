#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

// Vector API
wiVector wiVector_Create(float x, float y, float z, float w);
float wiVector_GetX(wiVector v);
float wiVector_GetY(wiVector v);
float wiVector_GetZ(wiVector v);
float wiVector_GetW(wiVector v);

wiVector wiVector_Add(wiVector v1, wiVector v2);
wiVector wiVector_Subtract(wiVector v1, wiVector v2);
wiVector wiVector_Multiply(wiVector v1, wiVector v2);
wiVector wiVector_Scale(wiVector v, float scale);
float wiVector_Dot(wiVector v1, wiVector v2);
wiVector wiVector_Cross(wiVector v1, wiVector v2);
wiVector wiVector_Normalize(wiVector v);
float wiVector_Length(wiVector v);
float wiVector_Distance(wiVector v1, wiVector v2);

// Matrix API
wiMatrix wiMatrix_Identity();
wiMatrix wiMatrix_Translation(wiVector v);
wiMatrix wiMatrix_Rotation(wiVector v); // Roll Pitch Yaw
wiMatrix wiMatrix_Scale(wiVector v);
wiMatrix wiMatrix_Multiply(wiMatrix m1, wiMatrix m2);
wiMatrix wiMatrix_Transpose(wiMatrix m);
wiMatrix wiMatrix_Inverse(wiMatrix m);

#ifdef __cplusplus
}
#endif
