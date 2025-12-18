#pragma once
#include "wiMath_API.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Handles
typedef struct wiScene_t *wiScene;
typedef uint32_t wiEntity; // wi::ecs::Entity is uint32_t
#define WI_INVALID_ENTITY 0

typedef struct wiNameComponent_t *wiNameComponent;
typedef struct wiLayerComponent_t *wiLayerComponent;
typedef struct wiTransformComponent_t *wiTransformComponent;

typedef struct wiMeshComponent_t *wiMeshComponent;
typedef struct wiMaterialComponent_t *wiMaterialComponent;
typedef struct wiObjectComponent_t *wiObjectComponent;
typedef struct wiLightComponent_t *wiLightComponent;
typedef struct wiCameraComponent_t *wiCameraComponent;

typedef struct wiRigidBodyPhysicsComponent_t *wiRigidBodyPhysicsComponent;
typedef struct wiSoftBodyPhysicsComponent_t *wiSoftBodyPhysicsComponent;
typedef struct wiForceFieldComponent_t *wiForceFieldComponent;
typedef struct wiWeatherComponent_t *wiWeatherComponent;
typedef struct wiAnimationComponent_t *wiAnimationComponent;

// --- wiScene ---
wiScene wiScene_GetGlobal();
void wiScene_Update(wiScene scene, float dt);
void wiScene_Clear(wiScene scene);
void wiScene_Merge(wiScene scene, wiScene other);

// --- Entity Management ---
wiEntity wiScene_Entity_Create(wiScene scene);
void wiScene_Entity_Remove(wiScene scene, wiEntity entity);
wiEntity wiScene_Entity_Duplicate(wiScene scene, wiEntity entity);
bool wiScene_Entity_IsDescendant(wiScene scene, wiEntity entity,
                                 wiEntity ancestor);
wiEntity wiScene_Entity_FindByName(wiScene scene, const char *name,
                                   wiEntity ancestor);

// --- Component: Name ---
wiNameComponent wiScene_Component_CreateName(wiScene scene, wiEntity entity);
wiNameComponent wiScene_Component_GetName(wiScene scene, wiEntity entity);
void wiScene_Component_RemoveName(wiScene scene, wiEntity entity);
void wiNameComponent_Set(wiNameComponent component, const char *name);
const char *wiNameComponent_Get(wiNameComponent component);

// --- Component: Layer ---
wiLayerComponent wiScene_Component_CreateLayer(wiScene scene, wiEntity entity);
wiLayerComponent wiScene_Component_GetLayer(wiScene scene, wiEntity entity);
void wiScene_Component_RemoveLayer(wiScene scene, wiEntity entity);
void wiLayerComponent_SetLayerMask(wiLayerComponent component,
                                   uint32_t layerMask);
uint32_t wiLayerComponent_GetLayerMask(wiLayerComponent component);

// --- Component: Transform ---
wiTransformComponent wiScene_Component_CreateTransform(wiScene scene,
                                                       wiEntity entity);
wiTransformComponent wiScene_Component_GetTransform(wiScene scene,
                                                    wiEntity entity);
void wiScene_Component_RemoveTransform(wiScene scene, wiEntity entity);
void wiTransformComponent_SetPosition(wiTransformComponent component,
                                      wiVector position);
wiVector wiTransformComponent_GetPosition(wiTransformComponent component);
void wiTransformComponent_SetRotation(wiTransformComponent component,
                                      wiVector rotation); // Quaternion
wiVector wiTransformComponent_GetRotation(wiTransformComponent component);
void wiTransformComponent_SetScale(wiTransformComponent component,
                                   wiVector scale);
wiVector wiTransformComponent_GetScale(wiTransformComponent component);
void wiTransformComponent_UpdateTransform(wiTransformComponent component);
void wiTransformComponent_Translate(wiTransformComponent component,
                                    wiVector translation);
