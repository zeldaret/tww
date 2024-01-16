/**
 * d_a_player_fan.inc
 *
 * Code relating to the Deku Leaf item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/actor/d_a_player_main.h"

/* 8014BAA0-8014BAEC       .text fanWindEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindEffectDraw() {
    /* Nonmatching */
}

/* 8014BAEC-8014BB38       .text fanWindCrashEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindCrashEffectDraw() {
    /* Nonmatching */
}

/* 8014BB38-8014BBE8       .text fanJointCB__9daPy_lk_cFi */
void daPy_lk_c::fanJointCB(int) {
    /* Nonmatching */
}

/* 8014BBE8-8014BC2C       .text daPy_fanJointCallback__FP7J3DNodei */
BOOL daPy_fanJointCallback(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->fanJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BC2C-8014BD08       .text parachuteJointCB__9daPy_lk_cFi */
void daPy_lk_c::parachuteJointCB(int) {
    /* Nonmatching */
}

/* 8014BD08-8014BD4C       .text daPy_parachuteJointCallback__FP7J3DNodei */
BOOL daPy_parachuteJointCallback(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->parachuteJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BD4C-8014BE50       .text setShapeFanLeaf__9daPy_lk_cFv */
void daPy_lk_c::setShapeFanLeaf() {
    /* Nonmatching */
}

/* 8014BE50-8014BEEC       .text checkFanGlideProc__9daPy_lk_cFi */
BOOL daPy_lk_c::checkFanGlideProc(int) {
    /* Nonmatching */
}

/* 8014BEEC-8014BFBC       .text setFanModel__9daPy_lk_cFv */
void daPy_lk_c::setFanModel() {
    /* Nonmatching */
}

/* 8014BFBC-8014C0C0       .text setSmallFanModel__9daPy_lk_cFv */
void daPy_lk_c::setSmallFanModel() {
    /* Nonmatching */
}

/* 8014C0C0-8014C254       .text setParachuteFanModel__9daPy_lk_cFf */
void daPy_lk_c::setParachuteFanModel(f32 f31) {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_FANBA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_FANB));
    
    mpParachuteFanMorf = new mDoExt_McaMorf(
        modelData, NULL, NULL, bck,
        J3DFrameCtrl::LOOP_ONCE_e, daPy_HIO_fan_c0::m.field_0x20, f31, daPy_HIO_fan_c0::m.field_0x4, 0,
        NULL,
        0x00000000,
        0x11020203
    );
    if (mpParachuteFanMorf == NULL || mpParachuteFanMorf->getModel() == NULL) { JUT_ASSERT(323, 0); }
    
    mpHeldItemModel = mpParachuteFanMorf->getModel();
    mDoExt_setCurrentHeap(oldHeap);
    mpHeldItemModel->setUserArea(reinterpret_cast<u32>(this));
    modelData->getJointNodePointer(0x01)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_Lroot joint
    modelData->getJointNodePointer(0x07)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_Rroot joint
    modelData->getJointNodePointer(0x03)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_LarmB joint
    modelData->getJointNodePointer(0x09)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_RarmB joint
}

/* 8014C254-8014C34C       .text procFanSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing_init() {
    /* Nonmatching */
}

/* 8014C34C-8014CA1C       .text procFanSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing() {
    /* Nonmatching */
}

/* 8014CA1C-8014CB94       .text procFanGlide_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procFanGlide_init(int) {
    /* Nonmatching */
}

/* 8014CB94-8014D778       .text procFanGlide__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanGlide() {
    /* Nonmatching */
}
