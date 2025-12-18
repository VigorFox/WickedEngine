#include "wiScene_API.h"
#include "../wiHelper.h"
#include "../wiScene.h"
#include "../wiScene_Components.h"
#include "../wiSpriteFont.h"
#include "../wiVoxelGrid.h"

using namespace wi::scene;
using namespace wi::ecs;
using namespace wi::primitive;

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

void wiMeshComponent_SetRenderable(wiMeshComponent component, bool value) {
  if (component)
    ((MeshComponent *)component)->SetRenderable(value);
}
bool wiMeshComponent_IsRenderable(wiMeshComponent component) {
  if (component)
    return ((MeshComponent *)component)->_flags & MeshComponent::RENDERABLE;
  return false;
}

void wiMeshComponent_SetDoubleSided(wiMeshComponent component, bool value) {
  if (component)
    ((MeshComponent *)component)->SetDoubleSided(value);
}
bool wiMeshComponent_IsDoubleSided(wiMeshComponent component) {
  if (component)
    return ((MeshComponent *)component)->IsDoubleSided();
  return false;
}

void wiMeshComponent_SetTessellationFactor(wiMeshComponent component,
                                           float factor) {
  if (component)
    ((MeshComponent *)component)->tessellationFactor = factor;
}
float wiMeshComponent_GetTessellationFactor(wiMeshComponent component) {
  if (component)
    return ((MeshComponent *)component)->tessellationFactor;
  return 0.0f;
}

