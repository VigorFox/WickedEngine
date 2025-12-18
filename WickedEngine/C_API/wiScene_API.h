#pragma once
#include "wiMath_API.h"
#include "wiPrimitive_API.h"
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
typedef struct wiEmitterComponent_t *wiEmitterComponent;

typedef struct wiRigidBodyPhysicsComponent_t *wiRigidBodyPhysicsComponent;
typedef struct wiSoftBodyPhysicsComponent_t *wiSoftBodyPhysicsComponent;
typedef struct wiForceFieldComponent_t *wiForceFieldComponent;
typedef struct wiWeatherComponent_t *wiWeatherComponent;
typedef struct wiAnimationComponent_t *wiAnimationComponent;
typedef struct wiCharacterComponent_t *wiCharacterComponent;
typedef struct wiVoxelGridComponent_t *wiVoxelGridComponent;

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
void wiMeshComponent_SetRenderable(wiMeshComponent component, bool value);
bool wiMeshComponent_IsRenderable(wiMeshComponent component);
void wiMeshComponent_SetDoubleSided(wiMeshComponent component, bool value);
bool wiMeshComponent_IsDoubleSided(wiMeshComponent component);
void wiMeshComponent_SetTessellationFactor(wiMeshComponent component,
                                           float factor);
float wiMeshComponent_GetTessellationFactor(wiMeshComponent component);
void wiMeshComponent_SetQuantizedPositionsDisabled(wiMeshComponent component,
                                                   bool value);
bool wiMeshComponent_IsQuantizedPositionsDisabled(wiMeshComponent component);

// --- Component: Material ---
wiMaterialComponent wiScene_Component_CreateMaterial(wiScene scene,
                                                     wiEntity entity);
wiMaterialComponent wiScene_Component_GetMaterial(wiScene scene,
                                                  wiEntity entity);
void wiMaterialComponent_SetBaseColor(wiMaterialComponent component,
                                      wiColor color);
wiColor wiMaterialComponent_GetBaseColor(wiMaterialComponent component);
void wiMaterialComponent_SetSpecularColor(wiMaterialComponent component,
                                          wiColor color);
wiColor wiMaterialComponent_GetSpecularColor(wiMaterialComponent component);
void wiMaterialComponent_SetEmissiveColor(wiMaterialComponent component,
                                          wiColor color);
wiColor wiMaterialComponent_GetEmissiveColor(wiMaterialComponent component);
void wiMaterialComponent_SetRoughness(wiMaterialComponent component,
                                      float roughness);
float wiMaterialComponent_GetRoughness(wiMaterialComponent component);
void wiMaterialComponent_SetMetalness(wiMaterialComponent component,
                                      float metalness);
float wiMaterialComponent_GetMetalness(wiMaterialComponent component);
void wiMaterialComponent_SetReflectance(wiMaterialComponent component,
                                        float reflectance);
float wiMaterialComponent_GetReflectance(wiMaterialComponent component);
void wiMaterialComponent_SetEmissiveStrength(wiMaterialComponent component,
                                             float strength);
float wiMaterialComponent_GetEmissiveStrength(wiMaterialComponent component);
void wiMaterialComponent_SetNormalMapStrength(wiMaterialComponent component,
                                              float strength);
float wiMaterialComponent_GetNormalMapStrength(wiMaterialComponent component);
void wiMaterialComponent_SetParallaxOcclusionMapping(
    wiMaterialComponent component, float amount);
float wiMaterialComponent_GetParallaxOcclusionMapping(
    wiMaterialComponent component);
void wiMaterialComponent_SetDisplacementMapping(wiMaterialComponent component,
                                                float amount);
float wiMaterialComponent_GetDisplacementMapping(wiMaterialComponent component);
void wiMaterialComponent_SetSubsurfaceScattering(wiMaterialComponent component,
                                                 wiColor color); // .w is amount
wiColor
wiMaterialComponent_GetSubsurfaceScattering(wiMaterialComponent component);
void wiMaterialComponent_SetOpacity(wiMaterialComponent component,
                                    float opacity);
float wiMaterialComponent_GetOpacity(wiMaterialComponent component);
void wiMaterialComponent_SetAlphaRef(wiMaterialComponent component,
                                     float alphaRef);
float wiMaterialComponent_GetAlphaRef(wiMaterialComponent component);
void wiMaterialComponent_SetUserStencilRef(wiMaterialComponent component,
                                           uint8_t ref);
uint8_t wiMaterialComponent_GetUserStencilRef(wiMaterialComponent component);
void wiMaterialComponent_SetCastShadow(wiMaterialComponent component,
                                       bool value);
