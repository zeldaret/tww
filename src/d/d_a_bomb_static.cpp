/**
 * d_a_bomb_static.cpp
 * Bomb - Static
 */

#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_bomb2.h"
#include "JSystem/JUtility/JUTAssert.h"

#define L_daBomb_Version 1

/* 80067FA0-80067FD0       .text getBombRestTime__8daBomb_cFv */
s16 daBomb_c::getBombRestTime() {
    _prm_chk_version();

    return mRestTime;
}

/* 80067FD0-80068000       .text getBombCheck_Flag__8daBomb_cFv */
s16 daBomb_c::getBombCheck_Flag() {
    _prm_chk_version();

    return field_0x6F1;
}

/* 80068000-80068034       .text setBombCheck_Flag__8daBomb_cFv */
void daBomb_c::setBombCheck_Flag() {
    _prm_chk_version();

    field_0x6F1 = true;
}

/* 80068034-80068068       .text setBombFire_ON__8daBomb_cFv */
void daBomb_c::setBombFire_ON() {
    _prm_chk_version();

    field_0x6F2 = true;
}

/* 80068068-800680CC       .text setBombNoHit__8daBomb_cFv */
void daBomb_c::setBombNoHit() {
    _prm_chk_version();

    mSph.OffTgSPrmBit(TG_SPRM_SET);
    mSph.OffCoSPrmBit(CO_SPRM_SET);
    mSph.OffAtSPrmBit(AT_SPRM_SET);
    mSph.ClrAtSet();

    field_0x6F3 = true;
}

/* 800680CC-80068104       .text setBombOffCoSet__8daBomb_cFv */
void daBomb_c::setBombOffCoSet() {
    _prm_chk_version();

    mSph.OffCoSPrmBit(CO_SPRM_SET);
}

/* 80068104-8006813C       .text setBombOnCoSet__8daBomb_cFv */
void daBomb_c::setBombOnCoSet() {
    _prm_chk_version();

    mSph.OnCoSPrmBit(CO_SPRM_SET);
}

/* 8006813C-800681CC       .text setBombNoEff__8daBomb_cFv */
void daBomb_c::setBombNoEff() {
    _prm_chk_version();

    if(mSmoke.mpEmitter) {
        mSmoke.mpEmitter->mpEmitterCallBack = 0;
        mSmoke.mpEmitter->becomeInvalidEmitter();
    }
    mSmoke.mpEmitter = 0;

    if(mSparks.mpEmitter) {
        mSparks.mpEmitter->mpEmitterCallBack = 0;
        mSparks.mpEmitter->becomeInvalidEmitter();
    }
    mSparks.mpEmitter = 0;
}

/* 800681CC-80068208       .text setBombRestTime__8daBomb_cFs */
void daBomb_c::setBombRestTime(s16 time) {
    _prm_chk_version();

    mRestTime = time;
}

/* 80068208-80068244       .text setNoGravityTime__8daBomb_cFs */
void daBomb_c::setNoGravityTime(s16 time) {
    _prm_chk_version();

    mNoGravityTime = time;
}

/* 80068244-80068274       .text prm_make__8daBomb_cFQ28daBomb_c7State_ebb */
int daBomb_c::prm_make(daBomb_c::State_e state, bool param_1, bool param_2) {
    return (((param_2 ? 1 : 0) << 17) | (state | ((param_1 ? 1 : 0) << 16))) | 0x80000000;
}

/* 80068274-800682C0       .text chk_state__8daBomb_cCFQ28daBomb_c7State_e */
bool daBomb_c::chk_state(daBomb_c::State_e state) const {
    _prm_chk_version();

    return state == prm_get_state();
}

/* 800682C0-800682F0       .text change_state__8daBomb_cFQ28daBomb_c7State_e */
void daBomb_c::change_state(daBomb_c::State_e new_state) {
    mBase.mParameters = (mBase.mParameters & ~(((1 << PRM_STATE_W) - 1) << PRM_STATE_S)) | (new_state << PRM_STATE_S); // & 0xFF000000

    _prm_chk_version();
}

/* 800682F0-8006832C       .text prm_get_state__8daBomb_cCFv */
int daBomb_c::prm_get_state() const {
    _prm_chk_version();

    return daObj::PrmAbstract(this, PRM_STATE_W, PRM_STATE_S);
}

/* 8006832C-80068340       .text get_explode_instant__8daBomb_cCFv */
bool daBomb_c::get_explode_instant() const {
    return field_0x784 == true;
}

/* 80068340-80068388       .text prm_get_cheapEff__8daBomb_cCFv */
bool daBomb_c::prm_get_cheapEff() const {
    _prm_chk_version();

    return daObj::PrmAbstract(this, PRM_CHEAP_EFF_W, PRM_CHEAP_EFF_S);
}

/* 80068388-800683D0       .text prm_get_angXZero__8daBomb_cCFv */
bool daBomb_c::prm_get_angXZero() const {
    _prm_chk_version();

    return daObj::PrmAbstract(this, PRM_ANGXZERO_W, PRM_ANGXZERO_S);
}

/* 800683D0-800683F8       .text prm_get_version__8daBomb_cCFv */
int daBomb_c::prm_get_version() const {
    return daObj::PrmAbstract(this, PRM_VERSION_W, PRM_VERSION_S);
}

/* 800683F8-80068450       .text _prm_chk_version__8daBomb_cCFv */
void daBomb_c::_prm_chk_version() const {
    int ver = prm_get_version();
    JUT_ASSERT(0xCE, ver == L_daBomb_Version);
}

/* 80068450-80068488       .text remove_fuse_effect__Q27daBomb25Act_cFv */
void daBomb2::Act_c::remove_fuse_effect() {
    mSmoke.deleteCallBack();
    mSparks.deleteCallBack();
}

/* 80068488-80068490       .text set_time__Q27daBomb25Act_cFi */
void daBomb2::Act_c::set_time(int time) {
    field_0x738 = time;
}

/* 80068490-80068498       .text get_time__Q27daBomb25Act_cCFv */
int daBomb2::Act_c::get_time() const {
    return field_0x738;
}

/* 80068498-800684A0       .text chk_eat__Q27daBomb25Act_cCFv */
bool daBomb2::Act_c::chk_eat() const {
    return field_0x745;
}

/* 800684A0-800684AC       .text set_eat__Q27daBomb25Act_cFv */
void daBomb2::Act_c::set_eat() {
    field_0x745 = true;
}

/* 800684AC-800684E0       .text set_no_hit__Q27daBomb25Act_cFv */
void daBomb2::Act_c::set_no_hit() {
    mSph.OffTgSPrmBit(TG_SPRM_SET);
    mSph.OffCoSPrmBit(CO_SPRM_SET);
    mSph.OffAtSPrmBit(AT_SPRM_SET);
    mSph.ClrAtSet();
}

/* 800684E0-800684F4       .text chk_explode__Q27daBomb25Act_cFv */
bool daBomb2::Act_c::chk_explode() {
    return mState == 2;
}