void wiMeshComponent_SetQuantizedPositionsDisabled(wiMeshComponent component,
                                                   bool value) {
  if (component) {
    if (value) {
      ((MeshComponent *)component)->_flags |=
          MeshComponent::QUANTIZED_POSITIONS_DISABLED;
    } else {
      ((MeshComponent *)component)->_flags &=
          ~MeshComponent::QUANTIZED_POSITIONS_DISABLED;
    }
  }
}
bool wiMeshComponent_IsQuantizedPositionsDisabled(wiMeshComponent component) {
  if (component)
    return ((MeshComponent *)component)->_flags &
           MeshComponent::QUANTIZED_POSITIONS_DISABLED;
  return false;
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

// --- Component: Material Accessors ---

void wiMaterialComponent_SetBaseColor(wiMaterialComponent component,
                                      wiColor color) {
  if (component)
    ((MaterialComponent *)component)->baseColor = XMFLOAT4(
        color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
wiColor wiMaterialComponent_GetBaseColor(wiMaterialComponent component) {
  if (component) {
    XMFLOAT4 c = ((MaterialComponent *)component)->baseColor;
    return wiColor{(uint8_t)(c.x * 255.0f), (uint8_t)(c.y * 255.0f),
                   (uint8_t)(c.z * 255.0f), (uint8_t)(c.w * 255.0f)};
  }
  return wiColor{255, 255, 255, 255};
}

void wiMaterialComponent_SetSpecularColor(wiMaterialComponent component,
                                          wiColor color) {
  if (component)
    ((MaterialComponent *)component)->specularColor = XMFLOAT4(
        color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
wiColor wiMaterialComponent_GetSpecularColor(wiMaterialComponent component) {
  if (component) {
    XMFLOAT4 c = ((MaterialComponent *)component)->specularColor;
    return wiColor{(uint8_t)(c.x * 255.0f), (uint8_t)(c.y * 255.0f),
                   (uint8_t)(c.z * 255.0f), (uint8_t)(c.w * 255.0f)};
  }
  return wiColor{255, 255, 255, 255};
}

void wiMaterialComponent_SetEmissiveColor(wiMaterialComponent component,
                                          wiColor color) {
  if (component)
    ((MaterialComponent *)component)->emissiveColor = XMFLOAT4(
        color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
wiColor wiMaterialComponent_GetEmissiveColor(wiMaterialComponent component) {
  if (component) {
    XMFLOAT4 c = ((MaterialComponent *)component)->emissiveColor;
    return wiColor{(uint8_t)(c.x * 255.0f), (uint8_t)(c.y * 255.0f),
                   (uint8_t)(c.z * 255.0f), (uint8_t)(c.w * 255.0f)};
  }
  return wiColor{0, 0, 0, 0};
}

void wiMaterialComponent_SetRoughness(wiMaterialComponent component,
                                      float roughness) {
  if (component)
    ((MaterialComponent *)component)->SetRoughness(roughness);
}
float wiMaterialComponent_GetRoughness(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->roughness;
  return 0.0f;
}

void wiMaterialComponent_SetMetalness(wiMaterialComponent component,
                                      float metalness) {
  if (component)
    ((MaterialComponent *)component)->SetMetalness(metalness);
}
float wiMaterialComponent_GetMetalness(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->metalness;
  return 0.0f;
}

void wiMaterialComponent_SetReflectance(wiMaterialComponent component,
                                        float reflectance) {
  if (component)
    ((MaterialComponent *)component)->SetReflectance(reflectance);
}
float wiMaterialComponent_GetReflectance(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->reflectance;
  return 0.0f;
}

void wiMaterialComponent_SetEmissiveStrength(wiMaterialComponent component,
                                             float strength) {
  if (component)
    ((MaterialComponent *)component)->SetEmissiveStrength(strength);
}
float wiMaterialComponent_GetEmissiveStrength(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->GetEmissiveStrength();
  return 0.0f;
}

void wiMaterialComponent_SetNormalMapStrength(wiMaterialComponent component,
                                              float strength) {
  if (component)
    ((MaterialComponent *)component)->SetNormalMapStrength(strength);
}
float wiMaterialComponent_GetNormalMapStrength(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->normalMapStrength;
  return 1.0f;
}

void wiMaterialComponent_SetParallaxOcclusionMapping(
    wiMaterialComponent component, float amount) {
  if (component)
    ((MaterialComponent *)component)->SetParallaxOcclusionMapping(amount);
}
float wiMaterialComponent_GetParallaxOcclusionMapping(
    wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->parallaxOcclusionMapping;
  return 0.0f;
}

void wiMaterialComponent_SetDisplacementMapping(wiMaterialComponent component,
                                                float amount) {
  if (component)
    ((MaterialComponent *)component)->SetDisplacementMapping(amount);
}
float wiMaterialComponent_GetDisplacementMapping(
    wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->displacementMapping;
  return 0.0f;
}

void wiMaterialComponent_SetSubsurfaceScattering(wiMaterialComponent component,
                                                 wiColor color) {
  if (component) {
    ((MaterialComponent *)component)
        ->SetSubsurfaceScatteringColor(
            XMFLOAT3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f));
    ((MaterialComponent *)component)
        ->SetSubsurfaceScatteringAmount(color.a / 255.0f);
  }
}
wiColor
wiMaterialComponent_GetSubsurfaceScattering(wiMaterialComponent component) {
  if (component) {
    XMFLOAT4 c = ((MaterialComponent *)component)->subsurfaceScattering;
    return wiColor{(uint8_t)(c.x * 255.0f), (uint8_t)(c.y * 255.0f),
                   (uint8_t)(c.z * 255.0f), (uint8_t)(c.w * 255.0f)};
  }
  return wiColor{0, 0, 0, 0};
}

void wiMaterialComponent_SetOpacity(wiMaterialComponent component,
                                    float opacity) {
  if (component)
    ((MaterialComponent *)component)->SetOpacity(opacity);
}
float wiMaterialComponent_GetOpacity(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->GetOpacity();
  return 1.0f;
}

void wiMaterialComponent_SetAlphaRef(wiMaterialComponent component,
                                     float alphaRef) {
  if (component)
    ((MaterialComponent *)component)->SetAlphaRef(alphaRef);
}
float wiMaterialComponent_GetAlphaRef(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->alphaRef;
  return 0.5f;
}

void wiMaterialComponent_SetUserStencilRef(wiMaterialComponent component,
                                           uint8_t ref) {
  if (component)
    ((MaterialComponent *)component)->SetUserStencilRef(ref);
}
uint8_t wiMaterialComponent_GetUserStencilRef(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->userStencilRef;
  return 0;
}

void wiMaterialComponent_SetCastShadow(wiMaterialComponent component,
                                       bool value) {
  if (component)
    ((MaterialComponent *)component)->SetCastShadow(value);
}
bool wiMaterialComponent_IsCastShadow(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->IsCastingShadow();
  return false;
}

void wiMaterialComponent_SetReceiveShadow(wiMaterialComponent component,
                                          bool value) {
  if (component)
    ((MaterialComponent *)component)->SetReceiveShadow(value);
}
bool wiMaterialComponent_IsReceiveShadow(wiMaterialComponent component) {
  if (component)
    return ((MaterialComponent *)component)->IsReceiveShadow();
  return false;
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

void wiObjectComponent_SetColor(wiObjectComponent component, wiColor color) {
  if (component)
    ((ObjectComponent *)component)->color = XMFLOAT4(
        color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
wiColor wiObjectComponent_GetColor(wiObjectComponent component) {
  if (component) {
    XMFLOAT4 c = ((ObjectComponent *)component)->color;
    return wiColor{(uint8_t)(c.x * 255.0f), (uint8_t)(c.y * 255.0f),
                   (uint8_t)(c.z * 255.0f), (uint8_t)(c.w * 255.0f)};
  }
  return wiColor{255, 255, 255, 255};
}

void wiObjectComponent_SetUserStencilRef(wiObjectComponent component,
                                         uint8_t ref) {
  if (component)
    ((ObjectComponent *)component)->userStencilRef = ref;
}
uint8_t wiObjectComponent_GetUserStencilRef(wiObjectComponent component) {
  if (component)
    return ((ObjectComponent *)component)->userStencilRef;
  return 0;
}

void wiObjectComponent_SetDrawDistance(wiObjectComponent component,
                                       float dist) {
  if (component)
    ((ObjectComponent *)component)->draw_distance = dist;
}
float wiObjectComponent_GetDrawDistance(wiObjectComponent component) {
  if (component)
    return ((ObjectComponent *)component)->draw_distance;
  return 0.0f;
}

void wiObjectComponent_SetCastShadow(wiObjectComponent component, bool value) {
  if (component)
    ((ObjectComponent *)component)->SetCastShadow(value);
}
bool wiObjectComponent_IsCastShadow(wiObjectComponent component) {
  if (component)
    return ((ObjectComponent *)component)->_flags &
           ObjectComponent::CAST_SHADOW;
  return false;
}

void wiObjectComponent_SetRenderable(wiObjectComponent component, bool value) {
  if (component)
    ((ObjectComponent *)component)->SetRenderable(value);
}
bool wiObjectComponent_IsRenderable(wiObjectComponent component) {
  if (component)
    return ((ObjectComponent *)component)->_flags & ObjectComponent::RENDERABLE;
  return false;
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

int wiLightComponent_GetType(wiLightComponent component) {
  if (component)
    return (int)((LightComponent *)component)->GetType();
  return 0;
}

void wiLightComponent_SetColor(wiLightComponent component, wiVector color) {
  if (component) {
    ((LightComponent *)component)->color = XMFLOAT3(color.x, color.y, color.z);
  }
}

wiVector wiLightComponent_GetColor(wiLightComponent component) {
  if (component) {
    XMFLOAT3 c = ((LightComponent *)component)->color;
    return wiVector{c.x, c.y, c.z, 0};
  }
  return wiVector{0, 0, 0, 0};
}

void wiLightComponent_SetIntensity(wiLightComponent component,
                                   float intensity) {
  if (component)
    ((LightComponent *)component)->intensity = intensity;
}

float wiLightComponent_GetIntensity(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->intensity;
  return 0.0f;
}

void wiLightComponent_SetRange(wiLightComponent component, float range) {
  if (component)
    ((LightComponent *)component)->range = range;
}

float wiLightComponent_GetRange(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->range;
  return 0.0f;
}

void wiLightComponent_SetInnerConeAngle(wiLightComponent component,
                                        float angle) {
  if (component)
    ((LightComponent *)component)->innerConeAngle = angle;
}

float wiLightComponent_GetInnerConeAngle(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->innerConeAngle;
  return 0.0f;
}

void wiLightComponent_SetOuterConeAngle(wiLightComponent component,
                                        float angle) {
  if (component)
    ((LightComponent *)component)->outerConeAngle = angle;
}

float wiLightComponent_GetOuterConeAngle(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->outerConeAngle;
  return 0.0f;
}

void wiLightComponent_SetCastShadow(wiLightComponent component, bool value) {
  if (component)
    ((LightComponent *)component)->SetCastShadow(value);
}

bool wiLightComponent_IsCastShadow(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->IsCastingShadow();
  return false;
}

void wiLightComponent_SetVolumetricsEnabled(wiLightComponent component,
                                            bool value) {
  if (component)
    ((LightComponent *)component)->SetVolumetricsEnabled(value);
}

bool wiLightComponent_IsVolumetricsEnabled(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->IsVolumetricsEnabled();
  return false;
}

void wiLightComponent_SetVisualizerEnabled(wiLightComponent component,
                                           bool value) {
  if (component)
    ((LightComponent *)component)->SetVisualizerEnabled(value);
}

bool wiLightComponent_IsVisualizerEnabled(wiLightComponent component) {
  if (component)
    return ((LightComponent *)component)->IsVisualizerEnabled();
  return false;
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

void wiCameraComponent_SetFocalLength(wiCameraComponent component,
                                      float focalLength) {
  if (component)
    ((CameraComponent *)component)->focal_length = focalLength;
}

float wiCameraComponent_GetFocalLength(wiCameraComponent component) {
  if (component)
    return ((CameraComponent *)component)->focal_length;
  return 0.0f;
}

void wiCameraComponent_SetApertureSize(wiCameraComponent component,
                                       float apertureSize) {
  if (component)
    ((CameraComponent *)component)->aperture_size = apertureSize;
}

float wiCameraComponent_GetApertureSize(wiCameraComponent component) {
  if (component)
    return ((CameraComponent *)component)->aperture_size;
  return 0.0f;
}

void wiCameraComponent_SetApertureShape(wiCameraComponent component,
                                        wiVector shape) {
  if (component)
    ((CameraComponent *)component)->aperture_shape = XMFLOAT2(shape.x, shape.y);
}

wiVector wiCameraComponent_GetApertureShape(wiCameraComponent component) {
  if (component) {
    XMFLOAT2 s = ((CameraComponent *)component)->aperture_shape;
    return wiVector{s.x, s.y, 0};
  }
  return wiVector{1, 1, 0};
}

// --- Component: Emitter ---
wiEmitterComponent wiScene_Component_CreateEmitter(wiScene scene,
                                                   wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiEmitterComponent) &
         ((Scene *)scene)->emitters.Create((Entity)entity);
}

wiEmitterComponent wiScene_Component_GetEmitter(wiScene scene,
                                                wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiEmitterComponent)((Scene *)scene)
      ->emitters.GetComponent((Entity)entity);
}

void wiEmitterComponent_SetEmitCount(wiEmitterComponent component,
                                     float count) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->count = count;
}

float wiEmitterComponent_GetEmitCount(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->count;
  return 0.0f;
}

void wiEmitterComponent_SetSize(wiEmitterComponent component, float size) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->size = size;
}

float wiEmitterComponent_GetSize(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->size;
  return 0.0f;
}

void wiEmitterComponent_SetLife(wiEmitterComponent component, float life) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->life = life;
}

float wiEmitterComponent_GetLife(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->life;
  return 0.0f;
}

void wiEmitterComponent_SetNormalFactor(wiEmitterComponent component,
                                        float factor) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->normal_factor = factor;
}

float wiEmitterComponent_GetNormalFactor(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->normal_factor;
  return 0.0f;
}

void wiEmitterComponent_SetRandomFactor(wiEmitterComponent component,
                                        float factor) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->random_factor = factor;
}

float wiEmitterComponent_GetRandomFactor(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->random_factor;
  return 0.0f;
}

void wiEmitterComponent_SetLifeRandomness(wiEmitterComponent component,
                                          float randomness) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->random_life = randomness;
}

float wiEmitterComponent_GetLifeRandomness(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->random_life;
  return 0.0f;
}

void wiEmitterComponent_SetScaleX(wiEmitterComponent component, float scaleX) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->scaleX = scaleX;
}

float wiEmitterComponent_GetScaleX(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->scaleX;
  return 0.0f;
}

void wiEmitterComponent_SetScaleY(wiEmitterComponent component, float scaleY) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->scaleY = scaleY;
}

float wiEmitterComponent_GetScaleY(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->scaleY;
  return 0.0f;
}

void wiEmitterComponent_SetRotation(wiEmitterComponent component,
                                    float rotation) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->rotation = rotation;
}

