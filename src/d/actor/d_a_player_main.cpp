/**
 * d_a_player_main.cpp
 * 
 * Main file for the Link (Player) actor.
 * 
 * Much of Link's code is spread across various `.inc` files and included directly
 * into this one to make the file size more managable.
 * The original split locations are indicated in the map file.
*/

#include "d/actor/d_a_player_link.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "JSystem/JKernel/JKRHeap.h"

/* 80102E8C-80102EAC       .text daPy_createHeap__FP10fopAc_ac_c */
void daPy_createHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 80102F64-80103074       .text calc__13daPy_matAnm_cCFP11J3DMaterial */
void daPy_matAnm_c::calc(J3DMaterial*) const {
    /* Nonmatching */
}

/* 80103074-801030BC       .text seStartOnlyReverb__9daPy_lk_cFUl */
void daPy_lk_c::seStartOnlyReverb(unsigned long) {
    /* Nonmatching */
}

/* 801030BC-80103104       .text seStartMapInfo__9daPy_lk_cFUl */
void daPy_lk_c::seStartMapInfo(unsigned long) {
    /* Nonmatching */
}

/* 80103104-8010314C       .text seStartSwordCut__9daPy_lk_cFUl */
void daPy_lk_c::seStartSwordCut(unsigned long) {
    /* Nonmatching */
}

/* 8010314C-801031A4       .text voiceStart__9daPy_lk_cFUl */
void daPy_lk_c::voiceStart(unsigned long) {
    /* Nonmatching */
}

/* 801031A4-801031DC       .text itemButton__9daPy_lk_cCFv */
void daPy_lk_c::itemButton() const {
    /* Nonmatching */
}

/* 801031DC-80103214       .text itemTrigger__9daPy_lk_cCFv */
void daPy_lk_c::itemTrigger() const {
    /* Nonmatching */
}

/* 80103214-80103258       .text getReadyItem__9daPy_lk_cFv */
void daPy_lk_c::getReadyItem() {
    /* Nonmatching */
}

/* 80103258-801032E4       .text checkGroupItem__9daPy_lk_cFii */
void daPy_lk_c::checkGroupItem(int, int) {
    /* Nonmatching */
}

/* 801032E4-801033E4       .text checkSetItemTrigger__9daPy_lk_cFii */
void daPy_lk_c::checkSetItemTrigger(int, int) {
    /* Nonmatching */
}

/* 801033E4-80103450       .text auraJointCB0__9daPy_lk_cFi */
void daPy_lk_c::auraJointCB0(int) {
    /* Nonmatching */
}

class J3DNode;

/* 80103450-80103494       .text daPy_auraCallback__FP7J3DNodei */
void daPy_auraCallback(J3DNode*, int) {
    /* Nonmatching */
}

/* 80103494-80103A88       .text jointBeforeCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
void daPy_lk_c::jointBeforeCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103A88-80103AAC       .text daPy_jointBeforeCallback__FUlUsP16J3DTransformInfoP10Quaternion */
void daPy_jointBeforeCallback(unsigned long, unsigned short, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103AAC-80103C1C       .text jointAfterCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
void daPy_lk_c::jointAfterCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103C1C-80103C40       .text daPy_jointAfterCallback__FUlUsP16J3DTransformInfoP10Quaternion */
void daPy_jointAfterCallback(unsigned long, unsigned short, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103C40-80103EE4       .text jointCB0__9daPy_lk_cFi */
void daPy_lk_c::jointCB0(int) {
    /* Nonmatching */
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
void daPy_jointCallback0(J3DNode*, int) {
    /* Nonmatching */
}

/* 80103F28-80104178       .text jointCB1__9daPy_lk_cFv */
void daPy_lk_c::jointCB1() {
    /* Nonmatching */
}

/* 80104178-801041B4       .text daPy_jointCallback1__FP7J3DNodei */
void daPy_jointCallback1(J3DNode*, int) {
    /* Nonmatching */
}

/* 801041B4-801041EC       .text setAnimeHeap__9daPy_lk_cFP12JKRSolidHeap */
void daPy_lk_c::setAnimeHeap(JKRSolidHeap*) {
    /* Nonmatching */
}

/* 801041EC-80104240       .text setItemHeap__9daPy_lk_cFv */
void daPy_lk_c::setItemHeap() {
    /* Nonmatching */
}

/* 80104240-80104280       .text setBlurPosResource__9daPy_lk_cFUs */
void daPy_lk_c::setBlurPosResource(unsigned short) {
    /* Nonmatching */
}

/* 80104280-80104364       .text getItemAnimeResource__9daPy_lk_cFUs */
void daPy_lk_c::getItemAnimeResource(unsigned short) {
    /* Nonmatching */
}

/* 80104364-801043F0       .text getAnimeResource__9daPy_lk_cFP14daPy_anmHeap_cUsUl */
void daPy_lk_c::getAnimeResource(daPy_anmHeap_c*, unsigned short, unsigned long) {
    /* Nonmatching */
}

/* 801043F0-801044E8       .text getUnderUpperAnime__9daPy_lk_cFPC15daPy_anmIndex_cPP15J3DAnmTransformPP15J3DAnmTransformiUl */
void daPy_lk_c::getUnderUpperAnime(const daPy_anmIndex_c*, J3DAnmTransform**, J3DAnmTransform**, int, unsigned long) {
    /* Nonmatching */
}

/* 801044E8-80104564       .text setTextureAnimeResource__9daPy_lk_cFP16J3DAnmTexPatterni */
void daPy_lk_c::setTextureAnimeResource(J3DAnmTexPattern*, int) {
    /* Nonmatching */
}

/* 80104564-80104600       .text loadTextureAnimeResource__9daPy_lk_cFUli */
void daPy_lk_c::loadTextureAnimeResource(unsigned long, int) {
    /* Nonmatching */
}

/* 80104600-801046CC       .text checkBossBgm__9daPy_lk_cFv */
void daPy_lk_c::checkBossBgm() {
    /* Nonmatching */
}

/* 801046CC-801046EC       .text checkMabaAnimeBtp__9daPy_lk_cFi */
void daPy_lk_c::checkMabaAnimeBtp(int) {
    /* Nonmatching */
}

/* 801046EC-80104A08       .text checkNormalFace__9daPy_lk_cFv */
void daPy_lk_c::checkNormalFace() {
    /* Nonmatching */
}

/* 80104A08-80104E08       .text setTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setTextureAnime(unsigned short, int) {
    /* Nonmatching */
}

/* 80104E08-80104EC8       .text setPriTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setPriTextureAnime(unsigned short, int) {
    /* Nonmatching */
}

/* 80104EC8-80104F74       .text resetPriTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetPriTextureAnime() {
    /* Nonmatching */
}

/* 80104F74-80105040       .text setDemoTextureAnime__9daPy_lk_cFUsUsiUs */
void daPy_lk_c::setDemoTextureAnime(unsigned short, unsigned short, int, unsigned short) {
    /* Nonmatching */
}

/* 80105040-80105164       .text resetDemoTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetDemoTextureAnime() {
    /* Nonmatching */
}

/* 80105164-80105220       .text setTextureScrollResource__9daPy_lk_cFP19J3DAnmTextureSRTKeyi */
void daPy_lk_c::setTextureScrollResource(J3DAnmTextureSRTKey*, int) {
    /* Nonmatching */
}

