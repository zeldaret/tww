/**
 * d_a_obj_movebox.cpp
 * Object - Pushable Box
 */

#include "global.h"

// Needed for the .data and .bss sections to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};
static u8 dummy5[0x4C];

#include "d/actor/d_a_obj_movebox.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "dolphin/types.h"
#include "d/actor/d_a_obj_buoyflag.h"
#include "d/actor/d_a_obj_jump.h"
#include "d/actor/d_a_obj_mmrr.h"
#include "d/actor/d_a_obj_mkie.h"
#include "d/actor/d_a_player.h"

enum ECUBE_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    ECUBE_BDL_ECUBE=0x4,
    
    /* DZB */
    ECUBE_DZB_ECUBE=0x7,
};

enum HBOX2_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    HBOX2_BDL_HBOX2=0x4,
    
    /* DZB */
    HBOX2_DZB_HBOX2=0x7,
};

enum HJUMP_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    HJUMP_BDL_HBOX1=0x4,
    HJUMP_BDL_HJUMP1=0x5,
    HJUMP_BDL_HJUMP2=0x6,
    
    /* DZB */
    HJUMP_DZB_HBOX1=0x9,
    HJUMP_DZB_HJUMP1A=0xA,
    HJUMP_DZB_HJUMP1B=0xB,
    HJUMP_DZB_HJUMP2=0xC,
};

enum KKIBA_00_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    KKIBA_00_BDL_KKIBA_00=0x4,
    
    /* DZB */
    KKIBA_00_DZB_KKIBA_00=0x7,
};

enum MMIRROR_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    MMIRROR_BCK_MSUSW=0x6,
    
    /* BDLM */
    MMIRROR_BDL_MMRR=0x9,
    MMIRROR_BDL_MSUSW=0xA,
    MMIRROR_BDL_YSSMR00=0xB,
    
    /* BTK */
    MMIRROR_BTK_MMRR=0xE,
    MMIRROR_BTK_MSUSW=0xF,
    MMIRROR_BTK_YSSMR00=0x10,
    
    /* DZB */
    MMIRROR_DZB_MMRR=0x13,
    MMIRROR_DZB_MSUSW=0x14,
};

enum MPWRB_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MPWRB_BDL_MPWRB=0x4,
    
    /* DZB */
    MPWRB_DZB_MPWRB=0x7,
};

enum OSIBLK_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    OSIBLK_BDL_OBM_OSIHIKIBLK1=0x4,
    OSIBLK_BDL_OBM_OSIHIKIBLK2=0x5,
    
    /* DZB */
    OSIBLK_DZB_OBM_OSIHIKIBLK1=0x8,
    OSIBLK_DZB_OBM_OSIHIKIBLK2=0x9,
};

namespace daObjMovebox {
    dBgS_ObjGndChk Bgc_c::M_gnd_work[23];
    dBgS_WtrChk Bgc_c::M_wrt_work;
    dBgS_ObjLinChk Bgc_c::M_wall_work[23];
    
    const BgcSrc_c Bgc_c::M_lin5[5] = {
        // TODO
        {0.0f, 0.0f, 0.0f, 0.0f},
        {-0.5f, -0.5f, 1.0f, 1.0f},
        {0.5f, -0.5f, -1.0f, 1.0f},
        {0.5f, 0.5f, -1.0f, -1.0f},
        {-0.5f, 0.5f, 1.0f, -1.0f},
    };
    
