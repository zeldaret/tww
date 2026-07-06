#include "d/dolzel.h" // IWYU pragma: keep
#include "f_op/f_op_msg_mng.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JUtility/JUTDataHeader.h"
#include "d/d_meter.h"
#if VERSION <= VERSION_JPN
#include "d/d_s_play.h"
#endif
#include "f_op/f_op_scene_mng.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_layer_iter.h"
#include "f_pc/f_pc_searcher.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_npc_bs1.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JUtility/JUTFont.h"
#include "SSystem/SComponent/c_malloc.h"
#include "m_Do/m_Do_controller_pad.h"
#include <stdio.h>

STControl stick;

fpc_ProcID i_msgID = fpcM_ERROR_PROCESS_ID_e;

struct mesg_header : JUTDataFileHeader {
    // first block is mesg_info
};

struct mesg_info : JUTDataBlockHeader {
    /* 0x08 */ u16 mNumEntry;
    /* 0x0A */ u16 mEntrySize;
    /* 0x0C */ u16 mGroupID;
    /* 0x10 */ u8 mColor;
    /* 0x14 */ JMSMesgEntry_c mEntries[];
};

struct mesg_data : JUTDataBlockHeader {
    char mData[];
};

static bool pushButton;
static bool pushButton2;
static bool demoFlag;
static bool tactFlag;
static bool nextMsg;

static struct {
    u8 itemNo;
    const char* filename;
} itemicon[] = {
    /* 0x00 */ {dItemNo_TELESCOPE_e, "telescope.bti"},
    /* 0x01 */ {dItemNo_SAIL_e, "sail_00.bti"},
    /* 0x02 */ {dItemNo_WIND_WAKER_e, "baton.bti"},
    /* 0x03 */ {dItemNo_GRAPPLING_HOOK_e, "rope.bti"},
    /* 0x04 */ {dItemNo_SPOILS_BAG_e, "coverofbeast.bti"},
    /* 0x05 */ {dItemNo_BOOMERANG_e, "boomerang.bti"},
    /* 0x06 */ {dItemNo_DEKU_LEAF_e, "fan.bti"},
    /* 0x07 */ {dItemNo_TINGLE_TUNER_e, "whistle.bti"},
    /* 0x08 */ {dItemNo_PICTO_BOX_e, "camera.bti"},
    /* 0x09 */ {dItemNo_IRON_BOOTS_e, "boots_00.bti"},
    /* 0x0A */ {dItemNo_MAGIC_ARMOR_e, "shield_02.bti"},
    /* 0x0B */ {dItemNo_BAIT_BAG_e, "coverofbait.bti"},
    /* 0x0C */ {dItemNo_BOW_e, "bow_01.bti"},
    /* 0x0D */ {dItemNo_BOMB_BAG_e, "bomb_00.bti"},
    /* 0x0E */ {dItemNo_EMPTY_BOTTLE_e, "bottle_00.bti"},
    /* 0x0F */ {dItemNo_RED_POTION_e, "bottle_01.bti"},
    /* 0x10 */ {dItemNo_GREEN_POTION_e, "bottle_02.bti"},
    /* 0x11 */ {dItemNo_BLUE_POTION_e, "bottle_03.bti"},
    /* 0x12 */ {dItemNo_DELIVERY_BAG_e, "delivery.bti"},
    /* 0x13 */ {dItemNo_HOOKSHOT_e, "hookshot.bti"},
    /* 0x14 */ {dItemNo_SKULL_HAMMER_e, "hammer_01.bti"},

    /* 0x15 */ {dItemNo_MAGIC_ARMOR_e, "shield_02.bti"},
    /* 0x16 */ {dItemNo_MAGIC_ARMOR_e, "shield_02.bti"},
    /* 0x17 */ {dItemNo_MAGIC_ARMOR_e, "shield_02.bti"},

    /* 0x18 */ {dItemNo_SKULL_NECKLACE_e, "beast_01.bti"},
    /* 0x19 */ {dItemNo_BOKOBABA_SEED_e, "beast_02.bti"},
    /* 0x1A */ {dItemNo_GOLDEN_FEATHER_e, "beast_03.bti"},
    /* 0x1B */ {dItemNo_KNIGHTS_CREST_e, "beast_04.bti"},
    /* 0x1C */ {dItemNo_RED_JELLY_e, "beast_05.bti"},
    /* 0x1D */ {dItemNo_GREEN_JELLY_e, "beast_06.bti"},
    /* 0x1E */ {dItemNo_BLUE_JELLY_e, "beast_07.bti"},
    /* 0x1F */ {dItemNo_JOY_PENDANT_e, "beast_08.bti"},

    /* 0x20 */ {dItemNo_NONE_e, "beast_09.bti"},
    /* 0x21 */ {dItemNo_NONE_e, "beast_10.bti"},
    /* 0x22 */ {dItemNo_NONE_e, "beast_11.bti"},
    /* 0x23 */ {dItemNo_NONE_e, "beast_12.bti"},

    /* 0x24 */ {dItemNo_HYOI_PEAR_e, "beast_02.bti"},
    /* 0x25 */ {dItemNo_BIRD_BAIT_5_e, "beast_02.bti"},
    /* 0x26 */ {dItemNo_NONE_e, "beast_03.bti"},
    /* 0x27 */ {dItemNo_NONE_e, "beast_04.bti"},
    /* 0x28 */ {dItemNo_NONE_e, "beast_05.bti"},
    /* 0x29 */ {dItemNo_NONE_e, "beast_06.bti"},
    /* 0x2A */ {dItemNo_NONE_e, "beast_07.bti"},
    /* 0x2B */ {dItemNo_NONE_e, "beast_08.bti"},

    /* 0x2C */ {dItemNo_NONE_e, "beast_09.bti"},
    /* 0x2D */ {dItemNo_NONE_e, "beast_10.bti"},
    /* 0x2E */ {dItemNo_NONE_e, "beast_11.bti"},
    /* 0x2F */ {dItemNo_NONE_e, "beast_12.bti"},

    /* 0x30 */ {dItemNo_TOWN_FLOWER_e, "beast_02.bti"},
    /* 0x31 */ {dItemNo_SEA_FLOWER_e, "beast_02.bti"},
    /* 0x32 */ {dItemNo_EXOTIC_FLOWER_e, "beast_03.bti"},
    /* 0x33 */ {dItemNo_HEROS_FLAG_e, "beast_04.bti"},
    /* 0x34 */ {dItemNo_BIG_CATCH_FLAG_e, "beast_05.bti"},
    /* 0x35 */ {dItemNo_BIG_SALE_FLAG_e, "beast_06.bti"},
    /* 0x36 */ {dItemNo_PINWHEEL_e, "beast_07.bti"},
    /* 0x37 */ {dItemNo_SICKLE_MOON_FLAG_e, "beast_08.bti"},

    /* 0x38 */ {dItemNo_SKULL_TOWER_IDOL_e, "beast_09.bti"},
    /* 0x39 */ {dItemNo_FOUNTAIN_IDOL_e, "beast_10.bti"},
    /* 0x3A */ {dItemNo_POSTMAN_STATUE_e, "beast_11.bti"},
    /* 0x3B */ {dItemNo_SHOP_GURU_STATUE_e, "beast_12.bti"},
};

u16 zfont[][2] = {
    0x8340, 0x84a4, 0x8341, 0x84a5, 0x8342, 0x84a6, 0x8343, 0x84a7, 0x8344, 0x84a8, 0x8345, 0x84a9, 0x8346, 0x84aa, 0x8347, 0x84ab, 0x8348, 0x84ac,
    0x8349, 0x84ad, 0x834a, 0x84ae, 0x834b, 0x84af, 0x834c, 0x84b0, 0x834d, 0x84b1, 0x834e, 0x84b2, 0x834f, 0x84b3, 0x8350, 0x84b4, 0x8351, 0x84b5,
    0x8352, 0x84b6, 0x8353, 0x84b7, 0x8354, 0x84b8, 0x8355, 0x84b9, 0x8356, 0x84ba, 0x8357, 0x84bb, 0x8358, 0x84bc, 0x8359, 0x84bd, 0x835a, 0x84be,
    0x835b, 0x8740, 0x835c, 0x8741, 0x835d, 0x8742, 0x835e, 0x8743, 0x835f, 0x8744, 0x8360, 0x8745, 0x8361, 0x8746, 0x8362, 0x8747, 0x8363, 0x8748,
    0x8364, 0x8749, 0x8365, 0x874a, 0x8366, 0x874b, 0x8367, 0x874c, 0x8368, 0x874d, 0x8369, 0x874e, 0x836a, 0x874f, 0x836b, 0x8750, 0x836c, 0x8751,
    0x836d, 0x8752, 0x836e, 0x8753, 0x836f, 0x8754, 0x8370, 0x8755, 0x8371, 0x8756, 0x8372, 0x8757, 0x8373, 0x8758, 0x8374, 0x8759, 0x8375, 0x875a,
    0x8376, 0x875b, 0x8377, 0x875c, 0x8378, 0x875d, 0x8379, 0x875f, 0x837a, 0x8760, 0x837b, 0x8761, 0x837c, 0x8762, 0x837d, 0x8763, 0x837e, 0x8764,
    0x8380, 0x8765, 0x8381, 0x8766, 0x8382, 0x8767, 0x8383, 0x8768, 0x8384, 0x8769, 0x8385, 0x876a, 0x8386, 0x876b, 0x8387, 0x876c, 0x8388, 0x876d,
    0x8389, 0x876e, 0x838a, 0x876f, 0x838b, 0x8770, 0x838c, 0x8771, 0x838d, 0x8772, 0x838e, 0x8773, 0x838f, 0x8774, 0x8390, 0x8775, 0x8391, 0x877e,
    0x8392, 0x8780, 0x8393, 0x8781, 0x824f, 0x8782, 0x8250, 0x8783, 0x8251, 0x8784, 0x8252, 0x8785, 0x8253, 0x8786, 0x8254, 0x8787, 0x8255, 0x8788,
    0x8256, 0x8789, 0x8257, 0x878a, 0x8258, 0x878b, 0x8141, 0x878c, 0x815b, 0x878d, 0x8175, 0x878e, 0x8176, 0x878f,
};

struct fopMsgM_pane_alpha_class;

/* 8002ABB4-8002AC1C       .text drawSelf__9MyPictureFff */
void MyPicture::drawSelf(f32 i_posx, f32 i_posy) {
    Mtx mtx;
    MTXIdentity(mtx);
    drawSelf(i_posx, i_posy, &mtx);
}

/* 8002AC1C-8002AC90       .text drawSelf__9MyPictureFffPA3_A4_f */
void MyPicture::drawSelf(f32 i_posx, f32 i_posy, Mtx* i_mtx) {
    if (mpTexture[0]) {
        drawFullSet2(mGlobalBounds.i.x + i_posx, mGlobalBounds.i.y + i_posy, mBounds.getWidth(), mBounds.getHeight(), J2DBinding(mBinding), getMirror(), isTumble(), i_mtx);
    }
}

/* 8002AC90-8002AD4C       .text drawFullSet2__9MyPictureFffff10J2DBinding9J2DMirrorbPA3_A4_f */
void MyPicture::drawFullSet2(f32 i_posx, f32 i_posy, f32 i_width, f32 i_height, J2DBinding i_binding, J2DMirror i_mirror, bool i_tumble, Mtx* i_mtx) {
    f32 s0, t0, s1, t1;
    s0 = m124;
    s1 = m12C;
    t0 = m128;
    t1 = m130;

    if (i_mirror & J2DMirror_X) {
        f32 tmp = s0;
        s0 = s1;
        s1 = tmp;
    }
    if (i_mirror & J2DMirror_Y) {
        f32 tmp = t0;
        t0 = t1;
        t1 = tmp;
    }

    if (m134) {
        if (!i_tumble) {
            drawTexCoord(0.0f, 0.0f, i_width, i_height, s0, t0, s1, t0, s0, t1, s1, t1, i_mtx);
        } else {
            drawTexCoord(0.0f, 0.0f, i_width, i_height, s0, t1, s0, t0, s1, t1, s1, t0, i_mtx);
        }
    } else {
        drawFullSet(i_posx, i_posy, i_width, i_height, i_binding, i_mirror, i_tumble, i_mtx);
    }
}

#if VERSION >= VERSION_USA
/* 8002AD4C-8002AE28       .text fopMsgM_hyrule_language_check__FUl */
bool fopMsgM_hyrule_language_check(u32 i_msgNo) {
    if (dComIfGs_getClearCount() != 0) {
        return false;
    }

    switch (i_msgNo) {
        case 0xD49:
        case 0xD4B:
        case 0xD4D:
        case 0xD4F:
        case 0xD51:
        case 0xD53:
        case 0xD54:
        case 0xD55:
        case 0xD57:
        case 0xD59:
        case 0x1178:
        case 0x117A:
        case 0x1389:
        case 0x138A:
        case 0x196E:
            return true;
        default:
            break;
    }

    return false;
}
#endif

/* 8002AE28-8002AED4       .text fopMsgM_setStageLayer__FPv */
s32 fopMsgM_setStageLayer(void* i_proc) {
    scene_class* stageProc = fopScnM_SearchByID(dStage_roomControl_c::getProcID());
    JUT_ASSERT(VERSION_SELECT(0x15C, 0x15C, 0x189, 0x189), stageProc != NULL);
    u32 layer = fpcM_LayerID(stageProc);
    return fpcM_ChangeLayerID(i_proc, layer);
}

/* 8002AED4-8002AEF4       .text fopMsgM_SearchByID__FUi */
msg_class* fopMsgM_SearchByID(fpc_ProcID i_pid) {
    return (msg_class*)fpcEx_SearchByID(i_pid);
}

/* 8002AEF4-8002AF24       .text fopMsgM_SearchByName__Fs */
msg_class* fopMsgM_SearchByName(s16 i_name) {
    return (msg_class*)fpcLyIt_AllJudge(fpcSch_JudgeForPName, &i_name);
}

/* 8002AF24-8002AF44       .text fopMsgM_IsExecuting__FUi */
BOOL fopMsgM_IsExecuting(fpc_ProcID i_pid) {
    return fpcEx_IsExist(i_pid);
}

/* 8002AF44-8002AF4C       .text fopMsgM_GetAppend__FPv */
fopMsg_prm_class* fopMsgM_GetAppend(void* i_proc) {
    return (fopMsg_prm_class*)fpcM_GetAppend(i_proc);
}

/* 8002AF4C-8002AF6C       .text fopMsgM_Delete__FPv */
void fopMsgM_Delete(void* i_proc) {
    fpcM_Delete(i_proc);
}

/* 8002AF6C-8002B030       .text createAppend__FP10fopAc_ac_cP4cXyzPUlPUlUi */
fopMsg_prm_class* createAppend(fopAc_ac_c* i_actor, cXyz* i_pos, u32* i_msgNo, u32* p4, uint p5) {
    fopMsg_prm_class* params = (fopMsg_prm_class*)cMl::memalignB(-4, sizeof(fopMsg_prm_class));
    if (params == NULL)
        return NULL;

    params->mpActor = i_actor;
    if (i_msgNo != NULL)
        params->mMsgNo = *i_msgNo;
    if (p4 != NULL)
        params->field_0x14 = *p4;

    if (i_pos != NULL) {
        params->mPos = *i_pos;
    } else {
        cXyz zero;
        zero.setall(0.0f);
        params->mPos = zero;
    }
    params->field_0x18 = p5;

    return params;
}

struct fopMsg_prm_MGameTerm : public fopMsg_prm_class {
    u32 field_0x1C;
    u32 field_0x20;
    u16 field_0x24;
    u16 field_0x26;
}; // Size: 0x28

/* 8002B030-8002B0CC       .text createMGameTermAppend__FssiiUi */
fopMsg_prm_MGameTerm* createMGameTermAppend(s16 param_1, s16 param_2, int param_3, int param_4, uint param_5) {
    fopMsg_prm_MGameTerm* req = (fopMsg_prm_MGameTerm*)cMl::memalignB(-4, sizeof(fopMsg_prm_MGameTerm));
    if (req == NULL) {
        return NULL;
    }

    req->mpActor = NULL;
    req->mMsgNo = 0;
    req->field_0x14 = 0;
    cXyz temp(0.0f, 0.0f, 0.0f);
    req->mPos = temp;
    req->field_0x18 = param_5;
    req->field_0x24 = param_1;
    req->field_0x26 = param_2;
    req->field_0x1C = param_3;
    req->field_0x20 = param_4;

    return req;
}

/* 8002B0CC-8002B1C8       .text createTimerAppend__FiUsUcUcffffUi */
fopMsg_prm_timer* createTimerAppend(int i_mode, u16 i_limitTimeMs, u8 i_showType, u8 i_iconType, f32 i_posX, f32 i_posY, f32 i_rupeePosX, f32 i_rupeePosY, uint param_9) {
    fopMsg_prm_timer* req = (fopMsg_prm_timer*)cMl::memalignB(-4, sizeof(fopMsg_prm_timer));
    if (req == NULL) {
        return NULL;
    }

    req->mpActor = NULL;
    req->mMsgNo = 0;
    req->field_0x14 = 0;
    cXyz temp(0.0f, 0.0f, 0.0f);
    req->mPos = temp;
    req->field_0x18 = param_9;
    req->mTimerMode = i_mode;
    req->mLimitTimeMs = i_limitTimeMs;
    req->mShowType = i_showType;
    req->mIconType = i_iconType;
    req->mTimerPos.x = i_posX;
    req->mTimerPos.y = i_posY;
    req->mRupeePos.x = i_rupeePosX;
    req->mRupeePos.y = i_rupeePosY;

    return req;
}

/* 8002B1C8-8002B23C       .text fopMsgM_create__FsP10fopAc_ac_cP4cXyzPUlPUlPFPv_i */
fpc_ProcID fopMsgM_create(s16 i_procName, fopAc_ac_c* i_actor, cXyz* i_pos, u32* i_msgNo, u32* param_5, fopMsgCreateFunc i_createFunc) {
    fopMsg_prm_class* appen = createAppend(i_actor, i_pos, i_msgNo, param_5, -1);
    if (appen == NULL) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    return fpcSCtRq_Request(fpcLy_CurrentLayer(), i_procName, (stdCreateFunc)i_createFunc, NULL, appen);
}

