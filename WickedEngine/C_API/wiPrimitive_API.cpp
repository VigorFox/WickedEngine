#include "wiPrimitive_API.h"
#include "wiMath.h" // For vector conversion if needed
#include "wiPrimitive.h"


using namespace wi::primitive;

// Helper to convert C types to C++ types
inline Ray ToCpp(wiRay r) {
  XMVECTOR o = XMLoadFloat4((XMFLOAT4 *)&r.origin);
  XMVECTOR d = XMLoadFloat4((XMFLOAT4 *)&r.direction);
  Ray ret(o, d);
  ret.TMin = r.TMin;
  ret.TMax = r.TMax;
  return ret;
}

inline AABB ToCpp(wiAABB a) {
  XMFLOAT3 min, max;
  min.x = a._min.x;
  min.y = a._min.y;
  min.z = a._min.z;
  max.x = a._max.x;
  max.y = a._max.y;
  max.z = a._max.z;
  return AABB(min, max);
}

inline Sphere ToCpp(wiSphere s) {
  XMFLOAT3 c;
  c.x = s.center.x;
  c.y = s.center.y;
  c.z = s.center.z;
  return Sphere(c, s.radius);
}

inline Capsule ToCpp(wiCapsule c) {
  XMFLOAT3 b, t;
  b.x = c.base.x;
  b.y = c.base.y;
  b.z = c.base.z;
  t.x = c.tip.x;
  t.y = c.tip.y;
  t.z = c.tip.z;
  return Capsule(b, t, c.radius);
}

inline wiVector FromXMVECTOR(XMVECTOR v) {
  XMFLOAT4 f;
  XMStoreFloat4(&f, v);
  wiVector ret;
  ret.x = f.x;
  ret.y = f.y;
  ret.z = f.z;
  ret.w = f.w;
  return ret;
}

inline wiVector FromXMFLOAT3(XMFLOAT3 v) {
  wiVector ret;
  ret.x = v.x;
  ret.y = v.y;
  ret.z = v.z;
  ret.w = 0;
  return ret;
}

