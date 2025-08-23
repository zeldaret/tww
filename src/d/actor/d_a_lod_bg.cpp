/**
 * d_a_lod_bg.cpp
 * Background island LOD model actor
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_lod_bg.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_obj_light.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_printf.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include <stdio.h>

const char daLodbg_c::LodAllPath[] = "/res/Stage/sea/LODALL.arc";

daLodbg_c::daLodbg_c() {
    if (sObjectCount == 0) {
        JUT_ASSERT(0x5e, sLocalHeap == NULL);
        sLocalHeap = JKRCreateExpHeap(0x20000, mDoExt_getArchiveHeap(), false);
        JUT_ASSERT(0x60, sLocalHeap != NULL);
    }

    sObjectCount++;
    mExecuteFunc = NULL;
    mModel = NULL;
    mModel2[0] = NULL;
    mModel2[1] = NULL;
    mAlpha = 0;
    mDrawModel2 = false;
    mMountCommand = NULL;
    mArchive = NULL;
    mDataSize = 0;
    mDataSize2 = 0;
    mDataHeap = NULL;
    mDataHeap2 = NULL;
    setExecute(&daLodbg_c::execCreateWait);
    scale.x *= 20000.0f;
    scale.z = scale.x + 20000.0f;
    dKy_tevstr_init(&tevStr, fopAcM_GetParam(this), 0xFF);
}

daLodbg_c::~daLodbg_c() {
    deleteModelData();
    if (--sObjectCount == 0) {
        JUT_ASSERT(0x91, sLocalHeap != NULL);
        JUT_ASSERT(0x92, sLocalHeap->getTotalUsedSize() == 0);
        sLocalHeap->destroy();
        sLocalHeap = NULL;
    }
}

s32 daLodbg_c::getRoomNo() {
    return fopAcM_GetParam(this);
}

/* 0000031C-0000046C       .text deleteModelData__9daLodbg_cFv */
void daLodbg_c::deleteModelData() {
    if (mMountCommand != NULL) {
        OSReport_Warning("LOD読み込み中に削除処理ですか?\n");
        bool sync = mMountCommand->sync();
        mMountCommand->destroy();
        mMountCommand = NULL;
    }
    if (mModelData != NULL) {
        const void* binary = mModelData->getBinary();
        JKRFreeToHeap(NULL, mModelData);
        mModelData = NULL;
        if (binary != NULL)
            JKRFreeToHeap(NULL, (void*)binary);
    }
    if (mDataHeap != NULL) {
        mDataHeap->destroy();
        JKRFreeToHeap(NULL, mDataHeap);
        mDataHeap = NULL;
    }
    if (mModelData2 != NULL) {
        const void* binary = mModelData2->getBinary();
        JKRFreeToHeap(NULL, mModelData2);
        mModelData2 = NULL;
        if (binary != NULL)
            JKRFreeToHeap(NULL, (void*)binary);
    }
    if (mDataHeap2 != NULL) {
        mDataHeap2->destroy();
        JKRFreeToHeap(NULL, mDataHeap2);
        mDataHeap2 = NULL;
    }
    if (mArchive != NULL) {
        mArchive->unmount();
        mArchive = NULL;
    }
}

