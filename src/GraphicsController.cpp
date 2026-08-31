#include "GraphicsController.hpp"

#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/cocos/platform/android/CCApplication.h>
#include <EGL/egl.h>

#include <algorithm>
#include <cmath>

using namespace geode::prelude;

namespace {
    bool s_vsyncAttempted = false;
    bool s_vsyncSucceeded = false;
    double s_defaultAnimationInterval = 0.0;
    std::string s_lastTextureQuality;

    int64_t targetFPS() {
        return std::clamp<int64_t>(
            Mod::get()->getSettingValue<int64_t>("target-fps"),
            30,
            360
        );
    }

    TextureQuality resolveTextureQuality(std::string const& value) {
        if (value == "Low") {
            return kTextureQualityLow;
        }
        if (value == "Medium") {
            return kTextureQualityMedium;
        }
        if (value == "High") {
            return kTextureQualityHigh;
        }

        auto const pixels = CCDirector::sharedDirector()->getWinSizeInPixels();
        if (pixels.width >= 1600.f || pixels.height >= 900.f) {
            return kTextureQualityHigh;
        }
        if (pixels.width >= 960.f || pixels.height >= 540.f) {
            return kTextureQualityMedium;
        }
        return kTextureQualityLow;
    }
}

void GraphicsController::applyVSync() {
    auto const enabled = Mod::get()->getSettingValue<bool>("vertical-sync");
    auto const display = eglGetCurrentDisplay();

    s_vsyncAttempted = true;
    if (display == EGL_NO_DISPLAY) {
        s_vsyncSucceeded = false;
        log::warn("VSync: no hay EGLDisplay actual; se reintentara cuando exista un contexto grafico");
        return;
    }

    s_vsyncSucceeded = eglSwapInterval(display, enabled ? 1 : 0) == EGL_TRUE;
    if (s_vsyncSucceeded) {
        log::info("VSync Android solicitado: {}", enabled ? "ON" : "OFF");
    }
    else {
        log::warn("eglSwapInterval rechazo el cambio de VSync; el compositor/controlador puede estar forzandolo");
    }
}

void GraphicsController::applyFrameRate() {
    auto* director = CCDirector::sharedDirector();
    if (!director) {
        return;
    }

    if (s_defaultAnimationInterval <= 0.0) {
        auto const current = director->getAnimationInterval();
        s_defaultAnimationInterval = std::isfinite(current) && current > 0.0
            ? current
            : (1.0 / 60.0);
    }

    auto const vsync = Mod::get()->getSettingValue<bool>("vertical-sync");
    auto const unlock = Mod::get()->getSettingValue<bool>("unlock-fps");

    double interval = s_defaultAnimationInterval;
    if (!vsync && unlock) {
        interval = 1.0 / static_cast<double>(targetFPS());
    }

    if (auto* app = CCApplication::sharedApplication()) {
        app->setAnimationInterval(interval);
        log::info(
            "Frame target Android: {:.2f} FPS{}",
            1.0 / interval,
            vsync ? " (VSync tiene prioridad)" : ""
        );
    }
}

void GraphicsController::applyTextureQuality() {
    auto* director = CCDirector::sharedDirector();
    if (!director) {
        return;
    }

    auto const value = Mod::get()->getSettingValue<std::string>("texture-quality");
    if (value == s_lastTextureQuality) {
        return;
    }

    s_lastTextureQuality = value;
    director->updateContentScale(resolveTextureQuality(value));
    log::info("Texture Quality: {}", value);
}

void GraphicsController::applyAll() {
    applyTextureQuality();
    applyVSync();
    applyFrameRate();
}

bool GraphicsController::lastVSyncApplySucceeded() {
    return s_vsyncAttempted && s_vsyncSucceeded;
}

std::string GraphicsController::statusText() {
    auto const vsync = Mod::get()->getSettingValue<bool>("vertical-sync");
    auto const unlock = Mod::get()->getSettingValue<bool>("unlock-fps");

    return fmt::format(
        "Fullscreen Android | VSync {}{} | FPS {}",
        vsync ? "ON" : "OFF",
        s_vsyncAttempted ? (s_vsyncSucceeded ? "" : " (driver)") : " (?)",
        (!vsync && unlock) ? std::to_string(targetFPS()) : "sistema"
    );
}

$execute {
    listenForSettingChanges<bool>("vertical-sync", [](bool) {
        GraphicsController::applyVSync();
        GraphicsController::applyFrameRate();
    });

    listenForSettingChanges<bool>("unlock-fps", [](bool) {
        GraphicsController::applyFrameRate();
    });

    listenForSettingChanges<int64_t>("target-fps", [](int64_t) {
        GraphicsController::applyFrameRate();
    });

    listenForSettingChanges<std::string>("texture-quality", [](std::string) {
        GraphicsController::applyTextureQuality();
    });

    listenForSettingChanges<bool>("smooth-fix", [](bool enabled) {
        if (enabled) {
            CCDirector::sharedDirector()->resetSmoothFixCounter();
        }
    });
}
