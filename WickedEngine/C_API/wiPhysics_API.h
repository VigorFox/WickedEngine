#pragma once
#include "wiC_API.h"
#include "wiPrimitive_API.h"
#include "wiScene_API.h"

#ifdef __cplusplus
extern "C" {
#endif

// --- Global Physics Settings ---
void wiPhysics_Initialize(void);
void wiPhysics_SetEnabled(bool value);
bool wiPhysics_IsEnabled(void);

void wiPhysics_SetSimulationEnabled(bool value);
bool wiPhysics_IsSimulationEnabled(void);

void wiPhysics_SetInterpolationEnabled(bool value);
bool wiPhysics_IsInterpolationEnabled(void);

void wiPhysics_SetDebugDrawEnabled(bool value);
bool wiPhysics_IsDebugDrawEnabled(void);

void wiPhysics_SetAccuracy(int value);
int wiPhysics_GetAccuracy(void);

void wiPhysics_SetFrameRate(float value);
float wiPhysics_GetFrameRate(void);

// --- Rigid Body Physics Component Manipulation ---
// Note: These functions operate on a wiRigidBodyPhysicsComponent handle.
// You must get this handle from the scene
// (wiScene_Component_GetRigidBodyPhysics).

void wiPhysics_RigidBody_SetPosition(wiRigidBodyPhysicsComponent component,
                                     wiVector position);
void wiPhysics_RigidBody_SetPositionAndRotation(
    wiRigidBodyPhysicsComponent component, wiVector position,
    wiVector rotation);
void wiPhysics_RigidBody_SetLinearVelocity(
    wiRigidBodyPhysicsComponent component, wiVector velocity);
void wiPhysics_RigidBody_SetAngularVelocity(
    wiRigidBodyPhysicsComponent component, wiVector velocity);
void wiPhysics_RigidBody_ApplyForce(wiRigidBodyPhysicsComponent component,
                                    wiVector force);
void wiPhysics_RigidBody_ApplyForceAt(wiRigidBodyPhysicsComponent component,
                                      wiVector force, wiVector position);
void wiPhysics_RigidBody_ApplyImpulse(wiRigidBodyPhysicsComponent component,
                                      wiVector impulse);
void wiPhysics_RigidBody_ApplyImpulseAt(wiRigidBodyPhysicsComponent component,
                                        wiVector impulse, wiVector position);
void wiPhysics_RigidBody_ApplyTorque(wiRigidBodyPhysicsComponent component,
                                     wiVector torque);
void wiPhysics_RigidBody_Activate(wiRigidBodyPhysicsComponent component);
void wiPhysics_RigidBody_Deactivate(wiRigidBodyPhysicsComponent component);

wiVector wiPhysics_RigidBody_GetVelocity(wiRigidBodyPhysicsComponent component);
wiVector wiPhysics_RigidBody_GetPosition(wiRigidBodyPhysicsComponent component);
wiVector wiPhysics_RigidBody_GetRotation(wiRigidBodyPhysicsComponent component);

// --- Ray Casting ---
typedef struct wiRayIntersectionResult {
  wiEntity entity;
  wiVector position;
  wiVector normal;
  float distance;
  bool hit;
} wiRayIntersectionResult;

// Casts a ray in the physics world. Returns the first hit.
wiRayIntersectionResult wiPhysics_RayIntersect(wiRay ray);

#ifdef __cplusplus
}
#endif