bool wiMaterialComponent_IsCastShadow(wiMaterialComponent component);
void wiMaterialComponent_SetReceiveShadow(wiMaterialComponent component,
                                          bool value);
bool wiMaterialComponent_IsReceiveShadow(wiMaterialComponent component);

// --- Component: Object ---
wiObjectComponent wiScene_Component_CreateObject(wiScene scene,
                                                 wiEntity entity);
wiObjectComponent wiScene_Component_GetObject(wiScene scene, wiEntity entity);
void wiObjectComponent_SetMeshID(wiObjectComponent component,
                                 wiEntity meshEntity);
wiEntity wiObjectComponent_GetMeshID(wiObjectComponent component);
void wiObjectComponent_SetColor(wiObjectComponent component, wiColor color);
wiColor wiObjectComponent_GetColor(wiObjectComponent component);
void wiObjectComponent_SetUserStencilRef(wiObjectComponent component,
                                         uint8_t ref);
uint8_t wiObjectComponent_GetUserStencilRef(wiObjectComponent component);
void wiObjectComponent_SetDrawDistance(wiObjectComponent component, float dist);
float wiObjectComponent_GetDrawDistance(wiObjectComponent component);
void wiObjectComponent_SetCastShadow(wiObjectComponent component, bool value);
bool wiObjectComponent_IsCastShadow(wiObjectComponent component);
void wiObjectComponent_SetRenderable(wiObjectComponent component, bool value);
bool wiObjectComponent_IsRenderable(wiObjectComponent component);

// --- Component: Light ---
wiLightComponent wiScene_Component_CreateLight(wiScene scene, wiEntity entity);
wiLightComponent wiScene_Component_GetLight(wiScene scene, wiEntity entity);
void wiLightComponent_SetType(wiLightComponent component,
                              int type); // 0: Directional, 1: Point, 2: Spot
int wiLightComponent_GetType(wiLightComponent component);
void wiLightComponent_SetColor(wiLightComponent component, wiVector color);
wiVector wiLightComponent_GetColor(wiLightComponent component);
void wiLightComponent_SetIntensity(wiLightComponent component, float intensity);
float wiLightComponent_GetIntensity(wiLightComponent component);
void wiLightComponent_SetRange(wiLightComponent component, float range);
float wiLightComponent_GetRange(wiLightComponent component);
void wiLightComponent_SetInnerConeAngle(wiLightComponent component,
                                        float angle);
float wiLightComponent_GetInnerConeAngle(wiLightComponent component);
void wiLightComponent_SetOuterConeAngle(wiLightComponent component,
                                        float angle);
float wiLightComponent_GetOuterConeAngle(wiLightComponent component);
void wiLightComponent_SetCastShadow(wiLightComponent component, bool value);
bool wiLightComponent_IsCastShadow(wiLightComponent component);
void wiLightComponent_SetVolumetricsEnabled(wiLightComponent component,
                                            bool value);
bool wiLightComponent_IsVolumetricsEnabled(wiLightComponent component);
void wiLightComponent_SetVisualizerEnabled(wiLightComponent component,
                                           bool value);
bool wiLightComponent_IsVisualizerEnabled(wiLightComponent component);

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
void wiCameraComponent_SetFocalLength(wiCameraComponent component,
                                      float focalLength);
float wiCameraComponent_GetFocalLength(wiCameraComponent component);
void wiCameraComponent_SetApertureSize(wiCameraComponent component,
                                       float apertureSize);
float wiCameraComponent_GetApertureSize(wiCameraComponent component);
void wiCameraComponent_SetApertureShape(wiCameraComponent component,
                                        wiVector shape);
wiVector wiCameraComponent_GetApertureShape(wiCameraComponent component);

// --- Component: Emitter ---
wiEmitterComponent wiScene_Component_CreateEmitter(wiScene scene,
                                                   wiEntity entity);
wiEmitterComponent wiScene_Component_GetEmitter(wiScene scene, wiEntity entity);
void wiEmitterComponent_SetEmitCount(wiEmitterComponent component, float count);
float wiEmitterComponent_GetEmitCount(wiEmitterComponent component);
void wiEmitterComponent_SetSize(wiEmitterComponent component, float size);
float wiEmitterComponent_GetSize(wiEmitterComponent component);
void wiEmitterComponent_SetLife(wiEmitterComponent component, float life);
float wiEmitterComponent_GetLife(wiEmitterComponent component);
void wiEmitterComponent_SetNormalFactor(wiEmitterComponent component,
                                        float factor);
float wiEmitterComponent_GetNormalFactor(wiEmitterComponent component);
void wiEmitterComponent_SetRandomFactor(wiEmitterComponent component,
                                        float factor);
