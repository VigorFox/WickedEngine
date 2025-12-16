#include "wiPhysics_API.h"
#include "../wiHelper.h"
#include "../wiJobSystem.h"
#include "../wiPhysics.h"
#include "../wiScene.h"

using namespace wi::physics;
using namespace wi::scene;
using namespace DirectX;

extern "C" {

void wiPhysics_Initialize(void) {
  wi::jobsystem::Initialize();
  wi::physics::Initialize();
}

// --- Global Physics Settings ---
void wiPhysics_SetEnabled(bool value) { SetEnabled(value); }

bool wiPhysics_IsEnabled(void) { return IsEnabled(); }

void wiPhysics_SetSimulationEnabled(bool value) { SetSimulationEnabled(value); }

bool wiPhysics_IsSimulationEnabled(void) { return IsSimulationEnabled(); }

void wiPhysics_SetInterpolationEnabled(bool value) {
  SetInterpolationEnabled(value);
}

bool wiPhysics_IsInterpolationEnabled(void) { return IsInterpolationEnabled(); }

void wiPhysics_SetDebugDrawEnabled(bool value) { SetDebugDrawEnabled(value); }

bool wiPhysics_IsDebugDrawEnabled(void) { return IsDebugDrawEnabled(); }

void wiPhysics_SetAccuracy(int value) { SetAccuracy(value); }

int wiPhysics_GetAccuracy(void) { return GetAccuracy(); }

void wiPhysics_SetFrameRate(float value) { SetFrameRate(value); }

float wiPhysics_GetFrameRate(void) { return GetFrameRate(); }

// --- Rigid Body Physics Component Manipulation ---

// --- Rigid Body Physics Component Manipulation ---

void wiPhysics_RigidBody_SetPosition(wiRigidBodyPhysicsComponent component,
                                     wiVector position) {
  if (component) {
    SetPosition(*(RigidBodyPhysicsComponent *)component,
                XMFLOAT3(position.x, position.y, position.z));
  }
}

void wiPhysics_RigidBody_SetPositionAndRotation(
    wiRigidBodyPhysicsComponent component, wiVector position,
    wiVector rotation) {
  if (component) {
    SetPositionAndRotation(
        *(RigidBodyPhysicsComponent *)component,
        XMFLOAT3(position.x, position.y, position.z),
        XMFLOAT4(rotation.x, rotation.y, rotation.z, rotation.w));
  }
}

void wiPhysics_RigidBody_SetLinearVelocity(
    wiRigidBodyPhysicsComponent component, wiVector velocity) {
  if (component) {
    SetLinearVelocity(*(RigidBodyPhysicsComponent *)component,
                      XMFLOAT3(velocity.x, velocity.y, velocity.z));
  }
}

void wiPhysics_RigidBody_SetAngularVelocity(
    wiRigidBodyPhysicsComponent component, wiVector velocity) {
  if (component) {
    SetAngularVelocity(*(RigidBodyPhysicsComponent *)component,
                       XMFLOAT3(velocity.x, velocity.y, velocity.z));
  }
}

void wiPhysics_RigidBody_ApplyForce(wiRigidBodyPhysicsComponent component,
                                    wiVector force) {
  if (component) {
    ApplyForce(*(RigidBodyPhysicsComponent *)component,
               XMFLOAT3(force.x, force.y, force.z));
  }
}

void wiPhysics_RigidBody_ApplyForceAt(wiRigidBodyPhysicsComponent component,
                                      wiVector force, wiVector position) {
  if (component) {
    ApplyForceAt(*(RigidBodyPhysicsComponent *)component,
                 XMFLOAT3(force.x, force.y, force.z),
                 XMFLOAT3(position.x, position.y, position.z));
  }
}

void wiPhysics_RigidBody_ApplyImpulse(wiRigidBodyPhysicsComponent component,
                                      wiVector impulse) {
  if (component) {
    ApplyImpulse(*(RigidBodyPhysicsComponent *)component,
                 XMFLOAT3(impulse.x, impulse.y, impulse.z));
  }
}

void wiPhysics_RigidBody_ApplyImpulseAt(wiRigidBodyPhysicsComponent component,
                                        wiVector impulse, wiVector position) {
  if (component) {
    ApplyImpulseAt(*(RigidBodyPhysicsComponent *)component,
                   XMFLOAT3(impulse.x, impulse.y, impulse.z),
                   XMFLOAT3(position.x, position.y, position.z));
  }
}

void wiPhysics_RigidBody_ApplyTorque(wiRigidBodyPhysicsComponent component,
                                     wiVector torque) {
  if (component) {
    ApplyTorque(*(RigidBodyPhysicsComponent *)component,
                XMFLOAT3(torque.x, torque.y, torque.z));
  }
}

void wiPhysics_RigidBody_Activate(wiRigidBodyPhysicsComponent component) {
  if (component) {
    SetActivationState(*(RigidBodyPhysicsComponent *)component,
                       ActivationState::Active);
  }
}

void wiPhysics_RigidBody_Deactivate(wiRigidBodyPhysicsComponent component) {
  if (component) {
    SetActivationState(*(RigidBodyPhysicsComponent *)component,
                       ActivationState::Inactive);
  }
}

wiVector
wiPhysics_RigidBody_GetVelocity(wiRigidBodyPhysicsComponent component) {
  wiVector vec = {0, 0, 0, 0};
  if (component) {
    XMFLOAT3 v = GetVelocity(*(RigidBodyPhysicsComponent *)component);
    vec.x = v.x;
    vec.y = v.y;
    vec.z = v.z;
  }
  return vec;
}

wiVector
wiPhysics_RigidBody_GetPosition(wiRigidBodyPhysicsComponent component) {
  wiVector vec = {0, 0, 0, 0};
  if (component) {
    XMFLOAT3 v = GetPosition(*(RigidBodyPhysicsComponent *)component);
    vec.x = v.x;
    vec.y = v.y;
    vec.z = v.z;
  }
  return vec;
}

wiVector
wiPhysics_RigidBody_GetRotation(wiRigidBodyPhysicsComponent component) {
  wiVector vec = {0, 0, 0, 1};
  if (component) {
    XMFLOAT4 v = GetRotation(*(RigidBodyPhysicsComponent *)component);
    vec.x = v.x;
    vec.y = v.y;
    vec.z = v.z;
    vec.w = v.w;
  }
  return vec;
}

// --- Ray Casting ---

wiRayIntersectionResult wiPhysics_RayIntersect(wiRay ray) {
  wiRayIntersectionResult result = {0};
  result.entity = WI_INVALID_ENTITY;

  wi::primitive::Ray primitivesRay;
  primitivesRay.origin = XMFLOAT3(ray.origin.x, ray.origin.y, ray.origin.z);
  primitivesRay.direction =
      XMFLOAT3(ray.direction.x, ray.direction.y, ray.direction.z);

  wi::physics::RayIntersectionResult physicsResult =
      wi::physics::Intersects(wi::scene::GetScene(), primitivesRay);

  if (physicsResult.IsValid()) {
    result.hit = true;
    result.entity = (wiEntity)physicsResult.entity;

    result.position.x = physicsResult.position.x;
    result.position.y = physicsResult.position.y;
    result.position.z = physicsResult.position.z;

    result.normal.x = physicsResult.normal.x;
    result.normal.y = physicsResult.normal.y;
    result.normal.z = physicsResult.normal.z;

    // Calculate distance
    XMVECTOR O = XMLoadFloat3(&primitivesRay.origin);
    XMVECTOR P = XMLoadFloat3(&physicsResult.position);
    result.distance = XMVectorGetX(XMVector3Length(P - O));
  } else {
    result.hit = false;
  }
  return result;
}

} // extern "C"