void wiTransformComponent_Rotate(wiTransformComponent component,
                                 wiVector quaternion);
void wiTransformComponent_Scale(wiTransformComponent component, wiVector scale);
wiMatrix wiTransformComponent_GetMatrix(wiTransformComponent component);

// --- Component: Mesh ---
wiMeshComponent wiScene_Component_CreateMesh(wiScene scene, wiEntity entity);
wiMeshComponent wiScene_Component_GetMesh(wiScene scene, wiEntity entity);
// (Additional Mesh properties as needed)

// --- Component: Material ---
wiMaterialComponent wiScene_Component_CreateMaterial(wiScene scene,
                                                     wiEntity entity);
wiMaterialComponent wiScene_Component_GetMaterial(wiScene scene,
                                                  wiEntity entity);
// (Additional Material properties as needed)

// --- Component: Object ---
wiObjectComponent wiScene_Component_CreateObject(wiScene scene,
                                                 wiEntity entity);
wiObjectComponent wiScene_Component_GetObject(wiScene scene, wiEntity entity);
void wiObjectComponent_SetMeshID(wiObjectComponent component,
                                 wiEntity meshEntity);
wiEntity wiObjectComponent_GetMeshID(wiObjectComponent component);

// --- Component: Light ---
wiLightComponent wiScene_Component_CreateLight(wiScene scene, wiEntity entity);
wiLightComponent wiScene_Component_GetLight(wiScene scene, wiEntity entity);
// Basic Light properties
void wiLightComponent_SetType(wiLightComponent component,
                              int type); // 0: Directional, 1: Point, 2: Spot
void wiLightComponent_SetColor(wiLightComponent component,
                               wiVector color); // RGB
void wiLightComponent_SetIntensity(wiLightComponent component, float intensity);
void wiLightComponent_SetRange(wiLightComponent component, float range);

// --- Component: Camera ---
wiCameraComponent wiScene_Component_CreateCamera(wiScene scene,
                                                 wiEntity entity);
wiCameraComponent wiScene_Component_GetCamera(wiScene scene, wiEntity entity);
void wiCameraComponent_UpdateCamera(wiCameraComponent component);
void wiCameraComponent_SetFOV(wiCameraComponent component, float fov);
float wiCameraComponent_GetFOV(wiCameraComponent component);
void wiCameraComponent_SetNearPlane(wiCameraComponent component,
                                    float nearPlane);
void wiCameraComponent_SetFarPlane(wiCameraComponent component, float farPlane);

// --- Component: RigidBody Physics ---
wiRigidBodyPhysicsComponent
wiScene_Component_CreateRigidBodyPhysics(wiScene scene, wiEntity entity);
wiRigidBodyPhysicsComponent
wiScene_Component_GetRigidBodyPhysics(wiScene scene, wiEntity entity);

// --- Component: SoftBody Physics ---
wiSoftBodyPhysicsComponent
wiScene_Component_CreateSoftBodyPhysics(wiScene scene, wiEntity entity);
wiSoftBodyPhysicsComponent
wiScene_Component_GetSoftBodyPhysics(wiScene scene, wiEntity entity);

// --- Component: Force Field ---
wiForceFieldComponent wiScene_Component_CreateForceField(wiScene scene,
                                                         wiEntity entity);
wiForceFieldComponent wiScene_Component_GetForceField(wiScene scene,
                                                      wiEntity entity);

// --- Component: Weather ---
wiWeatherComponent wiScene_Component_CreateWeather(wiScene scene,
                                                   wiEntity entity);
wiWeatherComponent wiScene_Component_GetWeather(wiScene scene, wiEntity entity);

// --- Component: Animation ---
wiAnimationComponent wiScene_Component_CreateAnimation(wiScene scene,
                                                       wiEntity entity);
wiAnimationComponent wiScene_Component_GetAnimation(wiScene scene,
                                                    wiEntity entity);

#ifdef __cplusplus
}
#endif
