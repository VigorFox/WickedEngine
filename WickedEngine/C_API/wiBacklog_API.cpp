#include "wiBacklog_API.h"
#include "wiBacklog.h"

using namespace wi::backlog;

extern "C" {

void wiBacklog_Post(const char *text) { post(text); }

void wiBacklog_Clear() { clear(); }

void wiBacklog_SetFontSize(int value) { setFontSize(value); }

} // extern "C"
