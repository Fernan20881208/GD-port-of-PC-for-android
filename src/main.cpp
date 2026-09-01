#include "GraphicsController.hpp"
#include "PCPortPopup.hpp"
#include "PerformanceHud.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/UILayer.hpp>

#ifdef GEODE_IS_ANDROID
#include <Geode/utils/AndroidEvent.hpp>
#include <variant>
#endif

using namespace geode::prelude;

namespace {
#ifdef GEODE_IS_ANDROID
    constexpr int kAndroidSourceMouse = 0x00002002;
    constexpr int kAndroidSourceMouseRelative = 0x00020004;

    bool isMouseSource(int source) {
        return (source & kAndroidSourceMouse) == kAndroidSourceMouse ||
            (source & kAndroidSourceMouseRelative) == kAndroidSourceMouseRelative;
    }
#endif

    void attachPerformanceHud(GJBaseGameLayer* layer) {
        if (!layer || !layer->m_uiLayer) {
            return;
        }

        auto hud = PerformanceHud::create();
        if (!hud) {
            return;
        }
        hud->setID("performance-hud"_spr);
        auto const winSize = CCDirector::sharedDirector()->getWinSize();
        hud->setPosition({ 7.f, winSize.height - 7.f });
        layer->m_uiLayer->addChild(hud, 10000);
    }
}

class $modify(PCMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // The menu runs with an active graphics context on both mobile targets.
        GraphicsController::applyAll();

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("No se encontro bottom-menu; se omite el boton PC");
            return true;
        }

        auto sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        sprite->setScale(.78f);
        auto button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(PCMenuLayer::onPCPanel)
        );
        button->setID("pc-panel-button"_spr);
        menu->addChild(button);
        menu->updateLayout();
        return true;
    }

    void onPCPanel(CCObject*) {
        if (auto popup = PCPortPopup::create()) {
            popup->show();
        }
    }
};

class $modify(PCPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }
        GraphicsController::applyVSync();
        GraphicsController::applyFrameRate();
        attachPerformanceHud(this);
        return true;
    }
};

class $modify(PCLevelEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level, bool noUI) {
        if (!LevelEditorLayer::init(level, noUI)) {
            return false;
        }
        GraphicsController::applyVSync();
        GraphicsController::applyFrameRate();
        attachPerformanceHud(this);
        return true;
    }
};

class $modify(PCUILayer, UILayer) {
    struct Fields {
        bool m_desktopInput = false;
    };

    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer)) {
            return false;
        }

        auto const alwaysHide = Mod::get()->getSettingValue<bool>("always-hide-touch-ui");
        if (alwaysHide) {
            this->setDesktopInput(true);
        }

#ifdef GEODE_IS_ANDROID
        this->addEventListener(AndroidRichInputEvent(), [this](
            int64_t, int, int source, AndroidRichInput input
        ) {
            if (Mod::get()->getSettingValue<bool>("always-hide-touch-ui")) {
                this->setDesktopInput(true);
                return ListenerResult::Propagate;
            }

            if (!Mod::get()->getSettingValue<bool>("adaptive-touch-ui")) {
                this->setDesktopInput(false);
                return ListenerResult::Propagate;
            }

            if (std::holds_alternative<AndroidTouchInput>(input)) {
                this->setDesktopInput(isMouseSource(source));
            }
            else if (
                std::holds_alternative<AndroidKeyInput>(input) ||
                std::holds_alternative<AndroidScrollInput>(input) ||
                std::holds_alternative<AndroidJoystickInput>(input)
            ) {
                this->setDesktopInput(true);
            }
            return ListenerResult::Propagate;
        });
#endif

        return true;
    }

    void setDesktopInput(bool desktop) {
        if (m_fields->m_desktopInput == desktop) {
            return;
        }
        m_fields->m_desktopInput = desktop;
        this->updateUINodeVisibility(!desktop);
    }
};
