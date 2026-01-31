/**
 * d_a_npc_rsh1.cpp
 * NPC - Zunari
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_rsh1.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_item.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_rsh.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

class daNpc_Rsh1_HIO_c : public JORReflexible {
public:
    daNpc_Rsh1_HIO_c();
    virtual ~daNpc_Rsh1_HIO_c() {};

    void genMessage(JORMContext* ctx) {};
public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ dNpc_HIO_c field_0x0C;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ u8 field_0x5C[12];
    /* 0x68 */ u8 field_0x68;
    /* 0x69 */ u8 field_0x69;
    /* 0x6A */ u8 field_0x6A;
    /* 0x6B */ u8 field_0x6B;
};  // Size: 0x6C

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
        /* Height */ 80.0f,
    }},
};

char daNpc_Rsh1_c::m_arcname[] = "Rsh";

static daNpc_Rsh1_HIO_c l_HIO;
static fpc_ProcID l_msgId;
static msg_class* l_msg;

static cXyz l_in_chk_pos1_tbl[4] = {
    cXyz( 919.0f, 670.0f, -205111.0f),
    cXyz(1466.0f, 670.0f, -204723.0f),
    cXyz(1090.0f, 670.0f, -204173.0f),
    cXyz( 603.0f, 670.0f, -204461.0f)
};

static cXyz l_in_chk_pos2_tbl[4] = {
    cXyz(1466.0f, 670.0f, -204723.0f),
    cXyz(1700.0f, 670.0f, -204518.0f),
    cXyz(1423.0f, 670.0f, -204174.0f),
    cXyz(1125.0f, 670.0f, -204337.0f)
};

/* 000000EC-0000021C       .text __ct__16daNpc_Rsh1_HIO_cFv */
daNpc_Rsh1_HIO_c::daNpc_Rsh1_HIO_c() {
    field_0x0C.m04 = -20.0f;
    field_0x0C.mMaxHeadX = 0x200;
    field_0x0C.mMaxHeadY = 0x200;
    field_0x0C.mMaxBackboneX = 0x1388;
    field_0x0C.mMaxBackboneY = 0x1770;
    field_0x0C.mMinHeadX = -0x200;
    field_0x0C.mMinHeadY = -0x200;
    field_0x0C.mMinBackboneX = -5000;
    field_0x0C.mMinBackboneY = -6000;
    field_0x0C.mMaxTurnStep = 0x1000;
    field_0x0C.mMaxHeadTurnVel = 0x800;
    field_0x0C.mAttnYOffset = 80.0f;
    field_0x0C.mMaxAttnAngleY = 0x4000;
    field_0x0C.m22 = 0;
    field_0x0C.mMaxAttnDistXZ = 400.0f;
    field_0x34 = 1.0f;
    field_0x38 = 0.9f;
    field_0x3C = 0.5f;
    field_0x40 = 40.0f;
    field_0x44 = 30.0f;
    field_0x48 = 7.5f;
    field_0x4C = 1300.0f;
    field_0x50 = 100.0f;
    field_0x54 = 180.0f;
    field_0x58 = 190.0f;
    field_0x68 = 0;
    field_0x69 = 0;
    field_0x6A = 0;
    field_0x6B = 0;
    
    field_0x5C[0] = 0;
    field_0x5C[1] = 0;
    field_0x5C[2] = 0;
    field_0x5C[3] = 0;
    field_0x5C[4] = 0;
    field_0x5C[5] = 0;
    field_0x5C[6] = 0;
    field_0x5C[7] = 0;
    field_0x5C[8] = 0;
    field_0x5C[9] = 0;
    field_0x5C[10] = 0;
    field_0x5C[11] = 0;

    field_0x04 = -1;
    field_0x08 = -1;
}

/* 0000021C-0000045C       .text checkCreateInShopPlayer__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::checkCreateInShopPlayer() {
    cXyz* curr_tbl;
    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
    cXyz dir(
        -cM_scos(current.angle.y),
        0.0f,
        cM_ssin(current.angle.y)
    );

    cXyz link_pos = link_p->current.pos;
    cXyz diff = link_pos - current.pos;

    cXyz* chk_pos_tbls[] = {
        l_in_chk_pos1_tbl,
        l_in_chk_pos2_tbl
    };

    int i, j, k, l;
    for (i = 0; i < 2; i++) {
        for (j = 0, k = 1, l = 0, curr_tbl = chk_pos_tbls[i]; j < 4;) {
            cXyz temp2 = curr_tbl[j] - link_pos;
            cXyz temp3 = curr_tbl[k] - link_pos;
            cXyz t2_cross_t3 = temp2.outprod(temp3);
            cXyz base_y = cXyz::BaseY;
            
            if (base_y.getDotProduct(t2_cross_t3) > 0.0f) {
                l++;
            }

            k++; j++;
            if (k > 3) k = 0; 
        }

        if ((l == 4 || l == 0) && 
            diff.getDotProduct(dir) > 0.0f && 
            std::fabsf(diff.y) < 25.0f) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00000498-00000710       .text daNpc_Rsh1_checkRotenBaseTalkArea__Fv */
static BOOL daNpc_Rsh1_checkRotenBaseTalkArea() {
    static cXyz base_talk_area_tbl[] = {
        cXyz(580.0f, 671.0f, -204393.0f),
        cXyz(539.0f, 671.0f, -204321.0f),
        cXyz(930.0f, 671.0f, -204114.0f),
        cXyz(971.0f, 671.0f, -204189.0f)
    };

    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());

    cXyz* talk_area_pos_tbl_p;
    cXyz link_pos = link_p->current.pos;

    int j, k, l;
    for (talk_area_pos_tbl_p = base_talk_area_tbl, j = 0, k = 1, l = 0; j < 4;) {
        cXyz temp2 = talk_area_pos_tbl_p[j] - link_pos;
        cXyz temp3 = talk_area_pos_tbl_p[k] - link_pos;
        cXyz t2_cross_t3 = temp2.outprod(temp3);
        cXyz base_y = cXyz::BaseY;
        
        if (base_y.getDotProduct(t2_cross_t3) > 0.0f) {
            l++;
        }

        k++; j++;
        if (k > 3) k = 0; 
    }

    if (l == 4 || l == 0) {
        return TRUE;
    }

    return FALSE;
}

/* 00000710-000007A0       .text daNpc_Rsh1_countShop__Fv */
static int daNpc_Rsh1_countShop() {
    u8 i = 0;
    int result = 0;
    for (; i <= 11; i++) {
        if(dComIfGs_isGetItemReserve(i)) {
            result++;
        } else {
            if (i == 0 && dComIfGs_checkGetItem(dItem_DELIVERY_BAG_e)) {
                result++;
            }
        }
    }
    return result;
}

/* 000007A0-0000080C       .text daNpc_Rsh1_RotenItemNumInBag__Fv */
static int daNpc_Rsh1_RotenItemNumInBag() {
    int result = 0;
    for (u8 i = 0x8C; i <= 0x97; i++) {
        result += dComIfGs_checkReserveItem(i);
    }
    return result;
}

/* 0000080C-0000084C       .text daNpc_Rsh1_shopMsgCheck__FUl */
static BOOL daNpc_Rsh1_shopMsgCheck(u32 param_1) {
    if ((param_1 >= 0x286B && param_1 <= 0x2882) || 
        (param_1 >= 0x2868 && param_1 <= 0x286A) || 
        param_1 == 0x2863 || param_1 == 0x2884) {
        return TRUE;
    }
    return FALSE;
}