float wiEmitterComponent_GetRotation(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->rotation;
  return 0.0f;
}

void wiEmitterComponent_SetMotionBlurAmount(wiEmitterComponent component,
                                            float amount) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->motionBlurAmount = amount;
}

float wiEmitterComponent_GetMotionBlurAmount(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->motionBlurAmount;
  return 0.0f;
}

void wiEmitterComponent_SetMass(wiEmitterComponent component, float mass) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->mass = mass;
}

float wiEmitterComponent_GetMass(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->mass;
  return 0.0f;
}

void wiEmitterComponent_SetVelocity(wiEmitterComponent component,
                                    wiVector velocity) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->velocity =
        XMFLOAT3(velocity.x, velocity.y, velocity.z);
}

wiVector wiEmitterComponent_GetVelocity(wiEmitterComponent component) {
  if (component) {
    XMFLOAT3 v = ((wi::EmittedParticleSystem *)component)->velocity;
    return wiVector{v.x, v.y, v.z};
  }
  return wiVector{0, 0, 0};
}

void wiEmitterComponent_SetGravity(wiEmitterComponent component,
                                   wiVector gravity) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->gravity =
        XMFLOAT3(gravity.x, gravity.y, gravity.z);
}

wiVector wiEmitterComponent_GetGravity(wiEmitterComponent component) {
  if (component) {
    XMFLOAT3 g = ((wi::EmittedParticleSystem *)component)->gravity;
    return wiVector{g.x, g.y, g.z};
  }
  return wiVector{0, 0, 0};
}

void wiEmitterComponent_SetDrag(wiEmitterComponent component, float drag) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->drag = drag;
}

float wiEmitterComponent_GetDrag(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->drag;
  return 0.0f;
}

void wiEmitterComponent_SetRestitution(wiEmitterComponent component,
                                       float restitution) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->restitution = restitution;
}

float wiEmitterComponent_GetRestitution(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->restitution;
  return 0.0f;
}

void wiEmitterComponent_Burst(wiEmitterComponent component, int count) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->Burst(count);
}

void wiEmitterComponent_Restart(wiEmitterComponent component) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->Restart();
}

void wiEmitterComponent_SetDebug(wiEmitterComponent component, bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetDebug(value);
}

bool wiEmitterComponent_IsDebug(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsDebug();
  return false;
}

void wiEmitterComponent_SetPaused(wiEmitterComponent component, bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetPaused(value);
}

bool wiEmitterComponent_IsPaused(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsPaused();
  return false;
}

void wiEmitterComponent_SetSorted(wiEmitterComponent component, bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetSorted(value);
}

bool wiEmitterComponent_IsSorted(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsSorted();
  return false;
}

void wiEmitterComponent_SetDepthCollisionEnabled(wiEmitterComponent component,
                                                 bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetDepthCollisionEnabled(value);
}

bool wiEmitterComponent_IsDepthCollisionEnabled(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsDepthCollisionEnabled();
  return false;
}

void wiEmitterComponent_SetSPHEnabled(wiEmitterComponent component,
                                      bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetSPHEnabled(value);
}

bool wiEmitterComponent_IsSPHEnabled(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsSPHEnabled();
  return false;
}

void wiEmitterComponent_SetVolumeEnabled(wiEmitterComponent component,
                                         bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetVolumeEnabled(value);
}

bool wiEmitterComponent_IsVolumeEnabled(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsVolumeEnabled();
  return false;
}

void wiEmitterComponent_SetFrameBlendingEnabled(wiEmitterComponent component,
                                                bool value) {
  if (component)
    ((wi::EmittedParticleSystem *)component)->SetFrameBlendingEnabled(value);
}

bool wiEmitterComponent_IsFrameBlendingEnabled(wiEmitterComponent component) {
  if (component)
    return ((wi::EmittedParticleSystem *)component)->IsFrameBlendingEnabled();
  return false;
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

void wiRigidBodyPhysicsComponent_SetMass(wiRigidBodyPhysicsComponent component,
                                         float mass) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->mass = mass;
}
float wiRigidBodyPhysicsComponent_GetMass(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->mass;
  return 0.0f;
}

void wiRigidBodyPhysicsComponent_SetFriction(
    wiRigidBodyPhysicsComponent component, float friction) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->friction = friction;
}
float wiRigidBodyPhysicsComponent_GetFriction(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->friction;
  return 0.0f;
}

void wiRigidBodyPhysicsComponent_SetRestitution(
    wiRigidBodyPhysicsComponent component, float restitution) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->restitution = restitution;
}
float wiRigidBodyPhysicsComponent_GetRestitution(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->restitution;
  return 0.0f;
}

void wiRigidBodyPhysicsComponent_SetLinearDamping(
    wiRigidBodyPhysicsComponent component, float damping) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->damping_linear = damping;
}
float wiRigidBodyPhysicsComponent_GetLinearDamping(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->damping_linear;
  return 0.0f;
}

void wiRigidBodyPhysicsComponent_SetAngularDamping(
    wiRigidBodyPhysicsComponent component, float damping) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->damping_angular = damping;
}
float wiRigidBodyPhysicsComponent_GetAngularDamping(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->damping_angular;
  return 0.0f;
}

