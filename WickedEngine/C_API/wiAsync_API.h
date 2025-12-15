#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiAsync_t *wiAsync;

// In Lua bind, "Async" is just a namespace/static class wrapper around
// jobsystem things, OR it returns a context object. Lua: methods `Wait`,
// `IsCompleted` operate on `ctx`. The bind class `Async_BindLua` has a member
// `wi::jobsystem::context ctx`. It seems `wiAsync` wrapper in C should hold
// this context.

wiAsync wiAsync_Create();
void wiAsync_Destroy(wiAsync async);

void wiAsync_Wait(wiAsync async);
bool wiAsync_IsCompleted(wiAsync async);

// We might want to expose "Run" or "Execute" to actually do something async?
// Lua bindings often wrap specific async tasks returning this object.
// But the standalone Async object usually is just a synchronization primitive
// (context). C API users can use this to sync with internal engine jobs if we
// expose a way to launch them. For now mirroring Lua: just Wait/IsCompleted.

#ifdef __cplusplus
}
#endif
