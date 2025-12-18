#pragma once
#include "wiMath_API.h"
#include "wiPrimitive_API.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiVoxelGrid_t *wiVoxelGrid;

wiVoxelGrid wiVoxelGrid_Create();
void wiVoxelGrid_Destroy(wiVoxelGrid grid);

void wiVoxelGrid_Init(wiVoxelGrid grid, uint32_t dimX, uint32_t dimY,
                      uint32_t dimZ);
void wiVoxelGrid_ClearData(wiVoxelGrid grid);
void wiVoxelGrid_FromAABB(wiVoxelGrid grid, wiAABB aabb);
void wiVoxelGrid_InjectTriangle(wiVoxelGrid grid, wiVector a, wiVector b,
                                wiVector c, bool subtract);
void wiVoxelGrid_InjectAABB(wiVoxelGrid grid, wiAABB aabb, bool subtract);
void wiVoxelGrid_InjectSphere(wiVoxelGrid grid, wiSphere sphere, bool subtract);
void wiVoxelGrid_InjectCapsule(wiVoxelGrid grid, wiCapsule capsule,
                               bool subtract);

bool wiVoxelGrid_CheckVoxel(wiVoxelGrid grid, int x, int y, int z);
bool wiVoxelGrid_CheckVoxelPos(wiVoxelGrid grid, wiVector pos);
void wiVoxelGrid_SetVoxel(wiVoxelGrid grid, int x, int y, int z, bool value);
void wiVoxelGrid_SetVoxelPos(wiVoxelGrid grid, wiVector pos, bool value);

bool wiVoxelGrid_IsVisible(wiVoxelGrid grid, wiVector observer,
                           wiVector subject);
void wiVoxelGrid_FloodFill(wiVoxelGrid grid);

wiVector wiVoxelGrid_GetCenter(wiVoxelGrid grid);
void wiVoxelGrid_SetCenter(wiVoxelGrid grid, wiVector center);
wiVector wiVoxelGrid_GetVoxelSize(wiVoxelGrid grid);
void wiVoxelGrid_SetVoxelSize(wiVoxelGrid grid, wiVector size);

#ifdef __cplusplus
}
#endif
