#include "PerformanceHud.hpp"

#include <cmath>

using namespace geode::prelude;

bool PerformanceHud::init() {
    if (!CCNode::init()) {
        return false;
    }

    m_label = CCLabelBMFont::create("-- FPS | --.- ms", "bigFont.fnt");
    m_label->setAnchorPoint({ 0.f, 1.f });
    m_label->setScale(.35f);
    m_label->setOpacity(205);
    this->addChild(m_label);
    this->scheduleUpdate();
    return true;
}

void PerformanceHud::update(float dt) {
    auto const visible = Mod::get()->getSettingValue<bool>("show-fps");
    m_label->setVisible(visible);
    if (!visible || !std::isfinite(dt) || dt <= 0.f || dt > .5f) {
        return;
    }

    m_elapsed += dt;
    ++m_frames;

    if (m_elapsed >= .25f) {
        auto const fps = static_cast<float>(m_frames) / m_elapsed;
        auto const frameTime = (m_elapsed * 1000.f) / static_cast<float>(m_frames);
        m_label->setString(fmt::format("{:.0f} FPS | {:.1f} ms", fps, frameTime).c_str());
        m_elapsed = 0.f;
        m_frames = 0;
    }
}

PerformanceHud* PerformanceHud::create() {
    auto ret = new PerformanceHud();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