float wiEmitterComponent_GetRandomFactor(wiEmitterComponent component);
void wiEmitterComponent_SetLifeRandomness(wiEmitterComponent component,
                                          float randomness);
float wiEmitterComponent_GetLifeRandomness(wiEmitterComponent component);
void wiEmitterComponent_SetScaleX(wiEmitterComponent component, float scaleX);
float wiEmitterComponent_GetScaleX(wiEmitterComponent component);
void wiEmitterComponent_SetScaleY(wiEmitterComponent component, float scaleY);
float wiEmitterComponent_GetScaleY(wiEmitterComponent component);
void wiEmitterComponent_SetRotation(wiEmitterComponent component,
                                    float rotation);
float wiEmitterComponent_GetRotation(wiEmitterComponent component);
void wiEmitterComponent_SetMotionBlurAmount(wiEmitterComponent component,
                                            float amount);
float wiEmitterComponent_GetMotionBlurAmount(wiEmitterComponent component);
void wiEmitterComponent_SetMass(wiEmitterComponent component, float mass);
float wiEmitterComponent_GetMass(wiEmitterComponent component);
void wiEmitterComponent_SetVelocity(wiEmitterComponent component,
                                    wiVector velocity);
wiVector wiEmitterComponent_GetVelocity(wiEmitterComponent component);
void wiEmitterComponent_SetGravity(wiEmitterComponent component,
                                   wiVector gravity);
wiVector wiEmitterComponent_GetGravity(wiEmitterComponent component);
void wiEmitterComponent_SetDrag(wiEmitterComponent component, float drag);
float wiEmitterComponent_GetDrag(wiEmitterComponent component);
void wiEmitterComponent_SetRestitution(wiEmitterComponent component,
                                       float restitution);
float wiEmitterComponent_GetRestitution(wiEmitterComponent component);
void wiEmitterComponent_Burst(wiEmitterComponent component, int count);
void wiEmitterComponent_Restart(wiEmitterComponent component);
void wiEmitterComponent_SetDebug(wiEmitterComponent component, bool value);
bool wiEmitterComponent_IsDebug(wiEmitterComponent component);
void wiEmitterComponent_SetPaused(wiEmitterComponent component, bool value);
bool wiEmitterComponent_IsPaused(wiEmitterComponent component);
void wiEmitterComponent_SetSorted(wiEmitterComponent component, bool value);
bool wiEmitterComponent_IsSorted(wiEmitterComponent component);
void wiEmitterComponent_SetDepthCollisionEnabled(wiEmitterComponent component,
                                                 bool value);
bool wiEmitterComponent_IsDepthCollisionEnabled(wiEmitterComponent component);
void wiEmitterComponent_SetSPHEnabled(wiEmitterComponent component, bool value);
bool wiEmitterComponent_IsSPHEnabled(wiEmitterComponent component);
void wiEmitterComponent_SetVolumeEnabled(wiEmitterComponent component,
                                         bool value);
bool wiEmitterComponent_IsVolumeEnabled(wiEmitterComponent component);
void wiEmitterComponent_SetFrameBlendingEnabled(wiEmitterComponent component,
                                                bool value);
bool wiEmitterComponent_IsFrameBlendingEnabled(wiEmitterComponent component);

// --- Component: RigidBody Physics ---
wiRigidBodyPhysicsComponent
wiScene_Component_CreateRigidBodyPhysics(wiScene scene, wiEntity entity);
wiRigidBodyPhysicsComponent
wiScene_Component_GetRigidBodyPhysics(wiScene scene, wiEntity entity);
void wiRigidBodyPhysicsComponent_SetMass(wiRigidBodyPhysicsComponent component,
                                         float mass);