/* 0000084C-0000087C       .text daNpc_Rsh1_shopStickMoveMsgCheck__FUl */
static BOOL daNpc_Rsh1_shopStickMoveMsgCheck(u32 param_1) {
    if ((param_1 >= 0x286B && param_1 <= 0x2882 && (param_1 % 2 != 0)) || param_1 == 0x2863) {
        return TRUE;
    }
    return FALSE;
}

static const int l_bck_ix_tbl[] = {
    DEMO_SELECT(RSH_INDEX_BCK_RS_WAIT01, RSH_BCK_RS_WAIT01), 
    DEMO_SELECT(RSH_INDEX_BCK_RS_WAIT02, RSH_BCK_RS_WAIT02), 
    DEMO_SELECT(RSH_INDEX_BCK_RS_TALK01, RSH_BCK_RS_TALK01), 
    DEMO_SELECT(RSH_INDEX_BCK_RS_TALK02, RSH_BCK_RS_TALK02),
    DEMO_SELECT(RSH_INDEX_BCK_RS_TALK02, RSH_BCK_RS_TALK02), 
    DEMO_SELECT(RSH_INDEX_BCK_RS_WALK, RSH_BCK_RS_WALK), 
    DEMO_SELECT(RSH_INDEX_BCK_RS_PUSH, RSH_BCK_RS_PUSH)
};

static const int l_bas_ix_tbl[] = {
    DEMO_SELECT(RSH_INDEX_BAS_RS_WAIT01, RSH_BAS_RS_WAIT01), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_WAIT02, RSH_BAS_RS_WAIT02), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_TALK01, RSH_BAS_RS_TALK01), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_TALK02, RSH_BAS_RS_TALK02), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_TALK02, RSH_BAS_RS_TALK02), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_WALK, RSH_BAS_RS_WALK), 
    DEMO_SELECT(RSH_INDEX_BAS_RS_PUSH, RSH_BAS_RS_PUSH)
};

static const int l_btp_ix_tbl[] = {
    DEMO_SELECT(RSH_INDEX_BTP_RS_MABA01, RSH_BTP_RS_MABA01), 
    DEMO_SELECT(RSH_INDEX_BTP_RS_MABA01, RSH_BTP_RS_MABA01)
};

/* 0000087C-00000A44       .text nodeCallBack_Rsh__FP7J3DNodei */
static BOOL nodeCallBack_Rsh(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daNpc_Rsh1_c* actor_p = (daNpc_Rsh1_c *) model_p->getUserArea();
        J3DJoint* jnt_p = (J3DJoint *) i_node;
        s32 jnt_no = jnt_p->getJntNo();
        if (actor_p) {
            MtxP anm_mtx = j3dSys.getModel()->getAnmMtx(jnt_no);
            mDoMtx_copy(anm_mtx, *calc_mtx);
            if (jnt_no == actor_p->getHeadJntNum()) {
                cXyz temp1(0.0f, 0.0f, 0.0f);                
                cXyz temp2;
                cMtx_YrotM(*calc_mtx, -actor_p->getHead_y());
                cMtx_ZrotM(*calc_mtx, -actor_p->getHead_x());
                MtxPosition(&temp1, &temp2);

                actor_p->setAttentionBasePos(temp2);
                temp1.set(28.0f, 20.0f, 0.0f);
                MtxPosition(&temp1, &temp2);

                actor_p->setEyePos(temp2);
                if (actor_p->field_0x76F != 0xFF) {
                    actor_p->field_0x76F++;
                }
            } else if (jnt_no == actor_p->getBackboneJntNum()) {
                cMtx_XrotM(*calc_mtx, +actor_p->getBackbone_y());
                cMtx_ZrotM(*calc_mtx, +actor_p->getBackbone_x());
            }

            cMtx_copy(*calc_mtx, j3dSys.mCurrentMtx);
            model_p->setAnmMtx(jnt_no, *calc_mtx);
        } 
    }
    return TRUE;
}

/* 00000A44-00000B50       .text initTexPatternAnm__12daNpc_Rsh1_cFb */
BOOL daNpc_Rsh1_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* morf_model_data_p = mpMorf->getModel()->getModelData();
    m_head_tex_pattern = (J3DAnmTexPattern *) dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[field_0x958]);
    JUT_ASSERT(580, m_head_tex_pattern != NULL);


    if (mBtpAnm.init(
        morf_model_data_p, 
        m_head_tex_pattern, TRUE, 
        J3DFrameCtrl::EMode_LOOP, 
        1.0f, 0, -1, 
        i_modify, FALSE
    ) == 0) {
        return FALSE;
    }

    field_0x2BC = 0;
    field_0x2BE = 0;
    return TRUE;
}

/* 00000B50-00000BDC       .text playTexPatternAnm__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::playTexPatternAnm() {
    if (cLib_calcTimer(&field_0x2BE) == 0) {
        if (field_0x2BC >= m_head_tex_pattern->getFrameMax()) {
            field_0x2BC -= m_head_tex_pattern->getFrameMax();
            field_0x2BE = cM_rndF(100.0f) + 30.0f;
        } else {
            field_0x2BC++;
        }
    }
}

/* 00000BDC-00000C64       .text setAnm__12daNpc_Rsh1_cFSc */
void daNpc_Rsh1_c::setAnm(s8 i_index) {
    static int play_mode_tbl[7] = {
        2, 2, 2, 2,
        2, 2, 2
    };

    static float morf_frame_tbl[7] = {
        8.0f, 8.0f, 8.0f, 8.0f,
        8.0f, 8.0f, 8.0f
    };

    static float play_speed_tbl[7] = {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };


    if (i_index != field_0x959 || field_0x959 == -1) {
        field_0x959 = i_index;
        dNpc_setAnm_2(
            mpMorf, 
            play_mode_tbl[i_index],
            morf_frame_tbl[i_index], 
            play_speed_tbl[i_index],
            l_bck_ix_tbl[i_index],
            l_bas_ix_tbl[i_index],
            m_arcname
        );
    }
}

/* 00000C64-00000CA8       .text setTexAnm__12daNpc_Rsh1_cFSc */
void daNpc_Rsh1_c::setTexAnm(s8 param_1) {
    if (field_0x958 != param_1 || field_0x958 == -1) {
        field_0x958 = param_1;
        initTexPatternAnm(true);
    }
}

/* 00000CA8-00000DDC       .text setAnmFromMsgTag__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setAnmFromMsgTag() {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnm(0);
            break;
        case 1:
            setAnm(1);
            break;
        case 2:
            setAnm(2);
            break;
        case 3:
            setAnm(3);
            break;
        case 4:
            setAnm(4);
            field_0x95A = 2;
            break;
        case 5:
            setAnm(5);
            break;
        case 6:
            setAnm(6);
            break;
    }

    if (field_0x959 == 4) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            if (--field_0x95A <= 0) {
                setAnm(0);
                field_0x95A = 0;
            }
        }
    }

    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 00000DDC-00000F50       .text chkAttention__12daNpc_Rsh1_cF4cXyzs */
bool daNpc_Rsh1_c::chkAttention(cXyz i_pos, s16 i_angleAdjustment) {
    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
    
    f32 max_attn_dist_xz = l_HIO.field_0x0C.mMaxAttnDistXZ;
    int max_attn_angle_y = l_HIO.field_0x0C.mMaxAttnAngleY;
    cXyz pos_diff = link_p->current.pos - i_pos;

    f32 temp_abs_xz = pos_diff.absXZ();
    s16 angle = cM_atan2s(pos_diff.x, pos_diff.z);
    
    if (field_0x770 != 0) {
        max_attn_dist_xz += 40.0f;
        max_attn_angle_y += 0x71C;
    }

    angle -= i_angleAdjustment;
    return max_attn_angle_y > abs(angle) && max_attn_dist_xz > temp_abs_xz;
}