/* 8002B23C-8002B2B0       .text fop_MGameTerm_create__FsssiiPFPv_i */
fpc_ProcID fop_MGameTerm_create(s16 i_procName, s16 param_2, s16 param_3, int param_4, int param_5, fopMsgCreateFunc i_createFunc) {
    fopMsg_prm_MGameTerm* appen = createMGameTermAppend(param_2, param_3, param_4, param_5, -1);
    if (appen == NULL) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    return fpcSCtRq_Request(fpcLy_CurrentLayer(), i_procName, (stdCreateFunc)i_createFunc, NULL, appen);
}

/* 8002B2B0-8002B324       .text fop_Timer_create__FsUcUsUcUcffffPFPv_i */
fpc_ProcID fop_Timer_create(s16 i_procName, u8 i_mode, u16 i_limitTimeMs, u8 i_showType, u8 i_iconType, f32 i_posX, f32 i_posY, f32 i_rupeePosX, f32 i_rupeePosY, fopMsgCreateFunc i_createFunc) {
    fopMsg_prm_timer* appen = createTimerAppend(i_mode, i_limitTimeMs, i_showType, i_iconType, i_posX, i_posY, i_rupeePosX, i_rupeePosY, -1);
    if (appen == NULL) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    return fpcSCtRq_Request(fpcLy_CurrentLayer(), i_procName, (stdCreateFunc)i_createFunc, NULL, appen);
}

/* 8002B324-8002B520       .text fopMsgM_messageTypeSelect__FP10fopAc_ac_cP4cXyzPUlPUl */
fpc_ProcID fopMsgM_messageTypeSelect(fopAc_ac_c* i_actor, cXyz* i_pos, u32* i_msgNo, u32* param_4) {
    fopMsgM_msgGet_c msgGet;
    msgGet.mMsgIdx = 0;
    msgGet.mGroupID = 0;
    msgGet.mMsgNo = 0;
    msgGet.mResMsgNo = 0;

    fpc_ProcID pcId;
    if (*i_msgNo >> 0x10 == 0x63) {
        pcId = fopMsgM_create(fpcNm_SCP_e, i_actor, i_pos, i_msgNo, param_4, NULL);
    } else if (*i_msgNo >> 0x10 == 0x59) {
        pcId = fopMsgM_create(fpcNm_PB_e, i_actor, i_pos, i_msgNo, param_4, NULL);
    } else {
        mesg_header* header = msgGet.getMesgHeader(*i_msgNo);
        if (header != NULL) {
            if (msgGet.getMessage(header) != NULL) {
                const JMSMesgEntry_c& entry = msgGet.getMesgEntry(header);
                u16 price = entry.mItemPrice;
                u16 type = entry.mTextboxType;
                dComIfGp_setMesgAnimeAttrInfo(entry.mInitialAnimation);
                dComIfGp_setMesgCameraAttrInfo(entry.mInitialCamera);
                dComIfGp_setMessageRupee(price);

                if (type == 2 || type == 6 || type == 7) {
                    pcId = fopMsgM_create(fpcNm_MSG2_e, i_actor, i_pos, i_msgNo, param_4, NULL);
                } else {
                    pcId = fopMsgM_create(fpcNm_MSG_e, i_actor, i_pos, i_msgNo, param_4, NULL);
                }
            } else {
                *i_msgNo = 1;
                *param_4 = *i_msgNo;
                pcId = fopMsgM_create(fpcNm_MSG_e, i_actor, i_pos, i_msgNo, param_4, NULL);
            }
        } else {
            *i_msgNo = 1;
            *param_4 = *i_msgNo;
            pcId = fopMsgM_create(fpcNm_MSG_e, i_actor, i_pos, i_msgNo, param_4, NULL);
        }

        JKRFileLoader::removeResource(header, NULL);
    }

    return pcId;
}

/* 8002B568-8002B634       .text fopMsgM_searchMessageNumber__FUl */
u32 fopMsgM_searchMessageNumber(u32 i_msgNo) {
    fopMsgM_msgGet_c msgGet;
    msgGet.mMsgIdx = 0;
    msgGet.mGroupID = 0;
    msgGet.mMsgNo = 0;
    msgGet.mResMsgNo = 0;

    mesg_header* header;
    for (u32 i = i_msgNo & 0xFFFF; i < 0xFFFF; i++) {
        header = msgGet.getMesgHeader(i);
        if (header != NULL && msgGet.getMessage(header) != NULL) {
            return i;
        }

        JKRFileLoader::removeResource(header, NULL);
    }

    return i_msgNo;
}

/* 8002B634-8002B778       .text fopMsgM_messageSet__FUlP10fopAc_ac_c */
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo, fopAc_ac_c* i_actor) {
    if (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 7 && dComIfGp_isHeapLockFlag() != 8 && dComIfGp_isHeapLockFlag() != 9) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    dComIfGp_clearMesgAnimeTagInfo();
    dComIfGp_clearMesgCameraTagInfo();

    cXyz lookAtPos = i_actor->eyePos;
    if (i_msgID == fpcM_ERROR_PROCESS_ID_e) {
        i_msgID = fopMsgM_messageTypeSelect(i_actor, &lookAtPos, &i_msgNo, &i_msgNo);
    } else if (fopMsgM_IsExecuting(i_msgID)) {
        msg_class* pMsg = fopMsgM_SearchByID(i_msgID);
        if (pMsg == NULL) {
            i_msgID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            pMsg->mMsgNo = i_msgNo;
            pMsg->field_0xf0 = i_msgNo;
            if (fopMsgM_SearchByName(fpcNm_SCP_e) || fopMsgM_SearchByName(fpcNm_PB_e)) {
                fopMsgM_Delete(pMsg);
                i_msgID = fpcM_ERROR_PROCESS_ID_e;
            }
        }
    } else {
        i_msgID = fopMsgM_messageTypeSelect(i_actor, &lookAtPos, &i_msgNo, &i_msgNo);
    }

    return i_msgID;
}

/* 8002B778-8002B8A4       .text fopMsgM_messageSet__FUlP4cXyz */
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo, cXyz* i_lookAtPos) {
    if (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 7 && dComIfGp_isHeapLockFlag() != 8 && dComIfGp_isHeapLockFlag() != 9) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    dComIfGp_clearMesgAnimeTagInfo();
    dComIfGp_clearMesgCameraTagInfo();

    if (i_msgID == fpcM_ERROR_PROCESS_ID_e) {
        i_msgID = fopMsgM_messageTypeSelect(NULL, i_lookAtPos, &i_msgNo, &i_msgNo);
    } else if (fopMsgM_IsExecuting(i_msgID)) {
        msg_class* pMsg = fopMsgM_SearchByID(i_msgID);
        if (pMsg == NULL) {
            i_msgID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            pMsg->mMsgNo = i_msgNo;
            pMsg->field_0xf0 = i_msgNo;
            if (fopMsgM_SearchByName(fpcNm_SCP_e) || fopMsgM_SearchByName(fpcNm_PB_e)) {
                fopMsgM_Delete(pMsg);
                i_msgID = fpcM_ERROR_PROCESS_ID_e;
            }
        }
    } else {
        i_msgID = fopMsgM_messageTypeSelect(NULL, i_lookAtPos, &i_msgNo, &i_msgNo);
    }

    return i_msgID;
}

/* 8002B8A4-8002B9C4       .text fopMsgM_messageSet__FUl */
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo) {
    if (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 7 && dComIfGp_isHeapLockFlag() != 8 && dComIfGp_isHeapLockFlag() != 9) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    cXyz lookAtPos;
    lookAtPos.x = lookAtPos.y = lookAtPos.z = 0.0f;
    if (i_msgID == fpcM_ERROR_PROCESS_ID_e) {
        i_msgID = fopMsgM_messageTypeSelect(NULL, &lookAtPos, &i_msgNo, &i_msgNo);
    } else if (fopMsgM_IsExecuting(i_msgID)) {
        msg_class* pMsg = fopMsgM_SearchByID(i_msgID);
        if (pMsg == NULL) {
            i_msgID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            pMsg->mMsgNo = i_msgNo;
            pMsg->field_0xf0 = i_msgNo;
            if (fopMsgM_SearchByName(fpcNm_SCP_e) || fopMsgM_SearchByName(fpcNm_PB_e)) {
                fopMsgM_Delete(pMsg);
                i_msgID = fpcM_ERROR_PROCESS_ID_e;
            }
        }
    } else {
        i_msgID = fopMsgM_messageTypeSelect(NULL, &lookAtPos, &i_msgNo, &i_msgNo);
    }

    return i_msgID;
}

/* 8002B9C4-8002BA4C       .text fopMsgM_scopeMessageSet__FUl */
fpc_ProcID fopMsgM_scopeMessageSet(u32 i_msgNo) {
    if (fopMsgM_IsExecuting(i_msgID)) {
        msg_class* pMsg = fopMsgM_SearchByID(i_msgID);
        if (pMsg == NULL) {
            i_msgID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e) && dComIfGp_getScopeMesgStatus() == fopMsgStts_SCOPE_ACTIVE_e) {
                dComIfGp_setScopeMesgStatus(fopMsgStts_BOX_OPENING_e);
            }

            pMsg->mMsgNo = i_msgNo;
            pMsg->field_0xf0 = i_msgNo;
        }
    }

    return i_msgID;
}

/* 8002BA4C-8002BB78       .text fopMsgM_tactMessageSet__Fv */
u32 fopMsgM_tactMessageSet() {
    if (dComIfGp_isHeapLockFlag() != 0 && dComIfGp_isHeapLockFlag() != 7 && dComIfGp_isHeapLockFlag() != 8 && dComIfGp_isHeapLockFlag() != 9) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    u32 msgNoTemp = 0x5AC;
    cXyz lookAtPos;
    lookAtPos.x = lookAtPos.y = lookAtPos.z = 0.0f;
    if (i_msgID == fpcM_ERROR_PROCESS_ID_e) {
        i_msgID = fopMsgM_messageTypeSelect(NULL, &lookAtPos, &msgNoTemp, &msgNoTemp);
        fopMsgM_tactMsgFlagOn();
    } else if (fopMsgM_IsExecuting(i_msgID)) {
        msg_class* pMsg = fopMsgM_SearchByID(i_msgID);
        if (pMsg == NULL) {
            i_msgID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            pMsg->mMsgNo = msgNoTemp;
            pMsg->field_0xf0 = msgNoTemp;
            if (fopMsgM_SearchByName(fpcNm_SCP_e) || fopMsgM_SearchByName(fpcNm_PB_e)) {
                fopMsgM_Delete(pMsg);
                i_msgID = fpcM_ERROR_PROCESS_ID_e;
            }
        }
    } else {
        i_msgID = fopMsgM_messageTypeSelect(NULL, &lookAtPos, &msgNoTemp, &msgNoTemp);
        fopMsgM_tactMsgFlagOn();
    }

    return i_msgID;
}

/* 8002BB78-8002BDBC       .text fopMsgM_messageGet__FPcUl */
char* fopMsgM_messageGet(char* i_dest, u32 i_msgNo) {
    fopMsgM_itemMsgGet_c msgGet;

    mesg_header* head_p = msgGet.getMesgHeader(i_msgNo);
    JUT_ASSERT(VERSION_SELECT(0x690, 0x690, 0x6BD, 0x6BD), head_p);

    const char* src = msgGet.getMessage(head_p);
    const char* cursor = src;
    char* dstPtr = i_dest;

    char dstBuf[20];
    s32 current;
    while (current = *cursor, *cursor != '\0') {
        if ((u8)*cursor == 0x1A) {
            u32 next_as_int = *(u32*)(++cursor);
            if ((next_as_int & 0xFFFFFF) == 0x1E) {
                *dstPtr = 0x1A;
                dstPtr++;
            } else if ((next_as_int & 0xFFFFFF) == 0) {
#if VERSION > VERSION_JPN
                // There are some modifications done to the player name before
                // writing it to the dst pointer when the language is set to German.

                strcpy(dstBuf, dComIfGs_getPlayerName());
                if (dComIfGs_getPalLanguage() == 1 &&
                    (
#if VERSION == VERSION_PAL
                        // Version is PAL
                        i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7
#else
                    // Version is USA, we know it's not DEMO or JPN because of the outer #if
                        i_msgNo == 0x33B || i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7 || i_msgNo == 0x37DD ||
                        i_msgNo == 0x37DE
#endif
                    )
                ) {
                    s32 bufLen = strlen(dstBuf);
                    current = (dstBuf)[bufLen - 1];
                    if (current == 's' || current == 'S' || current == 'z' || current == 'Z' || current == 'x' || current == 'X') {
                        strcat(dstBuf, "\'");
                    } else {
                        strcat(dstBuf, "s");
                    }
                }

                for (char* bufPtr = dstBuf; *bufPtr != '\0'; bufPtr++) {
                    *dstPtr = *bufPtr;
                    dstPtr++;
                }
#else
                // In the JPN and DEMO versions, the player name is just written
                // to dst directly.

                for (const char* bufPtr = dComIfGs_getPlayerName(); *bufPtr != '\0'; bufPtr++) {
                    *dstPtr = *bufPtr;
                    dstPtr++;
                }
#endif
            }

            cursor += *cursor - 1;
        } else {
            int shifted = ((u32)*cursor >> 4) & 0xF;
            if ((shifted == 8 || shifted == 9) && VERSION != VERSION_PAL) {
                *(dstPtr++) = *(cursor++);
                *(dstPtr++) = *(cursor++);
            } else {
                *(dstPtr++) = *(cursor++);
            }
        }
    }

    *dstPtr = '\0';
    return i_dest;
}

/* 8002BE04-8002C02C       .text fopMsgM_passwordGet__FPcUl */
char* fopMsgM_passwordGet(char* i_dest, u32 i_msgNo) {
    fopMsgM_itemMsgGet_c msgGet;

    mesg_header* head_p = msgGet.getMesgHeader(i_msgNo);
    JUT_ASSERT(VERSION_SELECT(0x6F6, 0x6F6, 0x735, 0x739), head_p);

    const char* src = msgGet.getMessage(head_p);
    const char* cursor = src;
    char* dstPtr = i_dest;

    char dstBuf[20];
    s32 current;
    while (current = *cursor, *cursor != '\0') {
        if ((u8)*cursor == 0x1A) {
            u32 next_as_int = *(u32*)(++cursor);
            if ((next_as_int & 0xFFFFFF) == 0) {
#if VERSION > VERSION_JPN
                // There are some modifications done to the player name before
                // writing it to the dst pointer when the language is set to German.

                strcpy(dstBuf, dComIfGs_getPlayerName());
                if (dComIfGs_getPalLanguage() == 1 &&
                    (
#if VERSION == VERSION_PAL
                        // Version is PAL
                        i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7
#else
                        // Version is USA, we know it's not DEMO or JPN because of the outer #if
                        i_msgNo == 0x33B || i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7 || i_msgNo == 0x37DD ||
                        i_msgNo == 0x37DE
#endif
                    )
                ) {
                    s32 bufLen = strlen(dstBuf);
                    current = (dstBuf)[bufLen - 1];
                    if (current == 's' || current == 'S' || current == 'z' || current == 'Z' || current == 'x' || current == 'X') {
                        strcat(dstBuf, "\'");
                    } else {
                        strcat(dstBuf, "s");
                    }
                }

                for (char* bufPtr = dstBuf; *bufPtr != '\0'; bufPtr++) {
                    *dstPtr = *bufPtr;
                    dstPtr++;
                }
#else
                // In the JPN and DEMO versions, the player name is just written
                // to dst directly.

                for (const char* bufPtr = dComIfGs_getPlayerName(); *bufPtr != '\0'; bufPtr++) {
                    *dstPtr = *bufPtr;
                    dstPtr++;
                }
#endif
            }

            cursor += *cursor - 1;
        } else {
            int shifted = ((u32)*cursor >> 4) & 0xF;
            if ((shifted == 8 || shifted == 9) && VERSION != VERSION_PAL) {
                *(dstPtr++) = *(cursor++);
                *(dstPtr++) = *(cursor++);
            } else {
                *(dstPtr++) = *(cursor++);
            }
        }
    }

    *dstPtr = '\0';
    return i_dest;
}

static f32 dummyfloat0(int _) {
    switch (_) {
        case 0:
            return 0.0f;
        case 1:
            return 0.5f;
    }
}

static f64 dummyfloat1(int _) {
    switch (_) {
        case 0:
            return 4503601774854144.0;
        case 1:
            return 0.5;
        case 2:
            return 3.0;
    }
}

static f32 dummyfloat2(int _) {
    switch (_) {
        case 0:
            return 2.0f;
    }
}

struct fopMsgM_unk_struct {
    u16 _0;
    u16 _2;
    u16 _4;
    u16 _6;
    u16 _8;
    u16 _A;
    s16 _C;
    u16 _E;
    u8 _10;
};