    const BgcSrc_c Bgc_c::M_lin20[23] = {
        // TODO
        {0.0f, 0.0f, 0.0f, 0.0f},
        {-0.25f, -0.25f, 0.0f, 0.0f},
        {-0.5f, -0.5f, 1.0f, 1.0f},
        {0.0f, -0.5f, -1.0f, 1.0f},
        {0.0f, 0.0f, -1.0f, -1.0f},
        {-0.5f, 0.0f, 1.0f, -1.0f},
        {0.25f, -0.25f, 0.0f, 0.0f},
        {0.0f, -0.5f, 1.0f, 1.0f},
        {0.5f, -0.5f, -1.0f, 1.0f},
        {0.5f, 0.0f, -1.0f, -1.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
        {0.25f, 0.25f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.5f, 0.0f, -1.0f, 1.0f},
        {0.5f, 0.5f, -1.0f, -1.0f},
        {0.0f, 0.5f, 1.0f, -1.0f},
        {-0.25f, 0.25f, 0.0f, 0.0f},
        {-0.5f, 0.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, -1.0f, 1.0f},
        {0.0f, 0.5f, -1.0f, -1.0f},
        {-0.5f, 0.5f, 1.0f, -1.0f},
        {-0.75f, 0.25f, 0.0f, 0.0f},
        {-0.75f, -0.25f, 0.0f, 0.0f},
    };
    
    s32 Act_c::Mthd_Create() {
        fopAcM_SetupActor(this, Act_c);
        
        s32 phase_state;
        mType = prm_get_type();
        phase_state = cPhs_ERROR_e;
        prmX_init();
        prmZ_init();
        
        mbShouldAppear = chk_appear();
        if (mbShouldAppear) {
            phase_state = dComIfG_resLoad(&mPhs, M_arcname[mType]);
            if (phase_state == cPhs_COMPLEATE_e) {
                u32 heapSize = i_attr()->mDZBHeapSize;
                path_init();
                phase_state = MoveBGCreate(M_arcname[mType], i_attr()->mDZBFileIndex, dBgS_MoveBGProc_Trans, heapSize);
                JUT_ASSERT(1998, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
            }
        }
        
        return phase_state;
    }
    
    BOOL Act_c::Mthd_Delete() {
        s32 result = MoveBGDelete();
        if (mbShouldAppear) {
            dComIfG_resDelete(&mPhs, M_arcname[mType]);
        }
        return result;
    }
    
    /* 000000EC-000001B0       .text __ct__Q212daObjMovebox5Bgc_cFv */
    Bgc_c::Bgc_c() {
        for (int i = 0; i < ARRAY_SIZE(mGroundY); i++) {
            mGroundY[i] = 0.0f;
            mWallPos[i] = cXyz::Zero;
        }
        mMaxGroundIdx = -1;
        mWallIdx = -1;
        mNearestWallDist = FLOAT_MAX;
        mWaterY = 0.0f;
        mStateFlags = (State_e)0;
    }
    
    /* 000001F0-000003A4       .text gnd_pos__Q212daObjMovebox5Bgc_cFPCQ212daObjMovebox5Act_cPCQ212daObjMovebox8BgcSrc_cif */
    void Bgc_c::gnd_pos(const Act_c* movebox, const BgcSrc_c* bgcSrc, int bgcSrcCount, f32 param_4) {
        f32 tempz;
        f32 maxGroundY = -1000000000.0f;
        
        mDoMtx_stack_c::transS(movebox->current.pos);
        mDoMtx_stack_c::YrotM(movebox->home.angle.y);
        mMaxGroundIdx = -1;
        
        for (int i = 0; i < bgcSrcCount; i++, bgcSrc++) {
            cXyz offset(
                bgcSrc->m0C + bgcSrc->m04 * movebox->attr()->mScaleXZ,
                param_4,
                bgcSrc->m08 + bgcSrc->m00 * movebox->attr()->mScaleXZ
            );
            cXyz pos;
            mDoMtx_stack_c::multVec(&offset, &pos);
            M_gnd_work[i].SetPos(&pos);
            M_gnd_work[i].SetActorPid(movebox->base.mBsPcId);
            mGroundY[i] = dComIfG_Bgsp()->GroundCross(&M_gnd_work[i]);
            if (mGroundY[i] > maxGroundY) {
                fopAc_ac_c* groundActor = dComIfG_Bgsp()->GetActorPointer(M_gnd_work[i].GetBgIndex());
                if (!(groundActor && fopAcM_GetName(groundActor) == PROC_Obj_Movebox && ((Act_c*)groundActor)->mMode == Act_c::MODE_AFLOAT)) {
                    maxGroundY = mGroundY[i];
                    mMaxGroundIdx = i;
                }
            }
        }
    }
    
    /* 000003A4-00000474       .text wrt_pos__Q212daObjMovebox5Bgc_cFRC4cXyz */
    void Bgc_c::wrt_pos(const cXyz& pos) {
        cXyz groundPos(pos);
        f32 roofY = pos.y + 400.0f;
        groundPos.y -= 100.0f;
        M_wrt_work.Set(groundPos, roofY);
        if (dComIfG_Bgsp()->SplGrpChk(&M_wrt_work)) {
            mWaterY = M_wrt_work.GetHeight();
            cLib_onBit(mStateFlags, BgcState_ABOVE_WATER_e);
            if (mWaterY > pos.y) {
                cLib_onBit(mStateFlags, BgcState_IN_WATER_e);
            }
        }
    }
    
    /* 00000474-00000748       .text wall_pos__Q212daObjMovebox5Bgc_cFPCQ212daObjMovebox5Act_cPCQ212daObjMovebox8BgcSrc_cisf */
    void Bgc_c::wall_pos(const Act_c* movebox, const BgcSrc_c* bgcSrc, int bgcSrcCount, s16 param_4, f32 param_5) {
        s16 angle;
        cXyz startPos;
        cXyz endPos;
        cXyz temp_2c;
        cXyz temp_20;
        
        angle = movebox->home.angle.y + param_4;
        mWallIdx = -1;
        mNearestWallDist = FLOAT_MAX;
        mDoMtx_stack_c::YrotS((s16)angle);
        mDoMtx_stack_c::XrotM(0x4000);
        mDoMtx_stack_c::multVec(&cXyz::BaseY, &temp_20);
        temp_20 *= param_5 + movebox->attr()->mScaleXZ * 0.5f;
        
        for (int i = 0; i < bgcSrcCount; i++, bgcSrc++) {
            mDoMtx_stack_c::XrotS(0x4000);
            cXyz temp_14(bgcSrc->m0C, 0.0f, bgcSrc->m08);
            mDoMtx_stack_c::multVec(&temp_14, &temp_2c);
            mDoMtx_stack_c::YrotS((s16)angle);
            mDoMtx_stack_c::transM(temp_2c);
            mDoMtx_stack_c::scaleM(movebox->attr()->mScaleXZ, movebox->attr()->mScaleY, movebox->attr()->mScaleXZ);
            mDoMtx_stack_c::transM(0.0f, 0.5f, 0.0f);
            mDoMtx_stack_c::XrotM(0x4000);
            temp_14.set(bgcSrc->m04, 0.0f, bgcSrc->m00);
            mDoMtx_stack_c::multVec(&temp_14, &startPos);
            startPos += movebox->current.pos;
            endPos = startPos + temp_20;
            M_wall_work[i].Set(&startPos, &endPos, const_cast<Act_c*>(movebox));
            M_wall_work[i].SetActorPid(movebox->base.mBsPcId);
            if (dComIfG_Bgsp()->LineCross(&M_wall_work[i])) {
                mWallPos[i] = M_wall_work[i].GetCross();
                f32 dist = startPos.abs2(mWallPos[i]);
                if (dist < mNearestWallDist) {
                    mNearestWallDist = dist;
                    mWallIdx = i;
                }
            } else {
                mWallPos[i] = cXyz::Zero;
            }
        }
    }
    
    /* 00000748-000008E8       .text proc_vertical__Q212daObjMovebox5Bgc_cFPQ212daObjMovebox5Act_c */
    void Bgc_c::proc_vertical(Act_c* movebox) {
        State_e prevStateFlags = mStateFlags;
        mStateFlags = (State_e)0;
        
        gnd_pos(
            movebox,
            movebox->attr()->m9A ? M_lin20 : M_lin5,
            movebox->attr()->m9A ? ARRAY_SIZE(M_lin20)-2 : ARRAY_SIZE(M_lin5),
            100.0f
        );
        
        if (mMaxGroundIdx >= 0) {
            if (mGroundY[mMaxGroundIdx] > movebox->current.pos.y) {
                movebox->current.pos.y = mGroundY[mMaxGroundIdx];
                cLib_onBit(mStateFlags, BgcState_ON_GROUND_e);
                movebox->speed.y = 0.0f;
            }
        }
        
        wrt_pos(movebox->current.pos);
        
        if (cLib_checkBit(mStateFlags, BgcState_ABOVE_WATER_e) && mWaterY > movebox->current.pos.y) {
            cLib_onBit(mStateFlags, BgcState_IN_WATER_e);
        }
        if (!cLib_checkBit(mStateFlags, BgcState_ON_GROUND_e) && cLib_checkBit(prevStateFlags, BgcState_ON_GROUND_e)) {
            cLib_onBit(mStateFlags, BgcState_JUST_LEFT_GROUND_e);
            movebox->speed.y = movebox->attr()->m20;
        }
        if (cLib_checkBit(mStateFlags, BgcState_ON_GROUND_e) && !cLib_checkBit(prevStateFlags, BgcState_ON_GROUND_e)) {
            cLib_onBit(mStateFlags, BgcState_JUST_HIT_GROUND_e);
        }
        if (cLib_checkBit(mStateFlags, BgcState_IN_WATER_e) && !cLib_checkBit(prevStateFlags, BgcState_IN_WATER_e)) {
            cLib_onBit(mStateFlags, BgcState_JUST_HIT_WATER_e);
        }
        if (cLib_checkBit(mStateFlags, BgcState_ON_GROUND_e) && mMaxGroundIdx >= 0) {
            dComIfG_Bgsp()->RideCallBack(M_gnd_work[mMaxGroundIdx], movebox);
        }
    }
    
    /* 000008E8-00000928       .text chk_wall_pre__Q212daObjMovebox5Bgc_cFPCQ212daObjMovebox5Act_cPCQ212daObjMovebox8BgcSrc_cis */
    bool Bgc_c::chk_wall_pre(const Act_c* movebox, const BgcSrc_c* bgcSrc, int bgcSrcCount, s16 param_4) {
        wall_pos(movebox, bgcSrc, bgcSrcCount, param_4, 74.0f);
        return mWallIdx >= 0;
    }
    
    /* 00000928-00000CCC       .text chk_wall_touch__Q212daObjMovebox5Bgc_cFPCQ212daObjMovebox5Act_cPCQ212daObjMovebox8BgcSrc_cs */
    bool Bgc_c::chk_wall_touch(const Act_c* movebox, const BgcSrc_c* bgcSrc, s16 dirAngle) {
        static dBgS_ObjLinChk touch_work;
        cXyz startPos;
        cXyz endPos;
        cXyz offset;
        cXyz temp_20;
        cXyz direction;
        
        s16 angle = movebox->home.angle.y + dirAngle;
        mDoMtx_stack_c::YrotS((s16)angle);
        mDoMtx_stack_c::XrotM(0x4000);
        offset.set(bgcSrc->m0C, 0.0f, bgcSrc->m08);
        mDoMtx_stack_c::multVec(&cXyz::BaseY, &direction);
        direction *= 10.0f + movebox->attr()->mScaleXZ * 0.5f;
        
        mDoMtx_stack_c::XrotM(0x4000);
        offset.set(bgcSrc->m0C, 0.0f, bgcSrc->m08);
        mDoMtx_stack_c::multVec(&offset, &temp_20);
        mDoMtx_stack_c::YrotS((s16)angle);
        mDoMtx_stack_c::transM(temp_20);
        mDoMtx_stack_c::scaleM(movebox->attr()->mScaleXZ, movebox->attr()->mScaleY, movebox->attr()->mScaleXZ);
        mDoMtx_stack_c::transM(0.0f, 0.5f, 0.0f);
        mDoMtx_stack_c::XrotM(0x4000);
        offset.set(bgcSrc->m04, 0.0f, bgcSrc->m00);
        mDoMtx_stack_c::multVec(&offset, &startPos);
        startPos += movebox->current.pos;
        endPos = startPos + direction;
        
        touch_work.SetActorPid(movebox->base.mBsPcId);
        touch_work.Set(&startPos, &endPos, const_cast<Act_c*>(movebox));
        return dComIfG_Bgsp()->LineCross(&touch_work);
    }
    
    /* 00001258-000012E0       .text chk_wall_touch2__Q212daObjMovebox5Bgc_cFPCQ212daObjMovebox5Act_cPCQ212daObjMovebox8BgcSrc_cis */
    bool Bgc_c::chk_wall_touch2(const Act_c* movebox, const BgcSrc_c* bgcSrc, int bgcSrcCount, s16 dirAngle) {
        bool touch = false;
        for (int i = 0; i < bgcSrcCount; i++) {
            if (chk_wall_touch(movebox, &bgcSrc[i], dirAngle)) {
                touch = true;
                break;
            }
        }
        return touch;
    }
    
    const char* const Act_c::M_arcname[13] = {
        "Kkiba_00",
        "Osiblk",
        "Osiblk",
        "MpwrB",
        "Kkiba_00",
        "Hbox2",
        "Hjump",
        "Hjump",
        "Kkiba_00",
        "Kkiba_00",
        "Mmirror",
        "Osiblk",
        "Ecube",
    };
    
    const dCcD_SrcCyl Act_c::M_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_BOMB,
            /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
            /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VSGRP,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 75.0f,
            /* Height */ 150.0f,
        },
    };
    