/* 00000F50-00001038       .text eventOrder__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::eventOrder() {
    if (field_0x95B == 5) {
        fopAcM_orderOtherEventId(this, field_0x790);
    } else if (field_0x95B == 4) {
        fopAcM_orderOtherEvent2(this, "RSH_GET_DEMO", dEvtFlag_NOPARTNER_e);
    } else if (field_0x95B == 1 || field_0x95B == 2 || field_0x95B == 3) {
        if (field_0x95B != 3 || field_0x788 != -1 || daNpc_Rsh1_checkRotenBaseTalkArea()) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
        if (field_0x95B == 1 || field_0x95B == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001038-0000126C       .text checkOrder__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (field_0x95B == 5) {
            field_0x95B = 0;
            setAction(&daNpc_Rsh1_c::event_action, NULL);
        } else if (field_0x95B == 4) {
            field_0x95B = 0;
            mShopCamAct.Reset();
            setAction(&daNpc_Rsh1_c::getdemo_action, NULL);
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (field_0x95B == 1 || field_0x95B == 2 || field_0x95B == 3) {
            daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
            s16 temp = cLib_targetAngleY(&current.pos, &link_p->current.pos) - home.angle.y;
            if (temp > DEMO_SELECT(0x2000, 0x1800) || temp < DEMO_SELECT(-0x2000, -0x2800)) {
                field_0x780 = 0x2883;
            } else if (field_0x95B != 2) {
                mShopCamAct.shop_cam_action_init();
            }
            field_0x95B = 0;
            field_0x771 = 1;
            talkInit();
        }
    } else {
        mShopCamAct.Save();
    }
}

/* 0000126C-00001650       .text next_msgStatus__12daNpc_Rsh1_cFPUl */
u16 daNpc_Rsh1_c::next_msgStatus(u32* o_pMsgNo) {
    u16 msg_status;    
    s32 msg_rupee;
    msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_pMsgNo) {
    case 0x2845:
    case 0x2846:
    case 0x2847:
    case 0x2848:
    case 0x284B:
    case 0x284D:
    case 0x284E:
    case 0x284F:
    case 0x2850:
    case 0x2851:
    case 0x2852:
    case 0x2855:
    case 0x2857:
    case 0x2859:
    case 0x285A:
    case 0x285D:
    case 0x285E:
    case 0x2886:
    case 0x2887:
    case 0x2888:
    case 0x288D:
        *o_pMsgNo += 1;
        break;
    case 0x288C:
        *o_pMsgNo = 0x2889;
        break;
    case 0x2889:
        if (l_msg->mSelectNum == 0) {
            s32 msg_rupee = dComIfGp_getMessageRupee();
            if (msg_rupee > dComIfGs_getRupee()) {
                *o_pMsgNo = 0x288A;
                break;
            }

            dComIfGp_setItemRupeeCount(-(int)msg_rupee);
            *o_pMsgNo = 0x288D;
            break;
        }
        
        *o_pMsgNo = 0x288B; 
        break;
    case 0x2862:
        if (!shopPosMove()) {
            msg_status = fopMsgStts_MSG_DISPLAYED_e;
        } else {
            setAnm(0);
            *o_pMsgNo += 1;
        }
        break;
    case 0x283D:
    case 0x283F:
    case 0x2841:
    case 0x2843:
        *o_pMsgNo -= 1;
        break;
    case 0x284C:
        if (l_msg->mSelectNum == 0) {
            *o_pMsgNo = 0x284D;
        } else {
            *o_pMsgNo = 0x284A;
        }
        break;
    case 0x2853:
        if (l_msg->mSelectNum == 0) {
            *o_pMsgNo = 0x2855;
        } else {
            *o_pMsgNo = 0x2854;
        }
        break;
    case 0x2854:
        *o_pMsgNo = 0x284E;
        break;
    case 0x2866:
        *o_pMsgNo = 0x2863;
        break;
    case 0x2863:
        if (CPad_CHECK_TRIG_B(0)) {
            *o_pMsgNo = 0x2867;
        } else {
            dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
            dComIfGp_setAStatusForce(dActStts_CANCEL_e);
            msg_status = fopMsgStts_MSG_DISPLAYED_e;
        }
        break;
    case 0x286B:
    case 0x286D:
    case 0x286F:
    case 0x2871:
    case 0x2873:
    case 0x2875:
    case 0x2877:
    case 0x2879:
    case 0x287B:
    case 0x287D:
    case 0x287F:
    case 0x2881:
        if (CPad_CHECK_TRIG_B(0)) {
            *o_pMsgNo = 0x2867;
        } else {
            dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
            dComIfGp_setAStatusForce(dActStts_CANCEL_e);
            *o_pMsgNo += 1;
        }
        break;
    case 0x2868:
    case 0x2869:
    case 0x286A:
    case 0x2884:
        if (mpShopItems) {
            mpShopItems->mSelectedItemIdx = -1;
        }
        *o_pMsgNo = 0x2863;
        break;
    case 0x286C:
    case 0x286E:
    case 0x2870:
    case 0x2872:
    case 0x2874:
    case 0x2876:
    case 0x2878:
    case 0x287A:
    case 0x287C:
    case 0x287E:
    case 0x2880:
    case 0x2882:
        if (mpShopItems) {
            if (dComIfGp_checkMesgCancelButton()) {
                *o_pMsgNo = *o_pMsgNo - 1;
                break;
            }
            
            if (l_msg->mSelectNum == 0) {
                msg_rupee = dComIfGp_getMessageRupee();
                u8 status = dShop_BoughtErrorStatus(mpShopItems, 0, msg_rupee);

                if (status & 0x20) {
                    *o_pMsgNo = 0x2868;
                    break;
                } 

                if (status & 0x4) {
                    *o_pMsgNo = 0x2869;
                    break;
                } 

                if (daNpc_Rsh1_RotenItemNumInBag() >= 3) {
                    *o_pMsgNo = 0x2884;
                    break;
                } 
                
                fopAcM_seStart(this, JA_SE_SHOP_BOUGHT, 0);
                
                mpShopItems->hideSelectItem();
                field_0x792 = mpShopItems->getSelectItemNo();
                dComIfGp_setItemRupeeCount(-(int)msg_rupee);

                if (!checkItemGet((int)mpShopItems->getSelectItemNo(), TRUE)) {
                    field_0x95B = 4;
                    msg_status = fopMsgStts_MSG_ENDS_e;
                    break;
                }

                execItemGet((int)mpShopItems->getSelectItemNo());
                *o_pMsgNo = 0x286A;
                break;
            }
            
            *o_pMsgNo -= 1;
            break;
        }
        break;
    case 0x2849:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1110);
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x2858:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1108);
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* 00001650-00001808       .text getMsg__12daNpc_Rsh1_cFv */
u32 daNpc_Rsh1_c::getMsg() {
    u32 result;
    
    if (field_0x780 != 0) {
        result = field_0x780;
        field_0x780 = 0;
    } else {
        if (!checkItemGet(0x2A, TRUE) && daNpc_Rsh1_countShop() >= 3) {
            return 0x285D;
        }

        if (dComIfGs_checkGetItem(0x78) == 0) {
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2420)) {
                return 0x288C;
            }
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2420);
            return 0x2886;
        }

        if (!dComIfGs_checkGetItem(dItem_DELIVERY_BAG_e)) {
            return 0x2890;
        }

        if (field_0x788 == -1) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01) && 
                !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E08) && 
                dComIfGs_isEventBit(dSv_event_flag_c::UNK_1108)) {
                return 0x2859;
            }
            
            int shop_cnt = daNpc_Rsh1_countShop();
            
            if (shop_cnt >= 8) {
                return 0x283E;
            }

            if (shop_cnt > 1) {
                return 0x2840;
            }

            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1108)) {
                return 0x2842;
            }

            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1110)) {
                result = 0x2845;
            } else {
                result = 0x284B;
            }
        } else {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1108)) {
                result = 0x2865;
            } else {
                result = 0x2862;
            }
        }
    }
    
    return result;
}