/* 8002C02C-8002C568       .text fopMsgM_selectMessageGet__FP7J2DPaneP7J2DPanePcPcPcPcUl */
fopMsgM_unk_struct fopMsgM_selectMessageGet(J2DPane* i_textPane, J2DPane* i_rubyPane, char* param_3, char* param_4, char* param_5, char* param_6, u32 i_msgNo) {
    fopMsgM_msgDataProc_c msgData;
    fopMsgM_itemMsgGet_c msgGet;

    strcpy(param_3, "\x1B""CC[000000FF]\x1B""GM[0]");
    strcpy(param_4, "");
    strcpy(param_5, "");
    strcpy(param_6, "");

    J2DTextBox::TFontSize size;
    J2DTextBox::TFontSize size2;
    ((J2DTextBox*)i_rubyPane)->getFontSize(size);
    ((J2DTextBox*)i_textPane)->getFontSize(size2);

    mesg_header* head_p = msgGet.getMesgHeader(i_msgNo);
    JUT_ASSERT(1947, head_p);

    char* bmgData = (char*)msgGet.getMessage(head_p);
    fopMsgM_unk_struct sp40;
    JMSMesgEntry_c entry;
    entry = msgGet.getMesgEntry(head_p);

    msgData.dataInit();
    msgData.setBmgData(bmgData);
    msgData.setOutMessage(param_3, param_4, param_5, param_6);
    msgData.setFont(((J2DTextBox*)i_textPane)->getFont());
    msgData.setRubyFont(((J2DTextBox*)i_rubyPane)->getFont());
    msgData.setCharSpace(((J2DTextBox*)i_textPane)->getCharSpace());
    msgData.setRubyCharSpace(((J2DTextBox*)i_rubyPane)->getCharSpace());
    msgData.setLineSpace(((J2DTextBox*)i_textPane)->getLineSpace());
    msgData.setMesgEntry(&entry);
    msgData.setFontSize(size2.mSizeX);
    msgData.setRubyFontSize(size.mSizeX);
    msgData.setLineWidth(i_textPane->getWidth());
    msgData.setCenterLineWidth(i_textPane->getWidth());
    msgData.setSendSpeed(2);
    msgData.setSpaceTimer(0);
    msgData.shortCut();
    msgData.setSpaceFlagOff();
    msgData.stringLength();
    msgData.stringShift();
    msgData.iconIdxRefresh();

    s16 temp_r3 = msgData.getLineCount();
    msgData.setLineCount(0);

    int temp_r30_2 = 2 - temp_r3;
    f32 fVar2 = temp_r30_2 * (((J2DTextBox*)i_textPane)->getLineSpace() / 2);
    ((J2DTextBox*)i_rubyPane)->shiftSet(0.0f, fVar2);
    ((J2DTextBox*)i_textPane)->shiftSet(0.0f, fVar2);

    msgData.stringSet();
    ((J2DTextBox*)i_textPane)->setString(param_3);
    ((J2DTextBox*)i_rubyPane)->setString(param_4);

    int temp_r5 = ((J2DTextBox*)i_textPane)->getLineSpace() / 2;
    s16 temp_r6 = ((J2DTextBox*)i_textPane)->getBounds().i.x;
    s16 temp_r3_3 = ((J2DTextBox*)i_textPane)->getBounds().i.y;

    u8 var_r7 = false;
    for (int i = 0; i < 15; i++) {
        u8 temp_r9 = msgData.getIconNum(i);
        if (temp_r9 != 0xFF) {
            if (temp_r9 == 0x14) {
                if (!var_r7) {
                    sp40._0 = temp_r6 + msgData.getIconPosX(i);
                    sp40._4 = temp_r3_3 + (temp_r5 * (temp_r30_2 + (msgData.getIconPosY(i) * 2)));
                    var_r7 = true;
                } else {
                    sp40._2 = sp40._8 = temp_r6 + msgData.getIconPosX(i);
                    sp40._6 = sp40._C = temp_r3_3 + (temp_r5 * (temp_r30_2 + (msgData.getIconPosY(i) * 2)));
                }
            } else if (temp_r9 == 0x15) {
                sp40._10 = var_r7;
                if (!var_r7) {
                    sp40._0 = temp_r6 + msgData.getIconPosX(i);
                    sp40._4 = temp_r3_3 + (temp_r5 * (temp_r30_2 + (msgData.getIconPosY(i) * 2)));
                    var_r7 = true;
                } else {
                    sp40._2 = sp40._8 = temp_r6 + msgData.getIconPosX(i);
                    sp40._6 = sp40._C = temp_r3_3 + (temp_r5 * (temp_r30_2 + (msgData.getIconPosY(i) * 2)));
                }
            }
        }
    }

    sp40._A = temp_r6 + msgData.getNowCursorPos();
    sp40._E = sp40._C;
    return sp40;
}

/* 8002C568-8002C574       .text fopMsgM_demoMsgFlagOn__Fv */
void fopMsgM_demoMsgFlagOn() {
    demoFlag = true;
}

/* 8002C574-8002C580       .text fopMsgM_demoMsgFlagOff__Fv */
void fopMsgM_demoMsgFlagOff() {
    demoFlag = false;
}

/* 8002C580-8002C588       .text fopMsgM_demoMsgFlagCheck__Fv */
bool fopMsgM_demoMsgFlagCheck() {
    return demoFlag;
}

/* 8002C588-8002C594       .text fopMsgM_tactMsgFlagOn__Fv */
void fopMsgM_tactMsgFlagOn() {
    tactFlag = true;
}

/* 8002C594-8002C5A0       .text fopMsgM_tactMsgFlagOff__Fv */
void fopMsgM_tactMsgFlagOff() {
    tactFlag = false;
}

/* 8002C5A0-8002C5A8       .text fopMsgM_tactMsgFlagCheck__Fv */
bool fopMsgM_tactMsgFlagCheck() {
    return tactFlag;
}

/* 8002C5A8-8002C5B4       .text fopMsgM_nextMsgFlagOff__Fv */
void fopMsgM_nextMsgFlagOff() {
    nextMsg = false;
}

/* 8002C5B4-8002C5BC       .text fopMsgM_nextMsgFlagCheck__Fv */
bool fopMsgM_nextMsgFlagCheck() {
    return nextMsg;
}

/* 8002C5BC-8002C624       .text fopMsgM_getScopeMode__Fv */
bool fopMsgM_getScopeMode() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e) && dComIfGp_getScopeMesgStatus() == fopMsgStts_SCOPE_ACTIVE_e && !dComIfGp_event_runCheck()) {
        dComIfGp_setScopeMesgStatus(fopMsgStts_SCOPE_WAIT_e);
        return true;
    }
    if (dComIfGp_getScopeMesgStatus() == fopMsgStts_BOX_CLOSING_e) {
        dComIfGp_setMesgStatus(fopMsgStts_SCOPE_WAIT_e);
        return true;
    }

    return false;
}

/* 8002C624-8002C650       .text fopMsgM_forceSendOn__Fv */
bool fopMsgM_forceSendOn() {
    if (dComIfGp_getScopeMesgStatus() == fopMsgStts_CLOSE_WAIT_e) {
        pushButton = true;
        return true;
    }

    return false;
}

/* 8002C650-8002C65C       .text fopMsgM_forceSendOff__Fv */
void fopMsgM_forceSendOff() {
    pushButton = false;
}

/* 8002C65C-8002C664       .text fopMsgM_checkForceSend__Fv */
bool fopMsgM_checkForceSend() {
    return pushButton;
}

/* 8002C664-8002C670       .text fopMsgM_messageSendOn__Fv */
void fopMsgM_messageSendOn() {
    pushButton2 = true;
}

/* 8002C670-8002C67C       .text fopMsgM_messageSendOff__Fv */
void fopMsgM_messageSendOff() {
    pushButton2 = false;
}

/* 8002C67C-8002C684       .text fopMsgM_checkMessageSend__Fv */
bool fopMsgM_checkMessageSend() {
    return pushButton2;
}

/* 8002C684-8002C6B0       .text fopMsgM_releaseScopeMode__Fv */
bool fopMsgM_releaseScopeMode() {
    if (dComIfGp_getScopeMesgStatus() == fopMsgStts_SCOPE_WAIT_e) {
        dComIfGp_setScopeMesgStatus(fopMsgStts_SCOPE_ACTIVE_e);
        return true;
    }

    return false;
}

static const char* fopMsgM_buttonTex[] = {
    /* 0x00 */ "font_00.bti",
    /* 0x01 */ "font_01.bti",
    /* 0x02 */ "font_09.bti",
    /* 0x03 */ "font_04.bti",
    /* 0x04 */ "font_05.bti",
    /* 0x05 */ "font_02.bti",
    /* 0x06 */ "font_03.bti",
    /* 0x07 */ "font_06.bti",
    /* 0x08 */ "font_08.bti",
    /* 0x09 */ "font_07_01.bti",
    /* 0x0A */ "font_10.bti",
    /* 0x0B */ "font_10.bti",
    /* 0x0C */ "font_10.bti",
    /* 0x0D */ "font_10.bti",
    /* 0x0E */ "font_07_01.bti",
    /* 0x0F */ "font_07_01.bti",
    /* 0x10 */ "font_07_01.bti",
    /* 0x11 */ "font_07_01.bti",
    /* 0x12 */ "font_07_01.bti",
    /* 0x13 */ "font_07_01.bti",
    /* 0x14 */ "font_12.bti",
    /* 0x15 */ "font_13.bti",
    /* 0x16 */ "font_14.bti",
    /* 0x17 */ "font_15.bti",
};

static GXColor fopMsgM_buttonW[] = {
    /* 0x00 */ {0x00, 0xFF, 0xB4, 0xFF},
    /* 0x01 */ {0xFF, 0x32, 0x32, 0xFF},
    /* 0x02 */ {0xFF, 0xC8, 0x32, 0xFF},
    /* 0x03 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x04 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x05 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x06 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x07 */ {0xC8, 0x96, 0xFF, 0xFF},
    /* 0x08 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x09 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x0A */ {0xFF, 0xC8, 0x32, 0xFF},
    /* 0x0B */ {0xFF, 0xC8, 0x32, 0xFF},
    /* 0x0C */ {0xFF, 0xC8, 0x32, 0xFF},
    /* 0x0D */ {0xFF, 0xC8, 0x32, 0xFF},
    /* 0x0E */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x0F */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x10 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x11 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x12 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x13 */ {0xC8, 0xC8, 0xC8, 0xFF},
    /* 0x14 */ {0x00, 0xFF, 0xB4, 0xFF},
    /* 0x15 */ {0xFF, 0x32, 0x32, 0xFF},
    /* 0x16 */ {0xFF, 0xFF, 0xFF, 0xFF},
    /* 0x17 */ {0xFF, 0xFF, 0xFF, 0xFF},
};

/* 8002C6B0-8002C6C4       .text fopMsgM_outFontTex__Fi */
const char* fopMsgM_outFontTex(int i_no) {
    return fopMsgM_buttonTex[i_no];
}

/* 8002C6C4-8002C6D8       .text fopMsgM_outFontColorWhite__Fi */
GXColor fopMsgM_outFontColorWhite(int i_no) {
    return fopMsgM_buttonW[i_no];
}

/* 8002C6D8-8002C9B0       .text fopMsgM_outFontSet__FP10J2DPictureP10J2DPicturePsUlUc */
void fopMsgM_outFontSet(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, s16* i_timer, u32 i_color, u8 i_iconNo) {
    /* Nonmatching */
    if (i_iconNo == 0x17) {
        i_iconNo = 0x14;
    } else if (i_iconNo == 0x18) {
        i_iconNo = 0x15;
    } else if (i_iconNo == 0x19) {
        i_iconNo = 0x16;
    } else if (i_iconNo == 0x1A) {
        i_iconNo = 0x17;
    }

    i_iconPic->show();
    i_sdwPic->show();
    fopMsgM_blendDraw(i_iconPic, fopMsgM_buttonTex[i_iconNo]);
    fopMsgM_blendDraw(i_sdwPic, fopMsgM_buttonTex[i_iconNo]);
    if (i_iconNo == 0xA || i_iconNo == 0xB || i_iconNo == 0xC || i_iconNo == 0xD || i_iconNo == 0x15 || i_iconNo == 0x17) {
        GXColor col;
        col.r = i_color >> 0x18;
        col.g = i_color >> 0x10;
        col.b = i_color >> 0x8;
        col.a = 0xFF;
        i_iconPic->setWhite(col);
        i_iconPic->setBlack(0x00000000);
    } else {
        i_iconPic->setWhite(fopMsgM_buttonW[i_iconNo]);
        i_iconPic->setBlack(0x00000000);
    }

    i_sdwPic->setWhite(0x000000FF);
    i_sdwPic->setBlack(0x00000000);
    i_iconPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
    i_sdwPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);

    *i_timer = 0;
}

/* 8002C9B0-8002CBDC       .text fopMsgM_outFontSet__FP10J2DPicturePsUlUc */
void fopMsgM_outFontSet(J2DPicture* i_iconPic, s16* i_timer, u32 i_color, u8 i_iconNo) {
    /* Nonmatching */
    if (i_iconNo == 0x17) {
        i_iconNo = 0x14;
    } else if (i_iconNo == 0x18) {
        i_iconNo = 0x15;
    } else if (i_iconNo == 0x19) {
        i_iconNo = 0x16;
    } else if (i_iconNo == 0x1A) {
        i_iconNo = 0x17;
    }

    i_iconPic->show();
    fopMsgM_blendDraw(i_iconPic, fopMsgM_buttonTex[i_iconNo]);
    if (i_iconNo == 0xA || i_iconNo == 0xB || i_iconNo == 0xC || i_iconNo == 0xD || i_iconNo == 0x15 || i_iconNo == 0x17) {
        GXColor col;
        col.r = i_color >> 0x18;
        col.g = i_color >> 0x10;
        col.b = i_color >> 0x8;
        col.a = 0xFF;
        i_iconPic->setWhite(col);
        GXColor col2 = {0, 0, 0, 0};
        i_iconPic->setBlack(0x00000000);
    } else {
        i_iconPic->setWhite(fopMsgM_buttonW[i_iconNo]);
        i_iconPic->setBlack(0x00000000);
    }

    i_iconPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);

    *i_timer = 0;
}

/* 8002CBDC-8002CEB0       .text fopMsgM_outFontStickAnimePiece__FP10J2DPictureP10J2DPicturess */
void fopMsgM_outFontStickAnimePiece(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, s16 param_3, s16 param_4) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    s16 temp2 = g_msgHIO.field_0x88 + temp * param_4;
    s16 temp3 = g_msgHIO.field_0x87 + temp2;
    s16 temp4 = g_msgHIO.field_0x89 + temp3;
    s16 temp5 = g_msgHIO.field_0x87 + temp4;

    if (param_3 < temp2) {
        i_iconPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
        i_sdwPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
    } else if (param_3 < temp3) {
        float temp6 = fopMsgM_valueIncrease(temp, param_3 - temp2, 0);
        i_iconPic->setBlendRatio(temp6, 1.0f - temp6, 1.0f, 1.0f);
        i_sdwPic->setBlendRatio(temp6, 1.0f - temp6, 1.0f, 1.0f);
    } else if (param_3 < temp4) {
        i_iconPic->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
        i_sdwPic->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
    } else if (param_3 < temp5) {
        float temp6 = fopMsgM_valueIncrease(temp, param_3 - temp4, 0);
        i_iconPic->setBlendRatio(1.0f - temp6, temp6, 1.0f, 1.0f);
        i_sdwPic->setBlendRatio(1.0f - temp6, temp6, 1.0f, 1.0f);
    }
}

/* 8002CEB0-8002D088       .text fopMsgM_outFontStickAnimePiece__FP10J2DPicturess */
void fopMsgM_outFontStickAnimePiece(J2DPicture* i_iconPic, s16 param_2, s16 param_3) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    s16 temp2 = g_msgHIO.field_0x88 + temp * param_3;
    s16 temp3 = g_msgHIO.field_0x87 + temp2;
    s16 temp4 = g_msgHIO.field_0x89 + temp3;
    s16 temp5 = g_msgHIO.field_0x87 + temp4;

    if (param_2 < temp2) {
        i_iconPic->setBlendRatio(0.0f, 1.0f, 1.0f, 1.0f);
    } else if (param_2 < temp3) {
        float temp6 = fopMsgM_valueIncrease(temp, param_2 - temp2, 0);
        i_iconPic->setBlendRatio(temp6, 1.0f - temp6, 1.0f, 1.0f);
    } else if (param_2 < temp4) {
        i_iconPic->setBlendRatio(1.0f, 0.0f, 1.0f, 1.0f);
    } else if (param_2 < temp5) {
        float temp6 = fopMsgM_valueIncrease(temp, param_2 - temp4, 0);
        i_iconPic->setBlendRatio(1.0f - temp6, temp6, 1.0f, 1.0f);
    }
}

/* 8002D0E4-8002D2B8       .text fopMsgM_outFontStickAnime__FP10J2DPictureP10J2DPicturePiPiiPs */
void fopMsgM_outFontStickAnime(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int* param_3, int* param_4, int param_5, s16* i_timer) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;

    if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 0);
    } else if (*i_timer < temp * 2) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 1);
        *param_3 += param_5;
    } else if (*i_timer < temp * 3) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 2);
        *param_3 += param_5;
        *param_4 += param_5;
    } else if (*i_timer < temp * 4) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 3);
        *param_4 += param_5;
    }

    if (*i_timer % temp == 0) {
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, (*i_timer / temp) * -90.0f);
        i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, (*i_timer / temp) * -90.0f);
    }

    *i_timer += 1;
    if (*i_timer >= temp * 4) {
        *i_timer = 0;
    }
}

/* 8002D2B8-8002D464       .text fopMsgM_outFontStickAnime__FP10J2DPicturePiPiPiPiPs */
void fopMsgM_outFontStickAnime(J2DPicture* i_iconPic, int* param_2, int* param_3, int* param_4, int* param_5, s16* i_timer) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;

    if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 0);
    } else if (*i_timer < temp * 2) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 1);
        int temp2 = *param_4;
        *param_4 = *param_5;
        *param_5 = temp2;
        *param_2 += *param_5;
    } else if (*i_timer < temp * 3) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 2);
        *param_2 += *param_4;
        *param_3 += *param_5;
    } else if (*i_timer < temp * 4) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 3);
        int temp2 = *param_4;
        *param_4 = *param_5;
        *param_5 = temp2;
        *param_3 += *param_4;
    }

    if (*i_timer % temp == 0) {
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, (*i_timer / temp) * -90.0f);
    }

    *i_timer += 1;
    if (*i_timer >= temp * 4) {
        *i_timer = 0;
    }
}

/* 8002D464-8002D620       .text fopMsgM_outFontStickAnime2__FP10J2DPictureP10J2DPicturePiPiiPsUc */
void fopMsgM_outFontStickAnime2(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int* param_3, int* param_4, int param_5, s16* i_timer, u8 param_7) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    int temp2;

    if (param_7 == 0) {
        if (*i_timer < temp) {
            fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 0);
            *param_3 += param_5;
            temp2 = 1;
        } else if (*i_timer < temp * 2) {
            fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 1);
            *param_4 += param_5;
            temp2 = 3;
        }
    } else if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 0);
        temp2 = 0;
    } else if (*i_timer < temp * 2) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 1);
        *param_3 += param_5;
        *param_4 += param_5;
        temp2 = 2;
    }

    i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, temp2 * -90.0f);
    i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, temp2 * -90.0f);

    *i_timer += 1;
    if (*i_timer >= temp * 2) {
        *i_timer = 0;
    }
}

/* 8002D620-8002D7D0       .text fopMsgM_outFontStickAnime2__FP10J2DPicturePiPiPiPiPsUc */
void fopMsgM_outFontStickAnime2(J2DPicture* i_iconPic, int* param_2, int* param_3, int* param_4, int* param_5, s16* i_timer, u8 param_7) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    int temp3;

    if (param_7 == 0) {
        if (*i_timer < temp) {
            fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 0);
            int temp2 = *param_4;
            *param_4 = *param_5;
            *param_5 = temp2;
            *param_2 += *param_5;
            temp3 = 1;
        } else if (*i_timer < temp * 2) {
            fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 1);
            int temp2 = *param_4;
            *param_4 = *param_5;
            *param_5 = temp2;
            *param_3 += *param_4;
            temp3 = 3;
        }
    } else if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 0);
        temp3 = 0;
    } else if (*i_timer < temp * 2) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 1);
        *param_2 += *param_4;
        *param_3 += *param_5;
        temp3 = 2;
    }

    i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, temp3 * -90.0f);

    *i_timer += 1;
    if (*i_timer >= temp * 2) {
        *i_timer = 0;
    }
}