/* 80105220-801052BC       .text loadTextureScrollResource__9daPy_lk_cFUli */
void daPy_lk_c::loadTextureScrollResource(unsigned long, int) {
    /* Nonmatching */
}

/* 801052BC-8010552C       .text playTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::playTextureAnime() {
    /* Nonmatching */
}

/* 8010552C-8010558C       .text checkPlayerGuard__9daPy_lk_cCFv */
void daPy_lk_c::checkPlayerGuard() const {
    /* Nonmatching */
}

/* 8010558C-801056E4       .text setOutPower__9daPy_lk_cFfsi */
void daPy_lk_c::setOutPower(float, short, int) {
    /* Nonmatching */
}

/* 801056E4-80105814       .text checkSightLine__9daPy_lk_cFfP4cXyz */
void daPy_lk_c::checkSightLine(float, cXyz*) {
    /* Nonmatching */
}

/* 80105814-80105910       .text setBootsModel__9daPy_lk_cFPP8J3DModel */
void daPy_lk_c::setBootsModel(J3DModel**) {
    /* Nonmatching */
}

/* 80105910-80106660       .text setItemModel__9daPy_lk_cFv */
void daPy_lk_c::setItemModel() {
    /* Nonmatching */
}

/* 80106660-801066DC       .text checkUpperReadyAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkUpperReadyAnime() const {
    /* Nonmatching */
}

/* 801066DC-80106750       .text checkUpperReadyThrowAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkUpperReadyThrowAnime() const {
    /* Nonmatching */
}

/* 80106750-801067D8       .text checkNoCollisionCorret__9daPy_lk_cFv */
void daPy_lk_c::checkNoCollisionCorret() {
    /* Nonmatching */
}

/* 801067D8-80106BD0       .text setDrawHandModel__9daPy_lk_cFv */
void daPy_lk_c::setDrawHandModel() {
    /* Nonmatching */
}

/* 80106BD0-80106C40       .text entryDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::entryDLSetLight(J3DModel*, unsigned long) {
    /* Nonmatching */
}

/* 80106C40-80106CB0       .text updateDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::updateDLSetLight(J3DModel*, unsigned long) {
    /* Nonmatching */
}

/* 80106CB0-80106D8C       .text hideHatAndBackle__9daPy_lk_cFP11J3DMaterial */
void daPy_lk_c::hideHatAndBackle(J3DMaterial*) {
    /* Nonmatching */
}

/* 80106D8C-80106E50       .text drawMirrorLightModel__9daPy_lk_cFv */
void daPy_lk_c::drawMirrorLightModel() {
    /* Nonmatching */
}

/* 80106E50-80107210       .text drawShadow__9daPy_lk_cFv */
void daPy_lk_c::drawShadow() {
    /* Nonmatching */
}

/* 80107210-8010728C       .text offBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::offBodyEffect() {
    /* Nonmatching */
}

/* 8010728C-80107308       .text onBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::onBodyEffect() {
    /* Nonmatching */
}

/* 80107308-80108204       .text draw__9daPy_lk_cFv */
void daPy_lk_c::draw() {
    /* Nonmatching */
}

/* 80108204-80108224       .text daPy_Draw__FP9daPy_lk_c */
void daPy_Draw(daPy_lk_c*) {
    /* Nonmatching */
}

/* 80108224-8010841C       .text setAtnList__9daPy_lk_cFv */
void daPy_lk_c::setAtnList() {
    /* Nonmatching */
}

/* 8010841C-8010848C       .text setActor__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::setActor() {
    /* Nonmatching */
}

/* 8010848C-801084AC       .text setData__16daPy_actorKeep_cFP10fopAc_ac_c */
void daPy_actorKeep_c::setData(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 801084AC-801084C0       .text clearData__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::clearData() {
    /* Nonmatching */
}

/* 801084C0-80108564       .text setActorPointer__9daPy_lk_cFv */
void daPy_lk_c::setActorPointer() {
    /* Nonmatching */
}

/* 80108564-80108634       .text setTalkStatus__9daPy_lk_cFv */
void daPy_lk_c::setTalkStatus() {
    /* Nonmatching */
}

/* 80108634-801086C8       .text setHintActor__9daPy_lk_cFv */
void daPy_lk_c::setHintActor() {
    /* Nonmatching */
}

/* 801086C8-801088E8       .text setDoStatusBasic__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusBasic() {
    /* Nonmatching */
}

/* 801088E8-80108A9C       .text setDoStatus__9daPy_lk_cFv */
void daPy_lk_c::setDoStatus() {
    /* Nonmatching */
}

/* 80108A9C-80108B08       .text getDirectionFromAngle__9daPy_lk_cFs */
void daPy_lk_c::getDirectionFromAngle(short) {
    /* Nonmatching */
}

/* 80108B08-80108B38       .text getDirectionFromShapeAngle__9daPy_lk_cFv */
void daPy_lk_c::getDirectionFromShapeAngle() {
    /* Nonmatching */
}

/* 80108B38-80108B68       .text getDirectionFromCurrentAngle__9daPy_lk_cFv */
void daPy_lk_c::getDirectionFromCurrentAngle() {
    /* Nonmatching */
}

/* 80108B68-80108D80       .text setNormalSpeedF__9daPy_lk_cFffff */
void daPy_lk_c::setNormalSpeedF(float, float, float, float) {
    /* Nonmatching */
}

/* 80108D80-8010959C       .text posMoveFromFootPos__9daPy_lk_cFv */
void daPy_lk_c::posMoveFromFootPos() {
    /* Nonmatching */
}

/* 8010959C-80109E80       .text posMove__9daPy_lk_cFv */
void daPy_lk_c::posMove() {
    /* Nonmatching */
}

/* 80109E80-80109ED8       .text setShapeAngleToAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleToAtnActor() {
    /* Nonmatching */
}

/* 80109ED8-80109F4C       .text cancelItemUpperReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::cancelItemUpperReadyAnime() {
    /* Nonmatching */
}

/* 80109F4C-8010A204       .text checkBodyAngleX__9daPy_lk_cFs */
void daPy_lk_c::checkBodyAngleX(short) {
    /* Nonmatching */
}

/* 8010A204-8010A2F4       .text setBodyAngleToCamera__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleToCamera() {
    /* Nonmatching */
}

/* 8010A2F4-8010A4D4       .text setBodyAngleXReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleXReadyAnime() {
    /* Nonmatching */
}

/* 8010A4D4-8010A96C       .text setSpeedAndAngleNormal__9daPy_lk_cFs */
void daPy_lk_c::setSpeedAndAngleNormal(short) {
    /* Nonmatching */
}

/* 8010A96C-8010AA90       .text setSpeedAndAngleAtn__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtn() {
    /* Nonmatching */
}

/* 8010AA90-8010AB84       .text setSpeedAndAngleAtnBack__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnBack() {
    /* Nonmatching */
}

/* 8010AB84-8010AC8C       .text setSpeedAndAngleAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnActor() {
    /* Nonmatching */
}

/* 8010AC8C-8010ACEC       .text setFrameCtrl__9daPy_lk_cFP12J3DFrameCtrlUcssff */
void daPy_lk_c::setFrameCtrl(J3DFrameCtrl*, unsigned char, short, short, float, float) {
    /* Nonmatching */
}

/* 8010ACEC-8010AD2C       .text checkAtnWaitAnime__9daPy_lk_cFv */
void daPy_lk_c::checkAtnWaitAnime() {
    /* Nonmatching */
}