/* 0000046C-00000738       .text loadModelData__9daLodbg_cFPCcRP12J3DModelDataRP12JKRSolidHeapRUl */
BOOL daLodbg_c::loadModelData(const char* filename, J3DModelData*& mModelData, JKRSolidHeap*& mDataHeap, u32& mDataSize) {
    /* Nonmatching - regalloc */
    void* bin;
    bool success;
    void* dst;
    s32 resSize;
    JKRHeap* oldHeap;
    s32 size;

    JUT_ASSERT(0x124, mModelData == NULL);
    bin = mArchive->getResource(filename);
    if (bin == NULL)
        return FALSE;

    resSize = mArchive->getExpandedResSize(bin);
    JUT_ASSERT(0x12a, resSize != -1);
    success = mArchive->detachResource(bin);
    JUT_ASSERT(0x12f, success);

    if (sLocalHeap != NULL) {
        dst = sLocalHeap->alloc(resSize, 0x20);
        if (dst != NULL) {
            memcpy(dst, bin, resSize);
            JKRFreeToHeap(NULL, bin);
            bin = dst;
        }
    }

    JUT_ASSERT(0x13d, mDataHeap == NULL);
    mDataHeap = JKRSolidHeap::create(-1, sLocalHeap, false);
    if (mDataHeap != NULL && mDataHeap->getTotalFreeSize() < 0x2000) {
        mDataHeap->destroy();
        mDataHeap = NULL;
    }
    if (mDataHeap == NULL)
        mDataHeap = JKRSolidHeap::create(-1, mDoExt_getArchiveHeap(), false);
    oldHeap = JKRGetCurrentHeap();
    mDataHeap->becomeCurrentHeap();
    mModelData = J3DModelLoaderDataBase::loadBinaryDisplayList(bin, 0x2020);
    if (mModelData == NULL) {
        JKRFreeToHeap(NULL, bin);
        bin = NULL;
    }
    oldHeap->becomeCurrentHeap();
    size = mDataHeap->adjustSize();
    JUT_ASSERT(0x15f, size >= 0);

    mDataSize = size;
    if (bin != NULL)
        return TRUE;
    else
        return FALSE;
}

/* 00000738-000008B8       .text createModelData__9daLodbg_cFv */
BOOL daLodbg_c::createModelData() {
    static char resPath[32];
    JUT_ASSERT(0x177, mModelData == NULL);
    JUT_ASSERT(0x178, mModelData2 == NULL);
    sprintf(resPath, "/lod%02d/bdl/model.bdl", fopAcM_GetParam(this));
    if (!loadModelData(resPath, mModelData, mDataHeap, mDataSize))
        return FALSE;

    if (getRoomNo() == dIsleRoom_WindfallIsland_e) {
        if (!loadModelData("/lod11/bdl/shikari.bdl", mModelData2, mDataHeap2, mDataSize2))
            return FALSE;
    }
#if VERSION > VERSION_JPN
    else if (getRoomNo() == dIsleRoom_ForsakenFortress_e && !dComIfGs_isEventBit(0x1820)) {
        if (!loadModelData("/lod01/bdl/model1.bdl", mModelData2, mDataHeap2, mDataSize2))
            return FALSE;
    }
#endif

    return TRUE;
}

/* 000008B8-00000A38       .text createHeap__9daLodbg_cFv */
BOOL daLodbg_c::createHeap() {
    JUT_ASSERT(VERSION_SELECT(419, 419, 436, 436), mModelData != NULL);
    mModel = mDoExt_J3DModel__create(mModelData, 0x80000, 0x11000022);
    if (mModel == NULL)
        return FALSE;
    if (getRoomNo() == dIsleRoom_WindfallIsland_e) {
        JUT_ASSERT(VERSION_SELECT(430, 430, 447, 447), mModelData2 != NULL);
        for (s32 i = 0; i < 2; i++) {
            mModel2[i] = mDoExt_J3DModel__create(mModelData2, 0x80000, 0x11000022);
            if (mModel2[i] == NULL) {
                mModel2[0] = NULL;
                mModel = NULL;
                return FALSE;
            }
        }
    }
#if VERSION > VERSION_JPN
    else if (getRoomNo() == dIsleRoom_ForsakenFortress_e && mModelData2 != NULL) {
        mModel2[0] = mDoExt_J3DModel__create(mModelData2, 0x80000, 0x11000022);
        if (mModel2[0] == NULL) {
            mModel = NULL;
            return FALSE;
        }
    }
#endif

    return TRUE;
}

/* 00000A38-00000A58       .text createHeapCallBack__FP10fopAc_ac_c */
static BOOL createHeapCallBack(fopAc_ac_c* i_ac) {
    return ((daLodbg_c*)i_ac)->createHeap();
}

