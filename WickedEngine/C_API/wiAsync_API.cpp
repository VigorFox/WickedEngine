#include "wiAsync_API.h"
#include "../wiJobSystem.h"

extern "C" {

struct wiAsync_Internal {
  wi::jobsystem::context ctx;
};

wiAsync wiAsync_Create() { return (wiAsync) new wiAsync_Internal(); }

void wiAsync_Destroy(wiAsync async) {
  if (async)
    delete (wiAsync_Internal *)async;
}

void wiAsync_Wait(wiAsync async) {
  if (async)
    wi::jobsystem::Wait(((wiAsync_Internal *)async)->ctx);
}

bool wiAsync_IsCompleted(wiAsync async) {
  if (!async)
    return true;
  return !wi::jobsystem::IsBusy(((wiAsync_Internal *)async)->ctx);
}

} // extern "C"
