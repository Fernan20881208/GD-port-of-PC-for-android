#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

#include <cmath>

using namespace geode::prelude;

namespace {
    bool shouldUseRealGameplayDelta() {
        auto* mod = Mod::get();
        if (!mod) {
            return false;
        }

        return mod->getSettingValue<bool>("unlock-fps") &&
            !mod->getSettingValue<bool>("vertical-sync");
    }

    bool validRealDelta(float delta) {
        // Reject invalid values and large resume/background spikes. In those cases
        // vanilla GD is allowed to handle the frame with its normal safeguards.
        return std::isfinite(delta) && delta > 0.00001f && delta < 0.100f;
    }
}

class $modify(PCGameplayTimingFix, GJBaseGameLayer) {
    static void onModify(auto& self) {
        // Run early so later gameplay mods still receive a sane, wall-clock based
        // delta instead of a delta coupled to our Android render interval.
        (void) self.setHookPriority(
            "GJBaseGameLayer::getModifiedDelta",
            Priority::VeryEarly
        );
    }

    float getModifiedDelta(float delta) {
        if (!shouldUseRealGameplayDelta()) {
            return GJBaseGameLayer::getModifiedDelta(delta);
        }

        auto* director = CCDirector::sharedDirector();
        if (!director) {
            return GJBaseGameLayer::getModifiedDelta(delta);
        }

        auto const actualDelta = director->getActualDeltaTime();
        if (!validRealDelta(actualDelta)) {
            return GJBaseGameLayer::getModifiedDelta(delta);
        }

        // Feed GD its real elapsed wall-clock time. The Android render loop can
        // now run at 120/144/240/360 FPS without multiplying gameplay speed.
        return GJBaseGameLayer::getModifiedDelta(actualDelta);
    }
};
