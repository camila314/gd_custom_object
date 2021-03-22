
namespace CocoXIB {
template <typename T, typename F>
void renderCustomUI(T self, F mainLayer) {
auto wSize = CCDirector::sharedDirector()->getWinSize();
float hwidth = wSize.width/2;
float hheight = wSize.height/2;
typedef void (CCObject::*menusel)(CCObject*);

auto idrFe_NB_7Pv_l = CCLabelBMFont::create("Speed Command", "goldFont.fnt");
idrFe_NB_7Pv_l->setScale(0.6857142857142857);
CCPoint idrFe_NB_7Pv_pos(-0.5 + hwidth, 123.5 + hheight);
idrFe_NB_7Pv_l->setPosition(mainLayer->convertToNodeSpace(idrFe_NB_7Pv_pos));
mainLayer->addChild(idrFe_NB_7Pv_l);

auto idrsJ_EI_dqw_m = CCMenu::create();
auto idrsJ_EI_dqw_b = ButtonSprite::create("OK", 47.0, 1, 1, true);

auto idrsJ_EI_dqw_i = CCMenuItemSpriteExtra::create(idrsJ_EI_dqw_b, idrsJ_EI_dqw_b, self, menu_selector(SetupSpeedPopup::onClose));
idrsJ_EI_dqw_m->addChild(idrsJ_EI_dqw_i);
idrsJ_EI_dqw_b->setScale(0.8928571428571429);
mainLayer->addChild(idrsJ_EI_dqw_m);
CCPoint idrsJ_EI_dqw_loc(0.0 + hwidth, -113.0 + hheight);
idrsJ_EI_dqw_m->setPosition(idrsJ_EI_dqw_loc);

auto idain_Fn_flq_sq = extension::CCScale9Sprite::create("square02b_small.png");
auto idain_Fn_flq_i = CCTextInputNode::create(50.0, 40.0, "0", "Thonburi", 24, "bigFont.fnt");
idain_Fn_flq_sq->setOpacity(100);
idain_Fn_flq_sq->setColor(ccc3(0,0,0));
idain_Fn_flq_sq->setContentSize(CCSizeMake(60.0, 30.0));
idain_Fn_flq_i->setAllowedChars("0123456789.-");

CCPoint idain_Fn_flq_loc(-0.5 + hwidth, 2.0 + hheight);
idain_Fn_flq_i->setPosition(idain_Fn_flq_loc);
idain_Fn_flq_sq->setPosition(idain_Fn_flq_loc);
idain_Fn_flq_i->setMaxLabelScale(0.5714285714285714);
self->m_mainInput = idain_Fn_flq_i;
mainLayer->addChild(idain_Fn_flq_sq);
mainLayer->addChild(idain_Fn_flq_i);

auto idyms_e4_gEW_l = CCLabelBMFont::create("Speed", "goldFont.fnt");
idyms_e4_gEW_l->setScale(0.6476190476190476);
CCPoint idyms_e4_gEW_pos(-0.5 + hwidth, 35.0 + hheight);
idyms_e4_gEW_l->setPosition(mainLayer->convertToNodeSpace(idyms_e4_gEW_pos));
mainLayer->addChild(idyms_e4_gEW_l);

auto idYNY_S5_BJA_m = CCMenu::create();
mainLayer->addChild(idYNY_S5_BJA_m);
CCPoint idYNY_S5_BJA_pos(-128.0 + hwidth, -108.5 + hheight);
idYNY_S5_BJA_m->setPosition(mainLayer->convertToNodeSpace(idYNY_S5_BJA_pos));

auto idYNY_S5_BJA_t = Cacao::createToggler(self, menu_selector(SetupSpeedPopup::onTouch));
idYNY_S5_BJA_t->setScale(0.7142857142857143);
self->m_touchT = idYNY_S5_BJA_t;
idYNY_S5_BJA_m->addChild(idYNY_S5_BJA_t);

auto idQWC_uD_9bH_m = CCMenu::create();
mainLayer->addChild(idQWC_uD_9bH_m);
CCPoint idQWC_uD_9bH_pos(-128.0 + hwidth, -68.5 + hheight);
idQWC_uD_9bH_m->setPosition(mainLayer->convertToNodeSpace(idQWC_uD_9bH_pos));

auto idQWC_uD_9bH_t = Cacao::createToggler(self, menu_selector(SetupSpeedPopup::onSpawn));
idQWC_uD_9bH_t->setScale(0.7142857142857143);
self->m_spawnT = idQWC_uD_9bH_t;
idQWC_uD_9bH_m->addChild(idQWC_uD_9bH_t);

auto id3ob_Ii_L7I_l = CCLabelBMFont::create("Spawn   \nTriggered", "bigFont.fnt");
id3ob_Ii_L7I_l->setScale(0.37142857142857144);
CCPoint id3ob_Ii_L7I_pos(-74.5 + hwidth, -108.0 + hheight);
id3ob_Ii_L7I_l->setPosition(mainLayer->convertToNodeSpace(id3ob_Ii_L7I_pos));
mainLayer->addChild(id3ob_Ii_L7I_l);

auto idM9K_3P_c3x_l = CCLabelBMFont::create("Touch    \nTriggered", "bigFont.fnt");
idM9K_3P_c3x_l->setScale(0.37142857142857144);
CCPoint idM9K_3P_c3x_pos(-76.0 + hwidth, -68.0 + hheight);
idM9K_3P_c3x_l->setPosition(mainLayer->convertToNodeSpace(idM9K_3P_c3x_pos));
mainLayer->addChild(idM9K_3P_c3x_l);
} }