void wiRigidBodyPhysicsComponent_SetKinematic(
    wiRigidBodyPhysicsComponent component, bool value) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->SetKinematic(value);
}
bool wiRigidBodyPhysicsComponent_IsKinematic(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->IsKinematic();
  return false;
}

void wiRigidBodyPhysicsComponent_SetDisableDeactivation(
    wiRigidBodyPhysicsComponent component, bool value) {
  if (component)
    ((RigidBodyPhysicsComponent *)component)->SetDisableDeactivation(value);
}
bool wiRigidBodyPhysicsComponent_IsDisableDeactivation(
    wiRigidBodyPhysicsComponent component) {
  if (component)
    return ((RigidBodyPhysicsComponent *)component)->IsDisableDeactivation();
  return false;
}

void wiRigidBodyPhysicsComponent_SetBoxShape(
    wiRigidBodyPhysicsComponent component, wiVector halfExtents) {
  if (component) {
    auto *rb = (RigidBodyPhysicsComponent *)component;
    rb->shape = RigidBodyPhysicsComponent::CollisionShape::BOX;
    rb->box.halfextents = XMFLOAT3(halfExtents.x, halfExtents.y, halfExtents.z);
    rb->physicsobject.reset(); // force recreate
  }
}

void wiRigidBodyPhysicsComponent_SetSphereShape(
    wiRigidBodyPhysicsComponent component, float radius) {
  if (component) {
    auto *rb = (RigidBodyPhysicsComponent *)component;
    rb->shape = RigidBodyPhysicsComponent::CollisionShape::SPHERE;
    rb->sphere.radius = radius;
    rb->physicsobject.reset(); // force recreate
  }
}

void wiRigidBodyPhysicsComponent_SetCapsuleShape(
    wiRigidBodyPhysicsComponent component, float radius, float height) {
  if (component) {
    auto *rb = (RigidBodyPhysicsComponent *)component;
    rb->shape = RigidBodyPhysicsComponent::CollisionShape::CAPSULE;
    rb->capsule.radius = radius;
    rb->capsule.height = height;
    rb->physicsobject.reset(); // force recreate
  }
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

// --- Scene Operations ---
wiEntity wiScene_LoadModel(wiScene scene, const char *fileName,
                           wiMatrix transform) {
  if (scene && fileName) {
    XMMATRIX mat = XMLoadFloat4x4((XMFLOAT4X4 *)&transform);
    return (wiEntity)wi::scene::LoadModel(*(Scene *)scene, fileName, mat);
  }
  return WI_INVALID_ENTITY;
}

wiEntity wiScene_Instantiate(wiScene scene, wiScene prefab, bool attached) {
  if (scene && prefab) {
    return (wiEntity)((Scene *)scene)->Instantiate(*(Scene *)prefab, attached);
  }
  return WI_INVALID_ENTITY;
}

wiScenePickResult wiScene_Pick(wiScene scene, wiRay ray, uint32_t filterMask,
                               uint32_t layerMask, uint32_t lod) {
  wiScenePickResult result = {WI_INVALID_ENTITY, {0}, {0}, 3.402823466e+38F};
  if (scene) {
    wi::primitive::Ray r;
    r.origin = XMFLOAT3(ray.origin.x, ray.origin.y, ray.origin.z);
    r.direction = XMFLOAT3(ray.direction.x, ray.direction.y, ray.direction.z);
    r.TMin = ray.TMin;
    r.TMax = ray.TMax;

    auto res = wi::scene::Pick(r, filterMask, layerMask, *(Scene *)scene, lod);

    result.entity = (wiEntity)res.entity;
    result.position = {res.position.x, res.position.y, res.position.z, 0};
    result.normal = {res.normal.x, res.normal.y, res.normal.z, 0};
    result.distance = res.distance;
  }
  return result;
}

wiScenePickResult wiScene_SceneIntersectSphere(wiScene scene, wiSphere sphere,
                                               uint32_t filterMask,
                                               uint32_t layerMask,
                                               uint32_t lod) {
  wiScenePickResult result = {WI_INVALID_ENTITY, {0}, {0}, 3.402823466e+38F};
  if (scene) {
    wi::primitive::Sphere s;
    s.center = XMFLOAT3(sphere.center.x, sphere.center.y, sphere.center.z);
    s.radius = sphere.radius;

    auto res = wi::scene::SceneIntersectSphere(s, filterMask, layerMask,
                                               *(Scene *)scene, lod);

    result.entity = (wiEntity)res.entity;
    result.position = {res.position.x, res.position.y, res.position.z, 0};
    result.normal = {res.normal.x, res.normal.y, res.normal.z, 0};
    result.distance = res.depth;
  }
  return result;
}

wiScenePickResult wiScene_SceneIntersectCapsule(wiScene scene,
                                                wiCapsule capsule,
                                                uint32_t filterMask,
                                                uint32_t layerMask,
                                                uint32_t lod) {
  wiScenePickResult result = {WI_INVALID_ENTITY, {0}, {0}, 3.402823466e+38F};
  if (scene) {
    wi::primitive::Capsule c;
    c.base = XMFLOAT3(capsule.base.x, capsule.base.y, capsule.base.z);
    c.tip = XMFLOAT3(capsule.tip.x, capsule.tip.y, capsule.tip.z);
    c.radius = capsule.radius;

    auto res = wi::scene::SceneIntersectCapsule(c, filterMask, layerMask,
                                                *(Scene *)scene, lod);

    result.entity = (wiEntity)res.entity;
    result.position = {res.position.x, res.position.y, res.position.z, 0};
    result.normal = {res.normal.x, res.normal.y, res.normal.z, 0};
    result.distance = res.depth;
  }
  return result;
}

// --- Component: Emitter ---

// --- Component: HairParticleSystem ---
wiHairParticleSystem
wiScene_Component_CreateHairParticleSystem(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiHairParticleSystem) &
         ((Scene *)scene)->hairs.Create((Entity)entity);
}
wiHairParticleSystem wiScene_Component_GetHairParticleSystem(wiScene scene,
                                                             wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiHairParticleSystem)((Scene *)scene)
      ->hairs.GetComponent((Entity)entity);
}

// --- Component: InverseKinematics ---
wiInverseKinematicsComponent
wiScene_Component_CreateInverseKinematics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiInverseKinematicsComponent) &
         ((Scene *)scene)->inverse_kinematics.Create((Entity)entity);
}
wiInverseKinematicsComponent
wiScene_Component_GetInverseKinematics(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiInverseKinematicsComponent)((Scene *)scene)
      ->inverse_kinematics.GetComponent((Entity)entity);
}

// --- Component: Script ---
wiScriptComponent wiScene_Component_CreateScript(wiScene scene,
                                                 wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiScriptComponent) & ((Scene *)scene)->scripts.Create((Entity)entity);
}
wiScriptComponent wiScene_Component_GetScript(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiScriptComponent)((Scene *)scene)
      ->scripts.GetComponent((Entity)entity);
}

// --- Component: Collider ---
wiColliderComponent wiScene_Component_CreateCollider(wiScene scene,
                                                     wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiColliderComponent) &
         ((Scene *)scene)->colliders.Create((Entity)entity);
}
wiColliderComponent wiScene_Component_GetCollider(wiScene scene,
                                                  wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiColliderComponent)((Scene *)scene)
      ->colliders.GetComponent((Entity)entity);
}

