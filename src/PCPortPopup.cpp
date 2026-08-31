#include "PCPortPopup.hpp"

#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/loader/Loader.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/utils/AndroidEvent.hpp>
#include <Geode/utils/Keyboard.hpp>

#include <cmath>
#include <variant>

using namespace geode::prelude;

namespace {
    CCLabelBMFont* addStatusRow(CCNode* parent, char const* text, float y) {
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setAnchorPoint({ 0.f, .5f });
        label->setScale(.38f);
        label->setPosition({ 35.f, y });
        parent->addChild(label);
        return label;
    }

    CCMenuItemSpriteExtra* addButton(
        CCMenu* menu,
        CCObject* target,
        SEL_MenuHandler selector,
        char const* text,
        CCPoint position
    ) {
        auto sprite = ButtonSprite::create(text, "bigFont.fnt", "GJ_button_01.png", .75f);
        sprite->setScale(.72f);
        auto button = CCMenuItemSpriteExtra::create(sprite, target, selector);
        button->setPosition(position);
        menu->addChild(button);
        return button;
    }
}

bool PCPortPopup::init() {
    if (!Popup::init(390.f, 265.f)) {
        return false;
    }

    m_noElasticity = true;
    this->setTitle("PC Experience - Android");

    auto subtitle = CCLabelBMFont::create("Diagnostico en vivo", "goldFont.fnt");
    subtitle->setScale(.45f);
    subtitle->setPosition({ m_size.width / 2.f, m_size.height - 48.f });
    m_mainLayer->addChild(subtitle);

    m_keyboardStatus = addStatusRow(m_mainLayer, "Teclado: esperando una tecla", 183.f);
    m_pointerStatus = addStatusRow(m_mainLayer, "Raton / tactil: esperando entrada", 158.f);
    m_scrollStatus = addStatusRow(m_mainLayer, "Rueda: esperando desplazamiento", 133.f);
    m_performanceStatus = addStatusRow(m_mainLayer, "Rendimiento: midiendo...", 103.f);

    auto note = CCLabelBMFont::create(
        "Clic y rueda usan el puente de Geode; los atajos\ncompletos se configuran en Custom Keybinds.",
        "chatFont.fnt"
    );
    note->setAlignment(kCCTextAlignmentCenter);
    note->setScale(.58f);
    note->setColor({ 210, 225, 255 });
    note->setPosition({ m_size.width / 2.f, 73.f });
    m_mainLayer->addChild(note);

    addButton(
        m_buttonMenu, this, menu_selector(PCPortPopup::onKeybinds),
        "Teclas", { -105.f, -102.f }
    );
    addButton(
        m_buttonMenu, this, menu_selector(PCPortPopup::onSettings),
        "Opciones", { 0.f, -102.f }
    );
    addButton(
        m_buttonMenu, this, menu_selector(PCPortPopup::onRoadmap),
        "Estado", { 105.f, -102.f }
    );

    this->addEventListener(KeyboardInputEvent(), [this](KeyboardInputData& data) {
        if (data.action == KeyboardInputData::Action::Press) {
            m_keyboardStatus->setString(
                fmt::format("Teclado: detectado ({})", Keybind(data.key, data.modifiers).toString()).c_str()
            );
            m_keyboardStatus->setColor({ 90, 255, 120 });
        }
        return ListenerResult::Propagate;
    });

    this->addEventListener(ScrollWheelEvent(), [this](double x, double y) {
        m_scrollStatus->setString(fmt::format("Rueda: detectada ({:.1f}, {:.1f})", x, y).c_str());
        m_scrollStatus->setColor({ 90, 255, 120 });
        return ListenerResult::Propagate;
    });

    this->addEventListener(AndroidRichInputEvent(), [this](
        int64_t, int deviceID, int source, AndroidRichInput input
    ) {
        if (std::holds_alternative<AndroidTouchInput>(input)) {
            m_pointerStatus->setString(
                fmt::format("Raton / tactil: detectado (dispositivo {})", deviceID).c_str()
            );
            m_pointerStatus->setColor({ 90, 255, 120 });
        }
        else if (std::holds_alternative<AndroidScrollInput>(input)) {
            m_scrollStatus->setString(
                fmt::format("Rueda: detectada (fuente 0x{:x})", source).c_str()
            );
            m_scrollStatus->setColor({ 90, 255, 120 });
        }
        return ListenerResult::Propagate;
    });

    this->scheduleUpdate();
    return true;
}

void PCPortPopup::update(float dt) {
    if (!std::isfinite(dt) || dt <= 0.f || dt > .5f) {
        return;
    }

    m_elapsed += dt;
    ++m_frames;
    if (m_elapsed >= .4f) {
        auto const fps = static_cast<float>(m_frames) / m_elapsed;
        auto const frameTime = (m_elapsed * 1000.f) / static_cast<float>(m_frames);
        m_performanceStatus->setString(
            fmt::format("Rendimiento: {:.0f} FPS | {:.1f} ms", fps, frameTime).c_str()
        );
        m_performanceStatus->setColor(fps >= 55.f ? ccColor3B { 90, 255, 120 } : ccColor3B { 255, 210, 80 });
        m_elapsed = 0.f;
        m_frames = 0;
    }
}

void PCPortPopup::onKeybinds(CCObject*) {
    auto keybinds = Loader::get()->getInstalledMod("geode.custom-keybinds");
    if (keybinds) {
        openKeybindsPopup(std::nullopt, keybinds);
    }
}

void PCPortPopup::onSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void PCPortPopup::onRoadmap(CCObject*) {
    createQuickPopup(
        "Estado de compatibilidad",
        "<cg>Listo:</c> teclado, clic, rueda, atajos de juego/editor, HUD y controles adaptativos.\n\n"
        "<cy>En desarrollo:</c> cursor con hover, captura relativa del raton y equivalentes Android de las opciones avanzadas de video de PC.",
        "OK", nullptr, [](FLAlertLayer*, bool) {}
    );
}

PCPortPopup* PCPortPopup::create() {
    auto ret = new PCPortPopup();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