/* 8010AD2C-8010B798       .text setBlendMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendMoveAnime(float) {
    /* Nonmatching */
}

/* 8010B798-8010BB08       .text setBlendAtnBackMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnBackMoveAnime(float) {
    /* Nonmatching */
}

/* 8010BB08-8010C010       .text setBlendAtnMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnMoveAnime(float) {
    /* Nonmatching */
}

/* 8010C010-8010C100       .text setAnimeEquipSword__9daPy_lk_cFi */
void daPy_lk_c::setAnimeEquipSword(int) {
    /* Nonmatching */
}

/* 8010C100-8010C158       .text setAnimeEquipSingleItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeEquipSingleItem(unsigned short) {
    /* Nonmatching */
}

/* 8010C158-8010C1D4       .text setAnimeEquipItem__9daPy_lk_cFv */
void daPy_lk_c::setAnimeEquipItem() {
    /* Nonmatching */
}

/* 8010C1D4-8010C284       .text setAnimeUnequipSword__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequipSword() {
    /* Nonmatching */
}

/* 8010C284-8010C3C0       .text setAnimeUnequipItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeUnequipItem(unsigned short) {
    /* Nonmatching */
}

/* 8010C3C0-8010C430       .text setAnimeUnequip__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequip() {
    /* Nonmatching */
}

/* 8010C430-8010C4A4       .text checkBossGomaStage__9daPy_lk_cFv */
void daPy_lk_c::checkBossGomaStage() {
    /* Nonmatching */
}

/* 8010C4A4-8010C4C8       .text checkSingleItemEquipAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkSingleItemEquipAnime() const {
    /* Nonmatching */
}

/* 8010C4C8-8010C528       .text checkItemEquipAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkItemEquipAnime() const {
    /* Nonmatching */
}

/* 8010C528-8010C570       .text checkEquipAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkEquipAnime() const {
    /* Nonmatching */
}

/* 8010C570-8010C71C       .text deleteEquipItem__9daPy_lk_cFi */
void daPy_lk_c::deleteEquipItem(int) {
    /* Nonmatching */
}

/* 8010C71C-8010C7F4       .text setFallVoice__9daPy_lk_cFv */
void daPy_lk_c::setFallVoice() {
    /* Nonmatching */
}

/* 8010C7F4-8010C854       .text keepItemData__9daPy_lk_cFv */
void daPy_lk_c::keepItemData() {
    /* Nonmatching */
}

/* 8010C854-8010C8D4       .text returnKeepItemData__9daPy_lk_cFv */
void daPy_lk_c::returnKeepItemData() {
    /* Nonmatching */
}

/* 8010C8D4-8010CB70       .text makeItemType__9daPy_lk_cFv */
void daPy_lk_c::makeItemType() {
    /* Nonmatching */
}

/* 8010CB70-8010CBC8       .text setScopeModel__9daPy_lk_cFv */
void daPy_lk_c::setScopeModel() {
    /* Nonmatching */
}

/* 8010CBC8-8010CC78       .text setPhotoBoxModel__9daPy_lk_cFv */
void daPy_lk_c::setPhotoBoxModel() {
    /* Nonmatching */
}

/* 8010CC78-8010CD34       .text changeDragonShield__9daPy_lk_cFi */
void daPy_lk_c::changeDragonShield(int) {
    /* Nonmatching */
}

/* 8010CD34-8010CFB4       .text checkNewItemChange__9daPy_lk_cFUc */
void daPy_lk_c::checkNewItemChange(unsigned char) {
    /* Nonmatching */
}

/* 8010CFB4-8010D26C       .text checkItemChangeFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkItemChangeFromButton() {
    /* Nonmatching */
}

