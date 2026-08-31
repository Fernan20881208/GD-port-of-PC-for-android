#pragma once

#include <string>

namespace GraphicsController {
    void applyAll();
    void applyVSync();
    void applyFrameRate();
    void applyTextureQuality();
    bool lastVSyncApplySucceeded();
    std::string statusText();
}