/* 00001808-000018EC       .text setCollision__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setCollision() {
    f32 temp1, temp2;

    if (chkAction(&daNpc_Rsh1_c::pl_shop_out_action)) {
        temp1 = l_HIO.field_0x54;
        temp2 = l_HIO.field_0x58;
        mCyl.SetC(field_0x794);
    } else {
        temp1 = l_HIO.field_0x50;
        temp2 = l_HIO.field_0x58;
        mCyl.SetC(current.pos);
    }

    mCyl.SetR(temp1);
    mCyl.SetH(temp2);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 000018EC-000018F8       .text talkInit__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::talkInit() {
    field_0x961 = 0;
}

/* 000018F8-00001CB4       .text normal_talk__12daNpc_Rsh1_cFv */
u16 daNpc_Rsh1_c::normal_talk() {
    u16 status = l_msg->mStatus;
    if (status == fopMsgStts_MSG_DISPLAYED_e) {
        l_msg->mStatus = next_msgStatus(&field_0x778);
        if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
            fopMsgM_messageSet(field_0x778);
        }
    } else if (status == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
    } else if (status == fopMsgStts_MSG_PREPARING_e) {
        fopMsgM_demoMsgFlagOn();
    }

    if (mpShopItems) {
        cXyz zoom_pos = mShopCamAct.getItemZoomPos(125.0f);
        mpShopItems->Item_ZoomUp(zoom_pos);
    }


    mpShopCursor->hide();
    if (dComIfGp_checkMesgSendButton() == 1) {
        field_0x778 = l_msg->mMsgNo;

        static cXyz rel_cam_ctr_data[] = {
            cXyz(96.0f, -46.0f, -26.0f),
            cXyz(2.0f, -32.0f, 29.0f)
        };

        static cXyz rel_cam_eye_data[] = {
            cXyz(-156.0f, -16.0f, 166.0f),
            cXyz(144.0f, 19.0f, 215.0f)
        };
        
        switch(field_0x778) {
        case 0x2846:
        case 0x284E:
        case 0x2858:
        case 0x285A:
        case 0x285E:
        case 0x2887:
        case 0x2888:
            mShopCamAct.rsh_talk_cam_action_init(this, rel_cam_ctr_data[0], rel_cam_eye_data[0], 45.0f);
            break;
        case 0x2848:
        case 0x2851:
        case 0x2852:
        case 0x288D:
            mShopCamAct.rsh_talk_cam_action_init(this, rel_cam_ctr_data[1], rel_cam_eye_data[1], 45.0f);
            break;  
        case 0x2847:
        default:
            if (!mShopCamAct.checkCamAction(NULL) && !mShopCamAct.checkCamAction(&ShopCam_action_c::shop_cam_action)) {
                mShopCamAct.shop_cam_action_init();
            }
            break;
        }
    }

    return status;
}

/* 00001CB4-00001DE4       .text shop_talk__12daNpc_Rsh1_cFv */
u16 daNpc_Rsh1_c::shop_talk() {
    mpShopCursor->show();
    if (mpShopItems && dShop_now_triggercheck(l_msg, &mSTControl, mpShopItems, &field_0x778, NULL, NULL)) {
        field_0x749 = 1;
        field_0x77C = 0;
    }

    u16 status = l_msg->mStatus;
    if (status == fopMsgStts_MSG_DISPLAYED_e || status == fopMsgStts_MSG_CONTINUES_e) {
        if (field_0x749 != 0) {
            field_0x749 = 0;
        } else {
            field_0x77C = field_0x778;
            l_msg->mStatus = next_msgStatus(&field_0x77C);
            if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(field_0x77C);
            }
        }
    } else if (status == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        if (mpShopItems) {
            mpShopItems->mSelectedItemIdx = -1;
        }
    } else if (status == fopMsgStts_MSG_PREPARING_e) {
        fopMsgM_demoMsgFlagOn();
    }

    return status;
}

/* 00001DE4-00001FE0       .text talk__12daNpc_Rsh1_cFv */
u16 daNpc_Rsh1_c::talk() {
    u16 result = 0xFF;

    if (field_0x961 == 0) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        l_msg = NULL;
        field_0x778 = getMsg();
        field_0x77C = 0;
        field_0x961 = 1;
        field_0x792 = 0xFF;
    } else if (field_0x961 != -1) {
        if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
            l_msgId = fopMsgM_messageSet(field_0x778, this);
        } else if (l_msg == NULL) {
            l_msg = fopMsgM_SearchByID(l_msgId);
            if (l_msg) {
                if (!daNpc_Rsh1_shopStickMoveMsgCheck(field_0x778)) {
                    field_0x961 = 2;
                } else {
                    field_0x961 = 3;
                }
            }
        } else {
            setAnmFromMsgTag();
            switch (field_0x961) {
                case 2:
                    result = normal_talk();
                    break;
                case 3:
                    result = shop_talk();
                    break;
            }
            if (dComIfGp_checkMesgSendButton()) {
                field_0x778 = l_msg->mMsgNo;
                if (!daNpc_Rsh1_shopStickMoveMsgCheck(field_0x778)) {
                    if (!daNpc_Rsh1_shopMsgCheck(field_0x778) && mpShopItems) {
                        mpShopItems->mSelectedItemIdx = -1;
                        mpShopItems->showItem();
                    }
                    field_0x961 = 2;
                } else {
                    if (field_0x778 == 0x2863 && mpShopItems) {
                        mpShopItems->mSelectedItemIdx = -1;
                        mpShopItems->showItem();
                    }
                    field_0x961 = 3;
                }
            }
        }
    }

    if (mpShopItems) {
        mShopCamAct.m54 = mpShopItems->mSelectedItemIdx;
    }

    return result;
}

/* 00001FE0-00002358       .text CreateInit__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::CreateInit() {
    cXyz dummy(0.0f, 0.0f, 0.0f);
    field_0x766 = current.angle;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 173;
    attention_info.distances[8] = 173; // Bug?
    gravity = -30.0f;
    
    switch (field_0x95E) {
        case 0:
            setAction(&daNpc_Rsh1_c::wait_action, NULL);
            break;
        default:
            break;
    }

    field_0x758 = current.pos;
    
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    field_0x962 = 0;
    field_0x749 = 0;
    field_0x780 = 0;
    field_0x792 = 0xFF;

    mShopCamAct.setCamDataIdx(8);
    mShopCamAct.setCamAction(NULL);

    createShopList();

    if (field_0x788 != -1 && field_0x788 != -1) {
        mShopItemsArr[field_0x788].init();
    }

    field_0x788 = -1;

    if (field_0x788 != -1) {
        mpShopItems = &mShopItemsArr[field_0x788];
        mShopCamAct.setCamDataIdx(field_0x788 + 8);
    } else {
        mpShopItems = NULL;
    }

    pathGet();
    fopAcM_setCullSizeFar(this, 0.25f);
    set_mtx();
    mpMorf->setMorf(0.0f);
    field_0x794 = cXyz::Zero;
    field_0x7A0 = field_0x794;
    field_0x793 = 0;
    mEventCut.setActorInfo("Rsh1", this);
    mEventCut.setJntCtrlPtr(&mJntCtrl);

    if (checkCreateInShopPlayer()) {
        field_0x95B = 5;
        cLib_onBit<u32>(actor_status, fopAcStts_UNK4000_e);
        field_0x790 = dComIfGp_evmng_getEventIdx("RSH_SHOP_OUT");
        setAction(&daNpc_Rsh1_c::dummy_action, NULL);
    } else {
        field_0x95B = 0;
    }

    return TRUE;
}

/* 00002358-000023A8       .text daNpc_Rsh1_checkRotenItemGet__Fi */
static BOOL daNpc_Rsh1_checkRotenItemGet(int i_itemNo) {
    BOOL roten_item_get_check;
    if (i_itemNo != 0) {
        roten_item_get_check = dComIfGs_isGetItemReserve(i_itemNo);
    } else {
        roten_item_get_check = dComIfGs_checkGetItem(dItem_DELIVERY_BAG_e) ? TRUE : FALSE;
    }
    return roten_item_get_check;
}