/* 8010D26C-8010D754       .text checkItemAction__9daPy_lk_cFv */
void daPy_lk_c::checkItemAction() {
    /* Nonmatching */
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
void daPy_lk_c::getSlidePolygon() {
    /* Nonmatching */
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkJumpCutFromButton() {
    /* Nonmatching */
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
void daPy_lk_c::orderTalk() {
    /* Nonmatching */
}

/* 8010DB58-8010E448       .text checkNextActionFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionFromButton() {
    /* Nonmatching */
}

/* 8010E448-8010E75C       .text setShieldGuard__9daPy_lk_cFv */
void daPy_lk_c::setShieldGuard() {
    /* Nonmatching */
}

/* 8010E75C-8010E7C4       .text checkItemModeActorPointer__9daPy_lk_cFv */
void daPy_lk_c::checkItemModeActorPointer() {
    /* Nonmatching */
}

/* 8010E7C4-8010E828       .text checkNextActionItemFly__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionItemFly() {
    /* Nonmatching */
}

/* 8010E828-8010EC78       .text checkNextMode__9daPy_lk_cFi */
void daPy_lk_c::checkNextMode(int) {
    /* Nonmatching */
}

/* 8010EC78-8010ED68       .text checkIceSlipFall__9daPy_lk_cFv */
void daPy_lk_c::checkIceSlipFall() {
    /* Nonmatching */
}

/* 8010ED68-8010F9AC       .text setFrontWallType__9daPy_lk_cFv */
void daPy_lk_c::setFrontWallType() {
    /* Nonmatching */
}

/* 8010F9AC-8010FEC4       .text changeFrontWallTypeProc__9daPy_lk_cFv */
void daPy_lk_c::changeFrontWallTypeProc() {
    /* Nonmatching */
}

/* 8010FEC4-8010FFB0       .text changeSlideProc__9daPy_lk_cFv */
void daPy_lk_c::changeSlideProc() {
    /* Nonmatching */
}

/* 8010FFB0-80110028       .text changeWaitProc__9daPy_lk_cFv */
void daPy_lk_c::changeWaitProc() {
    /* Nonmatching */
}

/* 80110028-8011029C       .text changeLandProc__9daPy_lk_cFf */
void daPy_lk_c::changeLandProc(float) {
    /* Nonmatching */
}

/* 8011029C-80110338       .text setDamagePoint__9daPy_lk_cFf */
void daPy_lk_c::setDamagePoint(float) {
    /* Nonmatching */
}

/* 80110338-80110448       .text checkNormalDamage__9daPy_lk_cFi */
void daPy_lk_c::checkNormalDamage(int) {
    /* Nonmatching */
}

/* 80110448-801104E4       .text setDashDamage__9daPy_lk_cFv */
void daPy_lk_c::setDashDamage() {
    /* Nonmatching */
}

/* 801104E4-8011054C       .text checkAtHitEnemy__9daPy_lk_cFP12dCcD_GObjInf */
void daPy_lk_c::checkAtHitEnemy(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 8011054C-801105D8       .text checkElecReturnDamage__9daPy_lk_cFP12dCcD_GObjInfP4cXyz */
void daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf*, cXyz*) {
    /* Nonmatching */
}

/* 801105D8-80110654       .text checkWallAtributeDamage__9daPy_lk_cFP12dBgS_AcchCir */
void daPy_lk_c::checkWallAtributeDamage(dBgS_AcchCir*) {
    /* Nonmatching */
}

/* 80110654-80110F3C       .text changeDamageProc__9daPy_lk_cFv */
void daPy_lk_c::changeDamageProc() {
    /* Nonmatching */
}

/* 80110F3C-80111424       .text changeAutoJumpProc__9daPy_lk_cFv */
void daPy_lk_c::changeAutoJumpProc() {
    /* Nonmatching */
}

/* 80111424-80111A80       .text changeDemoProc__9daPy_lk_cFv */
void daPy_lk_c::changeDemoProc() {
    /* Nonmatching */
}

/* 80111A80-80111B80       .text changeDeadProc__9daPy_lk_cFv */
void daPy_lk_c::changeDeadProc() {
    /* Nonmatching */
}

/* 80111B80-80111D64       .text getDamageVec__9daPy_lk_cFP12dCcD_GObjInf */
void daPy_lk_c::getDamageVec(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 80111D64-80111E54       .text setOldRootQuaternion__9daPy_lk_cFsss */
void daPy_lk_c::setOldRootQuaternion(short, short, short) {
    /* Nonmatching */
}

/* 80111E54-80111EFC       .text checkRestHPAnime__9daPy_lk_cFv */
void daPy_lk_c::checkRestHPAnime() {
    /* Nonmatching */
}

/* 80111EFC-80111F5C       .text checkHeavyStateOn__9daPy_lk_cFv */
void daPy_lk_c::checkHeavyStateOn() {
    /* Nonmatching */
}

/* 80111F5C-80111F7C       .text checkBottleItem__9daPy_lk_cCFi */
void daPy_lk_c::checkBottleItem(int) const {
    /* Nonmatching */
}

/* 80111F7C-80111FEC       .text checkDrinkBottleItem__9daPy_lk_cCFi */
void daPy_lk_c::checkDrinkBottleItem(int) const {
    /* Nonmatching */
}

/* 80111FEC-8011201C       .text checkOpenBottleItem__9daPy_lk_cCFi */
void daPy_lk_c::checkOpenBottleItem(int) const {
    /* Nonmatching */
}

/* 8011201C-80112044       .text checkBowItem__9daPy_lk_cCFi */
void daPy_lk_c::checkBowItem(int) const {
    /* Nonmatching */
}

/* 80112044-80112064       .text checkPhotoBoxItem__9daPy_lk_cCFi */
void daPy_lk_c::checkPhotoBoxItem(int) const {
    /* Nonmatching */
}

/* 80112064-80112100       .text checkScopeEnd__9daPy_lk_cFv */
void daPy_lk_c::checkScopeEnd() {
    /* Nonmatching */
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    /* Nonmatching */
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
void daPy_lk_c::checkMaskDraw() {
    /* Nonmatching */
}

/* 801121C8-80112280       .text checkSubjectEnd__9daPy_lk_cFi */
void daPy_lk_c::checkSubjectEnd(int) {
    /* Nonmatching */
}

/* 80112280-80112330       .text checkGuardAccept__9daPy_lk_cFv */
void daPy_lk_c::checkGuardAccept() {
    /* Nonmatching */
}

/* 80112330-80112348       .text cancelNoDamageMode__9daPy_lk_cFv */
void daPy_lk_c::cancelNoDamageMode() {
    /* Nonmatching */
}

/* 80112348-80112954       .text commonProcInit__9daPy_lk_cFQ29daPy_lk_c9daPy_PROC */
void daPy_lk_c::commonProcInit(daPy_lk_c::daPy_PROC procID) {
    /* Nonmatching */
}

/* 80112954-80112A24       .text procScope_init__9daPy_lk_cFi */
void daPy_lk_c::procScope_init(int) {
    /* Nonmatching */
}

/* 80112A24-80112AA8       .text procScope__9daPy_lk_cFv */
void daPy_lk_c::procScope() {
    /* Nonmatching */
}

/* 80112AA8-80112B18       .text procSubjectivity_init__9daPy_lk_cFi */
void daPy_lk_c::procSubjectivity_init(int) {
    /* Nonmatching */
}

/* 80112B18-80112BEC       .text procSubjectivity__9daPy_lk_cFv */
void daPy_lk_c::procSubjectivity() {
    /* Nonmatching */
}

/* 80112BEC-80112C90       .text procCall_init__9daPy_lk_cFv */
void daPy_lk_c::procCall_init() {
    /* Nonmatching */
}

/* 80112C90-80112D38       .text procCall__9daPy_lk_cFv */
void daPy_lk_c::procCall() {
    /* Nonmatching */
}

/* 80112D38-80112DF4       .text procControllWait_init__9daPy_lk_cFv */
void daPy_lk_c::procControllWait_init() {
    /* Nonmatching */
}

/* 80112DF4-80112E60       .text procControllWait__9daPy_lk_cFv */
void daPy_lk_c::procControllWait() {
    /* Nonmatching */
}

/* 80112E60-80113044       .text procWait_init__9daPy_lk_cFv */
void daPy_lk_c::procWait_init() {
    /* Nonmatching */
}

/* 80113044-801133FC       .text procWait__9daPy_lk_cFv */
void daPy_lk_c::procWait() {
    /* Nonmatching */
}

/* 801133FC-801134A0       .text procFreeWait_init__9daPy_lk_cFv */
void daPy_lk_c::procFreeWait_init() {
    /* Nonmatching */
}

/* 801134A0-801135C4       .text procFreeWait__9daPy_lk_cFv */
void daPy_lk_c::procFreeWait() {
    /* Nonmatching */
}

/* 801135C4-80113628       .text procMove_init__9daPy_lk_cFv */
void daPy_lk_c::procMove_init() {
    /* Nonmatching */
}

/* 80113628-801136D4       .text procMove__9daPy_lk_cFv */
void daPy_lk_c::procMove() {
    /* Nonmatching */
}

/* 801136D4-80113738       .text procAtnMove_init__9daPy_lk_cFv */
void daPy_lk_c::procAtnMove_init() {
    /* Nonmatching */
}

/* 80113738-801137B4       .text procAtnMove__9daPy_lk_cFv */
void daPy_lk_c::procAtnMove() {
    /* Nonmatching */
}

/* 801137B4-8011388C       .text procAtnActorWait_init__9daPy_lk_cFv */
void daPy_lk_c::procAtnActorWait_init() {
    /* Nonmatching */
}

/* 8011388C-801138FC       .text procAtnActorWait__9daPy_lk_cFv */
void daPy_lk_c::procAtnActorWait() {
    /* Nonmatching */
}

/* 801138FC-80113960       .text procAtnActorMove_init__9daPy_lk_cFv */
void daPy_lk_c::procAtnActorMove_init() {
    /* Nonmatching */
}

/* 80113960-801139C0       .text procAtnActorMove__9daPy_lk_cFv */
void daPy_lk_c::procAtnActorMove() {
    /* Nonmatching */
}

/* 801139C0-80113AC4       .text procSideStep_init__9daPy_lk_cFi */
void daPy_lk_c::procSideStep_init(int) {
    /* Nonmatching */
}

/* 80113AC4-80113BDC       .text procSideStep__9daPy_lk_cFv */
void daPy_lk_c::procSideStep() {
    /* Nonmatching */
}

/* 80113BDC-80113CBC       .text procSideStepLand_init__9daPy_lk_cFv */
void daPy_lk_c::procSideStepLand_init() {
    /* Nonmatching */
}

/* 80113CBC-80113D30       .text procSideStepLand__9daPy_lk_cFv */
void daPy_lk_c::procSideStepLand() {
    /* Nonmatching */
}

/* 80113D30-80113DBC       .text procCrouchDefense_init__9daPy_lk_cFv */
void daPy_lk_c::procCrouchDefense_init() {
    /* Nonmatching */
}

/* 80113DBC-80114014       .text procCrouchDefense__9daPy_lk_cFv */
void daPy_lk_c::procCrouchDefense() {
    /* Nonmatching */
}

/* 80114014-801142F4       .text procCrouchDefenseSlip_init__9daPy_lk_cFv */
void daPy_lk_c::procCrouchDefenseSlip_init() {
    /* Nonmatching */
}

/* 801142F4-801143D4       .text procCrouchDefenseSlip__9daPy_lk_cFv */
void daPy_lk_c::procCrouchDefenseSlip() {
    /* Nonmatching */
}

/* 801143D4-80114440       .text procCrouch_init__9daPy_lk_cFv */
void daPy_lk_c::procCrouch_init() {
    /* Nonmatching */
}

/* 80114440-8011476C       .text procCrouch__9daPy_lk_cFv */
void daPy_lk_c::procCrouch() {
    /* Nonmatching */
}

/* 8011476C-80114804       .text procWaitTurn_init__9daPy_lk_cFv */
void daPy_lk_c::procWaitTurn_init() {
    /* Nonmatching */
}

/* 80114804-80114908       .text procWaitTurn__9daPy_lk_cFv */
void daPy_lk_c::procWaitTurn() {
    /* Nonmatching */
}

/* 80114908-801149EC       .text procMoveTurn_init__9daPy_lk_cFi */
void daPy_lk_c::procMoveTurn_init(int) {
    /* Nonmatching */
}

/* 801149EC-80114A60       .text procMoveTurn__9daPy_lk_cFv */
void daPy_lk_c::procMoveTurn() {
    /* Nonmatching */
}

/* 80114A60-80114B28       .text procSlip_init__9daPy_lk_cFv */
void daPy_lk_c::procSlip_init() {
    /* Nonmatching */
}

/* 80114B28-80114D2C       .text procSlip__9daPy_lk_cFv */
void daPy_lk_c::procSlip() {
    /* Nonmatching */
}

/* 80114D2C-80114DE4       .text procSlideFront_init__9daPy_lk_cFs */
void daPy_lk_c::procSlideFront_init(short) {
    /* Nonmatching */
}

/* 80114DE4-80114EE8       .text procSlideFront__9daPy_lk_cFv */
void daPy_lk_c::procSlideFront() {
    /* Nonmatching */
}

/* 80114EE8-80114FA0       .text procSlideBack_init__9daPy_lk_cFs */
void daPy_lk_c::procSlideBack_init(short) {
    /* Nonmatching */
}

/* 80114FA0-801150B0       .text procSlideBack__9daPy_lk_cFv */
void daPy_lk_c::procSlideBack() {
    /* Nonmatching */
}

/* 801150B0-80115118       .text procSlideFrontLand_init__9daPy_lk_cFv */
void daPy_lk_c::procSlideFrontLand_init() {
    /* Nonmatching */
}

/* 80115118-801151C8       .text procSlideFrontLand__9daPy_lk_cFv */
void daPy_lk_c::procSlideFrontLand() {
    /* Nonmatching */
}

/* 801151C8-80115220       .text procSlideBackLand_init__9daPy_lk_cFv */
void daPy_lk_c::procSlideBackLand_init() {
    /* Nonmatching */
}

/* 80115220-801152D0       .text procSlideBackLand__9daPy_lk_cFv */
void daPy_lk_c::procSlideBackLand() {
    /* Nonmatching */
}

/* 801152D0-80115478       .text procFrontRoll_init__9daPy_lk_cFf */
void daPy_lk_c::procFrontRoll_init(float) {
    /* Nonmatching */
}

/* 80115478-80115628       .text procFrontRoll__9daPy_lk_cFv */
void daPy_lk_c::procFrontRoll() {
    /* Nonmatching */
}

/* 80115628-801157D8       .text procFrontRollCrash_init__9daPy_lk_cFv */
void daPy_lk_c::procFrontRollCrash_init() {
    /* Nonmatching */
}

/* 801157D8-801158AC       .text procFrontRollCrash__9daPy_lk_cFv */
void daPy_lk_c::procFrontRollCrash() {
    /* Nonmatching */
}

/* 801158AC-8011590C       .text procNockBackEnd_init__9daPy_lk_cFv */
void daPy_lk_c::procNockBackEnd_init() {
    /* Nonmatching */
}

/* 8011590C-80115968       .text procNockBackEnd__9daPy_lk_cFv */
void daPy_lk_c::procNockBackEnd() {
    /* Nonmatching */
}

/* 80115968-80115A18       .text procSideRoll_init__9daPy_lk_cFv */
void daPy_lk_c::procSideRoll_init() {
    /* Nonmatching */
}

/* 80115A18-80115B08       .text procSideRoll__9daPy_lk_cFv */
void daPy_lk_c::procSideRoll() {
    /* Nonmatching */
}

/* 80115B08-80115BFC       .text procBackJump_init__9daPy_lk_cFv */
void daPy_lk_c::procBackJump_init() {
    /* Nonmatching */
}

/* 80115BFC-80115CA0       .text procBackJump__9daPy_lk_cFv */
void daPy_lk_c::procBackJump() {
    /* Nonmatching */
}

/* 80115CA0-80115DA8       .text procBackJumpLand_init__9daPy_lk_cFv */
void daPy_lk_c::procBackJumpLand_init() {
    /* Nonmatching */
}

/* 80115DA8-80115E88       .text procBackJumpLand__9daPy_lk_cFv */
void daPy_lk_c::procBackJumpLand() {
    /* Nonmatching */
}

/* 80115E88-80115EA4       .text checkAutoJumpFlying__9daPy_lk_cCFv */
void daPy_lk_c::checkAutoJumpFlying() const {
    /* Nonmatching */
}

/* 80115EA4-8011602C       .text procAutoJump_init__9daPy_lk_cFv */
void daPy_lk_c::procAutoJump_init() {
    /* Nonmatching */
}

/* 8011602C-801163D4       .text procAutoJump__9daPy_lk_cFv */
void daPy_lk_c::procAutoJump() {
    /* Nonmatching */
}

/* 801163D4-8011651C       .text procLand_init__9daPy_lk_cFfi */
void daPy_lk_c::procLand_init(float, int) {
    /* Nonmatching */
}

/* 8011651C-801165B4       .text procLand__9daPy_lk_cFv */
void daPy_lk_c::procLand() {
    /* Nonmatching */
}

/* 801165B4-80116768       .text procLandDamage_init__9daPy_lk_cFi */
void daPy_lk_c::procLandDamage_init(int) {
    /* Nonmatching */
}

/* 80116768-80116864       .text procLandDamage__9daPy_lk_cFv */
void daPy_lk_c::procLandDamage() {
    /* Nonmatching */
}

/* 80116864-80116A38       .text procFall_init__9daPy_lk_cFif */
void daPy_lk_c::procFall_init(int, float) {
    /* Nonmatching */
}

/* 80116A38-80116C14       .text procFall__9daPy_lk_cFv */
void daPy_lk_c::procFall() {
    /* Nonmatching */
}

/* 80116C14-80116CC4       .text procSlowFall_init__9daPy_lk_cFv */
void daPy_lk_c::procSlowFall_init() {
    /* Nonmatching */
}

/* 80116CC4-80116D3C       .text procSlowFall__9daPy_lk_cFv */
void daPy_lk_c::procSlowFall() {
    /* Nonmatching */
}

/* 80116D3C-80116EB4       .text procSmallJump_init__9daPy_lk_cFi */
void daPy_lk_c::procSmallJump_init(int) {
    /* Nonmatching */
}

/* 80116EB4-80116F54       .text procSmallJump__9daPy_lk_cFv */
void daPy_lk_c::procSmallJump() {
    /* Nonmatching */
}

/* 80116F54-80116FEC       .text procVerticalJump_init__9daPy_lk_cFv */
void daPy_lk_c::procVerticalJump_init() {
    /* Nonmatching */
}

/* 80116FEC-80117088       .text procVerticalJump__9daPy_lk_cFv */
void daPy_lk_c::procVerticalJump() {
    /* Nonmatching */
}

/* 80117088-801170F0       .text procGuardCrash__9daPy_lk_cFv */
void daPy_lk_c::procGuardCrash() {
    /* Nonmatching */
}

/* 801170F0-80117448       .text procDamage_init__9daPy_lk_cFv */
void daPy_lk_c::procDamage_init() {
    /* Nonmatching */
}

/* 80117448-801176FC       .text procDamage__9daPy_lk_cFv */
void daPy_lk_c::procDamage() {
    /* Nonmatching */
}

/* 801176FC-80117794       .text procPolyDamage_init__9daPy_lk_cFv */
void daPy_lk_c::procPolyDamage_init() {
    /* Nonmatching */
}

/* 80117794-801177CC       .text procPolyDamage__9daPy_lk_cFv */
void daPy_lk_c::procPolyDamage() {
    /* Nonmatching */
}

/* 801177CC-80117EAC       .text procLargeDamage_init__9daPy_lk_cFiiss */
void daPy_lk_c::procLargeDamage_init(int, int, short, short) {
    /* Nonmatching */
}

/* 80117EAC-8011810C       .text procLargeDamage__9daPy_lk_cFv */
void daPy_lk_c::procLargeDamage() {
    /* Nonmatching */
}

/* 8011810C-80118504       .text procLargeDamageUp_init__9daPy_lk_cFiiss */
void daPy_lk_c::procLargeDamageUp_init(int, int, short, short) {
    /* Nonmatching */
}

/* 80118504-80118640       .text procLargeDamageUp__9daPy_lk_cFv */
void daPy_lk_c::procLargeDamageUp() {
    /* Nonmatching */
}

/* 80118640-801189AC       .text procLargeDamageWall_init__9daPy_lk_cFiiss */
void daPy_lk_c::procLargeDamageWall_init(int, int, short, short) {
    /* Nonmatching */
}

/* 801189AC-801189F0       .text procLargeDamageWall__9daPy_lk_cFv */
void daPy_lk_c::procLargeDamageWall() {
    /* Nonmatching */
}

/* 801189F0-80118BC4       .text procLavaDamage_init__9daPy_lk_cFv */
void daPy_lk_c::procLavaDamage_init() {
    /* Nonmatching */
}

/* 80118BC4-80118C58       .text procLavaDamage__9daPy_lk_cFv */
void daPy_lk_c::procLavaDamage() {
    /* Nonmatching */
}

/* 80118C58-80118E6C       .text procElecDamage_init__9daPy_lk_cFPC4cXyz */
void daPy_lk_c::procElecDamage_init(const cXyz*) {
    /* Nonmatching */
}

/* 80118E6C-80118F40       .text procElecDamage__9daPy_lk_cFv */
void daPy_lk_c::procElecDamage() {
    /* Nonmatching */
}

/* 80118F40-80119248       .text procGuardSlip_init__9daPy_lk_cFv */
void daPy_lk_c::procGuardSlip_init() {
    /* Nonmatching */
}

/* 80119248-80119334       .text procGuardSlip__9daPy_lk_cFv */
void daPy_lk_c::procGuardSlip() {
    /* Nonmatching */
}

/* 80119334-80119478       .text procIceSlipFall_init__9daPy_lk_cFv */
void daPy_lk_c::procIceSlipFall_init() {
    /* Nonmatching */
}

/* 80119478-80119500       .text procIceSlipFall__9daPy_lk_cFv */
void daPy_lk_c::procIceSlipFall() {
    /* Nonmatching */
}

/* 80119500-80119688       .text procIceSlipFallUp_init__9daPy_lk_cFiss */
void daPy_lk_c::procIceSlipFallUp_init(int, short, short) {
    /* Nonmatching */
}

/* 80119688-8011970C       .text procIceSlipFallUp__9daPy_lk_cFv */
void daPy_lk_c::procIceSlipFallUp() {
    /* Nonmatching */
}

/* 8011970C-801197D4       .text procIceSlipAlmostFall_init__9daPy_lk_cFv */
void daPy_lk_c::procIceSlipAlmostFall_init() {
    /* Nonmatching */
}

/* 801197D4-80119864       .text procIceSlipAlmostFall__9daPy_lk_cFv */
void daPy_lk_c::procIceSlipAlmostFall() {
    /* Nonmatching */
}

/* 80119864-801198E0       .text procBootsEquip_init__9daPy_lk_cFUs */
void daPy_lk_c::procBootsEquip_init(unsigned short) {
    /* Nonmatching */
}

/* 801198E0-80119A5C       .text procBootsEquip__9daPy_lk_cFv */
void daPy_lk_c::procBootsEquip() {
    /* Nonmatching */
}

/* 80119A5C-80119BA0       .text procNotUse_init__9daPy_lk_cFi */
void daPy_lk_c::procNotUse_init(int) {
    /* Nonmatching */
}

/* 80119BA0-80119DA0       .text procNotUse__9daPy_lk_cFv */
void daPy_lk_c::procNotUse() {
    /* Nonmatching */
}

/* 80119DA0-80119EBC       .text getGroundAngle__9daPy_lk_cFP13cBgS_PolyInfos */
void daPy_lk_c::getGroundAngle(cBgS_PolyInfo*, short) {
    /* Nonmatching */
}

/* 80119EBC-8011A508       .text setLegAngle__9daPy_lk_cFfiPsPs */
void daPy_lk_c::setLegAngle(float, int, short*, short*) {
    /* Nonmatching */
}

/* 8011A508-8011ABB0       .text footBgCheck__9daPy_lk_cFv */
void daPy_lk_c::footBgCheck() {
    /* Nonmatching */
}

/* 8011ABB0-8011AC78       .text setWaterY__9daPy_lk_cFv */
void daPy_lk_c::setWaterY() {
    /* Nonmatching */
}

/* 8011AC78-8011AD9C       .text autoGroundHit__9daPy_lk_cFv */
void daPy_lk_c::autoGroundHit() {
    /* Nonmatching */
}

/* 8011AD9C-8011AE20       .text checkAttentionPosAngle__9daPy_lk_cFP10fopAc_ac_cPP4cXyz */
void daPy_lk_c::checkAttentionPosAngle(fopAc_ac_c*, cXyz**) {
    /* Nonmatching */
}

/* 8011AE20-8011BE08       .text setNeckAngle__9daPy_lk_cFv */
void daPy_lk_c::setNeckAngle() {
    /* Nonmatching */
}

/* 8011BE08-8011BEA4       .text checkOriginalHatAnimation__9daPy_lk_cFv */
void daPy_lk_c::checkOriginalHatAnimation() {
    /* Nonmatching */
}

/* 8011BEA4-8011CBA4       .text setHatAngle__9daPy_lk_cFv */
void daPy_lk_c::setHatAngle() {
    /* Nonmatching */
}

/* 8011CBA4-8011CCF4       .text setMoveSlantAngle__9daPy_lk_cFv */
void daPy_lk_c::setMoveSlantAngle() {
    /* Nonmatching */
}

/* 8011CCF4-8011CDB4       .text setWaistAngle__9daPy_lk_cFv */
void daPy_lk_c::setWaistAngle() {
    /* Nonmatching */
}

/* 8011CDB4-8011D070       .text setWorldMatrix__9daPy_lk_cFv */
void daPy_lk_c::setWorldMatrix() {
    /* Nonmatching */
}

/* 8011D070-8011D0E4       .text setAtParam__9daPy_lk_cFUli11dCcG_At_SplUcUcUcf */
void daPy_lk_c::setAtParam(unsigned long, int, dCcG_At_Spl, unsigned char, unsigned char, unsigned char, float) {
    /* Nonmatching */
}

/* 8011D0E4-8011D110       .text resetCurse__9daPy_lk_cFv */
void daPy_lk_c::resetCurse() {
    /* Nonmatching */
}

/* 8011D110-8011D4D0       .text checkLightHit__9daPy_lk_cFv */
void daPy_lk_c::checkLightHit() {
    /* Nonmatching */
}

/* 8011D4D0-8011D6C4       .text setSwordAtCollision__9daPy_lk_cFv */
void daPy_lk_c::setSwordAtCollision() {
    /* Nonmatching */
}

/* 8011D6C4-8011D788       .text getBlurTopRate__9daPy_lk_cFv */
void daPy_lk_c::getBlurTopRate() {
    /* Nonmatching */
}

/* 8011D788-8011EC0C       .text setCollision__9daPy_lk_cFv */
void daPy_lk_c::setCollision() {
    /* Nonmatching */
}

/* 8011EC0C-8011EEBC       .text setAttentionPos__9daPy_lk_cFv */
void daPy_lk_c::setAttentionPos() {
    /* Nonmatching */
}

/* 8011EEBC-8011EF94       .text setRoomInfo__9daPy_lk_cFv */
void daPy_lk_c::setRoomInfo() {
    /* Nonmatching */
}

/* 8011EF94-8011F9C0       .text setDemoData__9daPy_lk_cFv */
void daPy_lk_c::setDemoData() {
    /* Nonmatching */
}

/* 8011F9C0-8011FF50       .text setStickData__9daPy_lk_cFv */
void daPy_lk_c::setStickData() {
    /* Nonmatching */
}

/* 8011FF50-801200F8       .text setBgCheckParam__9daPy_lk_cFv */
void daPy_lk_c::setBgCheckParam() {
    /* Nonmatching */
}

/* 801200F8-8012010C       .text setParamData__9daPy_lk_cFiiii */
void daPy_lk_c::setParamData(int, int, int, int) {
    /* Nonmatching */
}

/* 8012010C-8012024C       .text checkLavaFace__9daPy_lk_cFP4cXyzi */
void daPy_lk_c::checkLavaFace(cXyz*, int) {
    /* Nonmatching */
}

/* 8012024C-80120724       .text checkFallCode__9daPy_lk_cFv */
void daPy_lk_c::checkFallCode() {
    /* Nonmatching */
}

/* 80120724-80120BBC       .text startRestartRoom__9daPy_lk_cFUlifi */
void daPy_lk_c::startRestartRoom(unsigned long, int, float, int) {
    /* Nonmatching */
}

/* 80120BBC-80120BE0       .text checkSuccessGuard__9daPy_lk_cFi */
void daPy_lk_c::checkSuccessGuard(int) {
    /* Nonmatching */
}

/* 80120BE0-80120F94       .text setShapeAngleOnGround__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleOnGround() {
    /* Nonmatching */
}

/* 80120F94-801211B8       .text setStepsOffset__9daPy_lk_cFv */
void daPy_lk_c::setStepsOffset() {
    /* Nonmatching */
}

/* 801211B8-8012135C       .text setBeltConveyerPower__9daPy_lk_cFv */
void daPy_lk_c::setBeltConveyerPower() {
    /* Nonmatching */
}

/* 8012135C-801216A8       .text setWindAtPower__9daPy_lk_cFv */
void daPy_lk_c::setWindAtPower() {
    /* Nonmatching */
}

/* 801216A8-80121870       .text checkRoofRestart__9daPy_lk_cFv */
void daPy_lk_c::checkRoofRestart() {
    /* Nonmatching */
}

/* 80121870-80122D30       .text execute__9daPy_lk_cFv */
void daPy_lk_c::execute() {
    /* Nonmatching */
}

/* 80122D30-80122D50       .text daPy_Execute__FP9daPy_lk_c */
void daPy_Execute(daPy_lk_c*) {
    /* Nonmatching */
}

/* 80122D50-80122D58       .text daPy_IsDelete__FP9daPy_lk_c */
void daPy_IsDelete(daPy_lk_c*) {
    /* Nonmatching */
}

/* 80122D58-80123058       .text playerDelete__9daPy_lk_cFv */
void daPy_lk_c::playerDelete() {
    /* Nonmatching */
}

/* 80123058-80123078       .text daPy_Delete__FP9daPy_lk_c */
void daPy_Delete(daPy_lk_c*) {
    /* Nonmatching */
}

/* 80123078-80123360       .text initTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::initTextureAnime() {
    /* Nonmatching */
}

/* 80123360-80123830       .text initTextureScroll__9daPy_lk_cFv */
void daPy_lk_c::initTextureScroll() {
    /* Nonmatching */
}

/* 80123834-8012469C       .text createHeap__9daPy_lk_cFv */
void daPy_lk_c::createHeap() {
    /* Nonmatching */
}

/* 8012469C-801249F8       .text createAnimeHeap__9daPy_lk_cFPP12JKRSolidHeapQ29daPy_lk_c14daPy_HEAP_TYPE */
void daPy_lk_c::createAnimeHeap(JKRSolidHeap**, daPy_lk_c::daPy_HEAP_TYPE) {
    /* Nonmatching */
}

/* 80124A40-80124B30       .text initModel__9daPy_lk_cFPP8J3DModeliUl */
void daPy_lk_c::initModel(J3DModel**, int, unsigned long) {
    /* Nonmatching */
}

/* 80124B30-80124BE4       .text entryBtk__9daPy_lk_cFP12J3DModelDatai */
void daPy_lk_c::entryBtk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124BE4-80124C98       .text entryBrk__9daPy_lk_cFP12J3DModelDatai */
void daPy_lk_c::entryBrk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124C98-80125CC8       .text playerInit__9daPy_lk_cFv */
void daPy_lk_c::playerInit() {
    /* Nonmatching */
}

int phase_1(daPy_lk_c* i_this) {
    g_dComIfG_gameInfo.play.mpPlayer[0] = i_this;
    g_dComIfG_gameInfo.play.mpPlayerPtr[0] = i_this;

    fopAcM_setStageLayer(i_this);
    i_this->mAttentionInfo.mFlags = 0xFFFFFFFF;

    i_this->mAttentionInfo.mPosition.x = i_this->current.pos.x;
    i_this->mAttentionInfo.mPosition.y = i_this->current.pos.y + 125.0f;
    i_this->mAttentionInfo.mPosition.z = i_this->current.pos.z;

    return cPhs_NEXT_e;
}

int phase_2(daPy_lk_c* i_this) {
    int result;

    if (g_dComIfG_gameInfo.play.mCameraInfo[g_dComIfG_gameInfo.play.mCurCamera[0]].mpCamera == NULL)  {
        result = cPhs_INIT_e;
    } else {
        fopAcM_SetupActor(i_this, daPy_lk_c);
        i_this->playerInit();

        result = cPhs_NEXT_e;
    }

    return result;
}

/* 80125DB4-80126F00       .text __ct__9daPy_lk_cFv */
daPy_lk_c::daPy_lk_c() {
    /* Nonmatching */
}

/* 80126F00-8012704C       .text __dt__15daPy_footData_cFv */
daPy_footData_c::~daPy_footData_c() {
    /* Nonmatching */
}

/* 8012704C-80127160       .text __ct__15daPy_footData_cFv */
daPy_footData_c::daPy_footData_c() {
    /* Nonmatching */
}

/* 80127160-80127B50       .text makeBgWait__9daPy_lk_cFv */
int daPy_lk_c::makeBgWait() {
    /* Nonmatching */
    return cPhs_NEXT_e;
}

int phase_3(daPy_lk_c* i_this) {
    return i_this->makeBgWait();
}

void daPy_Create(fopAc_ac_c* i_this) {
    static int (*l_method[3])(void*) = {
        (int (*)(void*))phase_1, 
        (int (*)(void*))phase_2,
        (int (*)(void*))phase_3,
    };
    daPy_lk_c* player_link = (daPy_lk_c*)i_this;

    dComLbG_PhaseHandler(&player_link->mPhsLoad, l_method, player_link);
}

/* 80127BA0-80127CC0       .text setSeAnime__9daPy_lk_cFPC14daPy_anmHeap_cP12J3DFrameCtrl */
void daPy_lk_c::setSeAnime(const daPy_anmHeap_c*, J3DFrameCtrl*) {
    /* Nonmatching */
}

/* 80127CC0-80127DEC       .text initSeAnime__9daPy_lk_cFv */
void daPy_lk_c::initSeAnime() {
    /* Nonmatching */
}

/* 80127DEC-80127E08       .text resetSeAnime__9daPy_lk_cFv */
void daPy_lk_c::resetSeAnime() {
    /* Nonmatching */
}

/* 80127E08-8012821C       .text setMoveAnime__9daPy_lk_cFfffQ29daPy_lk_c8daPy_ANMQ29daPy_lk_c8daPy_ANMif */
void daPy_lk_c::setMoveAnime(float, float, float, daPy_lk_c::daPy_ANM, daPy_lk_c::daPy_ANM, int, float) {
    /* Nonmatching */
}

/* 8012821C-80128494       .text setSingleMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANMffsf */
void daPy_lk_c::setSingleMoveAnime(daPy_lk_c::daPy_ANM, float, float, short, float) {
    /* Nonmatching */
}

/* 80128494-801285F8       .text setActAnimeUpper__9daPy_lk_cFUsQ29daPy_lk_c10daPy_UPPERffsf */
void daPy_lk_c::setActAnimeUpper(unsigned short, daPy_lk_c::daPy_UPPER, float, float, short, float) {
    /* Nonmatching */
}

/* 801285F8-801286C0       .text resetActAnimeUpper__9daPy_lk_cFQ29daPy_lk_c10daPy_UPPERf */
void daPy_lk_c::resetActAnimeUpper(daPy_lk_c::daPy_UPPER, float) {
    /* Nonmatching */
}

/* 801286C0-801287E8       .text animeUpdate__9daPy_lk_cFv */
void daPy_lk_c::animeUpdate() {
    /* Nonmatching */
}

/* 801287E8-8012887C       .text simpleAnmPlay__9daPy_lk_cFP10J3DAnmBase */
void daPy_lk_c::simpleAnmPlay(J3DAnmBase*) {
    /* Nonmatching */
}

/* 8012887C-801288A0       .text setHandModel__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setHandModel(daPy_lk_c::daPy_ANM) {
    /* Nonmatching */
}

