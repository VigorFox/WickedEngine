#include "wiTexture_API.h"
#include "../wiHelper.h"
#include "../wiResourceManager.h" // For texture resource checking if needed, though usually enclosed in Texture struct
#include "../wiTextureHelper.h"

using namespace wi::graphics;
using namespace wi::texturehelper;

// Opaque handle logic: wiTexture is effectively a pointer to a wi::Resource
// or wi::graphics::Texture depending on usage.
// However, the Lua bindings wrappers usually hold a wi::Resource or wrap it.
// Looking at BindLua: "resource = wi::resourcemanager::Load(name)" or created
// textures. The lua bindings store a `wi::Resource resource` member. Since we
// can't easily pass a stack object pointer out for a long time, we might need
// to allocate a wrapper or assume the user manages the pointer if we return
// generic ones. BUT, `wiTexture_GetLogo` returns a pointer to a static internal
// texture resource usually. Let's check `wiTextureHelper::getLogo()` returns
// `Resource*`. So we can define `wiTexture` as `wi::Resource*`.

extern "C" {

wiTexture wiTexture_GetLogo() {
  return (wiTexture)wi::texturehelper::getLogo();
}

wiTexture wiTexture_CreateGradientTexture(
    int gradient_type, uint32_t width, uint32_t height, wiVector uv_start,
    wiVector uv_end, int gradient_flags, float perlin_scale,
    uint32_t perlin_seed, int perlin_octaves, float perlin_persistence) {
  // This function returns a wi::graphics::Texture by value in C++.
  // That's tricky for C API. We need a persistent object.
  // We could allocate a new Resource on heap and move the texture into it.
  wi::Resource *res = new wi::Resource();
  res->SetTexture(wi::texturehelper::CreateGradientTexture(
      (GradientType)gradient_type, width, height,
      XMFLOAT2(uv_start.x, uv_start.y), XMFLOAT2(uv_end.x, uv_end.y),
      (GradientFlags)gradient_flags,
      wi::graphics::SwizzleFromString("rgba"), // Defaulting for simple C API
      perlin_scale, perlin_seed, perlin_octaves, perlin_persistence));
  return (wiTexture)res;
}

void wiTexture_Destroy(wiTexture texture) {
  if (texture) {
    delete (wi::Resource *)texture;
  }
}

// NOTE: Since we allocate in CreateGradientTexture, we might need a Destroy
// function! The plan didn't explicitly list one but it's needed for memory
// management of created textures. I will not add it to the header yet strictly
// to match the plan, but for a leak-free usage, we should have
// `wiTexture_Destroy` eventually. For now, let's assume this is a leak or user
// handles it if they know implementation details. Wait, `wiTexture` in plan was
// "Wraps wi::Resource". Let's add specific Destroy helper just in case, or
// leave it for now.

bool wiTexture_IsValid(wiTexture texture) {
  if (!texture)
    return false;
  wi::Resource *res = (wi::Resource *)texture;
  return res->IsValid() && res->GetTexture().IsValid();
}

int wiTexture_GetWidth(wiTexture texture) {
  if (!wiTexture_IsValid(texture))
    return 0;
  return ((wi::Resource *)texture)->GetTexture().GetDesc().width;
}

int wiTexture_GetHeight(wiTexture texture) {
  if (!wiTexture_IsValid(texture))
    return 0;
  return ((wi::Resource *)texture)->GetTexture().GetDesc().height;
}

int wiTexture_GetDepth(wiTexture texture) {
  if (!wiTexture_IsValid(texture))
    return 0;
  return ((wi::Resource *)texture)->GetTexture().GetDesc().depth;
}

int wiTexture_GetArraySize(wiTexture texture) {
  if (!wiTexture_IsValid(texture))
    return 0;
  return ((wi::Resource *)texture)->GetTexture().GetDesc().array_size;
}

void wiTexture_Save(wiTexture texture, const char *filename) {
  if (wiTexture_IsValid(texture) && filename) {
    wi::helper::saveTextureToFile(((wi::Resource *)texture)->GetTexture(),
                                  filename);
  }
}

} // extern "C"