/* 00000A58-00000B4C       .text execCreateWait__9daLodbg_cFv */
BOOL daLodbg_c::execCreateWait() {
    f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    if (dist > scale.x)
        return TRUE;

    JUT_ASSERT(VERSION_SELECT(474, 474, 503, 503), mMountCommand == NULL);
    mMountCommand = mDoDvdThd_mountXArchive_c::create(LodAllPath, 0, JKRArchive::MOUNT_ARAM);
    if (mMountCommand == NULL) {
        JUT_WARN(VERSION_SELECT(478, 478, 507, 507), "LODALL archive nothing !! <LODALL.arc>");
        return FALSE;
    }

    setExecute(&daLodbg_c::execReadWait);
    return TRUE;
}

/* 00000B4C-00000D68       .text execReadWait__9daLodbg_cFv */
BOOL daLodbg_c::execReadWait() {
    if (!mMountCommand->sync())
        return TRUE;

    JUT_ASSERT(VERSION_SELECT(506, 506, 535, 535), mArchive == NULL);
    mArchive = mMountCommand->getArchive();
    delete mMountCommand;
    mMountCommand = NULL;

    if (mArchive == NULL) {
        setExecute(&daLodbg_c::execDeleteWait);
        return TRUE;
    }

    createModelData();
    JUT_ASSERT(VERSION_SELECT(542, 542, 571, 571), mModel == NULL);
    JUT_ASSERT(VERSION_SELECT(543, 543, 572, 572), mModel2[0] == NULL);
    JUT_ASSERT(VERSION_SELECT(544, 544, 573, 573), mModel2[1] == NULL);

    if (!fopAcM_entrySolidHeap(this, createHeapCallBack, 0)) {
        mModel = NULL;
        mModel2[0] = NULL;
        mModel2[1] = NULL;
        setExecute(&daLodbg_c::execDeleteWait);
        return TRUE;
    }

    fopAcM_SetMtx(this, mModel->getBaseTRMtx());
    setExecute(&daLodbg_c::execDeleteWait);
    return TRUE;
}

/* 00000D68-00000FC4       .text execDeleteWait__9daLodbg_cFv */
BOOL daLodbg_c::execDeleteWait() {
    if (heap != NULL) {
#if VERSION != VERSION_PAL
        f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
#else
        // TODO: inline for this?
        cXyz delta = g_dComIfG_gameInfo.play.mCurrentView->mLookat.mEye - current.pos;
        f32 dist = delta.absXZ() + 700.0f;
#endif
        if (dist < scale.z) {
            s32 roomNo = getRoomNo();
            bool disp = dist > scale.x || (dComIfGp_roomControl_checkStatusFlag(roomNo, 0x01) && !dComIfGp_roomControl_checkStatusFlag(roomNo, 0x04)); // inline?
            cLib_chaseUC(&mAlpha, disp ? 0 : 255, 16);
            if (mAlpha != 0) {
                f32 y = (150000.0f - dist);

                if (y >= 0.0f)
                    y = 0.0f;
                else
                    y *= 0.1f;

                mDoMtx_stack_c::transS(current.pos.x, current.pos.y + y, current.pos.z);
                mDoMtx_stack_c::YrotM(shape_angle.y);
                mModel->setBaseTRMtx(mDoMtx_stack_c::get());
#if VERSION <= VERSION_JPN
                mModel->setBaseTRMtx(mDoMtx_stack_c::get());
#endif
                if (mModel2[0] != NULL) {
#if VERSION > VERSION_JPN
                    if (roomNo == dIsleRoom_WindfallIsland_e) {
#endif
                        mDrawModel2 = daObjLight::Act_c::renew_light_angle();
                        if (mDrawModel2) {
                            mDoMtx_stack_c::transS(630.46338f, y + 4044.508f, -202724.0f);
                            mDoMtx_stack_c::YrotM(daObjLight::Act_c::get_light_angle());
                            mModel2[0]->setBaseTRMtx(mDoMtx_stack_c::get());
                            mDoMtx_stack_c::YrotM(-0x8000);
                            mModel2[1]->setBaseTRMtx(mDoMtx_stack_c::get());
                        }
#if VERSION > VERSION_JPN
                    }
                    else if (roomNo == dIsleRoom_ForsakenFortress_e) {
                        mModel2[0]->setBaseTRMtx(mDoMtx_stack_c::get());
                        mDrawModel2 = true;
                    }
#endif
                }
            }

            return TRUE;
        }
    }

    mModel = NULL;
    mModel2[0] = NULL;
    mModel2[1] = NULL;
    mAlpha = 0;
    fopAcM_DeleteHeap(this);
    deleteModelData();
    setExecute(&daLodbg_c::execCreateWait);
    return TRUE;
}