extern Vec Item_set_pos_data_rshop_0[];
/* 000023A8-00002568       .text createShopList__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::createShopList() {
    csXyz temp(0, home.angle.y, 0);
    
    s16 y_vals[] = {
        0xE800,
        0xE400,
        0xE000,
        0xDC00
    };
        
    int i, k;
    for(k = 0, i = 0; i < ARRAY_SSIZE(mShopItemsArr); i++) {
        int j = 0;
        mShopItemsArr[i].setItemDataIdx(8);
        temp.y = y_vals[i];

        while(j < (ARRAY_SSIZE(mShopItemDataPtrs) / ARRAY_SSIZE(mShopItemsArr)) && k < ARRAY_SSIZE(mShopItemDataPtrs)) {
            int idx = i * ((ARRAY_SSIZE(mShopItemDataPtrs) / ARRAY_SSIZE(mShopItemsArr))) + j;
            mShopItemDataPtrs[k] = NULL;
            if (daNpc_Rsh1_checkRotenItemGet(k)) {
                mShopItemsArr[i].mItemActorProcessIds[j] = fopAcM_createShopItem(
                    (cXyz *)&Item_set_pos_data_rshop_0[idx], 
                    Item_setData_rshop[k]->mpItemData->mItemNo, 
                    &temp, fopAcM_GetRoomNo(this)
                );
                mShopItemDataPtrs[idx] = Item_setData_rshop[k];
                j++;
            }
            k++;
        }

        mShopItemsArr[i].setItemSum(j);

        if (j < (ARRAY_SSIZE(mShopItemDataPtrs) / ARRAY_SSIZE(mShopItemsArr))) {
            if (j == 0) {
                i--;
            }
            break;
        } else if (i == ARRAY_SSIZE(mShopItemsArr) - 1) {
            break;
        }
    }

    field_0x78C = i + 1;
    for (i = 0; i < field_0x78C; i++) {
        mShopItemsArr[i].setItemSetDataList(&mShopItemDataPtrs[i * 3]);
    }

    field_0x78C = field_0x78C > 1 ? field_0x78C : 1;
}

/* 00002568-000025C0       .text setAttention__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setAttention() {
    attention_info.position.set(
        field_0x758.x,
        field_0x758.y + l_HIO.field_0x0C.mAttnYOffset,
        field_0x758.z
    );

    eyePos = current.pos;
    eyePos.y += 170.0f;
}

/* 000025C0-00002868       .text lookBack__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::lookBack() {
    cXyz player_eye_pos;
    cXyz* vec_p = NULL;
    s16 temp2 = current.angle.y;
    bool temp = true;
    switch (field_0x95C) {
    case 1:
        if (field_0x770 != 0) {
            player_eye_pos = dNpc_playerEyePos(l_HIO.field_0x0C.m04);
            vec_p = &player_eye_pos;
            setTexAnm(0);
        } else {
            vec_p = NULL;
            setTexAnm(0);
        }
        break;
    case 2:
        if (mpShopItems) {
            if (mShopCamAct.checkCamAction(NULL) || mShopCamAct.checkCamAction(&ShopCam_action_c::rsh_talk_cam_action)) {
                player_eye_pos = dNpc_playerEyePos(l_HIO.field_0x0C.m04);
                temp = false;
            } else if (mpShopItems->mSelectedItemIdx == -1) {
                player_eye_pos = mShopCamAct.getItemZoomPos(125.0f);
                temp = false;
            } else {
                cXyz temp = mpShopItems->getSelectItemBasePos();
                player_eye_pos = mpShopItems->getSelectItemPos();
                mpShopCursor->setPos(temp);
                mpShopCursor->setScale(
                    l_HIO.field_0x34,
                    l_HIO.field_0x38,
                    l_HIO.field_0x3C,
                    l_HIO.field_0x40,
                    l_HIO.field_0x44
                );
                mpShopCursor->anm_play();
            }
            vec_p = &player_eye_pos;
        } else {
            vec_p = NULL;
        }
        break;
    default:
        break;
    }

    if (mJntCtrl.trnChk()) {
        cLib_addCalcAngleS2(&field_0x764, l_HIO.field_0x0C.mMaxHeadTurnVel, 4, 0x800);
    } else {
        field_0x764 = 0;
    }
    
    mJntCtrl.lookAtTarget(
        &current.angle.y, vec_p, 
        eyePos, temp2, 
        field_0x764, temp
    );
}

/* 00002868-00002930       .text pathGet__12daNpc_Rsh1_cFv */
bool daNpc_Rsh1_c::pathGet() {
    int param = (fopAcM_GetParam(this) >> 0x10) & 0xFF;
    mpPath = dPath_GetRoomPath(param, fopAcM_GetRoomNo(this));
    if (mpPath) {        
        int i;
        dPnt* point_p;
        for (i = 0, point_p = mpPath->m_points; i < mpPath->m_num; i++, point_p++) {
            if (point_p->mArg3 != 0xFF) {
                field_0x708[point_p->mArg3].set(
                    point_p->m_position.x,
                    point_p->m_position.y,
                    point_p->m_position.z
                );
                field_0x744[point_p->mArg3] = i;
                if (point_p->mArg3 == 1) {
                    field_0x704 = i;
                }
            }
        }
    }
    field_0x788 = 0;
    return true;
}

/* 00002930-00002B60       .text getAimShopPosIdx__12daNpc_Rsh1_cFv */
int daNpc_Rsh1_c::getAimShopPosIdx() {
    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
    cXyz link_pos = link_p->current.pos;
    int condition;
    int result_index = 1;    
    f32 fcond = l_HIO.field_0x4C; 
    int temp_78C = field_0x78C;

    condition = temp_78C < 1 ? 1 : temp_78C;

    for (int i = 0; i <= condition; i++) {
        cXyz temp = link_pos;
        temp -= field_0x708[i];
        f32 mag = std::sqrtf(temp.abs2XZ());
        
        if (mag < fcond) {
            fcond = std::sqrtf(temp.abs2XZ());
            result_index = i;
        }
    }

    return result_index;
}