/* 8002D7D0-8002D95C       .text fopMsgM_outFontStickAnime__FP10J2DPictureP10J2DPicturePiPiiPsUc */
void fopMsgM_outFontStickAnime(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int* param_3, int* param_4, int param_5, s16* i_timer, u8 param_7) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;

    if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, i_sdwPic, *i_timer, 0);
        switch (param_7) {
        case 1:
            *param_3 += param_5;
            break;
        case 2:
            *param_3 += param_5;
            *param_4 += param_5;
            break;
        case 3:
            *param_4 += param_5;
            break;
        }
    }

    i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, param_7 * -90.0f);
    i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, param_7 * -90.0f);

    *i_timer += 1;
    if (*i_timer >= temp) {
        *i_timer = 0;
    }
}

/* 8002D95C-8002DAE4       .text fopMsgM_outFontStickAnime__FP10J2DPicturePiPiPiPiPsUc */
void fopMsgM_outFontStickAnime(J2DPicture* i_iconPic, int* param_2, int* param_3, int* param_4, int* param_5, s16* i_timer, u8 param_7) {
    s16 temp = g_msgHIO.field_0x88 + g_msgHIO.field_0x87 + g_msgHIO.field_0x89 + g_msgHIO.field_0x87;
    s16 temp2;

    if (*i_timer < temp) {
        fopMsgM_outFontStickAnimePiece(i_iconPic, *i_timer, 0);
        switch (param_7) {
        case 1:
            temp2 = *param_4;
            *param_4 = *param_5;
            *param_5 = temp2;
            *param_2 += *param_5;
            break;
        case 2:
            *param_2 += *param_4;
            *param_3 += *param_5;
            break;
        case 3:
            temp2 = *param_4;
            *param_4 = *param_5;
            *param_5 = temp2;
            *param_3 += *param_4;
            break;
        }
    }

    i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, param_7 * -90.0f);

    *i_timer += 1;
    if (*i_timer >= temp) {
        *i_timer = 0;
    }
}

/* 8002DAE4-8002DC74       .text fopMsgM_outFontArrow__FP10J2DPictureP10J2DPicturePiPiiUc */
void fopMsgM_outFontArrow(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int* param_3, int* param_4, int param_5, u8 i_iconNo) {
    if (i_iconNo == 0xA) {
        *param_3 += param_5;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 270.0f);
        i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, 270.0f);
    } else if (i_iconNo == 0xB) {
        *param_4 += param_5;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 90.0f);
        i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, 90.0f);
    } else if (i_iconNo == 0xC) {
        *param_3 += param_5;
        *param_4 += param_5;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 180.0f);
        i_sdwPic->rotate(0.0f, 0.0f, ROTATE_Z, 180.0f);
    }
}

/* 8002DC74-8002DD98       .text fopMsgM_outFontArrow__FP10J2DPicturePiPiPiPiUc */
void fopMsgM_outFontArrow(J2DPicture* i_iconPic, int* param_2, int* param_3, int* param_4, int* param_5, u8 i_iconNo) {
    if (i_iconNo == 0xA) {
        int temp2 = *param_4;
        *param_4 = *param_5;
        *param_5 = temp2;
        *param_2 += *param_5;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 270.0f);
    } else if (i_iconNo == 0xB) {
        int temp2 = *param_4;
        *param_4 = *param_5;
        *param_5 = temp2;
        *param_3 += *param_4;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 90.0f);
    } else if (i_iconNo == 0xC) {
        *param_2 += *param_4;
        *param_3 += *param_5;
        i_iconPic->rotate(0.0f, 0.0f, ROTATE_Z, 180.0f);
    }
}

/* 8002DD98-8002DFB4       .text fopMsgM_outFontDraw__FP10J2DPictureP10J2DPictureiiiPsUcUc */
void fopMsgM_outFontDraw(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int param_3, int param_4, int param_5, s16* i_timer, u8 i_alpha, u8 i_iconNo) {
    switch (i_iconNo) {
    case 9:
        fopMsgM_outFontStickAnime(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer);
        break;
    case 0xE:
        fopMsgM_outFontStickAnime(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 1);
        break;
    case 0xF:
        fopMsgM_outFontStickAnime(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 3);
        break;
    case 0x10:
        fopMsgM_outFontStickAnime(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 0);
        break;
    case 0x11:
        fopMsgM_outFontStickAnime(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 2);
        break;
    case 0x12:
        fopMsgM_outFontStickAnime2(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 0);
        break;
    case 0x13:
        fopMsgM_outFontStickAnime2(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_timer, 1);
        break;
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
        fopMsgM_outFontArrow(i_iconPic, i_sdwPic, &param_3, &param_4, param_5, i_iconNo);
        break;
    }

    i_sdwPic->draw(param_3 + 2, param_4 + 1 + g_msgHIO.field_0x6a, param_5, param_5, false, false, false);
    i_iconPic->draw(param_3, param_4 - 1 + g_msgHIO.field_0x6a, param_5, param_5, false, false, false);

    i_iconPic->setAlpha(i_alpha);
    i_sdwPic->setAlpha(i_alpha);
}

/* 8002DFB4-8002E204       .text fopMsgM_outFontDraw2__FP10J2DPictureP10J2DPictureiiiiPsUcUc */
void fopMsgM_outFontDraw2(J2DPicture* i_iconPic, J2DPicture* param_2, int param_3, int param_4, int i_width, int i_height, s16* i_timer, u8 i_alpha, u8 i_iconNo) {
    int temp1 = 0, temp2 = 0;

    switch (i_iconNo) {
    case 9:
        fopMsgM_outFontStickAnime(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer);
        break;
    case 0xE:
        fopMsgM_outFontStickAnime(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 1);
        break;
    case 0xF:
        fopMsgM_outFontStickAnime(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 3);
        break;
    case 0x10:
        fopMsgM_outFontStickAnime(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 0);
        break;
    case 0x11:
        fopMsgM_outFontStickAnime(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 2);
        break;
    case 0x12:
        fopMsgM_outFontStickAnime2(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 0);
        break;
    case 0x13:
        fopMsgM_outFontStickAnime2(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_timer, 1);
        break;
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
        fopMsgM_outFontArrow(i_iconPic, &temp1, &temp2, &i_width, &i_height, i_iconNo);
        break;
    }

    param_2->move(param_3, param_4);
    i_iconPic->move(temp1, temp2);
    i_iconPic->resize(i_width, i_height);

    i_iconPic->setAlpha(i_alpha);
}

/* 8002E204-8002E254       .text fopMsgM_Create__FsPFPv_iPv */
fpc_ProcID fopMsgM_Create(s16 i_name, fopMsgCreateFunc i_createFunc, void* i_append) {
    return fpcSCtRq_Request(fpcLy_CurrentLayer(), i_name, (stdCreateFunc)i_createFunc, NULL, i_append);
}

/* 8002E254-8002E2D8       .text getMesgHeader__16fopMsgM_msgGet_cFUl */
mesg_header* fopMsgM_msgGet_c::getMesgHeader(u32 i_msgNo) {
    mGroupID = (i_msgNo >> 16);
    mMsgNo = i_msgNo;

#if VERSION <= VERSION_JPN
    char path[12];
    if (g_msgDHIO.field_0x08 == 0) {
        sprintf(path, "zel_%02d.bmg", mGroupID);
    } else {
        sprintf(path, "zel_e%02d.bmg", mGroupID);
    }
    JKRArchive* arc = dComIfGp_getMsgDtArchive();
    return (mesg_header*)JKRArchive::getGlbResource('ROOT', path, arc);
#else
    if (fopMsgM_hyrule_language_check(i_msgNo)) {
        JKRArchive* arc = dComIfGp_getMsgDt2Archive();
        return (mesg_header*)JKRArchive::getGlbResource('ROOT', "zel_01.bmg", arc);
    } else {
        JKRArchive* arc = dComIfGp_getMsgDtArchive();
        return (mesg_header*)JKRArchive::getGlbResource('ROOT', "zel_00.bmg", arc);
    }
#endif
}

/* 8002E2D8-8002E2E0       .text getMesgInfo__16fopMsgM_msgGet_cFP11mesg_header */
mesg_info* fopMsgM_msgGet_c::getMesgInfo(mesg_header* i_head) {
    return (mesg_info*)&i_head->mFirstBlock;
}

/* 8002E2E0-8002E308       .text getMesgData__16fopMsgM_msgGet_cFP11mesg_header */
mesg_data* fopMsgM_msgGet_c::getMesgData(mesg_header* i_head) {
    return (mesg_data*)getMesgInfo(i_head)->getNext();
}

/* 8002E308-8002E378       .text getMesgEntry__16fopMsgM_msgGet_cFP11mesg_header */
JMSMesgEntry_c fopMsgM_msgGet_c::getMesgEntry(mesg_header* i_head) {
    mesg_info* info = getMesgInfo(i_head);
    return info->mEntries[mMsgIdx];
}

/* 8002E378-8002E430       .text getMessage__16fopMsgM_msgGet_cFP11mesg_header */
const char* fopMsgM_msgGet_c::getMessage(mesg_header* i_head) {
    mesg_info* info = getMesgInfo(i_head);
    const char* data = getMesgData(i_head)->mData;

    const char* ret = NULL;

    for (u16 i = 0; i < info->mNumEntry; i++) {
        if (info->mEntries[i].mDataOffs == 0)
            continue;

        mMsgIdx = i;
        if (mMsgNo == info->mEntries[i].mMsgNo) {
            ret = &data[info->mEntries[mMsgIdx].mDataOffs];
            mResMsgNo = info->mEntries[mMsgIdx].mMsgNo;
            break;
        }
    }

    return ret;
}

/* 8002E430-8002E4AC       .text getMesgHeader__20fopMsgM_itemMsgGet_cFUl */
mesg_header* fopMsgM_itemMsgGet_c::getMesgHeader(u32 i_msgNo) {
#if VERSION <= VERSION_JPN
    u16 groupID = i_msgNo >> 16;
#endif
    mMsgNo = i_msgNo;

#if VERSION <= VERSION_JPN
    char path[12];
    if (g_msgDHIO.field_0x08 == 0) {
        sprintf(path, "zel_%02d.bmg", groupID);
    } else {
        sprintf(path, "zel_e%02d.bmg", groupID);
    }
    JKRArchive* arc = dComIfGp_getMsgDtArchive();
    return (mesg_header*)JKRArchive::getGlbResource('ROOT', path, arc);
#else
    if (fopMsgM_hyrule_language_check(i_msgNo)) {
        JKRArchive* arc = dComIfGp_getMsgDt2Archive();
        return (mesg_header*)JKRArchive::getGlbResource('ROOT', "zel_01.bmg", arc);
    } else {
        JKRArchive* arc = dComIfGp_getMsgDtArchive();
        return (mesg_header*)JKRArchive::getGlbResource('ROOT', "zel_00.bmg", arc);
    }
#endif
}

/* 8002E4AC-8002E4B4       .text getMesgInfo__20fopMsgM_itemMsgGet_cFP11mesg_header */
mesg_info* fopMsgM_itemMsgGet_c::getMesgInfo(mesg_header* i_head) {
    return (mesg_info*)&i_head->mFirstBlock;
}

/* 8002E4B4-8002E4DC       .text getMesgData__20fopMsgM_itemMsgGet_cFP11mesg_header */
mesg_data* fopMsgM_itemMsgGet_c::getMesgData(mesg_header* i_head) {
    return (mesg_data*)getMesgInfo(i_head)->getNext();
}

/* 8002E4DC-8002E54C       .text getMesgEntry__20fopMsgM_itemMsgGet_cFP11mesg_header */
JMSMesgEntry_c fopMsgM_itemMsgGet_c::getMesgEntry(mesg_header* i_head) {
    mesg_info* info = getMesgInfo(i_head);
    return info->mEntries[mMsgIdx];
}

/* 8002E54C-8002E5FC       .text getMessage__20fopMsgM_itemMsgGet_cFP11mesg_header */
const char* fopMsgM_itemMsgGet_c::getMessage(mesg_header* i_head) {
    mesg_info* info = getMesgInfo(i_head);
    const char* data = getMesgData(i_head)->mData;

    for (u16 i = 0; i < info->mNumEntry; i++) {
        if (info->mEntries[i].mDataOffs == 0)
            continue;

        mMsgIdx = i;
        if (mMsgNo == info->mEntries[i].mMsgNo) {
            break;
        }
    }

    const char* result = &data[info->mEntries[mMsgIdx].mDataOffs];
    mResMsgNo = info->mEntries[mMsgIdx].mMsgNo;
    return result;
}

/* 8002E5FC-8002E794       .text __ct__21fopMsgM_msgDataProc_cFv */
fopMsgM_msgDataProc_c::fopMsgM_msgDataProc_c() {
    field_0x14 = 0.0f;
    field_0x18 = 0.0f;
    field_0x1C = 0.0f;
    field_0x20 = 0.0f;
    field_0x24 = 0.0f;
    field_0x28 = 0.0f;

    for (int i = 0; i < 4; i++) {
        field_0xD8[i] = 0;
        field_0xF8[i] = 0;
        field_0x108[i] = 0;
        field_0xE8[i] = 0;
    }

    field_0x21C = 0;
    field_0xD4[2] = 0;
    field_0xD4[1] = 0;
    field_0xD4[0] = 0;
    field_0x2C = 0;
    field_0x30 = 0;
    field_0x34 = 0;
    field_0x38 = 0;
    count = 0;
    charSpace = 0;
    rubyCharSpace = 0;
    lineSpace = 0;
    lineWidth = 0;
    centerLineWidth = 0;
    lineCount = 0;
    field_0x134 = 0;
    nowLine = 0;
    aimLine = 0;
    field_0x140 = 0;
    fontSize = 0;
    field_0x148 = 0;
    rubyFontSize = 0;
    field_0x150 = 0;
    field_0x154 = 0;
    field_0x158 = 0;
    spaceTimer = 1;
    sendSpeed = 1;
    field_0x164 = 0;
    field_0x25C = -1;
    field_0x29D = 0;
    field_0x260 = 0;
    field_0x264 = 0.0f;
    field_0x268 = 0.0f;
    field_0x26C = 0.0f;
    field_0x270 = 0.0f;
    field_0x278 = 0.0f;
    field_0x274 = 0.0f;
    field_0x293 = 0;
    field_0x292 = 0;
    field_0x291 = 0;
    field_0x290 = 0;
    mesgStatus = 6;
    field_0x27D = 0;
    field_0x27E = 0;
    field_0x27F = 0;
    field_0x280 = 0;

    for (int i = 0; i < 0xF; i++) {
        field_0x168[i] = 0;
        field_0x1A4[i] = 0;
        field_0x1E0[i] = 0;
        field_0x281[i] = 0xFF;
        field_0x220[i] = 0;
    }

    field_0x10 = 0;
    field_0x299 = 0;
    field_0x29A = 0;
    selectFlag = 0;
    field_0x29B = 0;
    autoSendFlag = 0;
    handSendFlag = 0;
    spaceFlag = 0;
    field_0x295 = 0;
#if VERSION > VERSION_DEMO
    field_0x296 = 0;
#endif
}

/* 8002E794-8002E7DC       .text __dt__21fopMsgM_msgDataProc_cFv */
fopMsgM_msgDataProc_c::~fopMsgM_msgDataProc_c() {}

/* 8002E7DC-8002E95C       .text dataInit__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::dataInit() {
    field_0x14 = 0.0f;
    field_0x18 = 0.0f;
    field_0x1C = 0.0f;
    field_0x20 = 0.0f;
    field_0x24 = 0.0f;
    field_0x28 = 0.0f;
    for (int i = 0; i < 4; i++) {
        field_0xD8[i] = 0;
        field_0xF8[i] = 0;
        field_0xE8[i] = 0;
        field_0x108[i] = 0;
    }
    field_0x21C = 0;
    field_0xD4[2] = 0;
    field_0xD4[1] = 0;
    field_0xD4[0] = 0;
    field_0x2C = 0;
    field_0x30 = 0;
    field_0x34 = 0;
    field_0x38 = 0;
    count = 0;
    charSpace = 0;
    rubyCharSpace = 0;
    lineSpace = 0;
    lineWidth = 0;
    centerLineWidth = 0;
    lineCount = 0;
    field_0x134 = 0;
    nowLine = 0;
    aimLine = 0;
    field_0x140 = 0;
    fontSize = 0;
    field_0x148 = 0;
    rubyFontSize = 0;
    field_0x150 = 0;
    field_0x154 = 0;
    field_0x158 = 0;
    spaceTimer = 1;
    sendSpeed = 1;
    field_0x164 = 0;
    field_0x29D = 0;
    field_0x260 = 0;
    field_0x264 = 0.0f;
    field_0x268 = 0.0f;
    field_0x26C = 0.0f;
    field_0x270 = 0.0f;
    field_0x278 = 0.0f;
    field_0x274 = 0.0f;
    field_0x293 = 0;
    field_0x292 = 0;
    field_0x291 = 0;
    field_0x290 = 0;
    mesgStatus = 6;
    field_0x27D = 0;
    field_0x27E = 0;
    field_0x27F = 0;
    field_0x280 = 0;
    for (int i = 0; i < 0xF; i++) {
        field_0x168[i] = 0;
        field_0x1A4[i] = 0;
        field_0x1E0[i] = 0;
        field_0x281[i] = 0xFF;
        field_0x220[i] = 0;
    }
    field_0x299 = 0;
    field_0x29A = 0;
    selectFlag = 0;
    field_0x29B = 0;
    autoSendFlag = 0;
    handSendFlag = 0;
    spaceFlag = 0;
    field_0x295 = 0;
#if VERSION > VERSION_DEMO
    field_0x296 = 0;
#endif
}

/* 8002E95C-8002EA58       .text charLength__21fopMsgM_msgDataProc_cFiib */
f32 fopMsgM_msgDataProc_c::charLength(int i_scale, int i_charNo, bool param_2) {
    JUTFont::TWidth width;
    font[0]->getWidthEntry(i_charNo, &width);
    f32 charWidth = (f32)(int)width.field_0x1;
    f32 cellWidth = (f32)i_scale / (f32)font[0]->getCellWidth();

    if (param_2) {
        return charWidth * cellWidth;
    } else {
        return charSpace + (charWidth * cellWidth);
    }
}

