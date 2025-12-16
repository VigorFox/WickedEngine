#include "wiScene_API.h"
#include "../wiECS.h"
#include "../wiHelper.h"
#include "../wiScene.h"

using namespace wi::scene;
using namespace wi::ecs;

extern "C" {

// --- wiScene ---
wiScene wiScene_GetGlobal() { return (wiScene)&wi::scene::GetScene(); }

void wiScene_Update(wiScene scene, float dt) {
  if (scene)
    ((Scene *)scene)->Update(dt);
}

void wiScene_Clear(wiScene scene) {
  if (scene)
    ((Scene *)scene)->Clear();
}

void wiScene_Merge(wiScene scene, wiScene other) {
  if (scene && other)
    ((Scene *)scene)->Merge(*(Scene *)other);
}

// --- Entity Management ---
wiEntity wiScene_Entity_Create(wiScene scene) {
  // Entity creation is global in ECS, but conceptually part of scene management
  // if we attach components. wi::ecs::CreateEntity() creates a new ID.
  return (wiEntity)wi::ecs::CreateEntity();
}

void wiScene_Entity_Remove(wiScene scene, wiEntity entity) {
  if (scene)
    ((Scene *)scene)->Entity_Remove((Entity)entity);
}

wiEntity wiScene_Entity_Duplicate(wiScene scene, wiEntity entity) {
  if (scene)
    return (wiEntity)((Scene *)scene)->Entity_Duplicate((Entity)entity);
  return WI_INVALID_ENTITY;
}

bool wiScene_Entity_IsDescendant(wiScene scene, wiEntity entity,
                                 wiEntity ancestor) {
  if (scene)
    return ((Scene *)scene)
        ->Entity_IsDescendant((Entity)entity, (Entity)ancestor);
  return false;
}

wiEntity wiScene_Entity_FindByName(wiScene scene, const char *name,
                                   wiEntity ancestor) {
  if (scene && name)
    return (wiEntity)((Scene *)scene)
        ->Entity_FindByName(name, (Entity)ancestor);
  return WI_INVALID_ENTITY;
}

// --- Component: Name ---
wiNameComponent wiScene_Component_CreateName(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiNameComponent) & ((Scene *)scene)->names.Create((Entity)entity);
}

wiNameComponent wiScene_Component_GetName(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiNameComponent)((Scene *)scene)->names.GetComponent((Entity)entity);
}

void wiScene_Component_RemoveName(wiScene scene, wiEntity entity) {
  if (scene)
    ((Scene *)scene)->names.Remove((Entity)entity);
}

void wiNameComponent_Set(wiNameComponent component, const char *name) {
  if (component && name)
    ((NameComponent *)component)->name = name;
}

const char *wiNameComponent_Get(wiNameComponent component) {
  if (component)
    return ((NameComponent *)component)->name.c_str();
  return "";
}

// --- Component: Layer ---
wiLayerComponent wiScene_Component_CreateLayer(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiLayerComponent) & ((Scene *)scene)->layers.Create((Entity)entity);
}

wiLayerComponent wiScene_Component_GetLayer(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiLayerComponent)((Scene *)scene)
      ->layers.GetComponent((Entity)entity);
}

void wiScene_Component_RemoveLayer(wiScene scene, wiEntity entity) {
  if (scene)
    ((Scene *)scene)->layers.Remove((Entity)entity);
}

void wiLayerComponent_SetLayerMask(wiLayerComponent component,
                                   uint32_t layerMask) {
  if (component)
    ((LayerComponent *)component)->layerMask = layerMask;
}

uint32_t wiLayerComponent_GetLayerMask(wiLayerComponent component) {
  if (component)
    return ((LayerComponent *)component)->layerMask;
  return 0;
}

// --- Component: Transform ---
wiTransformComponent wiScene_Component_CreateTransform(wiScene scene,
                                                       wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiTransformComponent) &
         ((Scene *)scene)->transforms.Create((Entity)entity);
}

wiTransformComponent wiScene_Component_GetTransform(wiScene scene,
                                                    wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiTransformComponent)((Scene *)scene)
      ->transforms.GetComponent((Entity)entity);
}

void wiScene_Component_RemoveTransform(wiScene scene, wiEntity entity) {
  if (scene)
    ((Scene *)scene)->transforms.Remove((Entity)entity);
}

