#include "wiMath_API.h"
#include "wiMath.h"

using namespace DirectX;

extern "C" {

wiVector wiVector_Create(float x, float y, float z, float w) {
    wiVector v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

float wiVector_GetX(wiVector v) { return v.x; }
float wiVector_GetY(wiVector v) { return v.y; }
float wiVector_GetZ(wiVector v) { return v.z; }
float wiVector_GetW(wiVector v) { return v.w; }

wiVector wiVector_Add(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    XMVECTOR result = XMVectorAdd(xv1, xv2);
    wiVector v;
    XMStoreFloat4((XMFLOAT4*)&v, result);
    return v;
}

wiVector wiVector_Subtract(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    XMVECTOR result = XMVectorSubtract(xv1, xv2);
    wiVector v;
    XMStoreFloat4((XMFLOAT4*)&v, result);
    return v;
}

wiVector wiVector_Multiply(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    XMVECTOR result = XMVectorMultiply(xv1, xv2);
    wiVector v;
    XMStoreFloat4((XMFLOAT4*)&v, result);
    return v;
}

wiVector wiVector_Scale(wiVector v, float scale) {
    XMVECTOR xv = XMLoadFloat4((XMFLOAT4*)&v);
    XMVECTOR result = XMVectorScale(xv, scale);
    wiVector r;
    XMStoreFloat4((XMFLOAT4*)&r, result);
    return r;
}

float wiVector_Dot(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    return XMVectorGetX(XMVector3Dot(xv1, xv2));
}

wiVector wiVector_Cross(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    XMVECTOR result = XMVector3Cross(xv1, xv2);
    wiVector v;
    XMStoreFloat4((XMFLOAT4*)&v, result);
    return v;
}

wiVector wiVector_Normalize(wiVector v) {
    XMVECTOR xv = XMLoadFloat4((XMFLOAT4*)&v);
    XMVECTOR result = XMVector3Normalize(xv);
    wiVector r;
    XMStoreFloat4((XMFLOAT4*)&r, result);
    return r;
}

float wiVector_Length(wiVector v) {
    XMVECTOR xv = XMLoadFloat4((XMFLOAT4*)&v);
    return XMVectorGetX(XMVector3Length(xv));
}

float wiVector_Distance(wiVector v1, wiVector v2) {
    XMVECTOR xv1 = XMLoadFloat4((XMFLOAT4*)&v1);
    XMVECTOR xv2 = XMLoadFloat4((XMFLOAT4*)&v2);
    XMVECTOR diff = XMVectorSubtract(xv1, xv2);
    return XMVectorGetX(XMVector3Length(diff));
}

// Matrix API
wiMatrix wiMatrix_Identity() {
    wiMatrix m;
    XMStoreFloat4x4((XMFLOAT4X4*)&m, XMMatrixIdentity());
    return m;
}

wiMatrix wiMatrix_Translation(wiVector v) {
    wiMatrix m;
    XMStoreFloat4x4((XMFLOAT4X4*)&m, XMMatrixTranslation(v.x, v.y, v.z));
    return m;
}

wiMatrix wiMatrix_Rotation(wiVector v) {
    wiMatrix m;
    XMStoreFloat4x4((XMFLOAT4X4*)&m, XMMatrixRotationRollPitchYaw(v.x, v.y, v.z));
    return m;
}

wiMatrix wiMatrix_Scale(wiVector v) {
    wiMatrix m;
    XMStoreFloat4x4((XMFLOAT4X4*)&m, XMMatrixScaling(v.x, v.y, v.z));
    return m;
}

wiMatrix wiMatrix_Multiply(wiMatrix m1, wiMatrix m2) {
    XMMATRIX xm1 = XMLoadFloat4x4((XMFLOAT4X4*)&m1);
    XMMATRIX xm2 = XMLoadFloat4x4((XMFLOAT4X4*)&m2);
    wiMatrix m;
    XMStoreFloat4x4((XMFLOAT4X4*)&m, XMMatrixMultiply(xm1, xm2));
    return m;
}

wiMatrix wiMatrix_Transpose(wiMatrix m) {
    XMMATRIX xm = XMLoadFloat4x4((XMFLOAT4X4*)&m);
    wiMatrix r;
    XMStoreFloat4x4((XMFLOAT4X4*)&r, XMMatrixTranspose(xm));
    return r;
}

wiMatrix wiMatrix_Inverse(wiMatrix m) {
    XMMATRIX xm = XMLoadFloat4x4((XMFLOAT4X4*)&m);
    wiMatrix r;
    XMVECTOR det; // determinant
    XMStoreFloat4x4((XMFLOAT4X4*)&r, XMMatrixInverse(&det, xm));
    return r;
}

}