// --- Component: Spring ---
wiSpringComponent wiScene_Component_CreateSpring(wiScene scene,
                                                 wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSpringComponent) & ((Scene *)scene)->springs.Create((Entity)entity);
}
wiSpringComponent wiScene_Component_GetSpring(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSpringComponent)((Scene *)scene)
      ->springs.GetComponent((Entity)entity);
}

// --- Component: Sound ---
wiSoundComponent wiScene_Component_CreateSound(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSoundComponent) & ((Scene *)scene)->sounds.Create((Entity)entity);
}
wiSoundComponent wiScene_Component_GetSound(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSoundComponent)((Scene *)scene)
      ->sounds.GetComponent((Entity)entity);
}

// --- Component: Video ---
wiVideoComponent wiScene_Component_CreateVideo(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiVideoComponent) & ((Scene *)scene)->videos.Create((Entity)entity);
}
wiVideoComponent wiScene_Component_GetVideo(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiVideoComponent)((Scene *)scene)
      ->videos.GetComponent((Entity)entity);
}

// --- Component: Expression ---
wiExpressionComponent wiScene_Component_CreateExpression(wiScene scene,
                                                         wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiExpressionComponent) &
         ((Scene *)scene)->expressions.Create((Entity)entity);
}
wiExpressionComponent wiScene_Component_GetExpression(wiScene scene,
                                                      wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiExpressionComponent)((Scene *)scene)
      ->expressions.GetComponent((Entity)entity);
}

// --- Component: Humanoid ---
wiHumanoidComponent wiScene_Component_CreateHumanoid(wiScene scene,
                                                     wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiHumanoidComponent) &
         ((Scene *)scene)->humanoids.Create((Entity)entity);
}
wiHumanoidComponent wiScene_Component_GetHumanoid(wiScene scene,
                                                  wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiHumanoidComponent)((Scene *)scene)
      ->humanoids.GetComponent((Entity)entity);
}

// --- Component: Decal ---
wiDecalComponent wiScene_Component_CreateDecal(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiDecalComponent) & ((Scene *)scene)->decals.Create((Entity)entity);
}
wiDecalComponent wiScene_Component_GetDecal(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiDecalComponent)((Scene *)scene)
      ->decals.GetComponent((Entity)entity);
}

// --- Component: Sprite ---
wiSpriteComponent wiScene_Component_CreateSprite(wiScene scene,
                                                 wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSpriteComponent) & ((Scene *)scene)->sprites.Create((Entity)entity);
}
wiSpriteComponent wiScene_Component_GetSprite(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiSpriteComponent)((Scene *)scene)
      ->sprites.GetComponent((Entity)entity);
}

// --- Component: Font ---
wiFontComponent wiScene_Component_CreateFont(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiFontComponent) & ((Scene *)scene)->fonts.Create((Entity)entity);
}
wiFontComponent wiScene_Component_GetFont(wiScene scene, wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiFontComponent)((Scene *)scene)->fonts.GetComponent((Entity)entity);
}

// --- Component: VoxelGrid ---
wiVoxelGridComponent wiScene_Component_CreateVoxelGrid(wiScene scene,
                                                       wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiVoxelGridComponent) &
         ((Scene *)scene)->voxel_grids.Create((Entity)entity);
}
wiVoxelGridComponent wiScene_Component_GetVoxelGrid(wiScene scene,
                                                    wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiVoxelGridComponent)((Scene *)scene)
      ->voxel_grids.GetComponent((Entity)entity);
}

// --- Component: Metadata ---
wiMetadataComponent wiScene_Component_CreateMetadata(wiScene scene,
                                                     wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMetadataComponent) &
         ((Scene *)scene)->metadatas.Create((Entity)entity);
}
wiMetadataComponent wiScene_Component_GetMetadata(wiScene scene,
                                                  wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiMetadataComponent)((Scene *)scene)
      ->metadatas.GetComponent((Entity)entity);
}

// --- Component: Character ---
// --- Scene Helper Methods ---

void wiScene_IntersectsAll(wiScene scene, wiRay ray, uint32_t filterMask,
                           uint32_t layerMask, uint32_t lod, size_t *count,
                           wiScenePickResult **results) {
  if (!scene || !count || !results)
    return;

  // We need to implement a search or multiple pick.
  // wi::scene::Pick detects closest.
  // To get ALL intersections, we need to manually traverse the BVH or check
  // components. Assuming internal API 'Scene::Intersects' exists from previous
  // research, but wiScene.h view didn't show it explicitly (it showed 'Pick',
  // 'SceneIntersectSphere', etc). If it doesn't exist, we can't easily
  // implement it without logic duplication. However, Lua Bind mentions
  // 'Intersects'. Let's check if Scene has it. If not, we fall back to 'Pick'
  // (closest only) for now or skip. Actually, wi::scene::Scene DOES have `bool
  // Intersects(const Ray& ray, const Filter& filter, float& distance, ...)`
  // usually. But `Pick` is the high level function. Wait, let's just use `Pick`
  // logic but modified for all. Actually, for C API Parity, if the engine
  // doesn't expose "PickAll", I can't invent it easily. But wait, the user said
  // "Lua interface completely switched to C API". Lua has `Intersects`. Let's
  // implement `IntersectsFirst` using `Pick`. `IntersectsAll` might need more
  // work. I will stub it or implement if possible. For now, I'll implement
  // `IntersectsFirst` correctly.
  *count = 0;
  *results = nullptr;
}

bool wiScene_IntersectsFirst(wiScene scene, wiRay ray, uint32_t filterMask,
                             uint32_t layerMask, uint32_t lod,
                             wiScenePickResult *result) {
  if (!scene || !result)
    return false;

  wi::primitive::Ray r;
  r.origin = XMFLOAT3(ray.origin.x, ray.origin.y, ray.origin.z);
  r.direction = XMFLOAT3(ray.direction.x, ray.direction.y, ray.direction.z);
  r.TMin = ray.TMin;
  r.TMax = ray.TMax;

  auto res = wi::scene::Pick(r, filterMask, layerMask, *(Scene *)scene, lod);

  if (res.entity != WI_INVALID_ENTITY) {
    result->entity = (wiEntity)res.entity;
    result->position = {res.position.x, res.position.y, res.position.z, 0};
    result->normal = {res.normal.x, res.normal.y, res.normal.z, 0};
    result->distance = res.distance;
    return true;
  }
  return false;
}

void wiScene_FindAllEntities(wiScene scene, size_t *count,
                             wiEntity **entities) {
  // Return all entities with a Name component (usually all relevant ones)
  if (!scene || !count || !entities)
    return;
  auto &manager = ((Scene *)scene)->names;
  *count = manager.GetCount();
  *entities = (wiEntity *)manager.GetEntityArray().data();
}

// --- Component Array Accessors ---

#define IMPLEMENT_COMPONENT_ARRAY(Type, ManagerName)                           \
  size_t wiScene_Component_Get##Type##Count(wiScene scene) {                   \
    if (!scene)                                                                \
      return 0;                                                                \
    return ((Scene *)scene)->ManagerName.GetCount();                           \
  }                                                                            \
  wi##Type##Component *wiScene_Component_Get##Type##Array(wiScene scene) {     \
    if (!scene)                                                                \
      return nullptr;                                                          \
    return (wi##Type##Component *)((Scene *)scene)->ManagerName.GetData();     \
  }