float wiRigidBodyPhysicsComponent_GetMass(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetFriction(
    wiRigidBodyPhysicsComponent component, float friction);
float wiRigidBodyPhysicsComponent_GetFriction(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetRestitution(
    wiRigidBodyPhysicsComponent component, float restitution);
float wiRigidBodyPhysicsComponent_GetRestitution(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetLinearDamping(
    wiRigidBodyPhysicsComponent component, float damping);
float wiRigidBodyPhysicsComponent_GetLinearDamping(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetAngularDamping(
    wiRigidBodyPhysicsComponent component, float damping);
float wiRigidBodyPhysicsComponent_GetAngularDamping(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetKinematic(
    wiRigidBodyPhysicsComponent component, bool value);
bool wiRigidBodyPhysicsComponent_IsKinematic(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetDisableDeactivation(
    wiRigidBodyPhysicsComponent component, bool value);
bool wiRigidBodyPhysicsComponent_IsDisableDeactivation(
    wiRigidBodyPhysicsComponent component);
void wiRigidBodyPhysicsComponent_SetBoxShape(
    wiRigidBodyPhysicsComponent component, wiVector halfExtents);
void wiRigidBodyPhysicsComponent_SetSphereShape(
    wiRigidBodyPhysicsComponent component, float radius);
void wiRigidBodyPhysicsComponent_SetCapsuleShape(
    wiRigidBodyPhysicsComponent component, float radius, float height);

// --- Component: SoftBody Physics ---
wiSoftBodyPhysicsComponent
wiScene_Component_CreateSoftBodyPhysics(wiScene scene, wiEntity entity);
wiSoftBodyPhysicsComponent
wiScene_Component_GetSoftBodyPhysics(wiScene scene, wiEntity entity);
void wiSoftBodyPhysicsComponent_SetMass(wiSoftBodyPhysicsComponent component,
                                        float mass);
float wiSoftBodyPhysicsComponent_GetMass(wiSoftBodyPhysicsComponent component);
void wiSoftBodyPhysicsComponent_SetFriction(
    wiSoftBodyPhysicsComponent component, float friction);
float wiSoftBodyPhysicsComponent_GetFriction(
    wiSoftBodyPhysicsComponent component);
void wiSoftBodyPhysicsComponent_SetRestitution(
    wiSoftBodyPhysicsComponent component, float restitution);
float wiSoftBodyPhysicsComponent_GetRestitution(
    wiSoftBodyPhysicsComponent component);

// --- Component: Character ---
typedef struct wiCharacterComponent_t *wiCharacterComponent;
wiCharacterComponent wiScene_Component_CreateCharacter(wiScene scene,
                                                       wiEntity entity);
wiCharacterComponent wiScene_Component_GetCharacter(wiScene scene,
                                                    wiEntity entity);
void wiCharacterComponent_SetActive(wiCharacterComponent component,
                                    bool active);
bool wiCharacterComponent_IsActive(wiCharacterComponent component);
void wiCharacterComponent_SetPathGoal(wiCharacterComponent component,
                                      wiVector goal,
                                      wiVoxelGridComponent voxelGrid);

// --- Component: Force Field ---
wiForceFieldComponent wiScene_Component_CreateForceField(wiScene scene,
                                                         wiEntity entity);
wiForceFieldComponent wiScene_Component_GetForceField(wiScene scene,
                                                      wiEntity entity);
void wiForceFieldComponent_SetType(wiForceFieldComponent component, int type);
int wiForceFieldComponent_GetType(wiForceFieldComponent component);
void wiForceFieldComponent_SetGravity(wiForceFieldComponent component,
                                      float gravity);
float wiForceFieldComponent_GetGravity(wiForceFieldComponent component);
void wiForceFieldComponent_SetRange(wiForceFieldComponent component,
                                    float range);
float wiForceFieldComponent_GetRange(wiForceFieldComponent component);

// --- Component: Weather ---
wiWeatherComponent wiScene_Component_CreateWeather(wiScene scene,
                                                   wiEntity entity);
wiWeatherComponent wiScene_Component_GetWeather(wiScene scene, wiEntity entity);
void wiWeatherComponent_SetOceanEnabled(wiWeatherComponent component,
                                        bool value);
bool wiWeatherComponent_IsOceanEnabled(wiWeatherComponent component);
void wiWeatherComponent_SetOceanLevel(wiWeatherComponent component,
                                      float level);
float wiWeatherComponent_GetOceanLevel(wiWeatherComponent component);
void wiWeatherComponent_SetFogStart(wiWeatherComponent component, float start);
float wiWeatherComponent_GetFogStart(wiWeatherComponent component);
void wiWeatherComponent_SetFogDensity(wiWeatherComponent component,
                                      float fogDensity);
float wiWeatherComponent_GetFogDensity(wiWeatherComponent component);
void wiWeatherComponent_SetFogHeightStart(wiWeatherComponent component,
                                          float start);
float wiWeatherComponent_GetFogHeightStart(wiWeatherComponent component);
void wiWeatherComponent_SetFogHeightEnd(wiWeatherComponent component,
                                        float end);
float wiWeatherComponent_GetFogHeightEnd(wiWeatherComponent component);

// --- Component: Animation ---
wiAnimationComponent wiScene_Component_CreateAnimation(wiScene scene,
                                                       wiEntity entity);
wiAnimationComponent wiScene_Component_GetAnimation(wiScene scene,
                                                    wiEntity entity);
void wiAnimationComponent_Play(wiAnimationComponent component);
void wiAnimationComponent_Stop(wiAnimationComponent component);
bool wiAnimationComponent_IsPlaying(wiAnimationComponent component);
void wiAnimationComponent_SetLooped(wiAnimationComponent component, bool value);
bool wiAnimationComponent_IsLooped(wiAnimationComponent component);
void wiAnimationComponent_SetAmount(wiAnimationComponent component,
                                    float amount);
float wiAnimationComponent_GetAmount(wiAnimationComponent component);
void wiAnimationComponent_SetSpeed(wiAnimationComponent component, float speed);
float wiAnimationComponent_GetSpeed(wiAnimationComponent component);
void wiAnimationComponent_SetTimer(wiAnimationComponent component, float timer);
float wiAnimationComponent_GetTimer(wiAnimationComponent component);

// --- Scene Operations ---
wiEntity wiScene_LoadModel(wiScene scene, const char *fileName,
                           wiMatrix transform);
wiEntity wiScene_Instantiate(wiScene scene, wiScene prefab, bool attached);

typedef struct wiScenePickResult {
  wiEntity entity;
  wiVector position;
  wiVector normal;
  float distance;
} wiScenePickResult;

wiScenePickResult wiScene_Pick(wiScene scene, wiRay ray, uint32_t filterMask,
                               uint32_t layerMask, uint32_t lod);
wiScenePickResult wiScene_SceneIntersectSphere(wiScene scene, wiSphere sphere,
                                               uint32_t filterMask,
                                               uint32_t layerMask,
                                               uint32_t lod);
wiScenePickResult wiScene_SceneIntersectCapsule(wiScene scene,
                                                wiCapsule capsule,
                                                uint32_t filterMask,
                                                uint32_t layerMask,
                                                uint32_t lod);

// --- Component: Emitter ---
typedef struct wiEmitterComponent_t *wiEmitterComponent;
wiEmitterComponent wiScene_Component_CreateEmitter(wiScene scene,
                                                   wiEntity entity);
wiEmitterComponent wiScene_Component_GetEmitter(wiScene scene, wiEntity entity);

// --- Component: HairParticleSystem ---
typedef struct wiHairParticleSystem_t *wiHairParticleSystem;
wiHairParticleSystem
wiScene_Component_CreateHairParticleSystem(wiScene scene, wiEntity entity);
wiHairParticleSystem wiScene_Component_GetHairParticleSystem(wiScene scene,
                                                             wiEntity entity);
void wiHairParticleSystem_SetStrandCount(wiHairParticleSystem component,
                                         size_t count);
size_t wiHairParticleSystem_GetStrandCount(wiHairParticleSystem component);
void wiHairParticleSystem_SetLength(wiHairParticleSystem component,
                                    float length);
float wiHairParticleSystem_GetLength(wiHairParticleSystem component);
void wiHairParticleSystem_SetStiffness(wiHairParticleSystem component,
                                       float stiffness);
float wiHairParticleSystem_GetStiffness(wiHairParticleSystem component);
void wiHairParticleSystem_SetRandomness(wiHairParticleSystem component,
                                        float randomness);
float wiHairParticleSystem_GetRandomness(wiHairParticleSystem component);

// --- Component: InverseKinematics ---
typedef struct wiInverseKinematicsComponent_t *wiInverseKinematicsComponent;
wiInverseKinematicsComponent
wiScene_Component_CreateInverseKinematics(wiScene scene, wiEntity entity);
wiInverseKinematicsComponent
wiScene_Component_GetInverseKinematics(wiScene scene, wiEntity entity);

// --- Component: Script ---
typedef struct wiScriptComponent_t *wiScriptComponent;
wiScriptComponent wiScene_Component_CreateScript(wiScene scene,
                                                 wiEntity entity);
wiScriptComponent wiScene_Component_GetScript(wiScene scene, wiEntity entity);
void wiScriptComponent_SetScriptFile(wiScriptComponent component,
                                     const char *filename);
const char *wiScriptComponent_GetScriptFile(wiScriptComponent component);
void wiScriptComponent_Play(wiScriptComponent component);
void wiScriptComponent_Stop(wiScriptComponent component);

// --- Component: Collider ---
typedef struct wiColliderComponent_t *wiColliderComponent;
wiColliderComponent wiScene_Component_CreateCollider(wiScene scene,
                                                     wiEntity entity);
wiColliderComponent wiScene_Component_GetCollider(wiScene scene,
                                                  wiEntity entity);
void wiColliderComponent_SetShape(wiColliderComponent component,
                                  int shape); // 0: Box, 1: Sphere, 2: Capsule
int wiColliderComponent_GetShape(wiColliderComponent component);
void wiColliderComponent_SetRadius(wiColliderComponent component, float radius);
float wiColliderComponent_GetRadius(wiColliderComponent component);
void wiColliderComponent_SetOffset(wiColliderComponent component,
                                   wiVector offset);
wiVector wiColliderComponent_GetOffset(wiColliderComponent component);
void wiColliderComponent_SetTail(wiColliderComponent component, wiVector tail);
wiVector wiColliderComponent_GetTail(wiColliderComponent component);
void wiColliderComponent_SetCPUEnabled(wiColliderComponent component,
                                       bool value);
bool wiColliderComponent_IsCPUEnabled(wiColliderComponent component);

// --- Component: Spring ---
typedef struct wiSpringComponent_t *wiSpringComponent;
wiSpringComponent wiScene_Component_CreateSpring(wiScene scene,
                                                 wiEntity entity);
wiSpringComponent wiScene_Component_GetSpring(wiScene scene, wiEntity entity);
void wiSpringComponent_SetStiffness(wiSpringComponent component,
                                    float stiffness);
float wiSpringComponent_GetStiffness(wiSpringComponent component);
void wiSpringComponent_SetDamping(wiSpringComponent component, float damping);
float wiSpringComponent_GetDamping(wiSpringComponent component);
void wiSpringComponent_SetWindAffection(wiSpringComponent component,
                                        float value);
float wiSpringComponent_GetWindAffection(wiSpringComponent component);

// --- Component: Sound ---
typedef struct wiSoundComponent_t *wiSoundComponent;
wiSoundComponent wiScene_Component_CreateSound(wiScene scene, wiEntity entity);
wiSoundComponent wiScene_Component_GetSound(wiScene scene, wiEntity entity);
void wiSoundComponent_Play(wiSoundComponent component);
void wiSoundComponent_Stop(wiSoundComponent component);
bool wiSoundComponent_IsPlaying(wiSoundComponent component);
void wiSoundComponent_SetLooped(wiSoundComponent component, bool value);
bool wiSoundComponent_IsLooped(wiSoundComponent component);
void wiSoundComponent_SetVolume(wiSoundComponent component, float volume);
float wiSoundComponent_GetVolume(wiSoundComponent component);

// --- Component: Video ---
typedef struct wiVideoComponent_t *wiVideoComponent;
wiVideoComponent wiScene_Component_CreateVideo(wiScene scene, wiEntity entity);
wiVideoComponent wiScene_Component_GetVideo(wiScene scene, wiEntity entity);
void wiVideoComponent_Play(wiVideoComponent component);
void wiVideoComponent_Pause(wiVideoComponent component);
void wiVideoComponent_Stop(wiVideoComponent component);
bool wiVideoComponent_IsPlaying(wiVideoComponent component);
void wiVideoComponent_SetLooped(wiVideoComponent component, bool value);
bool wiVideoComponent_IsLooped(wiVideoComponent component);

// --- Component: Expression ---
typedef struct wiExpressionComponent_t *wiExpressionComponent;
wiExpressionComponent wiScene_Component_CreateExpression(wiScene scene,
                                                         wiEntity entity);
wiExpressionComponent wiScene_Component_GetExpression(wiScene scene,
                                                      wiEntity entity);
// SetPreset/SetWeight removed as ExpressionComponent structure is complex (list
// based). Provide specific API for managing Presets and ForceTalking.

typedef enum wiExpressionComponent_Preset {
  WI_EXPRESSION_HAPPY,
  WI_EXPRESSION_ANGRY,
  WI_EXPRESSION_SAD,
  WI_EXPRESSION_RELAXED,
  WI_EXPRESSION_SURPRISED,
  WI_EXPRESSION_AA,
  WI_EXPRESSION_IH,
  WI_EXPRESSION_OU,
  WI_EXPRESSION_EE,
  WI_EXPRESSION_OH,
  WI_EXPRESSION_BLINK,
  WI_EXPRESSION_BLINK_LEFT,
  WI_EXPRESSION_BLINK_RIGHT,
  WI_EXPRESSION_LOOK_UP,
  WI_EXPRESSION_LOOK_DOWN,
  WI_EXPRESSION_LOOK_LEFT,
  WI_EXPRESSION_LOOK_RIGHT,
  WI_EXPRESSION_NEUTRAL,
  WI_EXPRESSION_COUNT
} wiExpressionComponent_Preset;

void wiExpressionComponent_SetForceTalking(wiExpressionComponent component,
                                           bool value);
bool wiExpressionComponent_IsForceTalking(wiExpressionComponent component);
void wiExpressionComponent_SetPresetWeight(wiExpressionComponent component,
                                           wiExpressionComponent_Preset preset,
                                           float weight);
float wiExpressionComponent_GetPresetWeight(
    wiExpressionComponent component, wiExpressionComponent_Preset preset);

// --- Component: Humanoid ---
typedef struct wiHumanoidComponent_t *wiHumanoidComponent;
wiHumanoidComponent wiScene_Component_CreateHumanoid(wiScene scene,
                                                     wiEntity entity);
wiHumanoidComponent wiScene_Component_GetHumanoid(wiScene scene,
                                                  wiEntity entity);
void wiHumanoidComponent_SetBone(wiHumanoidComponent component, int bone,
                                 wiEntity boneEntity);
wiEntity wiHumanoidComponent_GetBone(wiHumanoidComponent component, int bone);

// --- Component: Decal ---
typedef struct wiDecalComponent_t *wiDecalComponent;
wiDecalComponent wiScene_Component_CreateDecal(wiScene scene, wiEntity entity);
wiDecalComponent wiScene_Component_GetDecal(wiScene scene, wiEntity entity);
void wiDecalComponent_SetSlopeBlendPower(wiDecalComponent component,
                                         float power);
float wiDecalComponent_GetSlopeBlendPower(wiDecalComponent component);

// --- Component: Sprite ---
typedef struct wiSpriteComponent_t *wiSpriteComponent;
wiSpriteComponent wiScene_Component_CreateSprite(wiScene scene,
                                                 wiEntity entity);
wiSpriteComponent wiScene_Component_GetSprite(wiScene scene, wiEntity entity);
// Sprite mainly relies on ImageParams, maybe just expose SetParams/GetParams
// wrapper? For now, let's omit complex params unless requested.

// --- Component: Font ---
typedef struct wiFontComponent_t *wiFontComponent;
wiFontComponent wiScene_Component_CreateFont(wiScene scene, wiEntity entity);
wiFontComponent wiScene_Component_GetFont(wiScene scene, wiEntity entity);
void wiFontComponent_SetText(wiFontComponent component, const char *text);
const char *wiFontComponent_GetText(wiFontComponent component);
void wiFontComponent_SetSize(wiFontComponent component, float size);
float wiFontComponent_GetSize(wiFontComponent component);

// --- Component: VoxelGrid ---
wiVoxelGridComponent wiScene_Component_CreateVoxelGrid(wiScene scene,
                                                       wiEntity entity);
wiVoxelGridComponent wiScene_Component_GetVoxelGrid(wiScene scene,
                                                    wiEntity entity);
void wiVoxelGridComponent_SetResolution(wiVoxelGridComponent component,
                                        uint32_t resolution);
uint32_t wiVoxelGridComponent_GetResolution(wiVoxelGridComponent component);

// --- Component: Metadata ---
typedef struct wiMetadataComponent_t *wiMetadataComponent;
wiMetadataComponent wiScene_Component_CreateMetadata(wiScene scene,
                                                     wiEntity entity);
wiMetadataComponent wiScene_Component_GetMetadata(wiScene scene,
                                                  wiEntity entity);
// Metadata Set/Get bool/int/float/string is complex for C API without defined
// types. For now, assume users use C++ or custom handling, or minimal int/float
// support. Let's Skip Metadata specific keys for now.

// --- Scene Helper Methods ---
void wiScene_IntersectsAll(wiScene scene, wiRay ray, uint32_t filterMask,
                           uint32_t layerMask, uint32_t lod, size_t *count,
                           wiScenePickResult **results);
bool wiScene_IntersectsFirst(wiScene scene, wiRay ray, uint32_t filterMask,
                             uint32_t layerMask, uint32_t lod,
                             wiScenePickResult *result);
void wiScene_FindAllEntities(wiScene scene, size_t *count, wiEntity **entities);

// --- Component Array Accessors ---

// Generic macro for decl would be nicer, but C API needs explicit calls.
// Name
size_t wiScene_Component_GetNameCount(wiScene scene);
wiNameComponent *wiScene_Component_GetNameArray(wiScene scene);
// Layer
size_t wiScene_Component_GetLayerCount(wiScene scene);
wiLayerComponent *wiScene_Component_GetLayerArray(wiScene scene);
// Transform
size_t wiScene_Component_GetTransformCount(wiScene scene);
wiTransformComponent *wiScene_Component_GetTransformArray(wiScene scene);
// Mesh
size_t wiScene_Component_GetMeshCount(wiScene scene);
wiMeshComponent *wiScene_Component_GetMeshArray(wiScene scene);
// Material
size_t wiScene_Component_GetMaterialCount(wiScene scene);
wiMaterialComponent *wiScene_Component_GetMaterialArray(wiScene scene);
// Object
size_t wiScene_Component_GetObjectCount(wiScene scene);
wiObjectComponent *wiScene_Component_GetObjectArray(wiScene scene);
// Light
size_t wiScene_Component_GetLightCount(wiScene scene);
wiLightComponent *wiScene_Component_GetLightArray(wiScene scene);
// Camera
size_t wiScene_Component_GetCameraCount(wiScene scene);
wiCameraComponent *wiScene_Component_GetCameraArray(wiScene scene);
// RigidBody
size_t wiScene_Component_GetRigidBodyPhysicsCount(wiScene scene);
wiRigidBodyPhysicsComponent *
wiScene_Component_GetRigidBodyPhysicsArray(wiScene scene);
// SoftBody
size_t wiScene_Component_GetSoftBodyPhysicsCount(wiScene scene);
wiSoftBodyPhysicsComponent *
wiScene_Component_GetSoftBodyPhysicsArray(wiScene scene);
// ForceField
size_t wiScene_Component_GetForceFieldCount(wiScene scene);
wiForceFieldComponent *wiScene_Component_GetForceFieldArray(wiScene scene);
// Weather
size_t wiScene_Component_GetWeatherCount(wiScene scene);
wiWeatherComponent *wiScene_Component_GetWeatherArray(wiScene scene);
// Animation
size_t wiScene_Component_GetAnimationCount(wiScene scene);
wiAnimationComponent *wiScene_Component_GetAnimationArray(wiScene scene);
// Emitter
size_t wiScene_Component_GetEmitterCount(wiScene scene);
wiEmitterComponent *wiScene_Component_GetEmitterArray(wiScene scene);
// HairReference
size_t wiScene_Component_GetHairParticleSystemCount(wiScene scene);
wiHairParticleSystem *
wiScene_Component_GetHairParticleSystemArray(wiScene scene);
// IK
size_t wiScene_Component_GetInverseKinematicsCount(wiScene scene);
wiInverseKinematicsComponent *
wiScene_Component_GetInverseKinematicsArray(wiScene scene);
// Script
size_t wiScene_Component_GetScriptCount(wiScene scene);
wiScriptComponent *wiScene_Component_GetScriptArray(wiScene scene);
// Collider
size_t wiScene_Component_GetColliderCount(wiScene scene);
wiColliderComponent *wiScene_Component_GetColliderArray(wiScene scene);
// Spring
size_t wiScene_Component_GetSpringCount(wiScene scene);
wiSpringComponent *wiScene_Component_GetSpringArray(wiScene scene);
// Sound
size_t wiScene_Component_GetSoundCount(wiScene scene);
wiSoundComponent *wiScene_Component_GetSoundArray(wiScene scene);
// Video
size_t wiScene_Component_GetVideoCount(wiScene scene);
wiVideoComponent *wiScene_Component_GetVideoArray(wiScene scene);
// Expression
size_t wiScene_Component_GetExpressionCount(wiScene scene);
wiExpressionComponent *wiScene_Component_GetExpressionArray(wiScene scene);
// Humanoid
size_t wiScene_Component_GetHumanoidCount(wiScene scene);
wiHumanoidComponent *wiScene_Component_GetHumanoidArray(wiScene scene);
// Decal
size_t wiScene_Component_GetDecalCount(wiScene scene);
wiDecalComponent *wiScene_Component_GetDecalArray(wiScene scene);
// Sprite
size_t wiScene_Component_GetSpriteCount(wiScene scene);
wiSpriteComponent *wiScene_Component_GetSpriteArray(wiScene scene);
// Font
size_t wiScene_Component_GetFontCount(wiScene scene);
wiFontComponent *wiScene_Component_GetFontArray(wiScene scene);
// VoxelGrid
size_t wiScene_Component_GetVoxelGridCount(wiScene scene);
wiVoxelGridComponent *wiScene_Component_GetVoxelGridArray(wiScene scene);
// Metadata
size_t wiScene_Component_GetMetadataCount(wiScene scene);
wiMetadataComponent *wiScene_Component_GetMetadataArray(wiScene scene);
// Character
size_t wiScene_Component_GetCharacterCount(wiScene scene);
wiCharacterComponent *wiScene_Component_GetCharacterArray(wiScene scene);
wiCharacterComponent wiScene_Component_CreateCharacter(wiScene scene,
                                                       wiEntity entity);
wiCharacterComponent wiScene_Component_GetCharacter(wiScene scene,
                                                    wiEntity entity);

#ifdef __cplusplus
}
#endif
