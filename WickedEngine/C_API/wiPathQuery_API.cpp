#include "wiPathQuery_API.h"
#include "../wiPathQuery.h"
#include "../wiVoxelGrid.h"

using namespace wi;

extern "C" {

wiPathQuery wiPathQuery_Create() { return (wiPathQuery) new PathQuery(); }

void wiPathQuery_Destroy(wiPathQuery query) {
  if (query)
    delete (PathQuery *)query;
}

void wiPathQuery_Process(wiPathQuery query, wiVector start, wiVector goal,
                         wiVoxelGrid voxelgrid) {
  if (query && voxelgrid) {
    XMFLOAT3 s, g;
    s.x = start.x;
    s.y = start.y;
    s.z = start.z;
    g.x = goal.x;
    g.y = goal.y;
    g.z = goal.z;
    ((PathQuery *)query)->process(s, g, *(VoxelGrid *)voxelgrid);
  }
}

bool wiPathQuery_SearchCover(wiPathQuery query, wiVector observer,
                             wiVector subject, wiVector direction,
                             float max_distance, wiVoxelGrid voxelgrid) {
  if (!query || !voxelgrid)
    return false;
  XMFLOAT3 o, s, d;
  o.x = observer.x;
  o.y = observer.y;
  o.z = observer.z;
  s.x = subject.x;
  s.y = subject.y;
  s.z = subject.z;
  d.x = direction.x;
  d.y = direction.y;
  d.z = direction.z;
  return ((PathQuery *)query)
      ->search_cover(o, s, d, max_distance, *(VoxelGrid *)voxelgrid);
}

bool wiPathQuery_IsSuccessful(wiPathQuery query) {
  if (!query)
    return false;
  return ((PathQuery *)query)->is_succesful();
}

wiVector wiPathQuery_GetNextWaypoint(wiPathQuery query) {
  wiVector v = {0, 0, 0, 0};
  if (query) {
    XMFLOAT3 p = ((PathQuery *)query)->get_next_waypoint();
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
  }
  return v;
}

int wiPathQuery_GetWaypointCount(wiPathQuery query) {
  if (!query)
    return 0;
  return (int)((PathQuery *)query)->get_waypoint_count();
}

wiVector wiPathQuery_GetWaypoint(wiPathQuery query, int index) {
  wiVector v = {0, 0, 0, 0};
  if (query && index >= 0 &&
      index < (int)((PathQuery *)query)->get_waypoint_count()) {
    XMFLOAT3 p = ((PathQuery *)query)->get_waypoint(index);
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
  }
  return v;
}

wiVector wiPathQuery_GetGoal(wiPathQuery query) {
  wiVector v = {0, 0, 0, 0};
  if (query) {
    XMFLOAT3 p = ((PathQuery *)query)->get_goal();
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
  }
  return v;
}

void wiPathQuery_SetFlying(wiPathQuery query, bool value) {
  if (query)
    ((PathQuery *)query)->flying = value;
}

bool wiPathQuery_IsFlying(wiPathQuery query) {
  return query ? ((PathQuery *)query)->flying : false;
}

void wiPathQuery_SetAgentHeight(wiPathQuery query, int height) {
  if (query)
    ((PathQuery *)query)->agent_height = height;
}

int wiPathQuery_GetAgentHeight(wiPathQuery query) {
  return query ? ((PathQuery *)query)->agent_height : 0;
}

void wiPathQuery_SetAgentWidth(wiPathQuery query, int width) {
  if (query)
    ((PathQuery *)query)->agent_width = width;
}

int wiPathQuery_GetAgentWidth(wiPathQuery query) {
  return query ? ((PathQuery *)query)->agent_width : 0;
}

void wiPathQuery_SetDebugDrawWaypointsEnabled(wiPathQuery query, bool enabled) {
  if (query)
    ((PathQuery *)query)->debug_waypoints = enabled;
}

} // extern "C"