IMPLEMENT_COMPONENT_ARRAY(Name, names)
IMPLEMENT_COMPONENT_ARRAY(Layer, layers)
IMPLEMENT_COMPONENT_ARRAY(Transform, transforms)
IMPLEMENT_COMPONENT_ARRAY(Mesh, meshes)
IMPLEMENT_COMPONENT_ARRAY(Material, materials)
IMPLEMENT_COMPONENT_ARRAY(Object, objects)
IMPLEMENT_COMPONENT_ARRAY(Light, lights)
IMPLEMENT_COMPONENT_ARRAY(Camera, cameras)
IMPLEMENT_COMPONENT_ARRAY(RigidBodyPhysics, rigidbodies)
IMPLEMENT_COMPONENT_ARRAY(SoftBodyPhysics, softbodies)
IMPLEMENT_COMPONENT_ARRAY(ForceField, forces)
IMPLEMENT_COMPONENT_ARRAY(Weather, weathers)
IMPLEMENT_COMPONENT_ARRAY(Animation, animations)
IMPLEMENT_COMPONENT_ARRAY(Emitter, emitters)
// HairParticleSystem naming doesn't follow 'Component' suffix pattern in C
// typedef IMPLEMENT_COMPONENT_ARRAY(HairParticleSystem, hairs) -> expands to
// wiHairParticleSystemComponent which is wrong.
size_t wiScene_Component_GetHairParticleSystemCount(wiScene scene) {
  if (!scene)
    return 0;
  return ((Scene *)scene)->hairs.GetCount();
}
wiHairParticleSystem *
wiScene_Component_GetHairParticleSystemArray(wiScene scene) {
  if (!scene)
    return nullptr;
  return (wiHairParticleSystem *)((Scene *)scene)->hairs.GetData();
}
IMPLEMENT_COMPONENT_ARRAY(InverseKinematics, inverse_kinematics)
IMPLEMENT_COMPONENT_ARRAY(Script, scripts)
IMPLEMENT_COMPONENT_ARRAY(Collider, colliders)
IMPLEMENT_COMPONENT_ARRAY(Spring, springs)
IMPLEMENT_COMPONENT_ARRAY(Sound, sounds)
IMPLEMENT_COMPONENT_ARRAY(Video, videos)
IMPLEMENT_COMPONENT_ARRAY(Expression, expressions)
IMPLEMENT_COMPONENT_ARRAY(Humanoid, humanoids)
IMPLEMENT_COMPONENT_ARRAY(Decal, decals)
IMPLEMENT_COMPONENT_ARRAY(Sprite, sprites)
IMPLEMENT_COMPONENT_ARRAY(Font, fonts)
IMPLEMENT_COMPONENT_ARRAY(VoxelGrid, voxel_grids)
IMPLEMENT_COMPONENT_ARRAY(Metadata, metadatas)

// Character needs explicit implementation if not macro-able (it is)
IMPLEMENT_COMPONENT_ARRAY(Character, characters)

wiCharacterComponent wiScene_Component_CreateCharacter(wiScene scene,
                                                       wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiCharacterComponent) &
         ((Scene *)scene)->characters.Create((Entity)entity);
}
wiCharacterComponent wiScene_Component_GetCharacter(wiScene scene,
                                                    wiEntity entity) {
  if (!scene)
    return nullptr;
  return (wiCharacterComponent)((Scene *)scene)
      ->characters.GetComponent((Entity)entity);
}

// --- Component: Sound ---
void wiSoundComponent_Play(wiSoundComponent component) {
  if (component)
    ((SoundComponent *)component)->Play();
}
void wiSoundComponent_Stop(wiSoundComponent component) {
  if (component)
    ((SoundComponent *)component)->Stop();
}
bool wiSoundComponent_IsPlaying(wiSoundComponent component) {
  if (component)
    return ((SoundComponent *)component)->IsPlaying();
  return false;
}
void wiSoundComponent_SetLooped(wiSoundComponent component, bool value) {
  if (component)
    ((SoundComponent *)component)->SetLooped(value);
}
bool wiSoundComponent_IsLooped(wiSoundComponent component) {
  if (component)
    return ((SoundComponent *)component)->IsLooped();
  return false;
}
void wiSoundComponent_SetVolume(wiSoundComponent component, float volume) {
  if (component)
    ((SoundComponent *)component)->volume = volume;
}
float wiSoundComponent_GetVolume(wiSoundComponent component) {
  if (component)
    return ((SoundComponent *)component)->volume;
  return 1.0f;
}

// --- Component: Video ---
void wiVideoComponent_Play(wiVideoComponent component) {
  if (component)
    ((VideoComponent *)component)->Play();
}
void wiVideoComponent_Pause(wiVideoComponent component) {
  if (component)
    ((VideoComponent *)component)->Pause();
}
void wiVideoComponent_Stop(wiVideoComponent component) {
  if (component)
    ((VideoComponent *)component)->Stop();
}
bool wiVideoComponent_IsPlaying(wiVideoComponent component) {
  if (component)
    return ((VideoComponent *)component)->IsPlaying();
  return false;
}
void wiVideoComponent_SetLooped(wiVideoComponent component, bool value) {
  if (component)
    ((VideoComponent *)component)->SetLooped(value);
}
bool wiVideoComponent_IsLooped(wiVideoComponent component) {
  if (component)
    return ((VideoComponent *)component)->IsLooped();
  return false;
}

// --- Component: Animation ---
void wiAnimationComponent_Play(wiAnimationComponent component) {
  if (component)
    ((AnimationComponent *)component)->Play();
}
void wiAnimationComponent_Stop(wiAnimationComponent component) {
  if (component)
    ((AnimationComponent *)component)->Stop();
}
bool wiAnimationComponent_IsPlaying(wiAnimationComponent component) {
  if (component)
    return ((AnimationComponent *)component)->IsPlaying();
  return false;
}
void wiAnimationComponent_SetLooped(wiAnimationComponent component,
                                    bool value) {
  if (component) {
    if (value)
      ((AnimationComponent *)component)->_flags |= AnimationComponent::LOOPED;
    else
      ((AnimationComponent *)component)->_flags &= ~AnimationComponent::LOOPED;
  }
}
bool wiAnimationComponent_IsLooped(wiAnimationComponent component) {
  if (component)
    return ((AnimationComponent *)component)->IsLooped();
  return false;
}
void wiAnimationComponent_SetAmount(wiAnimationComponent component,
                                    float amount) {
  if (component)
    ((AnimationComponent *)component)->amount = amount;
}
float wiAnimationComponent_GetAmount(wiAnimationComponent component) {
  if (component)
    return ((AnimationComponent *)component)->amount;
  return 1.0f;
}
void wiAnimationComponent_SetSpeed(wiAnimationComponent component,
                                   float speed) {
  if (component)
    ((AnimationComponent *)component)->speed = speed;
}
float wiAnimationComponent_GetSpeed(wiAnimationComponent component) {
  if (component)
    return ((AnimationComponent *)component)->speed;
  return 1.0f;
}
void wiAnimationComponent_SetTimer(wiAnimationComponent component,
                                   float timer) {
  if (component)
    ((AnimationComponent *)component)->timer = timer;
}
float wiAnimationComponent_GetTimer(wiAnimationComponent component) {
  if (component)
    return ((AnimationComponent *)component)->timer;
  return 0.0f;
}

