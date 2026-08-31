#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>

class PCPortPopup final : public geode::Popup {
protected:
    cocos2d::CCLabelBMFont* m_keyboardStatus = nullptr;
    cocos2d::CCLabelBMFont* m_pointerStatus = nullptr;
    cocos2d::CCLabelBMFont* m_scrollStatus = nullptr;
    cocos2d::CCLabelBMFont* m_performanceStatus = nullptr;
    float m_elapsed = 0.f;
    unsigned int m_frames = 0;

    bool init() override;
    void update(float dt) override;

    void onKeybinds(cocos2d::CCObject* sender);
    void onSettings(cocos2d::CCObject* sender);
    void onRoadmap(cocos2d::CCObject* sender);

public:
    static PCPortPopup* create();
};