/* 00002B60-00002C2C       .text shopPosMove__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::shopPosMove() {
    static Vec shop_buyer_pos[] = {
        1314.0f, 672.0f, -204426.0f,
        1544.0f, 672.0f, -204214.0f,
        1775.0f, 672.0f, -204029.0f,
        1985.0f, 672.0f, -203786.0f
    };

    if (field_0x788 != -1) {
        cXyz temp = shop_buyer_pos[field_0x788];
        if (cLib_chasePosXZ(&current.pos, temp, l_HIO.field_0x48) != 0) {
            setAnm(0);
            return TRUE;
        } else {
            s16 target = cLib_targetAngleY(&current.pos, &temp);
            cLib_addCalcAngleS2(&current.angle.y, target, 8, 0x1000);
            setAnm(5);
        }
    } else {
        return TRUE;
    }

    return FALSE;
}

/* 00002C2C-00002E00       .text pathMove__12daNpc_Rsh1_cFPi */
BOOL daNpc_Rsh1_c::pathMove(int* param_1) {
    dPnt* point;
    
    s8 temp;
    int temp2;
    int temp3;
    int temp4;

    if (param_1) {
        temp4 = *param_1;
    } else {
        temp4 = getAimShopPosIdx();
    }

    if (field_0x704 == field_0x744[temp4]) {
        temp = field_0x704;
    } else if (field_0x704 < field_0x744[temp4]) {
        temp = field_0x704 + 1;
    } else {
        temp = field_0x704 - 1;
    }

    point = &mpPath->m_points[temp];
    cXyz target_pos(point->m_position.x, point->m_position.y, point->m_position.z);
    int chase_result = cLib_chasePosXZ(&current.pos, target_pos, l_HIO.field_0x48);

    if (chase_result != 0) {
        field_0x704 = temp;
        if (point->mArg3 != 0xFF) {
            temp2 = point->mArg3 - 1; 
            temp3 = temp2 + 9;
            
            if (temp2 != -1 && field_0x788 != temp2) {
                mShopItemsArr[temp2].init();
            }

            if (field_0x788 != -1 && field_0x788 != temp2) {
                mShopItemsArr[field_0x788].init();
            }

            field_0x788 = temp2;
            if (field_0x788 != -1) {
                mpShopItems = &mShopItemsArr[field_0x788];
                mShopCamAct.setCamDataIdx(field_0x788 + 8);
            } else {
                mpShopItems = NULL;
            }

            mShopCamAct.setCamDataIdx(temp3);
            if (temp4 == temp2 + 1) {
                cLib_addCalcAngleS2(&current.angle.y, home.angle.y, 8, 0x1000);
                return TRUE;
            }
        }
    }
    s16 target = cLib_targetAngleY(&current.pos, &target_pos);
    cLib_addCalcAngleS2(&current.angle.y, target, 8, 0x1000);
    return FALSE;
}

/* 00002E00-00002F5C       .text wait01__12daNpc_Rsh1_cFv */
bool daNpc_Rsh1_c::wait01() {
    if (field_0x771 != 0) {
        field_0x95D = field_0x95C;
        field_0x95C = 2;
    } else {
        if (mCyl.ChkCoHit()) {
            fopAc_ac_c* actor_p = mCyl.GetCoHitAc();
            if (actor_p && fpcM_GetName(actor_p) == PROC_PLAYER) {
                field_0x95B = 2;
                field_0x793 = 1;
                field_0x780 = 0x2883;
            }
        } else {
            daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
            BOOL path_move_res = pathMove(NULL);
            if (!path_move_res) {
                setAnm(5);
                field_0x95B = 0;
            } else {
                setAnm(0);
            }

            if (field_0x770 != 0) {
                f32 abs_diff = std::fabsf(current.pos.y - link_p->current.pos.y);
                if (path_move_res && abs_diff < 100.0f) {
                    field_0x95B = 3;
                } else if (field_0x95B == 3) {
                    field_0x95B = 0;
                } 
            }
        }
    }

    return mpMorf->isMorf();
}

/* 00002F5C-00003154       .text talk01__12daNpc_Rsh1_cFv */
bool daNpc_Rsh1_c::talk01() {
    u16 result = talk();
    if (result == 0x12) {
        daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
        field_0x95C = field_0x95D;
        dComIfGp_event_onEventFlag(8);
        mShopCamAct.Reset();
        link_p->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
        field_0x771 = 0;
        setAnm(0);

        if (field_0x778 == 0x2856) {
            field_0x95B = 4;
            field_0x963 = 0x8C;
        } else if (field_0x778 == 0x288E) {
            field_0x95B = 4;
            field_0x963 = 0x78;
        } else if (field_0x778 == 0x285F) {
            field_0x95B = 4;
            field_0x963 = 0x2A;
        } else if (field_0x778 == 0x2883 && field_0x793 == 1) {
            setAction(&daNpc_Rsh1_c::pl_shop_out_action, NULL);
        } 
    } else if (result == 8 && daNpc_Rsh1_shopMsgCheck(field_0x778) && field_0x778 == mpShopItems->getSelectItemBuyMsg()) {
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        dComIfGp_setAStatusForce(dActStts_CANCEL_e);
    }

    return mpMorf->isMorf();
}

/* 00003154-00003358       .text getdemo_action__12daNpc_Rsh1_cFPv */
BOOL daNpc_Rsh1_c::getdemo_action(void* i_unusedP) {
    UNUSED(i_unusedP);
    int staff_idx = dComIfGp_evmng_getMyStaffId("Rsh1");

    if (field_0x960 == 0) {
        daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
        link_p->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
        field_0x95C = field_0x95D;
        mShopCamAct.Reset();

        fpc_ProcID pid = fopAcM_createItemForPresentDemo(
            &current.pos, field_0x963, 
            0, -1, 
            DEMO_SELECT(-1, fopAcM_GetRoomNo(this))
        );
        if (pid != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(pid);
        }

        dComIfGp_evmng_cutEnd(staff_idx);
        field_0x960++;
    } else if (field_0x960 != -1) {
        dComIfGp_evmng_cutEnd(staff_idx);
        if (dComIfGp_evmng_endCheck("RSH_GET_DEMO")) {
            field_0x95B = 1;
            dComIfGp_event_onEventFlag(0x8);

            if (field_0x963 == 0x8C) {
                field_0x780 = 0x2857;
            } else if (field_0x963 == 0x78) {
                field_0x780 = 0x288F;
            } else if (field_0x963 == 0x2A) {
                field_0x780 = 0x2860;
            }

            field_0x963 = 0xFF;

            setAction(&daNpc_Rsh1_c::wait_action, NULL);
        }
    }

    return TRUE;
}

/* 00003358-00003424       .text wait_action__12daNpc_Rsh1_cFPv */
BOOL daNpc_Rsh1_c::wait_action(void* i_unusedP) {
    UNUSED(i_unusedP);

    if (field_0x960 == 0) {
        field_0x95C = 1;
        field_0x960++;
    } else if (field_0x960 != -1) {
        s16 sum = current.angle.y + getHead_y() + getBackbone_y();
        field_0x770 = chkAttention(current.pos, sum);
        switch (field_0x95C) {
            case 1:
                wait01();
                break;
            case 2:
                talk01();
                break;
        } 
    }

    return TRUE;
}