void wiTransformComponent_SetPosition(wiTransformComponent component,
                                      wiVector position) {
  if (component) {
    ((TransformComponent *)component)->translation_local =
        XMFLOAT3(position.x, position.y, position.z);
  }
}

wiVector wiTransformComponent_GetPosition(wiTransformComponent component) {
  wiVector vec = {0, 0, 0, 0};
  if (component) {
    XMFLOAT3 pos = ((TransformComponent *)component)->translation_local;
    vec.x = pos.x;
    vec.y = pos.y;
    vec.z = pos.z;
  }
  return vec;
}

void wiTransformComponent_SetRotation(wiTransformComponent component,
                                      wiVector rotation) {
  if (component) {
    ((TransformComponent *)component)->rotation_local =
        XMFLOAT4(rotation.x, rotation.y, rotation.z, rotation.w);
  }
}

wiVector wiTransformComponent_GetRotation(wiTransformComponent component) {
  wiVector vec = {0, 0, 0, 1};
  if (component) {
    XMFLOAT4 rot = ((TransformComponent *)component)->rotation_local;
    vec.x = rot.x;
    vec.y = rot.y;
    vec.z = rot.z;
    vec.w = rot.w;
  }
  return vec;
}

void wiTransformComponent_SetScale(wiTransformComponent component,
                                   wiVector scale) {
  if (component) {
    ((TransformComponent *)component)->scale_local =
        XMFLOAT3(scale.x, scale.y, scale.z);
  }
}

wiVector wiTransformComponent_GetScale(wiTransformComponent component) {
  wiVector vec = {1, 1, 1, 0};
  if (component) {
    XMFLOAT3 s = ((TransformComponent *)component)->scale_local;
    vec.x = s.x;
    vec.y = s.y;
    vec.z = s.z;
  }
  return vec;
}

void wiTransformComponent_UpdateTransform(wiTransformComponent component) {
  if (component)
    ((TransformComponent *)component)->UpdateTransform();
}

void wiTransformComponent_Translate(wiTransformComponent component,
                                    wiVector translation) {
  if (component)
    ((TransformComponent *)component)
        ->Translate(XMLoadFloat3((XMFLOAT3 *)&translation));
}

void wiTransformComponent_Rotate(wiTransformComponent component,
                                 wiVector quaternion) {
  if (component)
    ((TransformComponent *)component)
        ->Rotate(XMLoadFloat4((XMFLOAT4 *)&quaternion));
}

void wiTransformComponent_Scale(wiTransformComponent component,
                                wiVector scale) {
  if (component)
    ((TransformComponent *)component)->Scale(XMLoadFloat3((XMFLOAT3 *)&scale));
}

wiMatrix wiTransformComponent_GetMatrix(wiTransformComponent component) {
  wiMatrix mat = {0};
  if (component) {
    mat = *(wiMatrix *)&((TransformComponent *)component)->world;
  }
  return mat;
}

// --- Component: Mesh ---
wiMeshComponent wiScene_Component_CreateMesh(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMeshComponent) & ((Scene *)scene)->meshes.Create((Entity)entity);
}

wiMeshComponent wiScene_Component_GetMesh(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMeshComponent)((Scene *)scene)->meshes.GetComponent((Entity)entity);
}

// --- Component: Material ---
wiMaterialComponent wiScene_Component_CreateMaterial(wiScene scene,
                                                     wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMaterialComponent) &
         ((Scene *)scene)->materials.Create((Entity)entity);
}

wiMaterialComponent wiScene_Component_GetMaterial(wiScene scene,
                                                  wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMaterialComponent)((Scene *)scene)
      ->materials.GetComponent((Entity)entity);
}

// --- Component: Object ---
wiObjectComponent wiScene_Component_CreateObject(wiScene scene,
                                                 wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiObjectComponent) & ((Scene *)scene)->objects.Create((Entity)entity);
}

wiObjectComponent wiScene_Component_GetObject(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiObjectComponent)((Scene *)scene)
      ->objects.GetComponent((Entity)entity);
}

void wiObjectComponent_SetMeshID(wiObjectComponent component,
                                 wiEntity meshEntity) {
  if (component)
    ((ObjectComponent *)component)->meshID = (Entity)meshEntity;
}

wiEntity wiObjectComponent_GetMeshID(wiObjectComponent component) {
  if (component)
    return (wiEntity)((ObjectComponent *)component)->meshID;
  return WI_INVALID_ENTITY;
}

