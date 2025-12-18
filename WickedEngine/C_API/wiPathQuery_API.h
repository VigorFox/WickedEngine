#pragma once
#include "wiMath_API.h"
#include "wiVoxelGrid_API.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiPathQuery_t *wiPathQuery;

wiPathQuery wiPathQuery_Create();
void wiPathQuery_Destroy(wiPathQuery query);

void wiPathQuery_Process(wiPathQuery query, wiVector start, wiVector goal,
                         wiVoxelGrid voxelgrid);
bool wiPathQuery_SearchCover(wiPathQuery query, wiVector observer,
                             wiVector subject, wiVector direction,
                             float max_distance, wiVoxelGrid voxelgrid);
bool wiPathQuery_IsSuccessful(wiPathQuery query);
wiVector wiPathQuery_GetNextWaypoint(wiPathQuery query);
int wiPathQuery_GetWaypointCount(wiPathQuery query);
wiVector wiPathQuery_GetWaypoint(wiPathQuery query, int index);
wiVector wiPathQuery_GetGoal(wiPathQuery query);

void wiPathQuery_SetFlying(wiPathQuery query, bool value);
bool wiPathQuery_IsFlying(wiPathQuery query);
void wiPathQuery_SetAgentHeight(wiPathQuery query, int height);
int wiPathQuery_GetAgentHeight(wiPathQuery query);
void wiPathQuery_SetAgentWidth(wiPathQuery query, int width);
int wiPathQuery_GetAgentWidth(wiPathQuery query);
void wiPathQuery_SetDebugDrawWaypointsEnabled(wiPathQuery query, bool enabled);

#ifdef __cplusplus
}
#endif
