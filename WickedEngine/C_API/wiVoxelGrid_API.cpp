#include "wiVoxelGrid_API.h"
#include "../wiPrimitive.h"
#include "../wiVoxelGrid.h"


using namespace wi;

// Helper conversions (assuming wiPrimitive_API.cpp logic is available or
// duplicated) Ideally we share them, but for standalone C API compilation units
// we often duplicate inline helpers. To avoid duplication mess, we'll do raw
// struct casts if binary compatible or manual copy. wiPrimitive types are
// mostly float3/float4 structs, compatible layout. But we need to be careful
// with layout. Manual copy is safest.

inline primitive::AABB ToInternal(wiAABB a) {
  XMFLOAT3 min, max;
  min.x = a._min.x;
  min.y = a._min.y;
  min.z = a._min.z;
  max.x = a._max.x;
  max.y = a._max.y;
  max.z = a._max.z;
  return primitive::AABB(min, max);
}
inline primitive::Sphere ToInternal(wiSphere s) {
  XMFLOAT3 c;
  c.x = s.center.x;
  c.y = s.center.y;
  c.z = s.center.z;
  return primitive::Sphere(c, s.radius);
}
inline primitive::Capsule ToInternal(wiCapsule c) {
  XMFLOAT3 b, t;
  b.x = c.base.x;
  b.y = c.base.y;
  b.z = c.base.z;
  t.x = c.tip.x;
  t.y = c.tip.y;
  t.z = c.tip.z;
  return primitive::Capsule(b, t, c.radius);
}

extern "C" {

wiVoxelGrid wiVoxelGrid_Create() { return (wiVoxelGrid) new VoxelGrid(); }

void wiVoxelGrid_Destroy(wiVoxelGrid grid) {
  if (grid)
    delete (VoxelGrid *)grid;
}

void wiVoxelGrid_Init(wiVoxelGrid grid, uint32_t dimX, uint32_t dimY,
                      uint32_t dimZ) {
  if (grid)
    ((VoxelGrid *)grid)->init(dimX, dimY, dimZ);
}

void wiVoxelGrid_ClearData(wiVoxelGrid grid) {
  if (grid)
    ((VoxelGrid *)grid)->cleardata();
}

void wiVoxelGrid_FromAABB(wiVoxelGrid grid, wiAABB aabb) {
  if (grid)
    ((VoxelGrid *)grid)->from_aabb(ToInternal(aabb));
}

void wiVoxelGrid_InjectTriangle(wiVoxelGrid grid, wiVector a, wiVector b,
                                wiVector c, bool subtract) {
  if (grid) {
    XMVECTOR A = XMLoadFloat4((XMFLOAT4 *)&a);
    XMVECTOR B = XMLoadFloat4((XMFLOAT4 *)&b);
    XMVECTOR C = XMLoadFloat4((XMFLOAT4 *)&c);
    ((VoxelGrid *)grid)->inject_triangle(A, B, C, subtract);
  }
}

void wiVoxelGrid_InjectAABB(wiVoxelGrid grid, wiAABB aabb, bool subtract) {
  if (grid)
    ((VoxelGrid *)grid)->inject_aabb(ToInternal(aabb), subtract);
}

void wiVoxelGrid_InjectSphere(wiVoxelGrid grid, wiSphere sphere,
                              bool subtract) {
  if (grid)
    ((VoxelGrid *)grid)->inject_sphere(ToInternal(sphere), subtract);
}

void wiVoxelGrid_InjectCapsule(wiVoxelGrid grid, wiCapsule capsule,
                               bool subtract) {
  if (grid)
    ((VoxelGrid *)grid)->inject_capsule(ToInternal(capsule), subtract);
}

bool wiVoxelGrid_CheckVoxel(wiVoxelGrid grid, int x, int y, int z) {
  if (!grid)
    return false;
  return ((VoxelGrid *)grid)->check_voxel(XMUINT3(x, y, z));
}

bool wiVoxelGrid_CheckVoxelPos(wiVoxelGrid grid, wiVector pos) {
  if (!grid)
    return false;
  XMFLOAT3 p;
  p.x = pos.x;
  p.y = pos.y;
  p.z = pos.z;
  return ((VoxelGrid *)grid)->check_voxel(p);
}

void wiVoxelGrid_SetVoxel(wiVoxelGrid grid, int x, int y, int z, bool value) {
  if (grid)
    ((VoxelGrid *)grid)->set_voxel(XMUINT3(x, y, z), value);
}

void wiVoxelGrid_SetVoxelPos(wiVoxelGrid grid, wiVector pos, bool value) {
  if (grid) {
    XMFLOAT3 p;
    p.x = pos.x;
    p.y = pos.y;
    p.z = pos.z;
    ((VoxelGrid *)grid)->set_voxel(p, value);
  }
}

bool wiVoxelGrid_IsVisible(wiVoxelGrid grid, wiVector observer,
                           wiVector subject) {
  if (!grid)
    return false;
  XMFLOAT3 o;
  o.x = observer.x;
  o.y = observer.y;
  o.z = observer.z;
  XMFLOAT3 s;
  s.x = subject.x;
  s.y = subject.y;
  s.z = subject.z;
  return ((VoxelGrid *)grid)->is_visible(o, s);
}

void wiVoxelGrid_FloodFill(wiVoxelGrid grid) {
  if (grid)
    ((VoxelGrid *)grid)->flood_fill();
}

wiVector wiVoxelGrid_GetCenter(wiVoxelGrid grid) {
  wiVector v = {0, 0, 0, 0};
  if (grid) {
    XMFLOAT3 c = ((VoxelGrid *)grid)->center;
    v.x = c.x;
    v.y = c.y;
    v.z = c.z;
  }
  return v;
}

void wiVoxelGrid_SetCenter(wiVoxelGrid grid, wiVector center) {
  if (grid) {
    ((VoxelGrid *)grid)->center = XMFLOAT3(center.x, center.y, center.z);
  }
}

wiVector wiVoxelGrid_GetVoxelSize(wiVoxelGrid grid) {
  wiVector v = {0, 0, 0, 0};
  if (grid) {
    XMFLOAT3 s = ((VoxelGrid *)grid)->voxelSize;
    v.x = s.x;
    v.y = s.y;
    v.z = s.z;
  }
  return v;
}

void wiVoxelGrid_SetVoxelSize(wiVoxelGrid grid, wiVector size) {
  if (grid)
    ((VoxelGrid *)grid)->set_voxelsize(XMFLOAT3(size.x, size.y, size.z));
}

} // extern "C"