/* 8002EA58-8002EB4C       .text rubyLength__21fopMsgM_msgDataProc_cFib */
f32 fopMsgM_msgDataProc_c::rubyLength(int i_charNo, bool param_2) {
    JUTFont::TWidth width;
    font[1]->getWidthEntry(i_charNo, &width);
    s32 advance = width.field_0x1;
    f32 width2 = font[1]->getCellWidth();
    f32 temp = ((s32)rubyFontSize / width2);
    if (param_2) {
        return advance * temp;
    }

    return (s32)rubyCharSpace + advance * temp;
}

/* 8002EB4C-80031064       .text stringLength__21fopMsgM_msgDataProc_cFv */
u32 fopMsgM_msgDataProc_c::stringLength() {
    /* Nonmatching */
}

/* 800310E4-800312B4       .text stringShift__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::stringShift() {
    /* Nonmatching */
}

/* 800312B4-80031420       .text iconSelect__21fopMsgM_msgDataProc_cFiUc */
void fopMsgM_msgDataProc_c::iconSelect(int param_1, u8 i_iconNo) {
    if (field_0x280 < 0xF) {
        field_0x281[field_0x280] = i_iconNo;
        field_0x168[field_0x280] = field_0x20;
        field_0x1A4[field_0x280] = lineCount;
        field_0x1E0[field_0x280] = param_1;
        field_0x220[field_0x280] = field_0x25C;
        field_0x280++;
    }

    if (i_iconNo != 0x16) {
        field_0x150++;
        field_0x14 += param_1;
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
        char buf[16];
        sprintf(buf, "\x1B""CR[%d]", param_1);
        strcat(field_0x60, buf);
        strcat(field_0x68, buf);
        count += bmgData[count + 1];
    }
}

/* 80031420-8003144C       .text iconIdxRefresh__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::iconIdxRefresh() {
    for (int i = 0; i < 0xF; i++) {
        field_0x281[i] = 0xFF;
    }

    field_0x280 = 0;
}

/* 8003144C-80031808       .text fopMsgM_arrowAnime__FP10J2DPicturePs */
void fopMsgM_arrowAnime(J2DPicture* i_iconPic, s16* param_2) {
    GXColor white, black;
    white.a = 0xFF;
    black.a = 0x0;
    u8 alpha = 0;

    static const GXColor color1 = {0xFF, 0x50, 0x50, 0x00};
    static const GXColor color2 = {0xFF, 0x96, 0x96, 0x00};

    if (*param_2 < 0x16) {
        float temp = fopMsgM_valueIncrease(0x16, *param_2, 2);
        black.r = temp * (color2.r - color1.r) + color1.r;
        white.r = black.r;
        black.g = temp * (color2.g - color1.g) + color1.g;
        white.g = black.g;
        black.b = temp * (color2.b - color1.b) + color1.b;
        white.b = black.b;
        alpha = g_msgHIO.field_0x2c + temp * (g_msgHIO.field_0x30 - g_msgHIO.field_0x2c);
    } else {
        float temp = fopMsgM_valueIncrease(0x16, *param_2 - 0x16, 2);
        black.r = temp * (color1.r - color2.r) + color2.r;
        white.r = black.r;
        black.g = temp * (color1.g - color2.g) + color2.g;
        white.g = black.g;
        black.b = temp * (color1.b - color2.b) + color2.b;
        white.b = black.b;
        alpha = g_msgHIO.field_0x30 + temp * (g_msgHIO.field_0x2c - g_msgHIO.field_0x30);
    }

    *param_2 += 1;
    if (*param_2 >= 45) {
        *param_2 = 0;
    }

    i_iconPic->setWhite(white);
    i_iconPic->setBlack(black);
    i_iconPic->setAlpha(alpha);
}