// --- Component: Light ---
wiLightComponent wiScene_Component_CreateLight(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiLightComponent) & ((Scene *)scene)->lights.Create((Entity)entity);
}

wiLightComponent wiScene_Component_GetLight(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiLightComponent)((Scene *)scene)
      ->lights.GetComponent((Entity)entity);
}

void wiLightComponent_SetType(wiLightComponent component, int type) {
  if (component)
    ((LightComponent *)component)->SetType((LightComponent::LightType)type);
}

void wiLightComponent_SetColor(wiLightComponent component, wiVector color) {
  if (component) {
    ((LightComponent *)component)->color = XMFLOAT3(color.x, color.y, color.z);
  }
}

void wiLightComponent_SetIntensity(wiLightComponent component,
                                   float intensity) {
  if (component)
    ((LightComponent *)component)->intensity = intensity;
}

void wiLightComponent_SetRange(wiLightComponent component, float range) {
  if (component)
    ((LightComponent *)component)->range = range;
}

// --- Component: Camera ---
wiCameraComponent wiScene_Component_CreateCamera(wiScene scene,
                                                 wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiCameraComponent) & ((Scene *)scene)->cameras.Create((Entity)entity);
}

wiCameraComponent wiScene_Component_GetCamera(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiCameraComponent)((Scene *)scene)
      ->cameras.GetComponent((Entity)entity);
}

void wiCameraComponent_UpdateCamera(wiCameraComponent component) {
  if (component)
    ((CameraComponent *)component)->UpdateCamera();
}

void wiCameraComponent_SetFOV(wiCameraComponent component, float fov) {
  if (component)
    ((CameraComponent *)component)->fov = fov;
}

float wiCameraComponent_GetFOV(wiCameraComponent component) {
  if (component)
    return ((CameraComponent *)component)->fov;
  return 0.0f;
}

void wiCameraComponent_SetNearPlane(wiCameraComponent component,
                                    float nearPlane) {
  if (component)
    ((CameraComponent *)component)->zNearP = nearPlane;
}

void wiCameraComponent_SetFarPlane(wiCameraComponent component,
                                   float farPlane) {
  if (component)
    ((CameraComponent *)component)->zFarP = farPlane;
}

// --- Component: RigidBody Physics ---
wiRigidBodyPhysicsComponent
wiScene_Component_CreateRigidBodyPhysics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiRigidBodyPhysicsComponent) &
         ((Scene *)scene)->rigidbodies.Create((Entity)entity);
}

wiRigidBodyPhysicsComponent
wiScene_Component_GetRigidBodyPhysics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiRigidBodyPhysicsComponent)((Scene *)scene)
      ->rigidbodies.GetComponent((Entity)entity);
}

// --- Component: SoftBody Physics ---
wiSoftBodyPhysicsComponent
wiScene_Component_CreateSoftBodyPhysics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSoftBodyPhysicsComponent) &
         ((Scene *)scene)->softbodies.Create((Entity)entity);
}

wiSoftBodyPhysicsComponent
wiScene_Component_GetSoftBodyPhysics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSoftBodyPhysicsComponent)((Scene *)scene)
      ->softbodies.GetComponent((Entity)entity);
}

// --- Component: Force Field ---
wiForceFieldComponent wiScene_Component_CreateForceField(wiScene scene,
                                                         wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiForceFieldComponent) &
         ((Scene *)scene)->forces.Create((Entity)entity);
}

wiForceFieldComponent wiScene_Component_GetForceField(wiScene scene,
                                                      wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiForceFieldComponent)((Scene *)scene)
      ->forces.GetComponent((Entity)entity);
}

// --- Component: Weather ---
wiWeatherComponent wiScene_Component_CreateWeather(wiScene scene,
                                                   wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiWeatherComponent) &
         ((Scene *)scene)->weathers.Create((Entity)entity);
}

wiWeatherComponent wiScene_Component_GetWeather(wiScene scene,
                                                wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiWeatherComponent)((Scene *)scene)
      ->weathers.GetComponent((Entity)entity);
}

// --- Component: Animation ---
wiAnimationComponent wiScene_Component_CreateAnimation(wiScene scene,
                                                       wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiAnimationComponent) &
         ((Scene *)scene)->animations.Create((Entity)entity);
}

wiAnimationComponent wiScene_Component_GetAnimation(wiScene scene,
                                                    wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiAnimationComponent)((Scene *)scene)
      ->animations.GetComponent((Entity)entity);
}

} // extern "C"
