#include "wiApplication_API.h"
#include "wiApplication.h"
#include "wiRenderPath.h"
#include "wiRenderPath2D.h"
#include "wiRenderPath3D.h"
#include "wiLoadingScreen.h"

using namespace wi;

extern "C" {

void wiApplication_SetActivePath(wiApplication app, wiRenderPath path) {
    if (app) {
        ((Application*)app)->ActivatePath((RenderPath*)path);
    }
}

void wiApplication_SetActivePathFade(wiApplication app, wiRenderPath path, float fadeSeconds, wiColor fadeColor, wiFadeType fadeType) {
    if (app) {
        wi::Color color(fadeColor.r, fadeColor.g, fadeColor.b, fadeColor.a);
        ((Application*)app)->ActivatePath((RenderPath*)path, fadeSeconds, color, (FadeManager::FadeType)fadeType);
    }
}

wiRenderPath wiApplication_GetActivePath(wiApplication app) {
    if (app) {
        return (wiRenderPath)((Application*)app)->GetActivePath();
    }
    return nullptr;
}

void wiApplication_SetFrameSkip(wiApplication app, bool enabled) {
    if (app) ((Application*)app)->setFrameSkip(enabled);
}

void wiApplication_SetFullScreen(wiApplication app, bool enabled) {
    if (app) ((Application*)app)->SetFullScreen(enabled);
}

void wiApplication_SetTargetFrameRate(wiApplication app, float value) {
    if (app) ((Application*)app)->setTargetFrameRate(value);
}

void wiApplication_SetFrameRateLock(wiApplication app, bool enabled) {
    if (app) ((Application*)app)->setFrameRateLock(enabled);
}

void wiApplication_SetInfoDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.active = active;
}

void wiApplication_SetWatermarkDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.watermark = active;
}

void wiApplication_SetFPSDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.fpsinfo = active;
}

void wiApplication_SetResolutionDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.resolution = active;
}

void wiApplication_SetLogicalSizeDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.logical_size = active;
}

void wiApplication_SetColorSpaceDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.colorspace = active;
}

void wiApplication_SetPipelineCountDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.pipeline_count = active;
}

void wiApplication_SetHeapAllocationCountDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.heap_allocation_counter = active;
}

void wiApplication_SetVRAMUsageDisplay(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.vram_usage = active;
}

void wiApplication_SetColorGradingHelper(wiApplication app, bool active) {
    if (app) ((Application*)app)->infoDisplay.colorgrading_helper = active;
}



bool wiApplication_IsHDRSupported(wiApplication app) {
    if (app) {
        return wi::graphics::GetDevice()->IsSwapChainSupportsHDR(&((Application*)app)->swapChain);
    }
    return false;
}

void wiApplication_SetHDR(wiApplication app, bool enabled) {
    if (app) {
        Application* application = (Application*)app;
        application->allow_hdr = enabled;
        application->swapChain.desc.allow_hdr = enabled;
        wi::graphics::GetDevice()->CreateSwapChain(&application->swapChain.desc, nullptr, &application->swapChain);
    }
}

wiCanvas wiApplication_GetCanvas(wiApplication app) {
    if (app) {
        return (wiCanvas)&((Application*)app)->canvas;
    }
    return nullptr;
}

void wiApplication_SetCanvas(wiApplication app, wiCanvas canvas) {
    if (app && canvas) {
        ((Application*)app)->canvas = *((Canvas*)canvas);
    }
}

void wiApplication_Exit(wiApplication app) {
    if (app) {
        ((Application*)app)->Exit();
    }
}

}
