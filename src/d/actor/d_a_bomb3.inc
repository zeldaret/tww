// Not sure what originally went in here but createHeap needs it for assert filenames

#include "d/actor/d_a_bomb.h"
#include "d/d_com_inf_game.h"

BOOL daBomb_c::createHeap() {
    BOOL ret;
    if(mType == 1) {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BDL_VBAKM));
        JUT_ASSERT(0x9A5, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        
        J3DAnmTransform* bck0_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BCK_VBAMX));
        JUT_ASSERT(0x9AE, bck0_data != 0);
        int temp = mBck0.init(modelData, bck0_data, true, 0, 1.0f, 0, -1, false);
        
        J3DAnmTransform* bck1_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BCK_VBAKM));
        JUT_ASSERT(0x9B4, bck1_data != 0);
        int temp2 = mBck1.init(modelData, bck1_data, true, 0, 1.0f, 0, -1, false);
        
        J3DAnmTevRegKey* brk0_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BRK_VBAMX));
        JUT_ASSERT(0x9BB, brk0_data != 0);
        int temp3 = mBrk0.init(modelData, brk0_data, true, 0, 1.0f, 0, -1, false, 0);
        
        J3DAnmTevRegKey* brk1_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BRK_VBAKM));
        JUT_ASSERT(0x9C1, brk1_data != 0);
        int temp4 = mBrk1.init(modelData, brk1_data, true, 0, 1.0f, 0, -1, false, 0);

        return mpModel && temp && temp2 && temp3 && temp4;
    }
    else {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_attrType[mType].resName, LINK_BDL_BOMB));
        JUT_ASSERT(0x9CE, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

        if(!mpModel) {
            return false;
        }
        else {
            J3DAnmTransform* bck0_data = (J3DAnmTransform*)dComIfG_getObjectRes(m_attrType[mType].resName, LINK_BCK_BOMB);
            int temp = mBck0.init(modelData, bck0_data, false, 2, 1.0f, 0, -1, false);

            return temp ? TRUE : FALSE;
        }
    }
}
