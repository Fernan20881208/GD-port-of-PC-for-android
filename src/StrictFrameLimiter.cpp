#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>

using namespace geode::prelude;

namespace {
    using Clock = std::chrono::steady_clock;

    Clock::time_point s_lastFrameStart{};
    bool s_hasLastFrame = false;
    int64_t s_lastTarget = 0;

    bool limiterEnabled() {
        auto* mod = Mod::get();
        return mod &&
            mod->getSettingValue<bool>("unlock-fps") &&
            !mod->getSettingValue<bool>("vertical-sync");
    }

    int64_t targetFPS() {
        return std::clamp<int64_t>(
            Mod::get()->getSettingValue<int64_t>("target-fps"),
            30,
            360
        );
    }

    void resetLimiter() {
        s_hasLastFrame = false;
        s_lastTarget = 0;
    }

    void waitForFrameSlot() {
        if (!limiterEnabled()) {
            resetLimiter();
            return;
        }

        auto const target = targetFPS();
        auto now = Clock::now();

        if (!s_hasLastFrame || s_lastTarget != target) {
            s_lastFrameStart = now;
            s_hasLastFrame = true;
            s_lastTarget = target;
            return;
        }

        auto const period = std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>(1.0 / static_cast<double>(target))
        );
        auto const deadline = s_lastFrameStart + period;

        // A long gap means the app was paused, backgrounded, or stalled. Starting
        // a fresh cadence avoids bursts that try to "catch up" old frame slots.
        if (now - s_lastFrameStart > std::chrono::milliseconds(250)) {
            s_lastFrameStart = now;
            return;
        }

        if (now < deadline) {
            std::this_thread::sleep_until(deadline);
            now = Clock::now();
        }

        // Anchor to the real start time instead of accumulating missed deadlines.
        // This guarantees at least one target interval between rendered frames.
        s_lastFrameStart = now;
    }
}

class $modify(PCStrictFrameLimiter, CCDirector) {
    static void onModify(auto& self) {
        (void) self.setHookPriority("CCDirector::drawScene", Priority::First);
    }

    void drawScene() {
        waitForFrameSlot();
        CCDirector::drawScene();
    }
};
