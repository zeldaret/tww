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
#include "d/actor/d_a_player_HIO.h"

extern char l_arcName[];

/* 8014BAA0-8014BAEC       .text fanWindEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindEffectDraw() {
    return (mpYuchw00Brk->getFrame() <= mpYuchw00Brk->getFrameMax() - 0.5f);
}

/* 8014BAEC-8014BB38       .text fanWindCrashEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindCrashEffectDraw() {
    return (mpYbafo00Btk->getFrame() <= mpYbafo00Btk->getFrameMax() - 0.5f);
}

/* 8014BB38-8014BBE8       .text fanJointCB__9daPy_lk_cFi */
BOOL daPy_lk_c::fanJointCB(int param_0) {
    if (param_0 == 2) {
        mDoMtx_ZrotS(mDoMtx_stack_c::now, m3558);
      } else {
        mDoMtx_ZrotS(mDoMtx_stack_c::now, m355A);
      }
      mDoMtx_concat(mpEquipItemModel->getAnmMtx(param_0), mDoMtx_stack_c::now,
                    mDoMtx_stack_c::now);
      mpEquipItemModel->setAnmMtx(1 * param_0, mDoMtx_stack_c::now);
      mDoMtx_copy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
      return true;
}

/* 8014BBE8-8014BC2C       .text daPy_fanJointCallback__FP7J3DNodei */
BOOL daPy_fanJointCallback(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->fanJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BC2C-8014BD08       .text parachuteJointCB__9daPy_lk_cFi */
BOOL daPy_lk_c::parachuteJointCB(int param_0) {
    if ((param_0 == 3) || (param_0 == 9)) {
        mDoMtx_trans(mDoMtx_stack_c::now, m3600, 0.0f, 0.0f);
      } else {
        if ((param_0 == 1) || (param_0 == 7)) {
          mDoMtx_YrotS(mDoMtx_stack_c::now, m355E);
        } else {
          return true;
        }
      }
      mDoMtx_concat(mpEquipItemModel->getAnmMtx(param_0), mDoMtx_stack_c::now,
                    mDoMtx_stack_c::now);
      mpEquipItemModel->setAnmMtx(1 * param_0, mDoMtx_stack_c::now);
      mDoMtx_copy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
      return true;
}

/* 8014BD08-8014BD4C       .text daPy_parachuteJointCallback__FP7J3DNodei */
BOOL daPy_parachuteJointCallback(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->parachuteJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BD4C-8014BE50       .text setShapeFanLeaf__9daPy_lk_cFv */
int daPy_lk_c::setShapeFanLeaf() {
    /* Nonmatching - floats */
    J3DMaterial *mesh;

    if (mpEquipItemModel != NULL) {
      mesh = mpEquipItemModel->getModelData()
                 ->getJointNodePointer(0x00)
                 ->getMesh()
                 ->getNext();
    }
    m355C = m355C + 0x82f;
    m3558 = 1536.0f * cM_ssin(m355C);
    m355A = 2048.0f * cM_ssin(m355C - 0xe00U);
    if (dComIfGs_getMagic() >= 1) {
      for (; mesh != NULL; mesh = mesh->getNext()) {
        mesh->getShape()->show();
      }
      return true;
    } else {
      for (; mesh != NULL; mesh = mesh->getNext()) {
        mesh->getShape()->hide();
      }
      return false;
    }
}

/* 8014BE50-8014BEEC       .text checkFanGlideProc__9daPy_lk_cFi */
BOOL daPy_lk_c::checkFanGlideProc(int param_0) {
    if (checkSetItemTrigger(dItem_DEKU_LEAF_e, 1)) {
        if (dComIfGs_getMagic() >= 1) {
          return procFanGlide_init(param_0);
        }
        mDoAud_seStart(JA_SE_ITEM_TARGET_OUT);
      }
      return false;
}

/* 8014BEEC-8014BFBC       .text setFanModel__9daPy_lk_cFv */
void daPy_lk_c::setFanModel() {
    J3DAnmTransform *bck = getItemAnimeResource(LKANM_BCK_USEFANAA);
    JKRHeap *oldHeap = setItemHeap();
    J3DModelData *tmp_modelData =
        initModel(&mpEquipItemModel, LINK_BDL_FAN, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP,
                              1.0f, 0, -1, false);
    if (!ret) {
      JUT_ASSERT(242, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8014BFBC-8014C0C0       .text setSmallFanModel__9daPy_lk_cFv */
void daPy_lk_c::setSmallFanModel() {
    J3DModelData *tmp_modelData;
    J3DAnmTransform *bck = getItemAnimeResource(LKANM_BCK_FANWAIT);
    JKRHeap *oldHeap = setItemHeap();
    tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_FANSMALL, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP,
                              1.0f, 0, -1, false);
    if (!ret) {
      JUT_ASSERT(275, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
    mpEquipItemModel->setUserArea(reinterpret_cast<u32>(this));
    tmp_modelData->getJointNodePointer(0x02)->setCallBack(daPy_fanJointCallback);
    tmp_modelData->getJointNodePointer(0x03)->setCallBack(daPy_fanJointCallback);
    m355C = 0;
}

/* 8014C0C0-8014C254       .text setParachuteFanModel__9daPy_lk_cFf */
void daPy_lk_c::setParachuteFanModel(f32 f31) {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_FANBA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_FANB));
    
    mpParachuteFanMorf = new mDoExt_McaMorf(
        modelData, NULL, NULL, bck,
        J3DFrameCtrl::EMode_NONE, daPy_HIO_fan_c0::m.field_0x20, f31, daPy_HIO_fan_c0::m.field_0x4, 0,
        NULL,
        0x00000000,
        0x11020203
    );
    if (mpParachuteFanMorf == NULL || mpParachuteFanMorf->getModel() == NULL) { JUT_ASSERT(323, FALSE); }
    
    mpEquipItemModel = mpParachuteFanMorf->getModel();
    mDoExt_setCurrentHeap(oldHeap);
    mpEquipItemModel->setUserArea(reinterpret_cast<u32>(this));
    modelData->getJointNodePointer(0x01)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_Lroot joint
    modelData->getJointNodePointer(0x07)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_Rroot joint
    modelData->getJointNodePointer(0x03)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_LarmB joint
    modelData->getJointNodePointer(0x09)->setCallBack(daPy_parachuteJointCallback); // skeleton_root_RarmB joint
}

/* 8014C254-8014C34C       .text procFanSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing_init() {
    /* Nonmatching - floats */
    commonProcInit(daPyProc_FAN_SWING_e);
    setSingleMoveAnime(
        ANM_USEFANA, daPy_HIO_fan_c0::m.field_0xC, daPy_HIO_fan_c0::m.field_0x10,
        daPy_HIO_fan_c0::m.field_0x2, daPy_HIO_fan_c0::m.field_0x14);
    setFanModel();
    m3570 = 0;
    voiceStart(7);
    setAtParam(AT_TYPE_UNK2000000, 1, dCcG_At_Spl_UNK0, dCcG_SE_UNK4,
               dCcG_AtHitMark_Nrm_e, 0, 50.0f);
    m35EC = daPy_HIO_fan_c0::m.field_0x10;
    if (setShapeFanLeaf()) {
      m34D0 = 1;
      seStartOnlyReverb(JA_SE_LK_FAN_PRE_SWING);
      dComIfGp_setPlayerStatus1(0, daPyStts1_DEKU_LEAF_FAN_e);
    } else {
      m34D0 = 0;
    }
    return true;
}

/* 8014C34C-8014CA1C       .text procFanSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing() {
    /* Nonmatching */
}

/* 8014CA1C-8014CB94       .text procFanGlide_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procFanGlide_init(int param_0) {
    float fVar1;

    commonProcInit(daPyProc_FAN_GLIDE_e);
    deleteEquipItem(FALSE);
    if (param_0 != 0) {
      fVar1 = daPy_HIO_fan_c0::m.field_0x24;
    } else {
      fVar1 = daPy_HIO_fan_c0::m.field_0x28;
    }
    setSingleMoveAnime(ANM_USEFANB, daPy_HIO_fan_c0::m.field_0x20, fVar1,
                       daPy_HIO_fan_c0::m.field_0x4,
                       daPy_HIO_fan_c0::m.field_0x2C);
    mEquipItem = daPyItem_UNK102_e;
    setParachuteFanModel(fVar1);
    m3600 = 0.0f;
    m3604 = 0.0f;
    m34D0 = 0;
    m34D4 = 0;
    m34D6 = 0;
    m34D8 = 0;
    m3570 = 0;
    m34DA = 0;
    m3730 = cXyz::Zero;
    voiceStart(5);
    seStartOnlyReverb(JA_SE_LK_FAN_CHUTE_OPEN);
    m3574 = daPy_HIO_fan_c0::m.field_0x8;
    if (!checkHeavyStateOn()) {
      dComIfGp_setItemMagicCount(-1);
    }
    dComIfGp_setPlayerStatus1(0, daPyStts1_DEKU_LEAF_FLY_e);
    m34D2 = daPy_HIO_fan_c0::m.field_0xA;
    return true;
}

/* 8014CB94-8014D778       .text procFanGlide__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanGlide() {
    /* Nonmatching */
}
