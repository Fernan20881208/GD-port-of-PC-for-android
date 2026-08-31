#pragma once

#include <Geode/Geode.hpp>

class PerformanceHud final : public cocos2d::CCNode {
protected:
    cocos2d::CCLabelBMFont* m_label = nullptr;
    float m_elapsed = 0.f;
    unsigned int m_frames = 0;

    bool init() override;
    void update(float dt) override;

public:
    static PerformanceHud* create();
};

