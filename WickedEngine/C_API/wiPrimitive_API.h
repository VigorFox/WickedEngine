#pragma once
#include "wiC_API.h"
#include "wiMath_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiRay {
  wiVector origin;
  wiVector direction;
  float TMin;
  float TMax;
} wiRay;

typedef struct wiAABB {
  wiVector _min;
  wiVector _max;
} wiAABB;

typedef struct wiSphere {
  wiVector center;
  float radius;
} wiSphere;

typedef struct wiCapsule {
  wiVector base;
  wiVector tip;
  float radius;
} wiCapsule;

// Ray methods
wiRay wiRay_Create(wiVector origin, wiVector direction);
wiRay wiRay_CreateFromPoints(wiVector a, wiVector b);
bool wiRay_IntersectsAABB(wiRay ray, wiAABB aabb);
bool wiRay_IntersectsSphere(wiRay ray, wiSphere sphere);
bool wiRay_IntersectsCapsule(wiRay ray, wiCapsule capsule);
wiVector wiRay_IntersectsPlane(wiRay ray, wiVector planePoint,
                               wiVector planeNormal);

// AABB methods
wiAABB wiAABB_Create(wiVector min, wiVector max);
bool wiAABB_Intersects(wiAABB aabb, wiAABB other);
bool wiAABB_IntersectsSphere(wiAABB aabb, wiSphere sphere);
bool wiAABB_IntersectsRay(wiAABB aabb, wiRay ray);
wiVector wiAABB_GetCenter(wiAABB aabb);
wiVector wiAABB_GetHalfExtents(wiAABB aabb);

// Sphere methods
wiSphere wiSphere_Create(wiVector center, float radius);
bool wiSphere_Intersects(wiSphere sphere, wiSphere other);
bool wiSphere_IntersectsAABB(wiSphere sphere, wiAABB aabb);
bool wiSphere_IntersectsCapsule(wiSphere sphere, wiCapsule capsule);
bool wiSphere_IntersectsRay(wiSphere sphere, wiRay ray);

// Capsule methods
wiCapsule wiCapsule_Create(wiVector base, wiVector tip, float radius);
bool wiCapsule_Intersects(wiCapsule capsule, wiCapsule other,
                          wiVector *position, wiVector *normal, float *depth);
bool wiCapsule_IntersectsSphere(wiCapsule capsule, wiSphere sphere,
                                float *depth, wiVector *normal);
bool wiCapsule_IntersectsRay(wiCapsule capsule, wiRay ray);
wiAABB wiCapsule_GetAABB(wiCapsule capsule);

#ifdef __cplusplus
}
#endif