/* 00003424-00003840       .text pl_shop_out_action__12daNpc_Rsh1_cFPv */
BOOL daNpc_Rsh1_c::pl_shop_out_action(void* i_unusedP) {
    UNUSED(i_unusedP);

    f32 trig_amplitude_1 = 140.0f;
    if (field_0x960 == 0) {
        setAnm(6);
        field_0x794 = current.pos;
        field_0x794.x -= cM_ssin(current.angle.y) * trig_amplitude_1;
        field_0x794.z -= cM_scos(current.angle.y) * trig_amplitude_1;
        field_0x793 = 0;
        field_0x960++;
    } else if (field_0x960 != -1) {
        int temp_78C = field_0x78C;
        daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
        cXyz link_pos = link_p->current.pos;
        s16 target = cLib_targetAngleY(&current.pos, &link_pos);
        if (pathMove(&temp_78C)) {
            cXyz temp = cXyz::Zero;
            f32 calc_pos = cLib_addCalcPos(&field_0x794, current.pos, 0.25f, REG10_F(1) + 5.0f, 1.0f);
            cLib_addCalcAngleS2(&current.angle.y, target, 4, 0x1000);
            if (calc_pos < 1.0f) {
                cLib_addCalcPos(&field_0x7A0, temp, 0.25f, REG10_F(1) + 5.0f, 1.0f);
                f32 mag = field_0x7A0.abs();
                if (mag > 1.0f) {
                    setAnm(5);
                } else {
                    setAnm(0);
                    setAction(&daNpc_Rsh1_c::wait_action, NULL);
                }
            } else {
                f32 trig_amplitude_2 = REG10_F(2) + 100.0f;
                temp.x += trig_amplitude_2 * cM_ssin(current.angle.y);
                temp.z += trig_amplitude_2 * cM_scos(current.angle.y);
                cLib_addCalcPos(&field_0x7A0, temp, 0.25f, REG10_F(1) + 5.0f, 1.0f);
            }
        } else {
            field_0x794 = current.pos;
            field_0x794.x -= cM_ssin(current.angle.y) * trig_amplitude_1;
            field_0x794.z -= cM_scos(current.angle.y) * trig_amplitude_1;
        }
    }
    return TRUE;
}

/* 00003840-000038A4       .text evn_setAnm_init__12daNpc_Rsh1_cFi */
bool daNpc_Rsh1_c::evn_setAnm_init(int param_1) {
    int* anm_no_p = (int*) dComIfGp_evmng_getMyIntegerP(param_1, "AnmNo");
    if (anm_no_p) {
        setAnm(*anm_no_p);
    }
    return true;
}

/* 000038A4-0000396C       .text evn_talk_init__12daNpc_Rsh1_cFi */
bool daNpc_Rsh1_c::evn_talk_init(int param_1) {
    u32* msg_no_p = (u32 *) dComIfGp_evmng_getMyIntegerP(param_1, "MsgNo");
    u32* end_msg_no_p = (u32 *) dComIfGp_evmng_getMyIntegerP(param_1, "EndMsgNo");

    l_msgId = -1;
    l_msg = 0;

    if (msg_no_p) {
        field_0x778 = *msg_no_p;
    } else {
        field_0x778 = 0;
    }

    if (end_msg_no_p) {
        field_0x784 = *end_msg_no_p;
    } else {
        field_0x784 = 0;
    }

    return true;
}

/* 0000396C-000039D4       .text evn_continue_talk_init__12daNpc_Rsh1_cFi */
bool daNpc_Rsh1_c::evn_continue_talk_init(int i_staffIdx) {
    u32* end_msg_no_p = (u32 *) dComIfGp_evmng_getMyIntegerP(i_staffIdx, "EndMsgNo");

    if (end_msg_no_p) {
        field_0x784 = *end_msg_no_p;
    } else {
        field_0x784 = 0;
    }

    return true;
}

/* 000039D4-00003B04       .text evn_talk__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::evn_talk() {
    if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        l_msgId = fopMsgM_messageSet(field_0x778, &eyePos);
    } else if (!l_msg) {
        l_msg = fopMsgM_SearchByID(l_msgId);
        fopMsgM_demoMsgFlagOn();
    } else {
        setAnmFromMsgTag();
        if (l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&field_0x778);
            if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(field_0x778);
            } 
        } else {
            if (l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                l_msg = NULL;
                l_msgId = -1;
                return true;
            }
            if ((l_msg->mStatus == 2 || l_msg->mStatus == 6) && field_0x778 == field_0x784) {
                field_0x784 = 0;
                return true;
            } 
        }
    }
    return false;
}

/* 00003B04-00003B88       .text evn_turn_init__12daNpc_Rsh1_cFi */
bool daNpc_Rsh1_c::evn_turn_init(int i_staffIdx) {
    int* prm_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "prm");
    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
    int prm;

    if (prm_p) {
        prm = *prm_p;
    } else {
        prm = 0;
    }

    if (prm == 1) {
        current.angle.y = cLib_targetAngleY(&current.pos, &link_p->current.pos);
    }

    return true;
}

/* 00003B88-00003C10       .text evn_turn__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::evn_turn() {
    daPy_lk_c* link_p = DEMO_SELECT((daPy_lk_c *) dComIfGp_getPlayer(0), daPy_getPlayerLinkActorClass());
    s16 target = cLib_targetAngleY(&current.pos, &link_p->current.pos);
    cLib_addCalcAngleS(&current.angle.y, target, 8, 0x1000, 0x100);
    return cLib_distanceAngleS(current.angle.y, target) < 0x100;
}

/* 00003C10-00003D80       .text privateCut__12daNpc_Rsh1_cFv */
bool daNpc_Rsh1_c::privateCut() {
    static char* cut_name_tbl[] = {
        "TALKMSG",
        "CONTINUE_TALK",
        "SETANM",
        "TURN"
    };
    int staff_idx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
    
    if (staff_idx == -1) {
        return false;
    }

    int act_idx = dComIfGp_evmng_getMyActIdx(
        staff_idx, cut_name_tbl, 
        ARRAY_SSIZE(cut_name_tbl), 
        TRUE, 0
    );
    if (act_idx == -1) {
        dComIfGp_evmng_cutEnd(staff_idx);
    } else {
        BOOL is_addvance = dComIfGp_evmng_getIsAddvance(staff_idx);
        if (is_addvance) {
            switch (act_idx) {
                case 0:
                    evn_talk_init(staff_idx);
                    break;
                case 1:
                    evn_continue_talk_init(staff_idx);
                    break;
                case 2:
                    evn_setAnm_init(staff_idx);
                    break;
                case 3:
                    evn_turn_init(staff_idx);
                    break;
            }
        }

        BOOL result;
        switch (act_idx) {
            case 0:
            case 1:
                result = evn_talk();
                break;
            case 3:
                result = evn_turn();
                break;
            case 2:
            default:
                result = true;
                break;
        }

        if (result) {
            dComIfGp_evmng_cutEnd(staff_idx);
        }
    }

    return true;
}

BOOL daNpc_Rsh1_c::event_action(void* i_unusedP) {
    UNUSED(i_unusedP);
    if (field_0x960 == 0) {
        dComIfGp_evmng_getMyStaffId("Rsh1");
        field_0x95C = field_0x95D;
        field_0x95B = 0;
        field_0x960++;
    } else if (field_0x960 != -1) {
        privateCut();
        if (dComIfGp_evmng_endCheck(field_0x790)) {
            if (cLib_checkBit<u32>(actor_status, 0x4000)) {
                cLib_offBit<u32>(actor_status, 0x4000);
            }
            dComIfGp_event_onEventFlag(0x8);
            setAction(&daNpc_Rsh1_c::wait_action, NULL);
        }
        lookBack();
    }

    return TRUE;
}

/* 00003EEC-00003F08       .text dummy_action__12daNpc_Rsh1_cFPv */
BOOL daNpc_Rsh1_c::dummy_action(void* i_unusedP) {
    UNUSED(i_unusedP);
    if (field_0x960 == 0) {
        field_0x960++;
    }
    return TRUE;
}