/* 00000FC4-00001274       .text draw__9daLodbg_cFv */
BOOL daLodbg_c::draw() {
    if (heap == NULL || mAlpha == 0)
        return TRUE;

    s32 roomNo = getRoomNo();
    if (roomNo == dIsleRoom_ToweroftheGods_e && !dComIfGs_isEventBit(0x1e40))
        return TRUE;

    g_env_light.settingTevStruct(TEV_TYPE_BG0, NULL, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    J3DModelData* modelData = mModel->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++)
        modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = mAlpha;
    mDoLib_clipper::changeFar(500000.0f);
    mModel->calc();
    mDoLib_clipper::clip(mModel);
    mDoExt_modelEntryDL(mModel);

    if (mModel2[0] != NULL && mDrawModel2) {
#if VERSION > VERSION_JPN
        if (roomNo == dIsleRoom_WindfallIsland_e) {
#endif
            J3DModelData* modelData = mModel2[0]->getModelData();
            for (u16 i = 0; i < modelData->getMaterialNum(); i++)
                modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = mAlpha;

            for (s32 i = 0; i < 2; i++) {
                mModel2[i]->calc();
                mDoLib_clipper::clip(mModel2[i]);
                mDoExt_modelEntryDL(mModel2[i]);
            }
#if VERSION > VERSION_JPN
        } else if (roomNo == dIsleRoom_ForsakenFortress_e) {
            g_env_light.setLightTevColorType(mModel2[0], &tevStr);
            J3DModelData* modelData = mModel2[0]->getModelData(); // ??? was this supposed to modify mModel2?
            for (u16 i = 0; i < modelData->getMaterialNum(); i++)
                modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = mAlpha;
            mModel2[0]->calc();
            mDoLib_clipper::clip(mModel2[0]);
            mDoExt_modelEntryDL(mModel2[0]);
        }
#endif
    }

    mDoLib_clipper::resetFar();
    return TRUE;
}

BOOL daLodbg_c::execute() {
    return (this->*this->mExecuteFunc)();
}

/* 00001274-00001294       .text daLodbg_Draw__FP9daLodbg_c */
static BOOL daLodbg_Draw(daLodbg_c* i_this) {
    return i_this->draw();
}

/* 00001294-000012BC       .text daLodbg_Execute__FP9daLodbg_c */
static BOOL daLodbg_Execute(daLodbg_c* i_this) {
    return i_this->execute();
}

/* 000012BC-000012C4       .text daLodbg_IsDelete__FP9daLodbg_c */
static BOOL daLodbg_IsDelete(daLodbg_c* i_this) {
    return TRUE;
}

/* 000012C4-000012EC       .text daLodbg_Delete__FP9daLodbg_c */
static BOOL daLodbg_Delete(daLodbg_c* i_this) {
    i_this->~daLodbg_c();
    return TRUE;
}

/* 000012EC-0000133C       .text daLodbg_Create__FP10fopAc_ac_c */
static cPhs_State daLodbg_Create(fopAc_ac_c* i_ac) {
    daLodbg_c* i_this = (daLodbg_c*)i_ac;
    fopAcM_SetupActor(i_this, daLodbg_c);
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daLodbg_Method = {
    (process_method_func)daLodbg_Create,
    (process_method_func)daLodbg_Delete,
    (process_method_func)daLodbg_Execute,
    (process_method_func)daLodbg_IsDelete,
    (process_method_func)daLodbg_Draw,
};

actor_process_profile_definition g_profile_LODBG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_LODBG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daLodbg_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_LODBG,
    /* Actor SubMtd */ &l_daLodbg_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