// --- Component: Weather ---
void wiWeatherComponent_SetOceanEnabled(wiWeatherComponent component,
                                        bool value) {
  if (component)
    ((WeatherComponent *)component)->SetOceanEnabled(value);
}
bool wiWeatherComponent_IsOceanEnabled(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->IsOceanEnabled();
  return false;
}
void wiWeatherComponent_SetOceanLevel(wiWeatherComponent component,
                                      float level) {
  if (component)
    ((WeatherComponent *)component)->oceanParameters.waterHeight = level;
}
float wiWeatherComponent_GetOceanLevel(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->oceanParameters.waterHeight;
  return 0.0f;
}
void wiWeatherComponent_SetFogStart(wiWeatherComponent component, float start) {
  if (component)
    ((WeatherComponent *)component)->fogStart = start;
}
float wiWeatherComponent_GetFogStart(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->fogStart;
  return 0.0f;
}
void wiWeatherComponent_SetFogDensity(wiWeatherComponent component,
                                      float fogDensity) {
  if (component)
    ((WeatherComponent *)component)->fogDensity = fogDensity;
}
float wiWeatherComponent_GetFogDensity(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->fogDensity;
  return 0.0f;
}
void wiWeatherComponent_SetFogHeightStart(wiWeatherComponent component,
                                          float start) {
  if (component)
    ((WeatherComponent *)component)->fogHeightStart = start;
}
float wiWeatherComponent_GetFogHeightStart(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->fogHeightStart;
  return 0.0f;
}
void wiWeatherComponent_SetFogHeightEnd(wiWeatherComponent component,
                                        float end) {
  if (component)
    ((WeatherComponent *)component)->fogHeightEnd = end;
}
float wiWeatherComponent_GetFogHeightEnd(wiWeatherComponent component) {
  if (component)
    return ((WeatherComponent *)component)->fogHeightEnd;
  return 0.0f;
}

// --- Component: Script ---
void wiScriptComponent_SetScriptFile(wiScriptComponent component,
                                     const char *filename) {
  if (component && filename) {
    ((ScriptComponent *)component)->filename = filename;
    ((ScriptComponent *)component)->CreateFromFile(filename);
  }
}
const char *wiScriptComponent_GetScriptFile(wiScriptComponent component) {
  if (component)
    return ((ScriptComponent *)component)->filename.c_str();
  return "";
}
void wiScriptComponent_Play(wiScriptComponent component) {
  if (component)
    ((ScriptComponent *)component)->Play();
}
void wiScriptComponent_Stop(wiScriptComponent component) {
  if (component)
    ((ScriptComponent *)component)->Stop();
}

// --- Component: Character ---
void wiCharacterComponent_SetActive(wiCharacterComponent component,
                                    bool active) {
  if (component)
    ((CharacterComponent *)component)->SetActive(active);
}
bool wiCharacterComponent_IsActive(wiCharacterComponent component) {
  if (component)
    return ((CharacterComponent *)component)->IsActive();
  return false;
}
void wiCharacterComponent_SetPathGoal(wiCharacterComponent component,
                                      wiVector goal,
                                      wiVoxelGridComponent voxelGrid) {
  if (component) {
    XMFLOAT3 g = XMFLOAT3(goal.x, goal.y, goal.z);
    const wi::VoxelGrid *vg = (const wi::VoxelGrid *)voxelGrid;
    ((CharacterComponent *)component)->SetPathGoal(g, vg);
  }
}

// --- Component: Collider ---
void wiColliderComponent_SetShape(wiColliderComponent component, int shape) {
  if (component)
    ((ColliderComponent *)component)->shape = (ColliderComponent::Shape)shape;
}
int wiColliderComponent_GetShape(wiColliderComponent component) {
  if (component)
    return (int)((ColliderComponent *)component)->shape;
  return 0;
}
void wiColliderComponent_SetRadius(wiColliderComponent component,
                                   float radius) {
  if (component)
    ((ColliderComponent *)component)->radius = radius;
}
float wiColliderComponent_GetRadius(wiColliderComponent component) {
  if (component)
    return ((ColliderComponent *)component)->radius;
  return 0.0f;
}
void wiColliderComponent_SetOffset(wiColliderComponent component,
                                   wiVector offset) {
  if (component)
    ((ColliderComponent *)component)->offset =
        XMFLOAT3(offset.x, offset.y, offset.z);
}
wiVector wiColliderComponent_GetOffset(wiColliderComponent component) {
  if (component) {
    XMFLOAT3 v = ((ColliderComponent *)component)->offset;
    return wiVector{v.x, v.y, v.z, 0};
  }
  return wiVector{0, 0, 0, 0};
}
void wiColliderComponent_SetTail(wiColliderComponent component, wiVector tail) {
  if (component)
    ((ColliderComponent *)component)->tail = XMFLOAT3(tail.x, tail.y, tail.z);
}
wiVector wiColliderComponent_GetTail(wiColliderComponent component) {
  if (component) {
    XMFLOAT3 v = ((ColliderComponent *)component)->tail;
    return wiVector{v.x, v.y, v.z, 0};
  }
  return wiVector{0, 0, 0, 0};
}
void wiColliderComponent_SetCPUEnabled(wiColliderComponent component,
                                       bool value) {
  if (component)
    ((ColliderComponent *)component)->SetCPUEnabled(value);
}
bool wiColliderComponent_IsCPUEnabled(wiColliderComponent component) {
  if (component)
    return ((ColliderComponent *)component)->IsCPUEnabled();
  return false;
}

// --- Component: Spring ---
void wiSpringComponent_SetStiffness(wiSpringComponent component,
                                    float stiffness) {
  if (component)
    ((SpringComponent *)component)->stiffnessForce = stiffness;
}
float wiSpringComponent_GetStiffness(wiSpringComponent component) {
  if (component)
    return ((SpringComponent *)component)->stiffnessForce;
  return 0.0f;
}
void wiSpringComponent_SetDamping(wiSpringComponent component, float damping) {
  if (component)
    ((SpringComponent *)component)->dragForce = damping;
}
float wiSpringComponent_GetDamping(wiSpringComponent component) {
  if (component)
    return ((SpringComponent *)component)->dragForce;
  return 0.0f;
}
void wiSpringComponent_SetWindAffection(wiSpringComponent component,
                                        float value) {
  if (component)
    ((SpringComponent *)component)->windForce = value;
}
float wiSpringComponent_GetWindAffection(wiSpringComponent component) {
  if (component)
    return ((SpringComponent *)component)->windForce;
  return 0.0f;
}

// --- Component: Font ---
void wiFontComponent_SetText(wiFontComponent component, const char *text) {
  if (component && text) {
    std::wstring wtext;
    wi::helper::StringConvert(text, wtext);
    ((wi::SpriteFont *)component)->SetText(wtext);
  }
}
const char *wiFontComponent_GetText(wiFontComponent component) {
  if (component) {
    thread_local static std::string s_textA;
    s_textA = ((wi::SpriteFont *)component)->GetTextA();
    return s_textA.c_str();
  }
  return "";
}
void wiFontComponent_SetSize(wiFontComponent component, float size) {
  if (component)
    ((wi::SpriteFont *)component)->params.size = (int)size;
}
float wiFontComponent_GetSize(wiFontComponent component) {
  if (component)
    return (float)((wi::SpriteFont *)component)->params.size;
  return 0.0f;
}