/* 00003F08-00004040       .text _draw__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_draw() {
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_data_p = morf_model_p->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);
    mBtpAnm.entry(morf_model_data_p, field_0x2BC);
    mpMorf->updateDL();
    mBtpAnm.remove(morf_model_data_p);

    cXyz temp(
        current.pos.x,
        current.pos.y + 120.0f,
        current.pos.z
    );

    f32 ground_y = mAcch.m_ground_h;
    field_0x29C = dComIfGd_setShadow(
        field_0x29C, 
        1, mpMorf->getModel(), 
        &temp, 800.0f, 20.0f, 
        current.pos.y, ground_y, 
        mAcch.m_gnd, &tevStr
    );  
    
    if (mpShopItems && mpShopItems->mSelectedItemIdx >= 0) {
        mpShopCursor->draw();
    }

    dSnap_RegistFig(DSNAP_TYPE_UNK5F, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 00004040-0000427C       .text _execute__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_execute() {
#if VERSION == VERSION_DEMO
    if (l_HIO.field_0x68 != 0) {
        for (int i = 0; i < ARRAY_SSIZE(l_HIO.field_0x5C); i++) {
            if (l_HIO.field_0x5C[i]) {
                dComIfGs_onGetItemReserve(i);
            } else {
                dComIfGs_offGetItemReserve(i);
            }
        }

        if (l_HIO.field_0x69) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0E08);
        } else {
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_0E08);
        }

        if (l_HIO.field_0x6A) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1110);
        } else {
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_1110);
        }

        if (l_HIO.field_0x6B) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1108);
        } else {
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_1108);
        }
    }
#endif

    cXyz center = dComIfGp_getCamera(0)->mLookat.mCenter;
    cXyz diff = center - current.pos;
    f32 dist = diff.abs();

    if (dist > REG10_F(10) + 5000.0f) {
        return TRUE;
    } else {
        mJntCtrl.setParam(
            l_HIO.field_0x0C.mMaxBackboneX,
            l_HIO.field_0x0C.mMaxBackboneY,
            l_HIO.field_0x0C.mMinBackboneX,
            l_HIO.field_0x0C.mMinBackboneY,
            l_HIO.field_0x0C.mMaxHeadX,
            l_HIO.field_0x0C.mMaxHeadY,
            l_HIO.field_0x0C.mMinHeadX,
            l_HIO.field_0x0C.mMinHeadY,
            l_HIO.field_0x0C.mMaxTurnStep
        );

        playTexPatternAnm();
        
        field_0x76E = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < field_0x774) {
            field_0x76E = 1;
        }
        field_0x774 = mpMorf->getFrame();
        
        checkOrder();

        (this->*mCurrProc)(NULL);

        mShopCamAct.move();
        if (mpShopItems) {
            mpShopItems->Item_Move();
        }

        eventOrder();
        lookBack();
        setAttention();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        
        mAcch.CrrPos(*dComIfG_Bgsp());
        tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
        
        set_mtx();
        setCollision();
    }

    return TRUE;
}

/* 0000427C-00004308       .text _delete__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_delete() {
    dComIfG_resDeleteDemo(&mPhs, m_arcname);
    if (DEMO_SELECT(true, heap) && mpMorf) {
        mpMorf->stopZelAnime();
    }

    if(l_HIO.field_0x08 >= 0) {
        l_HIO.field_0x08--;
        if (l_HIO.field_0x08 < 0) {
            mDoHIO_deleteChild(l_HIO.field_0x04);
        }
    }

    return TRUE;
}

/* 00004308-00004328       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->CreateHeap();
}

/* 00004328-00004464       .text _create__12daNpc_Rsh1_cFv */
cPhs_State daNpc_Rsh1_c::_create() {
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_Rsh1_c);
#endif

    cPhs_State state = dComIfG_resLoad(&mPhs, m_arcname);


    if (state == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(this, daNpc_Rsh1_c);
#endif
        field_0x95E = (fopAcM_GetParam(this) >> 0x14) & 0xF;

        switch (field_0x95E) {
            case 0:
                field_0x95E = 0;
                break;
            default:
                field_0x95E = 0;
                break;
        }
        
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x6100)) {
            return cPhs_ERROR_e;
        }

        cullMtx = mpMorf->getModel()->getBaseTRMtx();

        if (l_HIO.field_0x08 < 0) {
            l_HIO.field_0x04 = mDoHIO_createChild("露店の社長", &l_HIO); // "Stall owner"
        }
        l_HIO.field_0x08++;

        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }

    return state;
}

/* 00004698-000049A0       .text CreateHeap__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::CreateHeap() {
    J3DModelData* model_p = (J3DModelData *) dComIfG_getObjectRes(m_arcname, DEMO_SELECT(RSH_INDEX_BDL_RS, RSH_BDL_RS));
    mpMorf = new mDoExt_McaMorf(
        model_p, 
        NULL, NULL, 
        (J3DAnmTransform *) dComIfG_getObjectRes(m_arcname, DEMO_SELECT(RSH_INDEX_BCK_RS_WAIT01, RSH_BCK_RS_WAIT01)), 
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, 
        dComIfG_getObjectRes(m_arcname, DEMO_SELECT(RSH_INDEX_BAS_RS_WAIT01, RSH_BAS_RS_WAIT01)), 
        0, 0x11020203
    );

    if (!mpMorf || !mpMorf->getModel()) {
#if VERSION > VERSION_DEMO
        mpMorf = NULL;
#endif
        return FALSE;
    }

    m_head_jnt_num = model_p->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(2386, 2387), m_head_jnt_num >= 0);

    m_backbone_jnt_num = model_p->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(2389, 2390), m_backbone_jnt_num >= 0);

    switch (field_0x95E) {
        case 0:
            field_0x958 = 0;
            break;
    }

    BOOL init_result = initTexPatternAnm(false); 

#if VERSION > VERSION_DEMO
    if (!init_result) {
        return FALSE;
    }
#endif

    for (u16 i = 0; i < model_p->getJointNum(); i++) {
        if (i == m_head_jnt_num || i == m_backbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Rsh);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 0.0f);
    cXyz* speed_p = &speed;
    cXyz* old_pos_p = &old.pos;
    cXyz* current_pos_p = &current.pos;
    mAcch.Set(current_pos_p, old_pos_p, this, 1, &mAcchCir, speed_p);

    mpShopCursor = ShopCursor_create(
        (J3DModelData *) dComIfG_getObjectRes(m_arcname, DEMO_SELECT(RSH_INDEX_BMD_SHOP_CURSOR01, RSH_BMD_SHOP_CURSOR01)),
        (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arcname, DEMO_SELECT(RSH_INDEX_BRK_SHOP_CURSOR01, RSH_BRK_SHOP_CURSOR01)),
        l_HIO.field_0x34
    );

    return mpShopCursor != NULL ? TRUE : FALSE;
}

/* 000049A0-00004A28       .text set_mtx__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::set_mtx() {
    J3DModel* morf_model_p = mpMorf->getModel();
    mDoMtx_stack_c::transS(
        current.pos.x + field_0x7A0.x,
        current.pos.y + field_0x7A0.y,
        current.pos.z + field_0x7A0.z
    );
    mDoMtx_stack_c::YrotM(current.angle.y);
    morf_model_p->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00004A28-00004A48       .text daNpc_Rsh1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Rsh1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_create();
}

/* 00004A48-00004A68       .text daNpc_Rsh1_Delete__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Delete(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_delete();
}

/* 00004A68-00004A88       .text daNpc_Rsh1_Execute__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Execute(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_execute();
}

/* 00004A88-00004AA8       .text daNpc_Rsh1_Draw__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Draw(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_draw();
}

/* 00004AA8-00004AB0       .text daNpc_Rsh1_IsDelete__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_IsDelete(daNpc_Rsh1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Rsh1_Method = {
    (process_method_func)daNpc_Rsh1_Create,
    (process_method_func)daNpc_Rsh1_Delete,
    (process_method_func)daNpc_Rsh1_Execute,
    (process_method_func)daNpc_Rsh1_IsDelete,
    (process_method_func)daNpc_Rsh1_Draw,
};

actor_process_profile_definition g_profile_NPC_RSH1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_RSH1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Rsh1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_RSH1,
    /* Actor SubMtd */ &l_daNpc_Rsh1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