/* 801288A0-8012894C       .text getAnmData__9daPy_lk_cCFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::getAnmData(daPy_lk_c::daPy_ANM) const {
    /* Nonmatching */
}

/* 8012894C-80128988       .text checkGrabWeapon__9daPy_lk_cFi */
void daPy_lk_c::checkGrabWeapon(int) {
    /* Nonmatching */
}

/* 80128988-801289A8       .text onDekuSpReturnFlg__9daPy_lk_cFUc */
void daPy_lk_c::onDekuSpReturnFlg(unsigned char) {
    /* Nonmatching */
}

/* 801289A8-80128AA4       .text changeTextureAnime__9daPy_lk_cFUsUsi */
void daPy_lk_c::changeTextureAnime(unsigned short, unsigned short, int) {
    /* Nonmatching */
}

/* 80128AA4-80128B50       .text setThrowDamage__9daPy_lk_cFP4cXyzsffi */
void daPy_lk_c::setThrowDamage(cXyz*, short, float, float, int) {
    /* Nonmatching */
}

/* 80128B50-80128C10       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzs */
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, short) {
    /* Nonmatching */
}

/* 80128C10-80128CE4       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzP5csXyz */
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, csXyz*) {
    /* Nonmatching */
}

/* 80128CE4-80128DC0       .text setPlayerPosAndAngle__9daPy_lk_cFPA4_f */
void daPy_lk_c::setPlayerPosAndAngle(float(*)[4]) {
    /* Nonmatching */
}