/* 80031808-800319D8       .text selectCheck2__21fopMsgM_msgDataProc_cFP7J2DPaneiii */
int fopMsgM_msgDataProc_c::selectCheck2(J2DPane* param_1, int param_2, int param_3, int param_4) {
    field_0x264 = param_1->getWidth() / 2.0f;
    field_0x268 = param_1->getHeight() / 2.0f;
    field_0x278 = g_msgHIO.field_0x70;
    field_0x274 = g_msgHIO.field_0x70;
    int temp = field_0x164 > 0 ? field_0x164 - 1 : 0;
    field_0x164 = temp;

    if (!temp) {
        if (g_mDoCPd_cpadInfo[0].mMainStickPosY > 0.7f) {
            if (field_0x27D == 1) {
                field_0x27D = 0;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        } else if (g_mDoCPd_cpadInfo[0].mMainStickPosY < -0.7f) {
            if (field_0x27D == 0) {
                field_0x27D = 1;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        }
    }

    field_0x26C = param_2;
    field_0x270 = param_3 + field_0x27D * param_4;
    return field_0x27D;
}

/* 800319D8-80031C38       .text selectCheck3__21fopMsgM_msgDataProc_cFP7J2DPaneiii */
int fopMsgM_msgDataProc_c::selectCheck3(J2DPane* param_1, int param_2, int param_3, int param_4) {
    field_0x264 = param_1->getWidth() / 2.0f;
    field_0x268 = param_1->getHeight() / 2.0f;
    field_0x278 = g_msgHIO.field_0x70;
    field_0x274 = g_msgHIO.field_0x70;
    int temp = field_0x164 > 0 ? field_0x164 - 1 : 0;
    field_0x164 = temp;

    if (!temp) {
        if (g_mDoCPd_cpadInfo[0].mMainStickPosY > 0.7f) {
            if (field_0x27D == 1) {
                field_0x27D = 0;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            } else if (field_0x27D == 2) {
                field_0x27D = 1;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        } else if (g_mDoCPd_cpadInfo[0].mMainStickPosY < -0.7f) {
            if (field_0x27D == 0) {
                field_0x27D = 1;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            } else if (field_0x27D == 1) {
                field_0x27D = 2;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        }
    }

    field_0x26C = param_2;
    field_0x270 = param_3 + field_0x27D * param_4;
    return field_0x27D;
}

/* 80031C38-80031E04       .text selectCheckYoko__21fopMsgM_msgDataProc_cFP7J2DPaneiii */
int fopMsgM_msgDataProc_c::selectCheckYoko(J2DPane* param_1, int param_2, int param_3, int param_4) {
    field_0x264 = param_1->getWidth() / 2.0f;
    field_0x268 = param_1->getHeight() / 2.0f;
    field_0x278 = g_msgHIO.field_0x70;
    field_0x274 = g_msgHIO.field_0x70;
    int temp = field_0x164 > 0 ? field_0x164 - 1 : 0;
    field_0x164 = temp;

    if (!temp) {
        if (g_mDoCPd_cpadInfo[0].mMainStickPosX < -0.7f) {
            if (field_0x27D == 1) {
                field_0x27D = 0;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        } else if (g_mDoCPd_cpadInfo[0].mMainStickPosX > 0.7f) {
            if (field_0x27D == 0) {
                field_0x27D = 1;
                field_0x164 = 10;
                mDoAud_seStart(JA_SE_TALK_CURSOR);
            }
        }
    }

    field_0x26C = param_2 + field_0x27D * param_4;
    field_0x270 = param_3;
    return field_0x27D;
}

/* 80031E04-800320E0       .text inputNumber__21fopMsgM_msgDataProc_cFi */
int fopMsgM_msgDataProc_c::inputNumber(int param_1) {
    s16 temp = dComIfGp_getMessageSetNumber();
    bool temp2 = false;

    stick.setWaitParm(5, 2, 3, 2, 0.9f, 0.5f, 0, 0x2000);
    stick.checkTrigger();
    if (stick.checkRightTrigger()) {
        if (field_0x27D != 0) {
            field_0x27D--;
            mDoAud_seStart(JA_SE_AUC_BID_CURSOR_LR);
        }
    } else if (stick.checkLeftTrigger()) {
        if (field_0x27D < param_1 - 1) {
            field_0x27D++;
            mDoAud_seStart(JA_SE_AUC_BID_CURSOR_LR);
        }
    }

    if (stick.checkUpTrigger()) {
        if (field_0x27D == 0) {
            if (temp < 999) {
                temp2 = true;
                temp += 1;
            }
        } else if (field_0x27D == 1) {
            if (temp < 999) {
                temp += 10;
                if (temp > 999) {
                    temp = 99;
                }

                temp2 = true;
            }
        } else if (field_0x27D == 2) {
            if (temp < 999) {
                temp += 100;
                if (temp > 999) {
                    temp = 999;
                }

                temp2 = true;
            }
        }
    } else if (stick.checkDownTrigger()) {
        if (field_0x27D == 0) {
            if (temp > 0) {
                temp2 = true;
                temp -= 1;
            }
        } else if (field_0x27D == 1) {
            if (temp > 0) {
                temp -= 10;
                if (temp < 0) {
                    temp = 0;
                }

                temp2 = true;
            }
        } else if (field_0x27D == 2) {
            if (temp > 0) {
                temp -= 100;
                if (temp < 0) {
                    temp = 0;
                }

                temp2 = true;
            }
        }
    }

    if (param_1 == 2) {
        if (temp > daNpc_Bs1_c::m_tag_buy_item_max) {
            temp = daNpc_Bs1_c::m_tag_buy_item_max;
        } else if (temp < 1) {
            temp = 1;
        } else if (temp2) {
            mDoAud_seStart(JA_SE_AUC_BID_CURSOR_UD);
        }
    } else if (temp2) {
        mDoAud_seStart(JA_SE_AUC_BID_CURSOR_UD);
    }

    dComIfGp_setMessageSetNumber(temp);
    return field_0x27D;
}

/* 800320E0-800321CC       .text selectArrow__21fopMsgM_msgDataProc_cFP10J2DPictureffff */
void fopMsgM_msgDataProc_c::selectArrow(J2DPicture* param_1, f32 param_2, f32 param_3, f32 param_4, f32 param_5) {
    param_1->mBasePosition.x = param_4 / 2.0f;
    param_1->mBasePosition.y = param_5 / 2.0f;
    param_1->mRotationAxis = 'z';
    param_1->mRotation = 90.0f;
    param_1->calcMtx();
    fopMsgM_arrowAnime(param_1, &field_0x260);
    param_1->draw(param_2, param_3, param_4, param_5, false, false, false);
}

/* 800321CC-80032288       .text selectArrow__21fopMsgM_msgDataProc_cFP10J2DPictureff */
void fopMsgM_msgDataProc_c::selectArrow(J2DPicture* param_1, f32 param_2, f32 param_3) {
    param_1->mBasePosition.x = param_2 / 2.0f;
    param_1->mBasePosition.y = param_3 / 2.0f;
    param_1->mRotationAxis = 'z';
    param_1->mRotation = 90.0f;
    param_1->calcMtx();
    param_1->resize(param_2, param_3);
    fopMsgM_arrowAnime(param_1, &field_0x260);
}

/* 80032288-800322B4       .text colorAnime__21fopMsgM_msgDataProc_cFP10J2DPicture */
void fopMsgM_msgDataProc_c::colorAnime(J2DPicture* i_pic) {
    fopMsgM_arrowAnime(i_pic, &field_0x260);
}

/* 800322B4-80034F3C       .text stringSet__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::stringSet() {
    /* Nonmatching */
    field_0x60 = field_0x40;
    field_0x64 = field_0x44;
    field_0x68 = field_0x48;
    field_0x6C = field_0x4C;
    mesgStatus = 6;

    if (bmgData[count] == '\0') {
        if (field_0x27E != 0) {
            field_0x27E = 0;
            field_0x60[field_0x2C] = '\0';
            field_0x68[field_0x30] = '\0';
            strcat(field_0x60, field_0xD4);
            strcat(field_0x68, field_0xD4);
        }
        if (field_0x27F != 0) {
            field_0x27F = 0;
            field_0x64[field_0x34] = '\0';
            field_0x6C[field_0x38] = '\0';
            strcat(field_0x64, field_0x70);
            strcat(field_0x6C, field_0x70);
        }
        if (mesgStatus != 8 && mesgStatus != 9 && mesgStatus != 0x14 && mesgStatus != 0x15) {
            if (mesgEntry->mTextboxType != 2 && mesgEntry->mTextboxType != 6 && mesgEntry->mTextboxType != 7 && mesgEntry->mTextboxType != 0xB &&
                mesgEntry->mTextboxType != 5 && mesgEntry->mTextboxType != 0xD && mesgEntry->mTextboxType != 9)
            {
                if (dComIfGp_roomControl_getStayNo()) {
                    mDoAud_messageSePlay(0, 0, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
                } else {
                    mDoAud_messageSePlay(0, 0, 0);
                }
            }

            if (fopMsgM_nextMsgFlagCheck()) {
                if (mesgEntry->mNextMsgNo != 0) {
                    fopMsgM_messageSet(mesgEntry->mNextMsgNo);
                    mesgStatus = 0xF;
                } else {
                    mesgStatus = 0x10;
                }
            } else {
                if (getAutoSendFlag() || getHandSendFlag()) {
                    mesgStatus = 0xA;
                } else {
                    mesgStatus = 0xE;
                }
            }
        }

        return;
    }

    while (true) {
        while (true) {
            if (bmgData[count] == '\0') {
                if (field_0x299 == 0 && field_0x29A == 0 && autoSendFlag == 0 && handSendFlag == 0 && selectFlag) {
                    return;
                }

                if (field_0x27E != 0) {
                    field_0x27E = 0;
                    field_0x60[field_0x2C] = '\0';
                    field_0x68[field_0x30] = '\0';
                    strcat(field_0x60, field_0xD4);
                    strcat(field_0x68, field_0xD4);
                }
                if (field_0x27F != 0) {
                    field_0x27F = 0;
                    field_0x64[field_0x34] = '\0';
                    field_0x6C[field_0x38] = '\0';
                    strcat(field_0x64, field_0x70);
                    strcat(field_0x6C, field_0x70);
                }

                if (mesgStatus == 8 || mesgStatus == 9 || mesgStatus == 0x14 || mesgStatus == 0x15) {
                    return;
                }

                if (mesgEntry->mTextboxType != 2 && mesgEntry->mTextboxType != 6 && mesgEntry->mTextboxType != 7 && mesgEntry->mTextboxType != 0xB &&
                    mesgEntry->mTextboxType != 5 && mesgEntry->mTextboxType != 0xD && mesgEntry->mTextboxType != 9)
                {
                    if (dComIfGp_roomControl_getStayNo()) {
                        mDoAud_messageSePlay(0, 0, dComIfGp_getReverb(dComIfGp_roomControl_getStayNo()));
                    } else {
                        mDoAud_messageSePlay(0, 0, 0);
                    }
                }

                if (fopMsgM_nextMsgFlagCheck()) {
                    if (mesgEntry->mNextMsgNo != 0) {
                        fopMsgM_messageSet(mesgEntry->mNextMsgNo);
                        mesgStatus = 0xF;
                    } else {
                        mesgStatus = 0x10;
                    }
                } else {
                    if (getAutoSendFlag() || getHandSendFlag()) {
                        mesgStatus = 0xA;
                    } else {
                        mesgStatus = 0xE;
                    }
                }
            }

            if (field_0x27E != 0) {
                field_0x27E = 0;
                field_0x60[field_0x2C] = '\0';
                field_0x68[field_0x30] = '\0';
                strcat(field_0x60, field_0xD4);
                strcat(field_0x68, field_0xD4);
            }
            if (field_0x27F != 0) {
                field_0x27F = 0;
                field_0x64[field_0x34] = '\0';
                field_0x6C[field_0x38] = '\0';
                strcat(field_0x64, field_0x70);
                strcat(field_0x6C, field_0x70);
            }

            u32 origOffset = count;
            const char* temp = &bmgData[origOffset];
            if (*temp != 0x1A)
                break;
            if (temp[2] == 0xFF && temp[3] == 0 && temp[4] == 0) {
                if (mesgEntry->mMsgNo == 0x42 || mesgEntry->mMsgNo == 0x43 || mesgEntry->mMsgNo == 0x44 || mesgEntry->mMsgNo == 0x45 ||
                    mesgEntry->mMsgNo == 0x46 || mesgEntry->mMsgNo == 0x47 || mesgEntry->mMsgNo == 0x48 || mesgEntry->mMsgNo == 0x49 ||
                    mesgEntry->mMsgNo == 0x4A || mesgEntry->mMsgNo == 0x4B)
                {
                    static const u32 colorTable[9] = {
                        0x000000FF,
                        0xB40000FF,
                        0x008282FF,
                        0x0000AAFF,
                        0xF0F01EFF,
                        0x82FFFFFF,
                        0x6400FFFF,
                        0x505050FF,
                        0xFFB400FF,
                    };
                    field_0x25C = colorTable[temp[5]];
                    char buf[16];
                    sprintf(buf, "\x1B""CC[%08x]\x1B""GM[0]", field_0x25C);
                    strcat(field_0x60, buf);
                } else {
                    if (temp[5] > -1 && temp[5] < 9) {
                        if (mesgEntry->mTextboxType == 2 || mesgEntry->mTextboxType == 6 || mesgEntry->mTextboxType == 7) {
                            static const u32 colorTable[9] = {
                                0x00000000,
                                0xB4000000,
                                0x00828200,
                                0x0000AA00,
                                0xF0F01E00,
                                0x82FFFF00,
                                0x6400FF00,
                                0x50505000,
                                0xFFB40000,
                            };
                            field_0x25C = colorTable[mesgEntry->mTextboxType];
                            char buf[16];
                            sprintf(buf,"\x1B""CC[%08x]\x1B""GC[%08x]", field_0x25C | field_0x290, field_0x25C | field_0x291);
                            strcat(field_0x60, buf);
                        }
                    } else if (temp[5] == 0xB) {
                        static const u32 colorTable[9] = {
                            0x000000FF,
                            0xB40000FF,
                            0x008282FF,
                            0x0000AAFF,
                            0xE67D0FFF,
                            0x82FFFFFF,
                            0x6400FFFF,
                            0x3C3C3CFF,
                            0xFFB400FF,
                        };
                        field_0x25C = colorTable[temp[5]];
                        char buf[16];
                        sprintf(buf,  "\x1B""CC[%08x]\x1B""GM[0]", field_0x25C);
                        strcat(field_0x60, buf);
                    } else {
                        field_0x25C = fopMsgM_getColorTable(temp[5]);
                        char buf[16];
                        sprintf(buf, "\x1B""CC[%08x]\x1B""GM[0]", field_0x25C);
                        strcat(field_0x60, buf);
                    }
                }

                count += bmgData[count + 1];
            } else if (temp[2] == 0xFF && temp[3] == 0 && temp[4] == 1) {
                f32 temp2 = *(u16*)(&temp[5]);
                u32 temp3 = field_0x148;
                field_0x148 = fontSize * temp2 * 0.1f + 0.5f;
                if (field_0x134 == 0) {
                    fopMsgM_setFontsizeCenter(field_0x60, field_0x68, field_0x64, field_0x6C, temp3, field_0x148);
                    if (temp2 * 0.1f > 1.0f && field_0x29D == 0) {
                        field_0x29D = 1;
                    }
                } else {
                    if (temp2 * 0.1f > 1.0f && field_0x29D == 0) {
                        strcat(field_0x60, "\n");
                        strcat(field_0x64, "\n");
                        strcat(field_0x68, "\n");
                        strcat(field_0x6C, "\n");
                        char buf[16];
                        sprintf(buf, "\x1B""CR[%d]", field_0x20);
                        strcat(field_0x60, buf);
                        strcat(field_0x68, buf);
                        field_0x29D = 1;
                    }
                    fopMsgM_setFontsizeCenter2(field_0x60, field_0x68, field_0x64, field_0x6C, temp3, field_0x148, fontSize, lineSpace);
                }

                count += bmgData[count + 1];
            } else if (temp[2] == 0xFF && temp[3] == 0 && temp[4] == 2) {
                if (temp[1] != 5) {
                    strcpy(field_0x70, "");
                    field_0x18 = 0.0f;
                    field_0x1C = 0.0f;
                    field_0x28 = field_0x20;
                    field_0x154 = bmgData[count + 5];
                    count += 6;
                    while (count < origOffset + temp[2]) {
                        char buf[3];
                        buf[0] = bmgData[count];
                        buf[1] = bmgData[count + 1];
                        buf[2] = '\0';
                        strcat(field_0x70, buf);
                        u16 temp2 = *(u16*)(&bmgData[count]);
                        if (field_0x29B == 0) {
                            field_0x18 = rubyLength(temp2, true);
                            field_0x29B = 1;
                        } else {
                            field_0x18 += rubyLength(temp2, false);
                        }

                        count += 2;
                    }
                }
            } else if (temp[2] == 0 && temp[3] == 0 && temp[4] == 0) {
                char buf[12];
                strcpy(buf, dComIfGs_getPlayerName());
                if (
#if VERSION > VERSION_JPN
                    dComIfGs_getPalLanguage() == 1 &&
#endif 
                        (mesgEntry->mMsgNo == 0x33B ||
                        mesgEntry->mMsgNo == 0xC8B  ||
                        mesgEntry->mMsgNo == 0x1D21 ||
                        mesgEntry->mMsgNo == 0x31D7 ||
                        mesgEntry->mMsgNo == 0x37DD ||
                        mesgEntry->mMsgNo == 0x37DE)
                ) {
                    s32 bufLen = strlen(buf);
                    char current = (buf)[bufLen - 1];
                    if (current == 's' || current == 'S' || current == 'z' || current == 'Z' || current == 'x' || current == 'X') {
                        strcat(buf, "\'");
                    } else {
                        strcat(buf, "s");
                    }
                }

                u32 curOffset = 0;
                for (s32 i = 0; buf[i] != '\0'; i++) {
                    char c = buf[i];
                    if (c == '\0')
                        break;
                    if ((c >> 4) == 8 || (c >> 4) == 9) {
                        field_0xD4[0] = buf[curOffset];
                        field_0xD4[1] = buf[curOffset + 1];
                        field_0xD4[2] = '\0';
                        curOffset += 2;
                    } else {
                        field_0xD4[0] = buf[curOffset];
                        field_0xD4[1] = '\0';
                        curOffset += 1;
                    }
                    if (field_0x150 == 0) {
                        field_0x14 = charLength(field_0x148, c, true);
                    } else {
                        field_0x14 += charLength(field_0x148, c, false);
                    }

                    strcat(field_0x60, field_0xD4);
                    strcat(field_0x68, field_0xD4);
                    field_0x150 += 1;
                }

                if (selectFlag != 1) {
                    field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
                } else {
                    field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
                }

                count += bmgData[count + 1];
            } else if (temp[2] == 0 && temp[3] == 0 && temp[4] == 1) {
                field_0x29A = 1;
                count = bmgData[count + 1];
            } else if (temp[2] == 0 && temp[3] == 0 && temp[4] == 2) {
                field_0x29A = 0;
                count = bmgData[count + 1];
            } else if (temp[2] == 0 && temp[3] == 0 && temp[4] == 3) {
                field_0x158 = temp[5] << 8;
                field_0x158 |= bmgData[count + 6];
                setAutoSendFlagOn();
                count = bmgData[count + 1];
            }

            sprintf(field_0x60, "\x1B""CL[%d]", 0.5f);
        }
    }

    if (field_0x154 != 0) {
        field_0x1C = field_0x20 - field_0x28;

        int temp1 = field_0x28 + field_0x1C / 2.0f - field_0x18 / 2.0f + 0.5f;
        if (field_0x24 > temp1) {
            char temp[16];
            sprintf(temp, "\x1b""CR[%d]", (int)(field_0x24 - temp1 + 0.5f));
            strcat(field_0x64, temp);
            strcat(field_0x6C, temp);
        } else if (temp1 == 0.0f) {
            char temp[16];
            sprintf(temp,  "\x1b""CL[%d]", (int)(temp1 - field_0x24 + 0.5f));
            strcat(field_0x64, temp);
            strcat(field_0x6C, temp);
        }

        strcat(field_0x64, field_0x70);
        strcat(field_0x6C, field_0x70);
        field_0x154 = 0;
    }

    strcat(field_0x60, "\n");
    strcat(field_0x64, "\n");
    strcat(field_0x68, "\n");
    strcat(field_0x6C, "\n");
    count++;
    lineCount++;
    if (field_0x29D) {
        lineCount++;
        field_0x29D = 0;
    }
}

/* 80034F5C-80034F68       .text setSelectFlagYokoOn__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::setSelectFlagYokoOn() {
    selectFlag = 2;
}

/* 80034F68-80034F74       .text setSelectFlagOn__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::setSelectFlagOn() {
    selectFlag = 1;
}

/* 80034F74-80034F80       .text setHandSendFlagOn__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::setHandSendFlagOn() {
    handSendFlag = 1;
}

/* 80034F80-80034F8C       .text setAutoSendFlagOn__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::setAutoSendFlagOn() {
    autoSendFlag = 1;
}

/* 80034F8C-80034F94       .text getHandSendFlag__21fopMsgM_msgDataProc_cFv */
u8 fopMsgM_msgDataProc_c::getHandSendFlag() {
    return handSendFlag;
}

/* 80034F94-80034F9C       .text getAutoSendFlag__21fopMsgM_msgDataProc_cFv */
u8 fopMsgM_msgDataProc_c::getAutoSendFlag() {
    return autoSendFlag;
}

/* 80034FE0-80034FF4       .text fopMsgM_itemNumIdx__FUc */
u8 fopMsgM_itemNumIdx(u8 i_no) {
    return itemicon[i_no].itemNo;
}

/* 80034FF4-80035060       .text fopMsgM_itemNum__FUc */
u8 fopMsgM_itemNum(u8 i_itemNo) {
    u8 invIdx = 0;
    for (u8 i = 0; i < ARRAY_SIZE(itemicon); i++) {
        if (i_itemNo == fopMsgM_itemNumIdx(i)) {
            invIdx = i;
            break;
        }
    }
    return invIdx;
}

/* 80035060-800350B8       .text fopMsgM_getColorTable__FUs */
u32 fopMsgM_getColorTable(u16 i_colorNo) {
    JKRArchive* arc = dComIfGp_getMsgDtArchive();
    u32* resource = (u32*)JKRArchive::getGlbResource('ROOT', "color.bmc", arc);
    return resource[i_colorNo + 0x0b]; // probably a struct i have no idea what it looks like though
}

/* 800350B8-80035170       .text fopMsgM_int_to_char__FPcib */
void fopMsgM_int_to_char(char* i_dest, int i_value, bool param_3) {
    int temp = 10000;
    bool temp2 = false;
#if VERSION > VERSION_JPN
    char buf[2];
    buf[1] = '\0';
#else
    char buf[3];
    // The JPN version uses shift-jis digits instead of ascii ones- this is the
    // high byte for those digits
    buf[0] = '\x82';
    buf[2] = '\0';
#endif

    if (!param_3) {
        strcpy(i_dest, "");
    }

    for (int i = 0; i < 5; i++) {
        if (i_value / temp != 0 || temp2 || temp == 1) {
#if VERSION > VERSION_JPN
            buf[0] = (i_value / temp) + '0';
#else
            buf[1] = (i_value / temp) + '\x4F';
#endif
            strcat(i_dest, buf);
            if (!temp2) {
                temp2 = true;
            }
        }

        i_value %= temp;
        temp /= 10;
    }
}

#if VERSION >= VERSION_USA
/* 80035170-800351E8       .text fopMsgM_int_to_char2__FPci */
void fopMsgM_int_to_char2(char* i_dest, int i_value) {
    char buf[2];
    buf[1] = '\0';
    buf[0] = (i_value / 10) + '0';
    strcat(i_dest, buf);
    buf[0] = i_value % 10 + '0';
    strcat(i_dest, buf);
}
#endif

/* 800351E8-80035408       .text getString__21fopMsgM_msgDataProc_cFPcUl */
void fopMsgM_msgDataProc_c::getString(char* i_dest, u32 i_msgNo) {
    /* Nonmatching */
    s32 i;
    fopMsgM_msgGet_c msgGet;
    msgGet.mMsgIdx = 0;
    msgGet.mGroupID = 0;
    msgGet.mMsgNo = 0;
    msgGet.mResMsgNo = 0;
#if VERSION > VERSION_JPN
    static const char* name = "no name";

    s32 curOffset = 0;
    s32 numRead = 0;
#endif

    mesg_header* header;
    const char* src;
#if VERSION > VERSION_JPN
    if (i_msgNo == 0) {
        src = name;
    } else
#endif
    {
        header = msgGet.getMesgHeader(i_msgNo);
        src = msgGet.getMessage(header);
    }

#if VERSION <= VERSION_JPN
    s32 curOffset = 0;
    s32 numRead = 0;
#endif

    const u8* cursor;
    s32 current;
    while (cursor = (u8*)src + curOffset, current = *cursor, (s8)*cursor != '\0') {
        if (*cursor == 0x1A) {
            int codeLen = cursor[1];
            if (cursor[2] == 0 && cursor[3] == 0 && cursor[4] == 0) {
#if VERSION > VERSION_JPN
                char str[24];
                strcpy(str, dComIfGs_getPlayerName());
                if (dComIfGs_getPalLanguage() == 1 &&
                    (
#if VERSION == VERSION_PAL
                        // Version is PAL
                        i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7
#else
                        // Version is USA, we know it's not DEMO or JPN because of the outer #if
                        i_msgNo == 0x33B || i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7 || i_msgNo == 0x37DD ||
                        i_msgNo == 0x37DE
#endif
                    )
                ) {
                    s32 bufLen = strlen(str);
                    current = (str)[bufLen - 1];
                    if (current == 's' || current == 'S' || current == 'z' || current == 'Z' || current == 'x' || current == 'X') {
                        strcat(str, "\'");
                    } else {
                        strcat(str, "s");
                    }
                }
#else
                const char* str = dComIfGs_getPlayerName();
#endif

                for (i = 0; str[i] != '\0'; i++) {
                    i_dest[numRead] = str[i];
                    numRead++;
                }
            }

            curOffset += codeLen;
        } else {
            i_dest[numRead] = current;
            curOffset++;
            numRead++;
        }
    }

    i_dest[numRead] = '\0';
}

/* 80035408-80035A24       .text getString__21fopMsgM_msgDataProc_cFPcPcPcPcUlPfPfPi */
void fopMsgM_msgDataProc_c::getString(char* i_dest, char*, char*, char*, u32 i_msgNo, f32*, f32*, int*) {
    /* Nonmatching */
    fopMsgM_msgGet_c msgGet;
    msgGet.mMsgIdx = 0;
    msgGet.mGroupID = 0;
    msgGet.mMsgNo = 0;
    msgGet.mResMsgNo = 0;
    static const char* name = "no name";

    s32 curOffset = 0;
    s32 numRead = 0;

    mesg_header* header;
    const char* src;
    if (i_msgNo == 0) {
        src = name;
    } else {
        header = msgGet.getMesgHeader(i_msgNo);
        src = msgGet.getMessage(header);
    }

    char dstBuf[24];
    const u8* cursor;
    s32 current;
    while (cursor = (u8*)src + curOffset, current = *cursor, (s8)*cursor != '\0') {
        if (*cursor == 0x1A) {
            int codeLen = cursor[1];
            if (cursor[2] == 0 && cursor[3] == 0 && cursor[4] == 0) {
                strcpy(dstBuf, dComIfGs_getPlayerName());
                if(
#if VERSION > VERSION_JPN
                    dComIfGs_getPalLanguage() == 1 &&
#endif
                     (i_msgNo == 0x33B || i_msgNo == 0xC8B || i_msgNo == 0x1D21 || i_msgNo == 0x31D7 || i_msgNo == 0x37DD || i_msgNo == 0x37DE)
                ) {
                    s32 bufLen = strlen(dstBuf);
                    current = (dstBuf)[bufLen - 1];
                    if (current == 's' || current == 'S' || current == 'z' || current == 'Z' || current == 'x' || current == 'X') {
                        strcat(dstBuf, "\'");
                    } else {
                        strcat(dstBuf, "s");
                    }
                }

                for (s32 i = 0; dstBuf[i] != '\0'; i++) {
                    i_dest[numRead] = dstBuf[i];
                    numRead++;
                }
            }

            curOffset += codeLen;
        } else {
            i_dest[numRead] = current;
            curOffset++;
            numRead++;
        }
    }

    i_dest[numRead] = '\0';
}

/* 80035A24-80035D28       .text getRubyString__21fopMsgM_msgDataProc_cFPcPcPcPcPcPcPfPfPi */
void fopMsgM_msgDataProc_c::getRubyString(char* param_1, char* param_2, char* param_3, char* param_4, char* param_5, char* param_6, f32* param_7, f32* param_8, int* param_9) {
    /* Nonmatching */
    f32 temp = *param_7;

    char* p1 = param_5;
    while (*p1 != '\0') {
        u8 c = *(u8*)p1;
        p1++;
        if (*param_9 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        *param_9 += 1;
    }

    strcat(param_1, param_5);
    strcat(param_2, param_5);

    if (selectFlag != 1) {
        *param_7 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        *param_7 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    f32 temp3 = 0.0f;
    p1 = param_6;
    while (*p1 != '\0') {
        u8 c = *(u8*)p1;
        p1++;

        temp3 += rubyLength(c, false);
    }

    char buf[12];
    int temp2 = temp + (*param_7 - temp) / 2.0f - (temp3 / 2.0f) + 0.5f;
    temp2 = (temp2 - *param_8) + 0.5f;
    if (temp2 > 0) {
        sprintf(buf, "\x1B""CR[%d]", temp2);
        strcat(param_3, buf);
        strcat(param_4, buf);
        *param_8 += temp2;
    } else if (temp2 == 0) {
        sprintf(buf, "\x1B""CL[%d]", temp2);
        strcat(param_3, buf);
        strcat(param_4, buf);
        *param_8 -= temp2;
    }

    *param_8 += temp3;
    strcat(param_3, param_6);
    strcat(param_4, param_6);
}

#if VERSION >= VERSION_USA
/* 80035D28-80035E40       .text tag_len_kaisen_game__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_kaisen_game(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[12];
    fopMsgM_int_to_char(buf, dComIfGs_getEventReg(dSv_event_flag_c::UNK_BEFF), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " coups");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcat(buf, " ca\361onazos");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " cannonate");
    } else {
        strcat(buf, "");
    }
#else
    strcat(buf, "");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80035E40-80035F68       .text tag_len_rupee__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_rupee(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    s16 num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80035F68-80036068       .text tag_len_num_input__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_num_input(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[12];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "000 Rubin(e)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "000 rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "000 rupia(s)");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "000 Rupie");
    } else {
        strcpy(buf, "000 Rupee(s)");
    }
#else
    strcpy(buf, "000 Rupee(s)");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036068-80036190       .text tag_len_sword_game__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_sword_game(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    s16 num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, " Treffer");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " fois");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " golpes");
        } else {
            strcat(buf, " golpe");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, " colpi");
        } else {
            strcat(buf, " colpo");
        }
    } else {
        if (num != 1) {
            strcat(buf, " blows");
        } else {
            strcat(buf, " blow");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " blows");
    } else {
        strcat(buf, " blow");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036190-80036280       .text tag_len_letter_game__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_letter_game(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    fopMsgM_int_to_char(buf, dComIfGp_getMiniGameRupee(), false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036280-80036384       .text tag_len_letter_game_max__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_letter_game_max(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];
    fopMsgM_int_to_char(buf, dComIfGs_getEventReg(dSv_event_flag_c::UNK_8AFF), false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036384-80036474       .text tag_len_fish__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_fish(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];
    fopMsgM_int_to_char(buf, dComIfGp_getMessageCountNumber(), false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036474-800365A0       .text tag_len_fish_rupee__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_fish_rupee(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber() * 10;
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 800365A0-800366C8       .text tag_len_letter__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_letter(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (mesgEntry->mMsgNo == 0xCEB) {
            if (num != 1) {
                strcat(buf, " Briefe");
            } else {
                strcat(buf, " Brief");
            }
        } else {
            strcat(buf, ". Brief");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " cartas");
        } else {
            strcat(buf, " carta");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " letters");
        } else {
            strcat(buf, " letter");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " letters");
    } else {
        strcat(buf, " letter");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 800366C8-800367CC       .text tag_len_rescue__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_rescue(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];
    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Freunde");
        } else {
            strcat(buf, " Freund");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, "");
    } else {
        strcat(buf, "");
    }
#else
    strcat(buf, "");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 800367CC-8003693C       .text tag_len_forest_timer__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_forest_timer(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
#if VERSION == VERSION_PAL
    char buf[32];
#else
    char buf[24];
#endif

    int minutes = dComIfGs_getFwaterTimer() / 1800;

#if VERSION == VERSION_PAL
    strcpy(buf, "");
    if (dComIfGs_getPalLanguage() == 1) {
        fopMsgM_int_to_char(buf, minutes, false);
        strcat(buf, ":");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minutes");
            } else {
                strcat(buf, " minute");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minutos");
            } else {
                strcat(buf, " minuto");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minuti");
            } else {
                strcat(buf, " minuto");
            }
        }
    } else {
        fopMsgM_int_to_char(buf, minutes, false);
        strcat(buf, ":");
    }
#else
    fopMsgM_int_to_char(buf, minutes, false);
    strcat(buf, ":");
#endif

    int seconds = (dComIfGs_getFwaterTimer() % 1800) / 30;
    if (minutes == 0 && seconds == 0) {
        seconds = 1;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        fopMsgM_int_to_char2(buf, seconds);
        strcat(buf, " Minuten");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (seconds != 0 || minutes == 0) {
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " secondes");
            } else {
                strcat(buf, " seconde");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (seconds != 0 || minutes == 0) {
            if (minutes != 0) {
                strcat(buf, " y ");
            }
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " segundos");
            } else {
                strcat(buf, " segundo");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (seconds != 0 || minutes == 0) {
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " secondi");
            } else {
                strcat(buf, " secondo");
            }
        }
    } else {
        fopMsgM_int_to_char2(buf, seconds);
        strcat(buf, "");
    }
#else
    fopMsgM_int_to_char2(buf, seconds);
    strcat(buf, "");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 8003693C-80036A64       .text tag_len_birdman__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_birdman(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, " Meter");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " m\350tres");
        } else {
            strcat(buf, " m\350tre");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " metros");
        } else {
            strcat(buf, " metro");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, " metri");
        } else {
            strcat(buf, " metro");
        }
    } else {
        if (num != 1) {
            strcat(buf, " yards");
        } else {
            strcat(buf, " yard");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " yards");
    } else {
        strcat(buf, " yard");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036A64-80036B9C       .text tag_len_point__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_point(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_86FF);
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Punkte");
        } else {
            strcat(buf, " Punkt");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " points");
        } else {
            strcat(buf, " point");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " puntos Terry");
        } else {
            strcat(buf, " punto Terry");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, " punti");
        } else {
            strcat(buf, " punto");
        }
    } else {
        if (num != 1) {
            strcat(buf, " points");
        } else {
            strcat(buf, " point");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " points");
    } else {
        strcat(buf, " point");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036B9C-80036CC4       .text tag_len_get_pendant__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_get_pendant(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = (u8)dComIfGs_getBeastNum(dBeastIdx_JOY_PENDANT_e);
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Gl\374cksamulette");
        } else {
            strcat(buf, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " Pendentifs du Bonheur");
        } else {
            strcat(buf, " Pendentif du Bonheur");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    }
#else
    if (num != 1) {
        strcat(buf, "");
    } else {
        strcat(buf, "");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036CC4-80036E18       .text tag_len_rev_pendant__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_rev_pendant(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF);
    fopMsgM_int_to_char(buf, dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Gl\374cksamulette");
        } else {
            strcat(buf, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " Pendentifs du Bonheur");
        } else {
            strcat(buf, " Pendentif du Bonheur");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    }
#else
    if (num != 1) {
        strcat(buf, "");
    } else {
        strcat(buf, "");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036E18-80036F74       .text tag_len_pig_timer__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_pig_timer(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
#if VERSION == VERSION_PAL
    char buf[32];
#else
    char buf[24];
#endif

    int minutes = dComIfGp_getItemTimer() / 1800;

#if VERSION == VERSION_PAL
    strcpy(buf, "");
    if (dComIfGs_getPalLanguage() == 1) {
        fopMsgM_int_to_char(buf, minutes, false);
        strcat(buf, ":");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minutes");
            } else {
                strcat(buf, " minute");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minutos");
            } else {
                strcat(buf, " minuto");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (minutes > 0) {
            fopMsgM_int_to_char(buf, minutes, false);
            if (minutes > 1) {
                strcat(buf, " minuti");
            } else {
                strcat(buf, " minuto");
            }
        }
    } else {
        fopMsgM_int_to_char(buf, minutes, false);
        strcat(buf, ":");
    }
#else
    fopMsgM_int_to_char(buf, minutes, false);
    strcat(buf, ":");
#endif

    int seconds = (dComIfGp_getItemTimer() % 1800) / 30;
    if (minutes == 0 && seconds == 0) {
        seconds = 1;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        fopMsgM_int_to_char2(buf, seconds);
        strcat(buf, " Minuten");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (seconds != 0 || minutes == 0) {
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " secondes");
            } else {
                strcat(buf, " seconde");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (seconds != 0 || minutes == 0) {
            if (minutes != 0) {
                strcat(buf, " y ");
            }
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " segundos");
            } else {
                strcat(buf, " segundo");
            }
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (seconds != 0 || minutes == 0) {
            fopMsgM_int_to_char(buf, seconds, true);
            if (seconds > 1) {
                strcat(buf, " secondi");
            } else {
                strcat(buf, " secondo");
            }
        }
    } else {
        fopMsgM_int_to_char2(buf, seconds);
        strcat(buf, "");
    }
#else
    fopMsgM_int_to_char2(buf, seconds);
    strcat(buf, "");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80036F74-8003709C       .text tag_len_get_bomb__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_get_bomb(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGs_getBombMax();
    fopMsgM_int_to_char(buf, dComIfGs_getBombMax(), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Bomben");
        } else {
            strcat(buf, " Bombe");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " bombes");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcat(buf, " bombas");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Bombe");
    } else {
        if (num != 1) {
            strcat(buf, " bombs");
        } else {
            strcat(buf, " bomb");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " bombs");
    } else {
        strcat(buf, " bomb");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 8003709C-800371C4       .text tag_len_get_arrow__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_get_arrow(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = dComIfGs_getArrowMax();
    fopMsgM_int_to_char(buf, dComIfGs_getArrowMax(), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Pfeile");
        } else {
            strcat(buf, " Pfeil");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " fl\350ches");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcat(buf, " flechas");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Frecce");
    } else {
        if (num != 1) {
            strcat(buf, " arrows");
        } else {
            strcat(buf, " arrow");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " arrows");
    } else {
        strcat(buf, " arrow");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 800371C4-800372E4       .text tag_len_stock_bokobaba__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_bokobaba(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, " Plantagranda-Samen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " semillas");
        } else {
            strcat(buf, " semilla");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " seeds");
        } else {
            strcat(buf, " seed");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " seeds");
    } else {
        strcat(buf, " seed");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 800372E4-80037404       .text tag_len_stock_dokuro__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_dokuro(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, daNpc_Bs1_c::getBuyItem(), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Totenkopfketten");
        } else {
            strcat(buf, " Totenkopfkette");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " colgantes");
        } else {
            strcat(buf, " colgante");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " neckalces");
        } else {
            strcat(buf, " neckalce");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " neckalces");
    } else {
        strcat(buf, " neckalce");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037404-80037500       .text tag_len_stock_chuchu__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_chuchu(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Schleim-Gelees");
        } else {
            strcat(buf, " Schleim-Gelee");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " jugos");
        } else {
            strcat(buf, " jugo");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        strcat(buf, "");
    }
#else
    strcat(buf, "");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037500-80037620       .text tag_len_stock_pendant__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_pendant(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, daNpc_Bs1_c::getBuyItem(), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Gl\374cksamulette");
        } else {
            strcat(buf, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " collares");
        } else {
            strcat(buf, " collar");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " necklaces");
        } else {
            strcat(buf, " necklace");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " necklaces");
    } else {
        strcat(buf, " necklace");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037620-80037740       .text tag_len_stock_hane__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_hane(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Goldfedern");
        } else {
            strcat(buf, " Goldfeder");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " plumas");
        } else {
            strcat(buf, "  pluma");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " feathers");
        } else {
            strcat(buf, " feather");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " feathers");
    } else {
        strcat(buf, " feather");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037740-80037860       .text tag_len_stock_kenshi__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_stock_kenshi(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, daNpc_Bs1_c::getBuyItem(), false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, " Ritterwappen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " blasones");
        } else {
            strcat(buf, " blas\363n");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, "");
        } else {
            strcat(buf, "");
        }
    } else {
        if (num != 1) {
            strcat(buf, " crests");
        } else {
            strcat(buf, " crest");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " crests");
    } else {
        strcat(buf, " crest");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037860-80037980       .text tag_len_terry_rupee__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_terry_rupee(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[24];

    int num = daNpc_Bs1_c::getPayRupee();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037980-80037A80       .text tag_len_input_bokobaba__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_bokobaba(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Plantagranda-Samen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 seed(s)");
    }
#else
    strcpy(buf, "00 seed(s)");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037A80-80037B80       .text tag_len_input_dokuro__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_dokuro(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Totenkopfkette(n)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 necklace(s)");
    }
#else
    strcpy(buf, "00 necklace(s)");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037B80-80037C80       .text tag_len_input_chuchu__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_chuchu(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Schleim-Gelee(s)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 ");
    }
#else
    strcpy(buf, "00 ");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037C80-80037D80       .text tag_len_input_pendant__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_pendant(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Gl\374cksamulett(e)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 pendant(s)");
    }
#else
    strcpy(buf, "00 pendant(s)");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037D80-80037E80       .text tag_len_input_hane__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_hane(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Goldfeder(n)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 feather(s)");
    }
#else
    strcpy(buf, "00 feather(s)");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037E80-80037F80       .text tag_len_input_kenshi__21fopMsgM_msgDataProc_cFPiPfPiPiPi */
void fopMsgM_msgDataProc_c::tag_len_input_kenshi(int* param_1, f32* param_2, int* param_3, int* param_4, int* param_5) {
    char buf[28];

    if (*param_5 != lineCount) {
        lineCount = *param_5;
    }

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, "00 Ritterwappen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, "00 ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, "00 ");
    } else {
        strcpy(buf, "00 crest(s)");
    }
#else
    strcpy(buf, "00 crest(s)");
#endif

    char* p1;
    u8* p2;
    p2 = (u8*)buf;
    p1 = buf;
    while (*p1 != '\0') {
        u8 c = *p2;
        p1++;
        p2++;
        if (*param_1 == 0) {
            *param_2 = charLength(*param_4, c, true);
        } else {
            *param_2 += charLength(*param_4, c, false);
        }

        *param_1 += 1;
    }

    param_3[*param_5] = *param_2 + 0.5f;
}

/* 80037F80-80038178       .text tag_kaisen_game__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_kaisen_game() {
    char buf[12];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BEFF);
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    dComIfGs_getEventReg(dSv_event_flag_c::UNK_BEFF);

#if VERSION == VERSION_PAL
    char buf2[20];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, " coups");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf2, " ca\361onazos");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf2, " cannonate");
    } else {
        strcpy(buf2, "");
    }
#else
    char buf2[12];

    strcpy(buf2, "");
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 80038178-80038330       .text tag_rupee__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_rupee() {
    char buf[20];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80038330-80038538       .text tag_num_input__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_num_input() {
    char buf[8];
    char buf2[16];

    int temp = (field_0x148 + charSpace) * 3;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf2, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf2);
    strcat(field_0x68, buf2);
    field_0x14 = temp;
    field_0x150 += 3;

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf, " Rubin(e)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf, " rupia(s)");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf, " Rupie");
    } else {
        strcpy(buf, " Rupee(s)");
    }
#else
    strcpy(buf, " Rupee(s)");
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80038538-8003872C       .text tag_sword_game__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_sword_game() {
    char buf[16];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    char buf2[12];

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf2, " Treffer");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, " fois");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " golpes");
        } else {
            strcpy(buf2, " golpe");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, " colpi");
        } else {
            strcpy(buf2, " colpo");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " blows");
        } else {
            strcpy(buf2, " blow");
        }
    }
#else
    if (num != 1) {
        strcpy(buf2, " blows");
    } else {
        strcpy(buf2, " blow");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003872C-800388AC       .text tag_letter_game__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_letter_game() {
    char buf[24];

    int num = dComIfGp_getMiniGameRupee();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 800388AC-80038A40       .text tag_letter_game_max__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_letter_game_max() {
    char buf[24];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_8AFF);
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80038A40-80038BC0       .text tag_fish__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_fish() {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80038BC0-80038D7C       .text tag_fish_rupee__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_fish_rupee() {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber() * 10;
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80038D7C-80038F70       .text tag_letter__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_letter() {
    char buf[16];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    char buf2[12];

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (mesgEntry->mMsgNo == 0xCEB) {
            if (num != 1) {
                strcpy(buf2, " Briefe");
            } else {
                strcpy(buf2, " Brief");
            }
        } else {
            strcpy(buf2, ". Brief");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " cartas");
        } else {
            strcpy(buf2, " carta");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " letters");
        } else {
            strcpy(buf2, " letter");
        }
    }
#else
    if (num != 1) {
        strcpy(buf2, " letters");
    } else {
        strcpy(buf2, " letter");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 80038F70-8003912C       .text tag_rescue__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_rescue() {
    char buf[20];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[12];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Freunde");
        } else {
            strcpy(buf2, " Freund");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf2, "");
    } else {
        strcpy(buf2, "");
    }

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
#else
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, "", "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003912C-800394B4       .text tag_forest_timer__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_forest_timer() {
    char buf[16];
    char buf2[4];

    int minutes = dComIfGs_getFwaterTimer() / 1800;
    fopMsgM_int_to_char(buf, minutes, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }
    strcpy(buf2, ":");
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    buf[0] = '\0';

    int seconds = (dComIfGs_getFwaterTimer() % 1800) / 30;
    if (minutes == 0 && seconds == 0) {
        seconds = 1;
    }
    fopMsgM_int_to_char2(buf, seconds);

    i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, "", "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 800394B4-8003966C       .text tag_birdman__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_birdman() {
    char buf[24];

    int num = dComIfGp_getMessageCountNumber();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcat(buf, " Meter");
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " m\350tres");
        } else {
            strcat(buf, " m\350tre");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " metros");
        } else {
            strcat(buf, " metro");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, " metri");
        } else {
            strcat(buf, " metro");
        }
    } else {
        if (num != 1) {
            strcat(buf, " yards");
        } else {
            strcat(buf, " yard");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " yards");
    } else {
        strcat(buf, " yard");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 8003966C-80039834       .text tag_point__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_point() {
    char buf[24];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_86FF);
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Punkte");
        } else {
            strcat(buf, " Punkt");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcat(buf, " points");
        } else {
            strcat(buf, " point");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " puntos Terry");
        } else {
            strcat(buf, " punto Terry");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcat(buf, " punti");
        } else {
            strcat(buf, " punto");
        }
    } else {
        if (num != 1) {
            strcat(buf, " points");
        } else {
            strcat(buf, " point");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " points");
    } else {
        strcat(buf, " point");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 80039834-80039A28       .text tag_get_pendant__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_get_pendant() {
    char buf[20];

    int num = (u8)dComIfGs_getBeastNum(dBeastIdx_JOY_PENDANT_e);
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[28];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Gl\374cksamulette");
        } else {
            strcpy(buf2, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcpy(buf2, " Pendentifs du Bonheur");
        } else {
            strcpy(buf2, " Pendentif du Bonheur");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    }
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, "");
    } else {
        strcpy(buf2, "");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 80039A28-80039C2C       .text tag_rev_pendant__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_rev_pendant() {
    char buf[20];

    int num = dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF);
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[28];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Gl\374cksamulette");
        } else {
            strcpy(buf2, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        if (num != 1) {
            strcpy(buf2, " Pendentifs du Bonheur");
        } else {
            strcpy(buf2, " Pendentif du Bonheur");
        }
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    }
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, "");
    } else {
        strcpy(buf2, "");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 80039C2C-80039FA0       .text tag_pig_timer__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_pig_timer() {
    char buf[16];
    char buf2[4];

    int minutes = dComIfGp_getItemTimer() / 1800;
    fopMsgM_int_to_char(buf, minutes, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }
    strcpy(buf2, ":");
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    buf[0] = '\0';

    int seconds = (dComIfGp_getItemTimer() % 1800) / 30;
    if (minutes == 0 && seconds == 0) {
        seconds = 1;
    }
    fopMsgM_int_to_char2(buf, seconds);

    i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, "", "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 80039FA0-8003A194       .text tag_get_bomb__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_get_bomb() {
    char buf[16];

    int num = dComIfGs_getBombMax();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    char buf2[12];

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Bomben");
        } else {
            strcpy(buf2, " Bombe");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, " bombes");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf2, " bombas");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf2, " Bombe");
    } else {
        if (num != 1) {
            strcpy(buf2, " bombs");
        } else {
            strcpy(buf2, " bomb");
        }
    }
#else
    if (num != 1) {
        strcpy(buf2, " bombs");
    } else {
        strcpy(buf2, " bomb");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003A194-8003A388       .text tag_get_arrow__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_get_arrow() {
    char buf[16];

    int num = dComIfGs_getArrowMax();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    char buf2[12];

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Pfeile");
        } else {
            strcpy(buf2, " Pfeil");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, " fl\350ches");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(buf2, " flechas");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(buf2, " Frecce");
    } else {
        if (num != 1) {
            strcpy(buf2, " arrows");
        } else {
            strcpy(buf2, " arrow");
        }
    }
#else
    if (num != 1) {
        strcpy(buf2, " arrows");
    } else {
        strcpy(buf2, " arrow");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003A388-8003A574       .text tag_stock_bokobaba__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_bokobaba() {
    char buf[20];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[20];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf2, " Plantagranda-Samen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " semillas");
        } else {
            strcpy(buf2, " semilla");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " seeds");
        } else {
            strcpy(buf2, " seed");
        }
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, " seeds");
    } else {
        strcpy(buf2, " seed");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003A574-8003A760       .text tag_stock_dokuro__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_dokuro() {
    char buf[20];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[20];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Totenkopfketten");
        } else {
            strcpy(buf2, " Totenkopfkette");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " colgantes");
        } else {
            strcpy(buf2, " colgante");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " neckalces");
        } else {
            strcpy(buf2, " neckalce");
        }
    }
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, " necklaces");
    } else {
        strcpy(buf2, " necklace");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003A760-8003A914       .text tag_stock_chuchu__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_chuchu() {
    char buf[20];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[20];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(text_buf, " Schleim-Gelees");
        } else {
            strcpy(text_buf, " Schleim-Gelee");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(text_buf, " jugos");
        } else {
            strcpy(text_buf, " jugo");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(text_buf, "");
        } else {
            strcpy(text_buf, "");
        }
    } else {
        strcpy(text_buf, "");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, "", "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003A914-8003AB00       .text tag_stock_pendant__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_pendant() {
    char buf[20];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[20];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Gl\374cksamulette");
        } else {
            strcpy(buf2, " Gl\374cksamulett");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " collares");
        } else {
            strcpy(buf2, " collar");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " necklaces");
        } else {
            strcpy(buf2, " necklace");
        }
    }
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, " necklaces");
    } else {
        strcpy(buf2, " necklace");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003AB00-8003ACEC       .text tag_stock_hane__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_hane() {
    char buf[20];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char buf2[16];

    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcpy(buf2, " Goldfedern");
        } else {
            strcpy(buf2, " Goldfeder");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " plumas");
        } else {
            strcpy(buf2, " pluma");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " feathers");
        } else {
            strcpy(buf2, " feather");
        }
    }
#else
    char buf2[12];

    if (num != 1) {
        strcpy(buf2, " feathers");
    } else {
        strcpy(buf2, " feather");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003ACEC-8003AED8       .text tag_stock_kenshi__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_stock_kenshi() {
    char buf[16];

    int num = daNpc_Bs1_c::getBuyItem();
    fopMsgM_int_to_char(buf, num, false);

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    char buf2[12];

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(buf2, " Ritterwappen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(buf2, "");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcpy(buf2, " blasones");
        } else {
            strcpy(buf2, " blas\363n");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        if (num != 1) {
            strcpy(buf2, "");
        } else {
            strcpy(buf2, "");
        }
    } else {
        if (num != 1) {
            strcpy(buf2, " crests");
        } else {
            strcpy(buf2, " crest");
        }
    }
#else
    if (num != 1) {
        strcpy(buf2, " crests");
    } else {
        strcpy(buf2, " crest");
    }
#endif

    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, buf2, "", &field_0x20, &field_0x24, &field_0x150);
    count += bmgData[count + 1];
}

/* 8003AED8-8003B088       .text tag_terry_rupee__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_terry_rupee() {
    char buf[24];

    int num = daNpc_Bs1_c::getPayRupee();
    fopMsgM_int_to_char(buf, num, false);

#if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        if (num != 1) {
            strcat(buf, " Rubine");
        } else {
            strcat(buf, " Rubin");
        }
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcat(buf, " rubis");
    } else if (dComIfGs_getPalLanguage() == 3) {
        if (num != 1) {
            strcat(buf, " rupias");
        } else {
            strcat(buf, " rupia");
        }
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcat(buf, " Rupie");
    } else {
        if (num != 1) {
            strcat(buf, " Rupees");
        } else {
            strcat(buf, " Rupee");
        }
    }
#else
    if (num != 1) {
        strcat(buf, " Rupees");
    } else {
        strcat(buf, " Rupee");
    }
#endif

    int i = 0;
    while (buf[i] != '\0') {
        u8 c = ((u8*)buf)[i];
        i++;
        if (field_0x150 == 0) {
            field_0x14 = charLength(field_0x148, c, true);
        } else {
            field_0x14 += charLength(field_0x148, c, false);
        }

        field_0x150 += 1;
    }

    strcat(field_0x60, buf);
    strcat(field_0x68, buf);

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

    count += bmgData[count + 1];
}

/* 8003B088-8003B21C       .text tag_input_bokobaba__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_bokobaba() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[32];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Plantagranda-Samen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " seed(s)");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char* text = "seed(s)";
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003B21C-8003B3B0       .text tag_input_dokuro__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_dokuro() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[32];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Totenkopfkette(n)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " necklace(s)");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char* text = "necklace(s)";
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003B3B0-8003B544       .text tag_input_chuchu__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_chuchu() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[32];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Schleim-Gelee(s)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " ");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, "", "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003B544-8003B6D8       .text tag_input_pendant__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_pendant() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[32];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Gl\374cksamulett(e)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " pendant(s)");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char* text = "pendant(s)";
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003B6D8-8003B86C       .text tag_input_hane__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_hane() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf, "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[24];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Goldfeder(n)");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " feather(s)");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char* text = "feather(s)";
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}

/* 8003B86C-8003BA00       .text tag_input_kenshi__21fopMsgM_msgDataProc_cFv */
void fopMsgM_msgDataProc_c::tag_input_kenshi() {
    /* Nonmatching */
    char buf[16];

    int temp = (field_0x148 + charSpace) * 2;
    selectFlag = 3;
    iconSelect(field_0x148, 0x16);
    mesgStatus = 0x15;
    sprintf(buf,  "\x1B""CR[%d]", temp);
    strcat(field_0x60, buf);
    strcat(field_0x68, buf);
    field_0x14 = temp;
    field_0x150 += 2;

    if (selectFlag != 1) {
        field_0x20 = field_0xF8[lineCount] + field_0x14 + 0.5f;
    } else {
        field_0x20 = field_0x108[lineCount] + field_0x14 + 0.5f;
    }

#if VERSION == VERSION_PAL
    char text_buf[24];

    if (dComIfGs_getPalLanguage() == 1) {
        strcpy(text_buf, " Ritterwappen");
    } else if (dComIfGs_getPalLanguage() == 2) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 3) {
        strcpy(text_buf, " ");
    } else if (dComIfGs_getPalLanguage() == 4) {
        strcpy(text_buf, " ");
    } else {
        strcpy(text_buf, " crest(s)");
    }
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text_buf, "", &field_0x20, &field_0x24, &field_0x150);
#else
    char* text = "crest(s)";
    getRubyString(field_0x60, field_0x68, field_0x64, field_0x6C, text, "", &field_0x20, &field_0x24, &field_0x150);
#endif

    count += bmgData[count + 1];
}
#endif

/* 8003BA00-8003BA40       .text fopMsgM_centerPosCalc__F17fopMsgM_f2d_class17fopMsgM_f2d_class */
fopMsgM_f2d_class fopMsgM_centerPosCalc(fopMsgM_f2d_class param_1, fopMsgM_f2d_class param_2) {
    fopMsgM_f2d_class ret;
    ret.x = param_1.x + param_2.x / 2.0f;
    ret.y = param_1.y + param_2.y / 2.0f;
    return ret;
}

/* 8003BA40-8003BB34       .text fopMsgM_pane_parts_set__FP18fopMsgM_pane_class */
void fopMsgM_pane_parts_set(fopMsgM_pane_class* i_pane) {
    i_pane->mPosTopLeftOrig.x = i_pane->pane->mBounds.i.x;
    i_pane->mPosTopLeftOrig.y = i_pane->pane->mBounds.i.y;
    i_pane->mSizeOrig.x = i_pane->pane->mBounds.f.x - i_pane->pane->mBounds.i.x;
    i_pane->mSizeOrig.y = i_pane->pane->mBounds.f.y - i_pane->pane->mBounds.i.y;
    fopMsgM_f2d_class center = fopMsgM_centerPosCalc(i_pane->mPosTopLeftOrig, i_pane->mSizeOrig);
    i_pane->mPosCenterOrig.x = center.x;
    i_pane->mPosCenterOrig.y = center.y;
    i_pane->mInitAlpha = i_pane->pane->getAlpha();
    i_pane->mPosTopLeft = i_pane->mPosTopLeftOrig;
    i_pane->mPosCenter = i_pane->mPosCenterOrig;
    i_pane->mSize = i_pane->mSizeOrig;
    i_pane->mNowAlpha = 0;
    i_pane->mUserArea = 0;
}

/* 8003BB34-8003BB4C       .text fopMsgM_pane_parts_set__FP24fopMsgM_pane_alpha_class */
void fopMsgM_pane_parts_set(fopMsgM_pane_alpha_class* i_pane) {
    i_pane->mInitAlpha = i_pane->pane->getAlpha();
    i_pane->mNowAlpha = 0;
}

/* 8003BB4C-8003BB78       .text fopMsgM_setPaneData__FP18fopMsgM_pane_classP7J2DPane */
void fopMsgM_setPaneData(fopMsgM_pane_class* i_pane, J2DPane* i_paneData) {
    if (i_paneData != NULL) {
        i_pane->pane = i_paneData;
        fopMsgM_pane_parts_set(i_pane);
    }
}

/* 8003BB78-8003BBCC       .text fopMsgM_setPaneData__FP18fopMsgM_pane_classP9J2DScreenUl */
void fopMsgM_setPaneData(fopMsgM_pane_class* i_pane, J2DScreen* i_scrn, u32 i_tag) {
    J2DPane* paneData = i_scrn->search(i_tag);
    if (paneData != NULL) {
        i_pane->pane = paneData;
        fopMsgM_pane_parts_set(i_pane);
    }
}

/* 8003BBCC-8003BBF8       .text fopMsgM_setPaneData__FP24fopMsgM_pane_alpha_classP7J2DPane */
void fopMsgM_setPaneData(fopMsgM_pane_alpha_class* i_pane, J2DPane* i_paneData) {
    if (i_paneData != NULL) {
        i_pane->pane = i_paneData;
        fopMsgM_pane_parts_set(i_pane);
    }
}

/* 8003BBF8-8003BC88       .text fopMsgM_setPaneData__FP24fopMsgM_pane_alpha_classP9J2DScreenUl */
void fopMsgM_setPaneData(fopMsgM_pane_alpha_class* i_pane, J2DScreen* i_scrn, u32 i_tag) {
    J2DPane* paneData = i_scrn->search(i_tag);
    if (paneData != NULL) {
        i_pane->pane = paneData;
        fopMsgM_pane_parts_set(i_pane);
    } else {
        JUT_ASSERT(VERSION_SELECT(0x22F9, 0x22F9, 0x398D, 0x3A73), FALSE);
    }
}

/* 8003BC88-8003BCC0       .text fopMsgM_paneTrans__FP18fopMsgM_pane_classff */
void fopMsgM_paneTrans(fopMsgM_pane_class* i_pane, f32 i_transX, f32 i_transY) {
    i_pane->mPosCenter.x = i_pane->mPosCenterOrig.x + i_transX;
    i_pane->mPosCenter.y = i_pane->mPosCenterOrig.y + i_transY;
    fopMsgM_cposMove(i_pane);
}

/* 8003BCC0-8003BCEC       .text fopMsgM_paneScaleX__FP18fopMsgM_pane_classf */
void fopMsgM_paneScaleX(fopMsgM_pane_class* i_pane, f32 i_scale) {
    i_pane->mSize.x = i_pane->mSizeOrig.x * i_scale;
    fopMsgM_cposMove(i_pane);
}

/* 8003BCEC-8003BD18       .text fopMsgM_paneScaleY__FP18fopMsgM_pane_classf */
void fopMsgM_paneScaleY(fopMsgM_pane_class* i_pane, f32 i_scale) {
    i_pane->mSize.y = i_pane->mSizeOrig.y * i_scale;
    fopMsgM_cposMove(i_pane);
}

/* 8003BD18-8003BD50       .text fopMsgM_paneScale__FP18fopMsgM_pane_classff */
void fopMsgM_paneScale(fopMsgM_pane_class* i_pane, f32 i_scaleX, f32 i_scaleY) {
    i_pane->mSize.x = i_pane->mSizeOrig.x * i_scaleX;
    i_pane->mSize.y = i_pane->mSizeOrig.y * i_scaleY;
    fopMsgM_cposMove(i_pane);
}

/* 8003BD50-8003BD88       .text fopMsgM_paneScaleXY__FP18fopMsgM_pane_classf */
void fopMsgM_paneScaleXY(fopMsgM_pane_class* i_pane, f32 i_scale) {
    i_pane->mSize.x = i_pane->mSizeOrig.x * i_scale;
    i_pane->mSize.y = i_pane->mSizeOrig.y * i_scale;
    fopMsgM_cposMove(i_pane);
}

/* 8003BD88-8003BE14       .text fopMsgM_cposMove__FP18fopMsgM_pane_class */
void fopMsgM_cposMove(fopMsgM_pane_class* i_pane) {
    i_pane->mPosTopLeft.x = i_pane->mPosCenter.x - i_pane->mSize.x / 2.0f;
    i_pane->mPosTopLeft.y = i_pane->mPosCenter.y - i_pane->mSize.y / 2.0f;
    i_pane->pane->move(i_pane->mPosTopLeft.x, i_pane->mPosTopLeft.y);
    i_pane->pane->resize(i_pane->mSize.x, i_pane->mSize.y);
}

/* 8003BE14-8003BE24       .text fopMsgM_setAlpha__FP18fopMsgM_pane_class */
void fopMsgM_setAlpha(fopMsgM_pane_class* i_pane) {
    i_pane->pane->setAlpha(i_pane->mNowAlpha);
}

/* 8003BE24-8003BE30       .text fopMsgM_setInitAlpha__FP18fopMsgM_pane_class */
void fopMsgM_setInitAlpha(fopMsgM_pane_class* i_pane) {
    i_pane->mNowAlpha = i_pane->mInitAlpha;
}

/* 8003BE30-8003BE6C       .text fopMsgM_setNowAlpha__FP18fopMsgM_pane_classf */
void fopMsgM_setNowAlpha(fopMsgM_pane_class* i_pane, f32 i_alpha) {
    i_pane->mNowAlpha = i_pane->mInitAlpha * i_alpha;
}

/* 8003BE6C-8003BE78       .text fopMsgM_setNowAlphaZero__FP18fopMsgM_pane_class */
void fopMsgM_setNowAlphaZero(fopMsgM_pane_class* i_pane) {
    i_pane->mNowAlpha = 0;
}

/* 8003BE78-8003BE88       .text fopMsgM_setAlpha__FP24fopMsgM_pane_alpha_class */
void fopMsgM_setAlpha(fopMsgM_pane_alpha_class* i_pane) {
    i_pane->pane->setAlpha(i_pane->mNowAlpha);
}

/* 8003BE88-8003BEC4       .text fopMsgM_setNowAlpha__FP24fopMsgM_pane_alpha_classf */
void fopMsgM_setNowAlpha(fopMsgM_pane_alpha_class* i_pane, f32 i_alpha) {
    i_pane->mNowAlpha = i_pane->mInitAlpha * i_alpha;
}

/* 8003BEC4-8003C07C       .text fopMsgM_valueIncrease__FiiUc */
f32 fopMsgM_valueIncrease(int i_max, int i_value, u8 i_mode) {
    if (i_max <= 0)
        return 1.0f;

    if (i_value < 0)
        i_value = 0;
    else if (i_value > i_max)
        i_value = i_max;

    f32 ret;
    f32 v = ((f32)i_value) / ((f32)i_max);
    switch (i_mode) {
    case 0:
        ret = v * v;
        break;
    case 1:
        ret = std::sqrtf(v);
        break;
    case 2:
    default:
        ret = v;
        break;
    case 3:
        ret = (v * 2.0f - 1.0f) * 2.0f - 1.0f;
        break;
    case 4:
        ret = JMASSin(v * 32768.0f * 0.5f) * JMASSin(v * 32768.0f * 0.5f);
        break;
    case 5:
        ret = JMASSin(v * 65535.0f * 0.5f) * JMASSin(v * 65535.0f * 0.5f);
        break;
    }
    return ret;
}

/* 8003C07C-8003C0F8       .text fopMsgM_blendInit__FP18fopMsgM_pane_classPCc */
void fopMsgM_blendInit(fopMsgM_pane_class* i_pane, const char* data) {
    ((J2DPicture*)i_pane->pane)->append(data, 1.0f);
    J2DPicture* pic = (J2DPicture*)i_pane->pane;
    pic->setBlendColorRatio(0.0f, 1.0f, 1.0f, 1.0f);
    pic->setBlendAlphaRatio(0.0f, 1.0f, 1.0f, 1.0f);
}

/* 8003C0F8-8003C16C       .text fopMsgM_blendInit__FP10J2DPicturePCc */
void fopMsgM_blendInit(J2DPicture* pic, const char* data) {
    pic->append(data, 1.0f);
    pic->setBlendColorRatio(0.0f, 1.0f, 1.0f, 1.0f);
    pic->setBlendAlphaRatio(0.0f, 1.0f, 1.0f, 1.0f);
}

/* 8003C16C-8003C1D4       .text fopMsgM_blendDraw__FP18fopMsgM_pane_classPCc */
void fopMsgM_blendDraw(fopMsgM_pane_class* i_pane, const char* data) {
    i_pane->pane->show();
    ((J2DPicture*)i_pane->pane)->remove();
    ((J2DPicture*)i_pane->pane)->append(data, 1.0f);
}

/* 8003C1D4-8003C234       .text fopMsgM_blendDraw__FP10J2DPicturePCc */
void fopMsgM_blendDraw(J2DPicture* pic, const char* data) {
    pic->show();
    pic->remove();
    pic->append(data, 1.0f);
}

/* 8003C234-8003C380       .text fopMsgM_setFontsizeCenter__FPcPcPcPcii */
void fopMsgM_setFontsizeCenter(char* param_1, char* param_2, char* param_3, char* param_4, int param_5, int param_6) {
    int temp = (param_6 - param_5) / 2;

    char buf1[44];
    char buf2[12];
    if (temp > 0) {
        sprintf(buf1, "\x1b""FX[%d]\x1b""FY[%d]", param_6, param_6);
        buf2[0] = '\0';
        strcat(param_1, buf1);
        strcat(param_2, buf1);
        strcat(param_3, buf2);
        strcat(param_4, buf2);
    } else if (temp < 0) {
        sprintf(buf1, "\x1b""FX[%d]\x1b""FY[%d]", param_6, param_6);
        buf2[0] = '\0';
        strcat(param_1, buf1);
        strcat(param_2, buf1);
        strcat(param_3, buf2);
        strcat(param_4, buf2);
    } else if (param_5 != param_6) {
        sprintf(buf1, "\x1b""FX[%d]\x1b""FY[%d]", param_6, param_6);
        strcat(param_1, buf1);
        strcat(param_2, buf1);
    }
}

/* 8003C380-8003C414       .text fopMsgM_setFontsizeCenter2__FPcPcPcPciiii */
void fopMsgM_setFontsizeCenter2(char* a, char* b, char* c, char* d, int, int size, int, int) {
    char buf1[32], buf2[12];
    sprintf(buf1, "\eFX[%d]\eFY[%d]", size, size);
    buf2[0] = '\0';
    strcat(a, buf1);
    strcat(b, buf1);
    strcat(c, buf2);
    strcat(d, buf2);
}

/* 8003C414-8003C450       .text fopMsgM_createExpHeap__FUl */
JKRExpHeap* fopMsgM_createExpHeap(u32 i_size) {
    return JKRExpHeap::create(i_size, mDoExt_getGameHeap(), FALSE);
}

/* 8003C450-8003C470       .text fopMsgM_destroyExpHeap__FP10JKRExpHeap */
void fopMsgM_destroyExpHeap(JKRExpHeap* i_heap) {
    i_heap->destroy();
}

static const char* dummy1 = "\x1B""CU[%d]";
static const char* dummy2 = "\x1B""CD[%d]";