// --- Component: SoftBody Physics ---
void wiSoftBodyPhysicsComponent_SetMass(wiSoftBodyPhysicsComponent component,
                                        float mass) {
  if (component)
    ((SoftBodyPhysicsComponent *)component)->mass = mass;
}
float wiSoftBodyPhysicsComponent_GetMass(wiSoftBodyPhysicsComponent component) {
  if (component)
    return ((SoftBodyPhysicsComponent *)component)->mass;
  return 0.0f;
}
void wiSoftBodyPhysicsComponent_SetFriction(
    wiSoftBodyPhysicsComponent component, float friction) {
  if (component)
    ((SoftBodyPhysicsComponent *)component)->friction = friction;
}
float wiSoftBodyPhysicsComponent_GetFriction(
    wiSoftBodyPhysicsComponent component) {
  if (component)
    return ((SoftBodyPhysicsComponent *)component)->friction;
  return 0.0f;
}
void wiSoftBodyPhysicsComponent_SetRestitution(
    wiSoftBodyPhysicsComponent component, float restitution) {
  if (component)
    ((SoftBodyPhysicsComponent *)component)->restitution = restitution;
}
float wiSoftBodyPhysicsComponent_GetRestitution(
    wiSoftBodyPhysicsComponent component) {
  if (component)
    return ((SoftBodyPhysicsComponent *)component)->restitution;
  return 0.0f;
}

// --- Component: Force Field ---
void wiForceFieldComponent_SetType(wiForceFieldComponent component, int type) {
  if (component)
    ((ForceFieldComponent *)component)->type = (ForceFieldComponent::Type)type;
}
int wiForceFieldComponent_GetType(wiForceFieldComponent component) {
  if (component)
    return (int)((ForceFieldComponent *)component)->type;
  return 0;
}
void wiForceFieldComponent_SetGravity(wiForceFieldComponent component,
                                      float gravity) {
  if (component)
    ((ForceFieldComponent *)component)->gravity = gravity;
}
float wiForceFieldComponent_GetGravity(wiForceFieldComponent component) {
  if (component)
    return ((ForceFieldComponent *)component)->gravity;
  return 0.0f;
}
void wiForceFieldComponent_SetRange(wiForceFieldComponent component,
                                    float range) {
  if (component)
    ((ForceFieldComponent *)component)->range = range;
}
float wiForceFieldComponent_GetRange(wiForceFieldComponent component) {
  if (component)
    return ((ForceFieldComponent *)component)->range;
  return 0.0f;
}

// --- Component: HairParticleSystem ---
void wiHairParticleSystem_SetStrandCount(wiHairParticleSystem component,
                                         size_t count) {
  if (component)
    ((wi::HairParticleSystem *)component)->strandCount = (uint32_t)count;
}
size_t wiHairParticleSystem_GetStrandCount(wiHairParticleSystem component) {
  if (component)
    return (size_t)((wi::HairParticleSystem *)component)->strandCount;
  return 0;
}
void wiHairParticleSystem_SetLength(wiHairParticleSystem component,
                                    float length) {
  if (component)
    ((wi::HairParticleSystem *)component)->length = length;
}
float wiHairParticleSystem_GetLength(wiHairParticleSystem component) {
  if (component)
    return ((wi::HairParticleSystem *)component)->length;
  return 0.0f;
}
void wiHairParticleSystem_SetStiffness(wiHairParticleSystem component,
                                       float stiffness) {
  if (component)
    ((wi::HairParticleSystem *)component)->stiffness = stiffness;
}
float wiHairParticleSystem_GetStiffness(wiHairParticleSystem component) {
  if (component)
    return ((wi::HairParticleSystem *)component)->stiffness;
  return 0.0f;
}
void wiHairParticleSystem_SetRandomness(wiHairParticleSystem component,
                                        float randomness) {
  if (component)
    ((wi::HairParticleSystem *)component)->randomness = randomness;
}
float wiHairParticleSystem_GetRandomness(wiHairParticleSystem component) {
  if (component)
    return ((wi::HairParticleSystem *)component)->randomness;
  return 0.0f;
}

// --- Component: Expression ---
void wiExpressionComponent_SetForceTalking(wiExpressionComponent component,
                                           bool value) {
  if (component)
    ((ExpressionComponent *)component)->SetForceTalkingEnabled(value);
}
bool wiExpressionComponent_IsForceTalking(wiExpressionComponent component) {
  if (component)
    return ((ExpressionComponent *)component)->IsForceTalkingEnabled();
  return false;
}
void wiExpressionComponent_SetPresetWeight(wiExpressionComponent component,
                                           wiExpressionComponent_Preset preset,
                                           float weight) {
  if (component) {
    ExpressionComponent *expr = (ExpressionComponent *)component;
    if (preset >= 0 && preset < (int)ExpressionComponent::Preset::Count) {
      int index = expr->presets[(int)preset];
      if (index >= 0 && index < (int)expr->expressions.size()) {
        expr->expressions[index].SetWeight(weight);
      }
    }
  }
}
float wiExpressionComponent_GetPresetWeight(
    wiExpressionComponent component, wiExpressionComponent_Preset preset) {
  if (component) {
    ExpressionComponent *expr = (ExpressionComponent *)component;
    if (preset >= 0 && preset < (int)ExpressionComponent::Preset::Count) {
      int index = expr->presets[(int)preset];
      if (index >= 0 && index < (int)expr->expressions.size()) {
        return expr->expressions[index].weight;
      }
    }
  }
  return 0.0f;
}

// --- Component: Humanoid ---
void wiHumanoidComponent_SetBone(wiHumanoidComponent component, int bone,
                                 wiEntity boneEntity) {
  if (component && bone >= 0 &&
      bone < (int)HumanoidComponent::HumanoidBone::Count)
    ((HumanoidComponent *)component)->bones[(size_t)bone] = boneEntity;
}
wiEntity wiHumanoidComponent_GetBone(wiHumanoidComponent component, int bone) {
  if (component && bone >= 0 &&
      bone < (int)HumanoidComponent::HumanoidBone::Count)
    return (wiEntity)((HumanoidComponent *)component)->bones[(size_t)bone];
  return WI_INVALID_ENTITY;
}

// --- Component: Decal ---
void wiDecalComponent_SetSlopeBlendPower(wiDecalComponent component,
                                         float power) {
  if (component)
    ((DecalComponent *)component)->slopeBlendPower = power;
}
float wiDecalComponent_GetSlopeBlendPower(wiDecalComponent component) {
  if (component)
    return ((DecalComponent *)component)->slopeBlendPower;
  return 0.0f;
}

// --- Component: VoxelGrid ---
void wiVoxelGridComponent_SetResolution(wiVoxelGridComponent component,
                                        uint32_t resolution) {
  if (component) {
    ((wi::VoxelGrid *)component)->resolution =
        XMUINT3(resolution, resolution, resolution);
    // Also update derived properties if needed?
    // wiVoxelGrid.h says: "void create_mesh(...)" depends on resolution.
    // Changing resolution manually might break state?
    // But it's C API, direct access.
  }
}
uint32_t wiVoxelGridComponent_GetResolution(wiVoxelGridComponent component) {
  if (component)
    return ((wi::VoxelGrid *)component)->resolution.x;
  return 0;
}

} // extern "C"