/* 80128DC0-80128F8C       .text endDemoMode__9daPy_lk_cFv */
void daPy_lk_c::endDemoMode() {
    /* Nonmatching */
}

/* 80128F8C-8012901C       .text getBokoFlamePos__9daPy_lk_cFP4cXyz */
void daPy_lk_c::getBokoFlamePos(cXyz*) {
    /* Nonmatching */
}

#include "src/d/actor/d_a_player_particle.inc"

#include "src/d/actor/d_a_player_dproc.inc"

#include "src/d/actor/d_a_player_ladder.inc"

#include "src/d/actor/d_a_player_hang.inc"

#include "src/d/actor/d_a_player_climb.inc"

#include "src/d/actor/d_a_player_whide.inc"

#include "src/d/actor/d_a_player_crawl.inc"

#include "src/d/actor/d_a_player_grab.inc"

#include "src/d/actor/d_a_player_swim.inc"

#include "src/d/actor/d_a_player_battle.inc"

#include "src/d/actor/d_a_player_ship.inc"

#include "src/d/actor/d_a_player_rope.inc"

#include "src/d/actor/d_a_player_boomerang.inc"

#include "src/d/actor/d_a_player_bow.inc"

#include "src/d/actor/d_a_player_hookshot.inc"

#include "src/d/actor/d_a_player_fan.inc"

#include "src/d/actor/d_a_player_tact.inc"

#include "src/d/actor/d_a_player_vomit.inc"

#include "src/d/actor/d_a_player_hammer.inc"

#include "src/d/actor/d_a_player_pushpull.inc"

#include "src/d/actor/d_a_player_bottle.inc"

#include "src/d/actor/d_a_player_weapon.inc"

#include "src/d/actor/d_a_player_food.inc"

#include "src/d/actor/d_a_player_sword.inc"