extern "C" {

// Ray
wiRay wiRay_Create(wiVector origin, wiVector direction) {
  wiRay r;
  r.origin = origin;
  r.direction = direction;
  r.TMin = 0;
  r.TMax = FLT_MAX;
  return r;
}

wiRay wiRay_CreateFromPoints(wiVector a, wiVector b) {
  XMVECTOR A = XMLoadFloat4((XMFLOAT4 *)&a);
  XMVECTOR B = XMLoadFloat4((XMFLOAT4 *)&b);
  Ray cppRay;
  XMFLOAT3 a3, b3;
  XMStoreFloat3(&a3, A);
  XMStoreFloat3(&b3, B);
  cppRay.CreateFromPoints(a3, b3);

  wiRay r;
  // Ray::CreateFromPoints uses XMFLOAT3, converting back
  r.origin = FromXMFLOAT3(cppRay.origin);
  r.direction = FromXMFLOAT3(cppRay.direction);
  r.TMin = cppRay.TMin;
  r.TMax = cppRay.TMax;
  return r;
}

bool wiRay_IntersectsAABB(wiRay ray, wiAABB aabb) {
  return ToCpp(ray).intersects(ToCpp(aabb));
}

bool wiRay_IntersectsSphere(wiRay ray, wiSphere sphere) {
  return ToCpp(ray).intersects(ToCpp(sphere));
}

bool wiRay_IntersectsCapsule(wiRay ray, wiCapsule capsule) {
  return ToCpp(ray).intersects(ToCpp(capsule));
}

wiVector wiRay_IntersectsPlane(wiRay ray, wiVector planePoint,
                               wiVector planeNormal) {
  XMVECTOR P = XMLoadFloat4((XMFLOAT4 *)&planePoint);
  XMVECTOR N =
      XMLoadFloat4((XMFLOAT4 *)&planeNormal); // Actually binding uses Normal?
                                              // Check Ray_BindLua
  // Ray_BindLua uses XMPlaneIntersectLine logic manually:
  // XMVECTOR I = XMPlaneIntersectLine(P, O + D * ray.TMin, O + D * ray.TMax);
  // But P in XMPlaneIntersectLine is Plane vector (Ax+By+Cz+D=0).
  // The bind lua code Intersects(Vector) treats argument as plane point?
  // "XMVECTOR P = XMLoadFloat4(&vec->data);"
  // "XMVECTOR I = XMPlaneIntersectLine(P, O + D * ray.TMin, O + D * ray.TMax);"
  // Wait, XMPlaneIntersectLine takes (Plane, LinePoint1, LinePoint2).
  // If user passed a single vector, it treats it as a Plane definition (Vec4).

  Ray cppRay = ToCpp(ray);
  XMVECTOR O = XMLoadFloat3(&cppRay.origin);
  XMVECTOR D = XMLoadFloat3(&cppRay.direction);
  XMVECTOR Plane = P; // Assuming planePoint is the plane equation vector
  XMVECTOR I = XMPlaneIntersectLine(Plane, O + D * ray.TMin, O + D * ray.TMax);
  return FromXMVECTOR(I);
}

// AABB
wiAABB wiAABB_Create(wiVector min, wiVector max) {
  wiAABB a;
  a._min = min;
  a._max = max;
  return a;
}

bool wiAABB_Intersects(wiAABB aabb, wiAABB other) {
  return ToCpp(aabb).intersects(ToCpp(other)) !=
         AABB::INTERSECTION_TYPE::OUTSIDE;
}

bool wiAABB_IntersectsSphere(wiAABB aabb, wiSphere sphere) {
  return ToCpp(aabb).intersects(ToCpp(sphere));
}

bool wiAABB_IntersectsRay(wiAABB aabb, wiRay ray) {
  return ToCpp(ray).intersects(ToCpp(aabb));
}

wiVector wiAABB_GetCenter(wiAABB aabb) {
  return FromXMFLOAT3(ToCpp(aabb).getCenter());
}

wiVector wiAABB_GetHalfExtents(wiAABB aabb) {
  return FromXMFLOAT3(ToCpp(aabb).getHalfWidth());
}

// Sphere
wiSphere wiSphere_Create(wiVector center, float radius) {
  wiSphere s;
  s.center = center;
  s.radius = radius;
  return s;
}

bool wiSphere_Intersects(wiSphere sphere, wiSphere other) {
  return ToCpp(sphere).intersects(ToCpp(other));
}

bool wiSphere_IntersectsAABB(wiSphere sphere, wiAABB aabb) {
  return ToCpp(sphere).intersects(ToCpp(aabb));
}

bool wiSphere_IntersectsCapsule(wiSphere sphere, wiCapsule capsule) {
  return ToCpp(sphere).intersects(ToCpp(capsule));
}

bool wiSphere_IntersectsRay(wiSphere sphere, wiRay ray) {
  return ToCpp(ray).intersects(ToCpp(sphere));
}

// Capsule
wiCapsule wiCapsule_Create(wiVector base, wiVector tip, float radius) {
  wiCapsule c;
  c.base = base;
  c.tip = tip;
  c.radius = radius;
  return c;
}

bool wiCapsule_Intersects(wiCapsule capsule, wiCapsule other,
                          wiVector *position, wiVector *normal, float *depth) {
  XMFLOAT3 p(0, 0, 0), n(0, 0, 0);
  float d = 0;
  bool res = ToCpp(capsule).intersects(ToCpp(other), p, n, d);
  if (position)
    *position = FromXMFLOAT3(p);
  if (normal)
    *normal = FromXMFLOAT3(n);
  if (depth)
    *depth = d;
  return res;
}

bool wiCapsule_IntersectsSphere(wiCapsule capsule, wiSphere sphere,
                                float *depth, wiVector *normal) {
  XMFLOAT3 n(0, 0, 0);
  float d = 0;
  bool res = ToCpp(capsule).intersects(ToCpp(sphere), d, n);
  if (depth)
    *depth = d;
  if (normal)
    *normal = FromXMFLOAT3(n);
  return res;
}

bool wiCapsule_IntersectsRay(wiCapsule capsule, wiRay ray) {
  return ToCpp(capsule).intersects(ToCpp(ray));
}

wiAABB wiCapsule_GetAABB(wiCapsule capsule) {
  AABB a = ToCpp(capsule).getAABB();
  wiAABB wa;
  wa._min.x = a._min.x;
  wa._min.y = a._min.y;
  wa._min.z = a._min.z;
  wa._min.w = 1;
  wa._max.x = a._max.x;
  wa._max.y = a._max.y;
  wa._max.z = a._max.z;
  wa._max.w = 1;
  return wa;
}

} // extern "C"
