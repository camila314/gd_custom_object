#include <Cacao.hpp>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

using namespace cocos2d;

namespace CocoXIB {
template <typename T, typename F>
void renderCustomUI(T self, F mainLayer);
}

ModContainer* m;
#define DREF(exp) (*((uint64_t*)(exp)))
class SetupSpeedPopup : public FLAlertLayer {
 public:
    SetupSpeedPopup() : 
        FLAlertLayer() {
            m_controlConnected = -1;
            m_joystickConnected = -1;
            m_ZOrder = 0;
            m_noElasticity = true;
            m_touchT = nullptr;
            m_spawnT = nullptr;
            m_effectObject = nullptr;
        }
    static SetupSpeedPopup* create(EffectGameObject* ego) {
        SetupSpeedPopup* ret = new SetupSpeedPopup();
        uint64_t ok1 = *((uint64_t*)ret);
        uint64_t ok2 = DREF(ok1-8)+16;

        uint64_t n_typinfo = getBase()+0x65d870;
        MemoryContainer(ok2, 8, reinterpret_cast<char*>(&n_typinfo)).enable();
        if (ret && ret->init(ego)) {
            ret->m_scene = NULL;
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }
    void onClose(CCObject* callback) {
        auto speed = std::strtod(m_mainInput->getString_s(), nullptr);
        m_effectObject->_spawnDelay() = speed;

        m_helper->keyBackClicked();
        setKeypadEnabled(false);
        setTouchEnabled(false);
        removeFromParentAndCleanup(true);
    }
    virtual void keyBackClicked() {
        onClose(NULL);
    }

    void onTouch(CCObject*) {m_effectObject->_touchTriggered() = !m_effectObject->_touchTriggered();}
    void onSpawn(CCObject*) {m_effectObject->_spawnTriggered() = !m_effectObject->_spawnTriggered();}

    void restoreDefaults() {
        std::string s = to_string(m_effectObject->_spawnDelay());
        if (s.length()>0 && m_effectObject->_spawnDelay() != 0.0f)
            m_mainInput->setString(s);

        if (m_touchT && m_spawnT) {
            m_touchT->toggle(m_effectObject->_touchTriggered());
            m_spawnT->toggle(m_effectObject->_spawnTriggered());
        }
    }

    bool init(EffectGameObject* ego) {

        if (CCLayerColor::initWithColor(ccc4(0,0,0,150))) {
            m_effectObject = ego;

            m_helper = FLAlertLayer::create("","","");
            m_helper->m_buttonMenu->setVisible(false);
            m_helper->m_noElasticity = true;
            m_helper->show();

            registerWithTouchDispatcher();
            CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);

            setTouchEnabled(true);
            setKeypadEnabled(true);

            m_mainLayer = CCLayer::create();
            addChild(m_mainLayer);

            //CCLayerColor* mycolor = CCLayerColor::create(ccc4(0,0,0,150), getContentSize().width, getContentSize().height);
            //m_mainLayer->addChild(mycolor, -3);


            auto scale9 = extension::CCScale9Sprite::create("GJ_square01.png");
            scale9->setContentSize(CCSizeMake(300, 280));
            scale9->setPosition(Cacao::relativePosition(50,50));
            m_mainLayer->addChild(scale9, -2);

            CocoXIB::renderCustomUI(this, m_mainLayer);
            restoreDefaults();
        }
        return true;
    }
 protected:
    template <typename T, typename F>
    friend void CocoXIB::renderCustomUI(T, F);

    EffectGameObject* m_effectObject;
    CCTextInputNode* m_mainInput;
    FLAlertLayer* m_helper;

    CCMenuItemToggler* m_touchT;
    CCMenuItemToggler* m_spawnT;
};

#include "cocoxib.h"

std::string mySaveString(EffectGameObject* ego) {
    std::string out = ORIG(mySaveString, 0xcd7e0)(ego);
    if (ego->_id()==3142 && ego->_spawnDelay() > 0) {
        out += ",63," + to_string(ego->_spawnDelay());
    }
    std::cout << out << "\n\n";
    return out;
}

bool g_lock;
std::string myGSaveString(EffectGameObject* ego) {
    if (ego->_id()==3142) {
        if (!g_lock) {
            g_lock = true;
            return mySaveString(ego);
        }
        g_lock = false;
    }
    return ORIG(myGSaveString, 0x33d3d0)(ego);
}

GameObject* obFromString(std::string st, bool idk) {
    auto go = ORIG(obFromString, 0x33b720)(st, idk);
    printf("%p ob id %d\n", go, go ? go->_id() : -1);
    auto mymap = GameToolbox::stringSetupToMap(st, ",");
    if (go && go->_id() == 3142) {
        auto ego = reinterpret_cast<EffectGameObject*>(go);

        for (auto const& pair: mymap) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }

        if (mymap.count("63")) {
            ego->_spawnDelay() = std::strtod(mymap["63"].c_str(), nullptr);
        }
        if (mymap.count("11") && mymap["11"]=="1") {
            ego->_touchTriggered() = true;
        }
        if (mymap.count("62") && mymap["62"]=="1") {
            ego->_spawnTriggered() = true;
        }
    }
    return go;
}

void inject() {
    g_lock = false;

    setupTypeinfos();
    m = new ModContainer("Swag");

    auto editor = Cacao::EditorUIEditor::create(m);

    constexpr int myObjectID = 3142;
    Cacao::addGDObject("checkpoint_01_001.png", myObjectID);

    editor
      ->bar(11)
      ->addIndex(12, myObjectID)
      ->addObjectsToGameSheet02(myObjectID)
      ->addEffectObjects(myObjectID);

    editor->addTriggerCallback(myObjectID, +[](GameObject* self, GJBaseGameLayer* gameLayer) {
        double newsp = (double)(reinterpret_cast<EffectGameObject*>(self)->_spawnDelay());
        double multiplier = 5.7700018882751465;
        gameLayer->_player1()->_speed() = newsp * multiplier;
    });
    
    editor->applyAll();

    void(*lam)(EditorUI*) = +[](EditorUI* self) {
        auto obs = self->getSelectedObjects();
        if (obs->count() == 1) {
            auto o = reinterpret_cast<EffectGameObject*>(obs->objectAtIndex(0));
            if (o->_id() == 3142) {
                SetupSpeedPopup::create(o)->show();
                return;
            }
        }
        ORIG(*lam, 0x195a0)(self);
    };
    m->registerHook(getBase()+0x195a0, lam);

    m->registerHook(getBase()+0xcd7e0, mySaveString);
    m->registerHook(getBase()+0x33b720, obFromString);
    m->registerHook(getBase()+0x33d3d0, myGSaveString);

    m->enable();
}
