//
// Generated by dtk
// Translation Unit: d_tree.cpp
//

#include "d/d_tree.h"
#include "dolphin/types.h"

/* 800787BC-80078960       .text WorkCo__12dTree_data_cFP10fopAc_ac_cUli */
void dTree_data_c::WorkCo(fopAc_ac_c*, unsigned long, int) {
    /* Nonmatching */
}

/* 80078960-80078CC0       .text
 * WorkAt_NoCutAnim__12dTree_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInfP8cCcD_Obj */
void dTree_data_c::WorkAt_NoCutAnim(fopAc_ac_c*, unsigned long, int, dCcMassS_HitInf*, cCcD_Obj*) {
    /* Nonmatching */
}

/* 80078CC0-80078ED4       .text WorkAt__12dTree_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInf */
void dTree_data_c::WorkAt(fopAc_ac_c*, unsigned long, int, dCcMassS_HitInf*) {
    /* Nonmatching */
}

/* 80078ED4-80078FA8       .text hitCheck__12dTree_data_cFP10fopAc_ac_ci */
void dTree_data_c::hitCheck(fopAc_ac_c*, int) {
    /* Nonmatching */
}

/* 80078FA8-8007945C       .text animation__12dTree_data_cFi */
void dTree_data_c::animation(int) {
    /* Nonmatching */
}

/* 8007945C-8007946C       .text newData__12dTree_room_cFP12dTree_data_c */
void dTree_room_c::newData(dTree_data_c* data) {
    data->mpNext = this->mpHead;
    this->mpHead = data;
    return;
}

/* 8007946C-800794D0       .text deleteData__12dTree_room_cFv */
void dTree_room_c::deleteData() {
    while (this->mpHead != (dTree_data_c*)0x0) {
        this->mpHead->field_0x000 = 0;
        mDoAud_seDeleteObject(&this->mpHead->mPos);
        this->mpHead = this->mpHead->mpNext;
    }
    return;
}

/* 800794D0-800795E8       .text __ct__14dTree_packet_cFv */
dTree_packet_c::dTree_packet_c() {
    dTree_data_c* pdVar1;
    dTree_anm_c* pdVar2;
    short sVar3;
    int iVar4;

    this->field_0x0010 = 0;
    this->field_0x6734 = 0;
    this->field_0x6736 = 0;
    pdVar1 = this->mData;
    iVar4 = 0x40;
    return;
}

/* 800795E8-800795F4       .text __ct__12dTree_room_cFv */
dTree_room_c::dTree_room_c() {
    this->mpHead = (dTree_data_c*)0x0;
    return;
}

/* 800795F4-80079600       .text __ct__11dTree_anm_cFv */
dTree_anm_c::dTree_anm_c() {
    return;
}

/* 80079600-8007960C       .text __ct__12dTree_data_cFv */
dTree_data_c::dTree_data_c() {
    this->field_0x000 = 0;
    return;
}

/* 8007960C-80079898       .text draw__14dTree_packet_cFv */
void dTree_packet_c::draw() {
    /* Nonmatching */
}

/* 80079898-80079B24       .text calc__14dTree_packet_cFv */
void dTree_packet_c::calc() {
    /* Nonmatching */
}

/* 80079B24-80079E6C       .text checkGroundY__FP12dTree_data_cR4cXyz */
void checkGroundY(dTree_data_c*, cXyz&) {
    /* Nonmatching */
}

/* 80079E6C-8007A14C       .text update__14dTree_packet_cFv */
void dTree_packet_c::update() {
    /* Nonmatching */
}

/* 8007A14C-8007A238       .text setData__14dTree_packet_cFP12dTree_data_ciR4cXyzUci */
void dTree_packet_c::setData(dTree_data_c*, int, cXyz&, unsigned char, int) {
    /* Nonmatching */
}

/* 8007A238-8007A36C       .text newData__14dTree_packet_cFR4cXyzUci */
void dTree_packet_c::newData(cXyz&, unsigned char, int) {
    /* Nonmatching */
}

/* 8007A36C-8007A3DC       .text newAnm__14dTree_packet_cFs */
void dTree_packet_c::newAnm(short) {
    /* Nonmatching */
}

/* 8007A3DC-8007A428       .text setAnm__14dTree_packet_cFis */
void dTree_packet_c::setAnm(int, short) {
    /* Nonmatching */
}