    const Attr_c Act_c::M_attr[13] = {
        // TYPE_BREAKABLE_WOODEN_CRATE
        // Arcname: Kkiba_00
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ KKIBA_00_BDL_KKIBA_00,
            /* mDZBFileIndex   */ KKIBA_00_DZB_KKIBA_00,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_WBLOCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_WBLOCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_WBOX_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_M,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_M,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_BLACK_BOX
        // Arcname: Osiblk
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ OSIBLK_BDL_OBM_OSIHIKIBLK1,
            /* mDZBFileIndex   */ OSIBLK_DZB_OBM_OSIHIKIBLK1,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
            
        },
        // TYPE_BLACK_BOX_WITH_STATUE
        // Arcname: Osiblk
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ OSIBLK_BDL_OBM_OSIHIKIBLK2,
            /* mDZBFileIndex   */ OSIBLK_DZB_OBM_OSIHIKIBLK2,
            /* mDZBHeapSize    */ 0x1560,
            /* mScaleY         */ 150.0f,
            /* m68             */ 300.0f,
            /* m6C             */ 1.0f/300.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 295,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_BIG_BLACK_BOX
        // Arcname: MpwrB
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 170.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 3.6f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ MPWRB_BDL_MPWRB,
            /* mDZBFileIndex   */ MPWRB_DZB_MPWRB,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 300.0f,
            /* m68             */ 300.0f,
            /* m6C             */ 1.0f/300.0f,
            /* mScaleXZ        */ 300.0f,
            /* m74             */ 1.0f/300.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -180,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -180,
            /* mCullMaxX       */ 180,
            /* mCullMaxY       */ 301,
            /* mCullMaxZ       */ 180,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ true,
        },
        // TYPE_WOODEN_CRATE
        // Arcname: Kkiba_00
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ KKIBA_00_BDL_KKIBA_00,
            /* mDZBFileIndex   */ KKIBA_00_DZB_KKIBA_00,
            /* mDZBHeapSize    */ 0x1620,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_WBLOCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_WBLOCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_WBOX_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_M,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_M,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_GOLDEN_CRATE
        // Arcname: Hbox2
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ HBOX2_BDL_HBOX2,
            /* mDZBFileIndex   */ HBOX2_DZB_HBOX2,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_WBLOCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_WBLOCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_WBOX_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_M,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_M,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_METAL_BOX
        // Arcname: Hjump
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ HJUMP_BDL_HBOX1,
            /* mDZBFileIndex   */ HJUMP_DZB_HBOX1,
            /* mDZBHeapSize    */ 0x7E0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_METAL_BOX_WITH_SPRING
        // Arcname: Hjump
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ -1,
            /* mDZBFileIndex   */ HJUMP_DZB_HJUMP1A,
            /* mDZBHeapSize    */ 0x320,
            /* mScaleY         */ 150.0f,
            /* m68             */ 300.0f,
            /* m6C             */ 1.0f/300.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 200,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_WOODEN_CRATE_2
        // Arcname: Kkiba_00
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ KKIBA_00_BDL_KKIBA_00,
            /* mDZBFileIndex   */ KKIBA_00_DZB_KKIBA_00,
            /* mDZBHeapSize    */ 0x1620,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_WBLOCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_WBLOCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_WBOX_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_M,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_M,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_WOODEN_CRATE_3
        // Arcname: Kkiba_00
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -3.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 3.9f,
            /* m2C             */ -0.39f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ KKIBA_00_BDL_KKIBA_00,
            /* mDZBFileIndex   */ KKIBA_00_DZB_KKIBA_00,
            /* mDZBHeapSize    */ 0x1620,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_WBLOCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_WBLOCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_WBOX_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_M,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_M,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_MIRROR
        // Arcname: Mmirror
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 170.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ -1,
            /* mDZBFileIndex   */ MMIRROR_DZB_MMRR,
            /* mDZBHeapSize    */ 0xD40,
            /* mScaleY         */ 300.0f,
            /* m68             */ 450.0f,
            /* m6C             */ 1.0f/450.0f,
            /* mScaleXZ        */ 300.0f,
            /* m74             */ 1.0f/300.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -150,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -150,
            /* mCullMaxX       */ 150,
            /* mCullMaxY       */ 681,
            /* mCullMaxZ       */ 150,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ true,
        },
        // TYPE_BLACK_BOX_WITH_MKIE
        // Arcname: Osiblk
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ OSIBLK_BDL_OBM_OSIHIKIBLK1,
            /* mDZBFileIndex   */ OSIBLK_DZB_OBM_OSIHIKIBLK1,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 350.0f,
            /* m6C             */ 1.0f/350.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ false,
            /* mbCastsShadow   */ false,
            /* m9A             */ false,
        },
        // TYPE_MOSSY_BLACK_BOX
        // Arcname: Ecube
        {
            /* m00             */ 4,
            /* m02             */ 4,
            /* m04             */ 20,
            /* m06             */ 4,
            /* m08             */ 4,
            /* m0A             */ 20,
            /* m0C             */ 75.0f,
            /* m10             */ 90.0f,
            /* m14             */ -5.0f,
            /* m18             */ 0.005f,
            /* m1C             */ 0.001f,
            /* m20             */ 0.0f,
            /* mLandSmokeScale */ 1.8f,
            /* m28             */ 4.5f,
            /* m2C             */ -0.5f,
            /* m30             */ -0.2f,
            /* m34             */ 0.02f,
            /* m38             */ 1000,
            /* m3C             */ 0.04f,
            /* m40             */ 0.013f,
            /* m44             */ 0.15f,
            /* m48             */ 0.1f,
            /* m4C             */ 0.1f,
            /* m50             */ 0.06f,
            /* m54             */ 0.075f,
            /* mModelFileIndex */ ECUBE_BDL_ECUBE,
            /* mDZBFileIndex   */ ECUBE_DZB_ECUBE,
            /* mDZBHeapSize    */ 0x8A0,
            /* mScaleY         */ 150.0f,
            /* m68             */ 150.0f,
            /* m6C             */ 1.0f/150.0f,
            /* mScaleXZ        */ 150.0f,
            /* m74             */ 1.0f/150.0f,
            /* mMoveSE         */ JA_SE_LK_MOVE_ROCK,
            /* mCantMoveSE     */ JA_SE_LK_MOVE_ROCK_LIMIT,
            /* mNormalFallSE   */ JA_SE_OBJ_BLOCK_FALL_NORMAL,
            /* mWaterFallSE    */ JA_SE_OBJ_FALL_WATER_L,
            /* mMagmaFallSE    */ JA_SE_OBJ_FALL_MAGMA_L,
            /* mCullMinX       */ -90,
            /* mCullMinY       */ -1,
            /* mCullMinZ       */ -90,
            /* mCullMaxX       */ 90,
            /* mCullMaxY       */ 151,
            /* mCullMaxZ       */ 90,
            /* mbUseBGTevType  */ true,
            /* mbCastsShadow   */ true,
            /* m9A             */ false,
        },
    };
    
    void Act_c::mode_proc_call() {
        static ModeFunc mode_proc[] = {
            &mode_wait,
            &mode_walk,
            &mode_afl,
        };
        (this->*mode_proc[mMode])();
    }
    
    /* 000012E0-00001308       .text prm_get_swSave1__Q212daObjMovebox5Act_cCFv */
    s32 Act_c::prm_get_swSave1() const {
        return daObj::PrmAbstract(this, PRM_SWSAVE1_W, PRM_SWSAVE1_S);
    }
    
    /* 00001308-00001380       .text prmZ_init__Q212daObjMovebox5Act_cFv */
    void Act_c::prmZ_init() {
        if (mbPrmZInitialized) {
            return;
        }
        mbPrmZInitialized = true;
        
        s32 switchEnablesSpawn = prm_get_swSave();
        if (switchEnablesSpawn) {
            // The appearing/disappearing type of box does not take pathId or swSave2 params.
            mPrmZ = 0xFFFF;
        } else {
            mPrmZ = home.angle.z;
        }
        
        home.angle.z = 0;
        current.angle.z = 0;
        shape_angle.z = 0;
    }
    
    /* 00001380-000013B0       .text prmX_init__Q212daObjMovebox5Act_cFv */
    void Act_c::prmX_init() {
        if (!mbPrmXInitialized) {
            mPrmX = home.angle.x;
            mbPrmXInitialized = true;
        }
        
        home.angle.x = 0;
        current.angle.x = 0;
        shape_angle.x = 0;
    }
    
    /* 000013B0-000013C8       .text attr__Q212daObjMovebox5Act_cCFv */
    const Attr_c* Act_c::attr() const {
        return &M_attr[mType];
    }
    
    /* 000013C8-00001674       .text set_mtx__Q212daObjMovebox5Act_cFv */
    void Act_c::set_mtx() {
        bool isFloating = mMode == MODE_AFLOAT;
        mDoMtx_stack_c::transS(current.pos);
        if (isFloating) {
            cXyz temp_40;
            Quaternion temp_30;
            temp_40.set(m614, 1.0f, m618);
            mDoMtx_stack_c::transM(0.0f, m624, 0.0f);
            daObj::quat_rotBaseY(&temp_30, temp_40);
            mDoMtx_stack_c::quatM(&temp_30);
        }
        
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        if (isFloating) {
            mDoMtx_stack_c::transM(0.0f, -m624, 0.0f);
        }
        
        if (mpModel) {
            mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
        }
        cMtx_copy(mDoMtx_stack_c::get(), mMtx);
        
        if (mChildPID == fpcM_ERROR_PROCESS_ID_e) {
            return;
        }
        fopAc_ac_c* childActor;
        if (fopAcM_SearchByID(mChildPID, &childActor)) {
            if (!childActor) {
                return;
            }
            if (mType == TYPE_METAL_BOX_WITH_SPRING) {
                daObjJump::Act_c* jump = (daObjJump::Act_c*)childActor;
                if (jump->current.pos.abs2(current.pos) > 0.0001f) {
                    jump->setup(&current.pos);
                }
            } else if (mType == TYPE_MIRROR) {
                daObjMmrr::Act_c* mmrr = (daObjMmrr::Act_c*)childActor;
                if (mmrr->current.pos.abs2(current.pos) > 0.0001f) {
                    mmrr->setup(&current.pos);
                }
            } else if (mType == TYPE_BLACK_BOX_WITH_MKIE) {
                daObjMkie::Act_c* mkie = (daObjMkie::Act_c*)childActor;
                cXyz targetPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
                if (mkie->current.pos.abs2(targetPos) > 0.0001f) {
                    mkie->setup(&targetPos);
                }
            } else {
                cXyz buoyOffset(0.0f, i_attr()->m68 - 5.0f, 0.0f);
                cXyz buoyOffsetSR;
                MtxP mtx = mDoMtx_stack_c::get();
                cMtx_multVecSR(mtx, &buoyOffset, &buoyOffsetSR);
                mtx[0][3] += buoyOffsetSR.x;
                mtx[1][3] += buoyOffsetSR.y;
                mtx[2][3] += buoyOffsetSR.z;
                daObjBuoyflag::Act_c* buoyflag = (daObjBuoyflag::Act_c*)childActor;
                buoyflag->setup(mtx);
            }
        } else {
            mChildPID = fpcM_ERROR_PROCESS_ID_e;
        }
    }
    
    /* 00001674-000016B8       .text init_mtx__Q212daObjMovebox5Act_cFv */
    void Act_c::init_mtx() {
        if (mpModel) {
            mpModel->mBaseScale = scale;
        }
        set_mtx();
    }
    
    /* 000016B8-00001830       .text path_init__Q212daObjMovebox5Act_cFv */
    void Act_c::path_init() {
        // Load the position the box was last left pushed to based on the path and switch(es).
        s32 pathId = prmZ_get_pathId();
        s32 swSave1 = prm_get_swSave1();
        if (pathId != 0xFF && swSave1 != 0xFF) {
            s32 swSave2 = prmZ_get_swSave2();
            
            bool isMoved1 = is_switch1();
            u32 isMoved2 = false;
            if (0xFF == swSave2) { // Literal must be on the left hand side for a match
                isMoved2 = false;
            } else {
                isMoved2 = is_switch2();
                isMoved2 = !!isMoved2;
            }
            isMoved2 = !!isMoved2;
            
            s32 pntIdx = 0;
            if (isMoved1 != false) {
                pntIdx = 1;
            }
            if (isMoved2) {
                pntIdx += 2;
            }
            
            mpPath = dPath_GetRoomPath(pathId, home.roomNo);
            dPath__Point* pnt = dPath_GetPnt(mpPath, pntIdx);
            home.pos = pnt->mPos;
            current.pos = pnt->mPos;
        }
    }
    
    /* 00001830-00001A10       .text path_save__Q212daObjMovebox5Act_cFv */
    void Act_c::path_save() {
        // Determine how far along the path the box has been pushed and save the position to the switch(es).
        // Supports up to 4 possible path points.
        s32 pathId = prmZ_get_pathId();
        s32 swSave1 = prm_get_swSave1();
        if (pathId != 0xFF && swSave1 != 0xFF) {
            s32 swSave2 = prmZ_get_swSave2();
            
            s32 numPnts;
            if (0xFF == swSave2) { // Literal must be on the left hand side for a match
                numPnts = 2;
            } else {
                numPnts = 4;
            }
            if (numPnts > mpPath->m_num) {
                numPnts = mpPath->m_num;
            }
            
            s32 pntIdx;
            for (pntIdx = 0; pntIdx < numPnts; pntIdx++) {
                cXyz pntPos = dPath_GetPnt(mpPath, pntIdx)->mPos;
                if (current.pos.abs2(pntPos) < 9.0f) {
                    break;
                }
            }
            if (pntIdx >= numPnts) {
                return;
            }
            
            // Store the low bit of the 2-bit index in swSave1.
            if (pntIdx & 1) {
                on_switch1();
            } else {
                off_switch1();
            }
            
            if (swSave2 != 0xFF) {
                // Store the high bit of the 2-bit index in swSave2.
                if (pntIdx & 2) {
                    on_switch2();
                } else {
                    off_switch2();
                }
            }
        }
    }
    
    /* 00001A10-00001B00       .text CreateHeap__Q212daObjMovebox5Act_cFv */
    int Act_c::CreateHeap() {
        BOOL success = TRUE;
        if (i_attr()->mModelFileIndex >= 0) {
            J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname[mType], i_attr()->mModelFileIndex);
            JUT_ASSERT(1722, modelData != 0);
            
            mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
            success = (mpModel != 0);
        } else {
            mpModel = NULL;
        }
        return success;
    }
    
    /* 00001B00-00001C64       .text RideCallBack__Q212daObjMovebox5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
    void Act_c::RideCallBack(dBgW*, fopAc_ac_c* actor1, fopAc_ac_c* actor2) {
        Act_c* movebox = (Act_c*)actor1;
        if (movebox->mMode != MODE_AFLOAT) {
            return;
        }
        const Attr_c* attr = movebox->i_attr();
        f32 f0 = movebox->i_attr()->m2C + movebox->i_attr()->m30;
        f32 deltaX = actor2->current.pos.x - actor1->current.pos.x;
        f32 deltaZ = actor2->current.pos.z - actor1->current.pos.z;
        f32 f3;
        f32 f4;
        if (fopAcM_GetProfName(actor2) == PROC_PLAYER) {
            f3 = movebox->i_attr()->m2C;
            f4 = movebox->i_attr()->m74 * movebox->i_attr()->m44;
        } else {
            f3 = movebox->i_attr()->m30;
            f4 = movebox->i_attr()->m74 * movebox->i_attr()->m48;
        }
        f32 f6 = sqrtf(deltaX*deltaX + deltaZ*deltaZ);
        f6 = 1.0f - f6 * attr->m74;
        f6 = f6 * 0.9f + 0.1f;
        if (f6 < 0.0f) {
            f6 = 0.0f;
        }
        f3 *= f6;
        movebox->m608 += f3;
        if (movebox->m608 < f0) {
            movebox->m608 = f0;
        }
        movebox->m60C += f4 * deltaX;
        movebox->m610 += f4 * deltaZ;
    }
    
    /* 00001C64-00001DD4       .text PPCallBack__Q212daObjMovebox5Act_cFP10fopAc_ac_cP10fopAc_ac_csQ24dBgW13PushPullLabel */
    fopAc_ac_c* Act_c::PPCallBack(fopAc_ac_c* actor, fopAc_ac_c*, s16 rot, dBgW::PushPullLabel orig_pp_label) {
        Act_c* i_this = (Act_c*)actor;
        
        dBgW::PushPullLabel pp_label = static_cast<dBgW::PushPullLabel>(orig_pp_label & (dBgW::PP_UNK1_e | dBgW::PP_UNK2_e));
        if (pp_label) {
            bool unk;
            if (!i_this->i_attr()->m9A) {
                unk = true;
            } else {
                unk = orig_pp_label & dBgW::PP_UNK8_e;
            }
            if (unk) {
                s16 angle = (s16)(pp_label & dBgW::PP_UNK2_e ? rot - 0x8000 : rot) - actor->home.angle.y;
                int pp_field = dBgW::PP_UNK1_e | dBgW::PP_UNK2_e;
                JUT_ASSERT(1813, pp_label != pp_field);
                
                i_this->mPPLabel = orig_pp_label;
                
                int whichSide;
                if (angle >= -0x2000 && angle < 0x2000) {
                    whichSide = 0;
                } else if (angle >= 0x2000 && angle < 0x6000) {
                    whichSide = 1;
                } else if (angle >= 0x6000 || angle < -0x6000) {
                    whichSide = 2;
                } else {
                    whichSide = 3;
                }
                
                for (int i = 0; i < 4; i++) {
                    if (i == whichSide) {
                        i_this->mMomentCnt[i]++;
                    } else {
                        i_this->mMomentCnt[i] = 0;
                    }
                }
                
                i_this->m64A = true;
            }
        }
        
        return actor;
    }
    
    /* 00001DD4-00002214       .text Create__Q212daObjMovebox5Act_cFv */
    int Act_c::Create() {
        m604 = 0;
        m608 = 0.0f;
        m60C = 0.0f;
        m610 = 0.0f;
        m614 = 0.0f;
        m618 = 0.0f;
        m61C = 0.0f;
        m620 = 0.0f;
        m624 = i_attr()->m68 * 0.5f;
        m628 = 0;
        m62C = 0;
        m630 = 0.0f;
        m634 = -1;
        mPPLabel = (dBgW::PushPullLabel)0;
        clr_moment_cnt();
        m644 = 0;
        m646 = 0;
        m648 = 0x14;
        m64A = false;
        
        mpBgW->SetRideCallback(RideCallBack);
        mpBgW->SetPushPullCallback(PPCallBack);
        mStts.Init(0xFF, 0xFF, this);
        mCyl.Set(M_cyl_src);
        mCyl.SetStts(&mStts);
        mCyl.SetTgVec((cXyz&)cXyz::Zero);
        mCyl.OnTgNoHitMark();
        mCyl.OffCoSetBit();
        
        fopAcM_SetMtx(this, mMtx);
        fopAcM_setCullSizeBox(this,
            i_attr()->mCullMinX, i_attr()->mCullMinY, i_attr()->mCullMinZ,
            i_attr()->mCullMaxX, i_attr()->mCullMaxY, i_attr()->mCullMaxZ
        );
        
        speedF = 0.0f;
        gravity = i_attr()->m14;
        fopAcM_posMoveF(this, NULL);
        mBgc.proc_vertical(this);
        cLib_offBit(mBgc.mStateFlags, static_cast<Bgc_c::State_e>(Bgc_c::BgcState_JUST_LEFT_GROUND_e | Bgc_c::BgcState_JUST_HIT_GROUND_e | Bgc_c::BgcState_JUST_HIT_WATER_e));
        
        m64F = true;
        mReverb = dComIfGp_getReverb(fopAcM_GetHomeRoomNo(this));
        
        mChildPID = fpcM_ERROR_PROCESS_ID_e;
        if (prm_get_buoy() == 0) {
            cXyz buoyPos(current.pos.x, current.pos.y + i_attr()->m68 - 5.0f, current.pos.z);
            mChildPID = daObjBuoyflag::Act_c::make_norm(fopAcM_GetID(this), &buoyPos, fopAcM_GetRoomNo(this), &shape_angle);
        } else if (mType == TYPE_METAL_BOX_WITH_SPRING) {
            u32 jumpParams = daObjJump::Act_c::prm_make_b();
            mChildPID = fopAcM_createChild(
                PROC_Obj_Jump, fopAcM_GetID(this),
                jumpParams, &current.pos,
                fopAcM_GetRoomNo(this), &shape_angle
            );
        } else if (mType == TYPE_MIRROR) {
            mChildPID = fopAcM_createChild(
                PROC_Obj_Mmrr, fopAcM_GetID(this),
                0, &current.pos,
                fopAcM_GetRoomNo(this), &shape_angle
            );
        } else if (mType == TYPE_BLACK_BOX_WITH_MKIE) {
            cXyz mkiePos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
            u32 mkieParams = daObjMkie::Act_c::prm_make(prmX_get_evId(), prmZ_get_swSave2_MkieB());
            mChildPID = fopAcM_createChild(
                PROC_Obj_Mkie, fopAcM_GetID(this),
                mkieParams, &mkiePos,
                fopAcM_GetRoomNo(this), &shape_angle
            );
        }
        
        init_mtx();
        mbRollCrash = FALSE;
        mode_wait_init();
        return TRUE;
    }
    
    /* 00002214-000024D4       .text afl_sway__Q212daObjMovebox5Act_cFv */
    void Act_c::afl_sway() {
        f32 f31 = m60C*m60C + m610*m610;
        f32 f30 = i_attr()->m4C*i_attr()->m4C;
        
        int bgcSrcCount;
        BgcSrc_c* bgcSrc;
        // fakematch? a cast here seems necessary to get the bgcSrc to temporarily be placed in r0 and then moved
        bgcSrc = const_cast<BgcSrc_c*>(i_attr()->m9A ? Bgc_c::M_lin20 : Bgc_c::M_lin5);
        bgcSrcCount = i_attr()->m9A ? ARRAY_SIZE(Bgc_c::M_lin20)-2 : ARRAY_SIZE(Bgc_c::M_lin5);
        
        bool touchedFrontBack = mBgc.chk_wall_touch2(this, bgcSrc, bgcSrcCount, M_dir_base[0]) ||
            mBgc.chk_wall_touch2(this, bgcSrc, bgcSrcCount, M_dir_base[2]);
        
        bool touchedLeftRight = mBgc.chk_wall_touch2(this, bgcSrc, bgcSrcCount, M_dir_base[1]) ||
            mBgc.chk_wall_touch2(this, bgcSrc, bgcSrcCount, M_dir_base[3]);
        
        if (f31 > f30) {
            f32 temp = i_attr()->m4C / sqrtf(f31);
            m60C *= temp;
            m610 *= temp;
        }
        
        f32 f5 = -(m618 - m610) * i_attr()->m50;
        f32 f6 = -m620 * i_attr()->m54;
        f32 f1 = -(m614 - m60C) * i_attr()->m50;
        f32 f0 = -m61C * i_attr()->m54;
        m61C += f1 + f0;
        m620 += f5 + f6;
        m614 += m61C;
        m618 += m620;
        
        if (touchedLeftRight) {
            m614 = 0.0f;
        }
        if (touchedFrontBack) {
            m618 = 0.0f;
        }
        
        m60C = 0.0f;
        m610 = 0.0f;
    }
    
    /* 000024D4-00002668       .text check_to_walk__Q212daObjMovebox5Act_cFv */
    int Act_c::check_to_walk() {
        int r30 = -1;
        bool r29 = true;
        
        if (m64A && cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_ON_GROUND_e) && (mType != TYPE_BLACK_BOX_WITH_MKIE || mChildPID == fpcM_ERROR_PROCESS_ID_e)) {
            BOOL temp = cLib_checkBit(mPPLabel, dBgW::PP_UNK2_e);
            BOOL r3 = cLib_checkBit(mPPLabel, dBgW::PP_UNK4_e);
            s16 r0;
            if (temp) {
                if (r3) {
                    r0 = i_attr()->m06;
                } else {
                    r0 = i_attr()->m08;
                }
            } else {
                if (r3) {
                    r0 = i_attr()->m00;
                } else {
                    r0 = i_attr()->m02;
                }
            }
            
            for (int i = 0; i < (int)ARRAY_SIZE(mMomentCnt); i++) {
                if (mMomentCnt[i] >= r0) {
                    const BgcSrc_c* bgcSrc = i_attr()->m9A ? Bgc_c::M_lin20 : Bgc_c::M_lin5;
                    int bgcSrcCount = i_attr()->m9A ? (mType == TYPE_MIRROR ? ARRAY_SIZE(Bgc_c::M_lin20) : ARRAY_SIZE(Bgc_c::M_lin20)-2) : ARRAY_SIZE(Bgc_c::M_lin5);
                    if (!mBgc.chk_wall_pre(this, bgcSrc, bgcSrcCount, M_dir_base[i])) {
                        r30 = i;
                    }
                } else {
                    r29 = false;
                }
            }
        }
        
        if (r29) {
            clr_moment_cnt();
        }
        m64A = false;
        return r30;
    }
    
    /* 00002668-0000268C       .text clr_moment_cnt__Q212daObjMovebox5Act_cFv */
    void Act_c::clr_moment_cnt() {
        for (int i = 0; i < 4; i++) {
            mMomentCnt[i] = 0;
        }
    }
    
    /* 0000268C-00002768       .text chk_appear__Q212daObjMovebox5Act_cCFv */
    bool Act_c::chk_appear() const {
        // Boxes that do not have a path to save their position instead use swSave1 to enable or disable spawning.
        s32 pathId = prmZ_get_pathId();
        int sw = prm_get_swSave1();
        if (pathId != 0xFF || sw == 0xFF) {
            return TRUE;
        }
        
        bool switchIsSet = is_switch1();
        bool switchEnablesSpawn = prm_get_swSave();
        bool shouldAppear = false;
        if ((!switchIsSet && !switchEnablesSpawn) || (switchIsSet && switchEnablesSpawn)) {
            shouldAppear = true;
        }
        return shouldAppear;
    }
    
    /* 00002768-0000290C       .text eff_set_slip_smoke_pos__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_set_slip_smoke_pos() {
        static cXyz base_pos[ARRAY_SIZE(mSmokeCbs)] = {
            cXyz(-0.5f, 0.0f, -0.5f),
            cXyz(0.5f, 0.0f, -0.5f)
        };
        
        s16 angle = home.angle.y + M_dir_base[m634];
        
        f32 scaleMag = i_attr()->mScaleXZ;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(angle);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 10.0f);
        mDoMtx_stack_c::scaleM(scaleMag, scaleMag, scaleMag);
        
        for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
            mDoMtx_stack_c::multVec(&base_pos[i], &mSmokeCbs[i].field_0x20);
            mSmokeCbs[i].field_0x2C.set(0, angle, 0);
        }
    }
    
    /* 0000290C-00002A14       .text eff_smoke_slip_start__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_smoke_slip_start() {
        static cXyz scl(0.6f, 0.6f, 0.6f);
        
        eff_set_slip_smoke_pos();
        
        for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
            JPABaseEmitter* emitter = dComIfGp_particle_setToon(
                0x2022, &mSmokeCbs[i].field_0x20, &mSmokeCbs[i].field_0x2C,
                &scl, 0xB9, &mSmokeCbs[i], fopAcM_GetRoomNo(this)
            );
            if (emitter) {
                emitter->setRate(2.0f);
                emitter->setDirectionalSpeed(15.0f);
                emitter->setSpread(0.15f);
                emitter->setLifeTime(30);
            }
        }
    }
    
    /* 00002A14-00002A74       .text eff_smoke_slip_end__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_smoke_slip_end() {
        for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
            mSmokeCbs[i].end();
        }
    }
    
    /* 00002A74-00002AD4       .text eff_smoke_slip_remove__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_smoke_slip_remove() {
        for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
            mSmokeCbs[i].end();
        }
    }
    
    /* 00002AD4-00002B48       .text mode_wait_init__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_wait_init() {
        speedF = 0.0f;
        gravity = i_attr()->m14;
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_Trans);
        clr_moment_cnt();
        m634 = -1;
        mMode = MODE_WAIT;
    }
    
    /* 00002B48-00002D84       .text mode_wait__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_wait() {
        if (m646 > 0) {
            m646--;
        }
        
        int r31 = check_to_walk();
        
        if (!m64F && cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_ON_GROUND_e)) {
            m64F = true;
            path_save();
        }
        
        daObj::posMoveF_stream(this, NULL, &cXyz::Zero, i_attr()->m18, i_attr()->m1C);
        
        mDoMtx_stack_c::transS(home.pos);
        mDoMtx_stack_c::YrotM(home.angle.y);
        mDoMtx_stack_c::transM(m628 * i_attr()->m0C, 0.0f, m62C * i_attr()->m0C);
        cXyz pos;
        mDoMtx_stack_c::multVec(&cXyz::Zero, &pos);
        current.pos.x = pos.x;
        current.pos.z = pos.z;
        
        if (r31 != -1) {
            m634 = r31;
            eff_smoke_slip_start();
            daPy_getPlayerActorClass()->onPushPullKeep();
            mode_walk_init();
            
            if (cLib_checkBit(mPPLabel, dBgW::PP_UNK2_e)) {
                m644 = i_attr()->m0A;
                m630 = (f32)0x8000 / i_attr()->m0A;
            } else {
                m644 = i_attr()->m04;
                m630 = (f32)0x8000 / i_attr()->m04;
            }
        }
    }
    
    /* 00002D84-00002DA4       .text mode_walk_init__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_walk_init() {
        speedF = 0.0f;
        m64F = false;
        mMode = MODE_WALK;
    }
    
    /* 00002DA4-000031AC       .text mode_walk__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_walk() {
        static cXyz dir_vec[4] = {
            cXyz(0.0f, 0.0f, 1.0f),
            cXyz(1.0f, 0.0f, 0.0f),
            cXyz(0.0f, 0.0f, -1.0f),
            cXyz(-1.0f, 0.0f, 0.0f),
        };
        
        bool r28 = --m644 <= 0;
        f32 temp = (cM_scos(m644 * m630) + 1.0f) * 0.5f;
        mDoMtx_stack_c::transS(home.pos);
        mDoMtx_stack_c::YrotM(home.angle.y);
        mDoMtx_stack_c::transM(
            (m628 + temp * dir_vec[m634].x) * i_attr()->m0C,
            0.0f,
            (m62C + temp * dir_vec[m634].z) * i_attr()->m0C
        );
        cXyz temp2;
        mDoMtx_stack_c::multVec(&cXyz::Zero, &temp2);
        current.pos.x = temp2.x;
        current.pos.z = temp2.z;
        eyePos = current.pos;
        sound_slip();
        
        if (r28) {
            const BgcSrc_c* bgcSrc = i_attr()->m9A ? Bgc_c::M_lin20 : Bgc_c::M_lin5;
            int bgcSrcCount = i_attr()->m9A ? (mType == TYPE_MIRROR ? ARRAY_SIZE(Bgc_c::M_lin20) : ARRAY_SIZE(Bgc_c::M_lin20)-2) : ARRAY_SIZE(Bgc_c::M_lin5);
            if (mBgc.chk_wall_pre(this, bgcSrc, bgcSrcCount, M_dir_base[m634])) {
                sound_limit();
            }
            eff_smoke_slip_end();
        } else {
            eff_set_slip_smoke_pos();
        }
        
        daObj::posMoveF_stream(this, NULL, &cXyz::Zero, i_attr()->m18, i_attr()->m1C);
        current.pos.x = temp2.x;
        current.pos.z = temp2.z;
        
        if (r28) {
            if (m634 == 0) {
                m62C++;
            } else if (m634 == 1) {
                m628++;
            } else if (m634 == 2) {
                m62C--;
            } else if (m634 == 3) {
                m628--;
            }
            daPy_getPlayerActorClass()->offPushPullKeep();
            mode_wait_init();
        }
    }
    
    /* 000031AC-000031D4       .text mode_afl_init__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_afl_init() {
        speedF = 0.0f;
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);
        mMode = MODE_AFLOAT;
    }
    
    /* 000031D4-000033D8       .text mode_afl__Q212daObjMovebox5Act_cFv */
    void Act_c::mode_afl() {
        f32 f1 = current.pos.y - mBgc.mWaterY;
        f32 f0;
        if (f1 >= 0.0f) {
            f0 = 0.0f;
        } else {
            if (f1 <= -i_attr()->m68) {
                f0 = 1.0f;
            } else {
                f1 = -f1;
                f0 = f1 * i_attr()->m6C;
            }
        }
        
        s16 r3 = i_attr()->m38 * (1.0f + cM_rnd());
        m604 += r3;
        gravity = (f0 * i_attr()->m28) + i_attr()->m14 + i_attr()->m34 * cM_ssin(m604) + m608;
        m608 = 0.0f;
        
        afl_sway();
        
        f32 temp3 = 1.0f - f0;
        f32 temp1 = f0*i_attr()->m3C + temp3*i_attr()->m18;
        f32 temp2 = f0*i_attr()->m40 + temp3*i_attr()->m1C;
        
        m624 = mBgc.mWaterY - current.pos.y;
        if (m624 < 0.0f) {
            m624 = 0.0f;
        } else if (m624 > i_attr()->m68) {
            m624 = i_attr()->m68;
        }
        
        daObj::posMoveF_stream(this, NULL, &cXyz::Zero, temp1, temp2);
    }
    
    /* 000033D8-00003450       .text make_item__Q212daObjMovebox5Act_cFv */
    void Act_c::make_item() {
        s32 itemTableNo = prm_get_itemNo();
        s32 itemBitNo = prm_get_itemSave();
        fopAcM_createItemFromTable(&current.pos, itemTableNo, itemBitNo, fopAcM_GetHomeRoomNo(this), 0, &current.angle, 7);
    }
    
    /* 00003450-00003570       .text eff_break__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_break() {
        static cXyz particle_scale(2.0f, 2.0f, 1.0f);
        cXyz particlePos;
        particlePos.set(current.pos.x, current.pos.y + 75.0f, current.pos.z);
        JPABaseEmitter* emitter = dComIfGp_particle_set(
            0x3E6, &particlePos, NULL, NULL, 0xFF, NULL, -1,
            &tevStr.mColorK0, &tevStr.mColorK0, &particle_scale
        );
        if (emitter) {
            emitter->setLifeTime(30);
            emitter->setAwayFromAxisSpeed(30.0f);
        }
        fopAcM_create(PROC_Obj_Eff, 0x5, &particlePos);
        // TODO daObjEff::Act_c::make_woodBox_smoke(cXyz*)
    }
    
    /* 00003570-00003808       .text sound_break__Q212daObjMovebox5Act_cFv */
    void Act_c::sound_break() {
        cXyz centerPos(current.pos.x, current.pos.y + 100.0f, current.pos.z);
        dBgS_ObjGndChk gndChk;
        gndChk.SetPos(&centerPos);
        gndChk.SetActorPid(base.mBsPcId);
        dComIfG_Bgsp()->GroundCross(&gndChk);
        s32 bgIndex = gndChk.GetBgIndex();
        s32 mtrlSndId = 0;
        if (bgIndex >= 0 && bgIndex < 0x100) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(gndChk);
        }
        fopAcM_seStart(this, JA_SE_OBJ_COL_SWC_WODCRL, mtrlSndId);
    }
    
    /* 00003AE0-00003BA4       .text sound_slip__Q212daObjMovebox5Act_cFv */
    void Act_c::sound_slip() {
        s32 mtrlSndId = 0;
        if (mBgc.mMaxGroundIdx >= 0) {
            dBgS_ObjGndChk& gndChk = Bgc_c::M_gnd_work[mBgc.mMaxGroundIdx];
            if (gndChk.GetBgIndex() >= 0 && gndChk.GetBgIndex() < 0x100) {
                mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(gndChk);
            }
        }
        
        mDoAud_seStart(i_attr()->mMoveSE, &eyePos, mtrlSndId, mReverb);
    }
    
    /* 00003BA4-00003C68       .text sound_limit__Q212daObjMovebox5Act_cFv */
    void Act_c::sound_limit() {
        s32 mtrlSndId = 0;
        if (mBgc.mWallIdx >= 0) {
            dBgS_ObjLinChk& linChk = Bgc_c::M_wall_work[mBgc.mWallIdx];
            if (linChk.GetBgIndex() >= 0 && linChk.GetBgIndex() < 0x100) {
                mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(linChk);
            }
        }
        
        mDoAud_seStart(i_attr()->mCantMoveSE, &eyePos, mtrlSndId, mReverb);
    }
    
    /* 00003C68-00003D2C       .text sound_land__Q212daObjMovebox5Act_cFv */
    void Act_c::sound_land() {
        s32 mtrlSndId = 0;
        if (mBgc.mMaxGroundIdx >= 0) {
            dBgS_ObjGndChk& gndChk = Bgc_c::M_gnd_work[mBgc.mMaxGroundIdx];
            if (gndChk.GetBgIndex() >= 0 && gndChk.GetBgIndex() < 0x100) {
                mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(gndChk);
            }
        }
        
        mDoAud_seStart(i_attr()->mNormalFallSE, &eyePos, mtrlSndId, mReverb);
    }
    
    /* 00003D2C-00003D80       .text vib_land__Q212daObjMovebox5Act_cFv */
    void Act_c::vib_land() {
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    }
    
    /* 00003D80-00003E04       .text eff_land_smoke__Q212daObjMovebox5Act_cFv */
    void Act_c::eff_land_smoke() {
        cXyz smokeScale;
        smokeScale.setall(i_attr()->mLandSmokeScale);
        smokeScale *= 5.0f/3.0f;
        fopAcM_create(PROC_Obj_Eff, 0x3, &current.pos, -1, NULL, &smokeScale);
        // TODO daObjEff::Act_c::make_land_smoke(cXyz*, float)
    }
    
    /* 00003E04-000040D0       .text Execute__Q212daObjMovebox5Act_cFPPA3_A4_f */
    BOOL Act_c::Execute(Mtx** pMtx) {
        if (mCyl.ChkTgHit() || mbRollCrash) {
            make_item();
            eff_break();
            sound_break();
            fopAcM_delete(this);
        } else {
            if (cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_JUST_HIT_WATER_e)) {
                mDoAud_seStart(i_attr()->mWaterFallSE, &eyePos, 0, mReverb);
            }
            
            if (mMode == MODE_WAIT) {
                if (cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_IN_WATER_e) && m646 == 0) {
                    if (cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_ON_GROUND_e)) {
                        if (i_attr()->m28 + i_attr()->m14 > 0.0f) {
                            mode_afl_init();
                        }
                    } else {
                        mode_afl_init();
                    }
                }
            } else if (mMode == MODE_AFLOAT && cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_ON_GROUND_e)) {
                mode_wait_init();
                m646 = 20;
            }
            
            mode_proc_call();
            mBgc.proc_vertical(this);
            if (mBgc.mMaxGroundIdx >= 0) {
                tevStr.mRoomNo = current.roomNo;
                tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(Bgc_c::M_gnd_work[mBgc.mMaxGroundIdx]);
            }
            
            if (m648 > 0) {
                m648--;
            } else {
                if (cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_JUST_HIT_GROUND_e)) {
                    sound_land();
                    vib_land();
                    if (!cLib_checkBit(mBgc.mStateFlags, Bgc_c::BgcState_IN_WATER_e)) {
                        eff_land_smoke();
                    }
                }
            }
            
            set_mtx();
            
            if (mType == TYPE_BREAKABLE_WOODEN_CRATE || mType == TYPE_GOLDEN_CRATE) {
                mCyl.MoveCTg(current.pos);
                dComIfG_Ccsp()->Set(&mCyl);
            }
        }
        
        *pMtx = &mMtx;
        return TRUE;
    }
    
    /* 000040D0-00004254       .text Draw__Q212daObjMovebox5Act_cFv */
    BOOL Act_c::Draw() {
        if (mpModel) {
            int tevType = !i_attr()->mbUseBGTevType ? TEV_TYPE_ACTOR : TEV_TYPE_BG0;
            g_env_light.settingTevStruct(tevType, &current.pos, &tevStr);
            g_env_light.setLightTevColorType(mpModel, &tevStr);
            dComIfGd_setListBG();
            mDoExt_modelUpdateDL(mpModel);
            dComIfGd_setList();
        }
        
        if (!i_attr()->mbCastsShadow && mBgc.mMaxGroundIdx >= 0) {
            int temp = mBgc.mMaxGroundIdx;
            f32 groundH = mBgc.mGroundY[temp];
            cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(Bgc_c::M_gnd_work[temp]);
            if (triPla && groundH != -1000000000.0f) {
                dComIfGd_setSimpleShadow(&current.pos, groundH, i_attr()->m10, &triPla->mNormal, shape_angle.y, 1.0f, NULL);
            }
        }
        
        return TRUE;
    }
    
    /* 00004254-000042A0       .text Delete__Q212daObjMovebox5Act_cFv */
    BOOL Act_c::Delete() {
        eff_smoke_slip_remove();
        if (mpBgW) {
            mpBgW->mpRideCb = NULL;
            mpBgW->mpPushPullCb = NULL;
        }
        return TRUE;
    }
    
    namespace {
        /* 000042A0-000044E0       .text Mthd_Create__Q212daObjMovebox29@unnamed@d_a_obj_movebox_cpp@FPv */
        s32 Mthd_Create(void* i_this) {
            return static_cast<Act_c*>(i_this)->Mthd_Create();
        }
        
        /* 000044E0-00004544       .text Mthd_Delete__Q212daObjMovebox29@unnamed@d_a_obj_movebox_cpp@FPv */
        BOOL Mthd_Delete(void* i_this) {
            return static_cast<Act_c*>(i_this)->Mthd_Delete();
        }
        
        /* 00004544-00004564       .text Mthd_Execute__Q212daObjMovebox29@unnamed@d_a_obj_movebox_cpp@FPv */
        BOOL Mthd_Execute(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGExecute();
        }
        
        /* 00004564-00004590       .text Mthd_Draw__Q212daObjMovebox29@unnamed@d_a_obj_movebox_cpp@FPv */
        BOOL Mthd_Draw(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGDraw();
        }
        
        /* 00004590-000045BC       .text Mthd_IsDelete__Q212daObjMovebox29@unnamed@d_a_obj_movebox_cpp@FPv */
        BOOL Mthd_IsDelete(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGIsDelete();
        }
        
        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }
}

actor_process_profile_definition g_profile_Obj_Movebox = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 3,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_Obj_Movebox,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMovebox::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0015,
    /* Actor SubMtd */ &daObjMovebox::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
