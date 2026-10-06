/**
 * d_a_obj_vyasi.cpp
 * Object - Palm tree blowing in the wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vyasi.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/d_lib.h"

namespace daObjVyasi {

namespace {
struct Attr_c {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ s16 field_0x20;
    /* 0x22 */ s16 field_0x22;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ u8 pad[0x84 - 0x30];
}; // Size: 0x84

static Attr_c const L_attr = {
    1.0f, 79.0f, 250.0f, 0.0f, 0.0f, 0.0f, 0.4f, 1.5f, 2, 0, 700.0f, 1700.0f, 1700.0f, {},
};

inline Attr_c const& attr() {
    return L_attr;
}
} // namespace

static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};


static const dCcD_SrcCps M_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
    }},
};


static const dCcD_SrcSph M_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
    }},
};

static u8 joint_kind_table[14] = { 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

}; // namespace daObjVyasi

/* 000000EC-0000015C       .text SetStopJointAnimation__Q210daObjVyasi5Act_cFP18J3DAnmTransformKeyff */
BOOL daObjVyasi::Act_c::SetStopJointAnimation(J3DAnmTransformKey* i_key, float i_speed, float i_morf) {
    if (i_key != NULL) {
        mpMorf->setAnm(i_key, 0, i_morf, i_speed, 0.0f, -1.0f, NULL);
        field_0x19C4 = 1;
        return true;
    }
    return false;
}

/* 0000015C-00000194       .text PlayStopJointAnimation__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::PlayStopJointAnimation() {
    if (mpMorf->play(NULL, 0, 0) == 0) {
        return TRUE;
    }
    return FALSE;
}

/* 00000194-0000021C       .text set_first_process__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_first_process() {
    process_init(is_switch() ? 4 : 1);
    mNormalCounter = 0;
    field_0x19D4 = 1.0f;
    shape_angle.y += 0x8000;
}

/* 0000021C-000005B8       .text set_collision__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_collision() {
    if (mCyl.ChkTgHit()) {
        mCyl.GetTgHitObj();
        daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &mCyl, 7);
        daObj::HitEff_kikuzu(this, &mCyl);
        dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
        mCyl.ClrTgHit();
    } else {
        mCyl.SetR(79.0f);
        mCyl.SetH(250.0f);
        mCyl.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    }

    for (int i = 0; i < 5; i++) {
        if (field_0x7E0[i].ChkTgHit()) {
            field_0x7E0[i].GetTgHitObj();
            daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &field_0x7E0[i], 7);
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            field_0x7E0[i].ClrTgHit();
        } else {
            int k = i + 1;
            field_0xDF8[i].mStart = field_0x400[i];
            field_0xDF8[i].mEnd = field_0x400[k];
            field_0xDF8[i].mRadius = 47.4f;
            field_0x7E0[i].cM3dGCps::Set(field_0xDF8[i]);
            dComIfG_Ccsp()->Set(&field_0x7E0[i]);
        }
    }

    for (int i = 0; i < 8; i += 2) {
        int idx = i >> 1;
        int j = idx + 1;
        int k = idx + 2;

        cXyz delta(
            (field_0x400[k].x - field_0x400[j].x) * 0.33333f,
            (field_0x400[k].y - field_0x400[j].y) * 0.33333f,
            (field_0x400[k].z - field_0x400[j].z) * 0.33333f
        );

        cXyz pos;
        pos.x = field_0x400[j].x + delta.x;
        pos.y = field_0x400[j].y + delta.y;
        pos.z = field_0x400[j].z + delta.z;
        field_0x1064[i].SetC(pos);
        field_0x1064[i].SetR(47.4f);
        dComIfG_Ccsp()->Set(&field_0x1064[i]);

        pos.x = field_0x400[j].x + delta.x * 2.0f;
        pos.y = field_0x400[j].y + delta.y * 2.0f;
        pos.z = field_0x400[j].z + delta.z * 2.0f;
        field_0x1064[i + 1].SetC(pos);
        field_0x1064[i + 1].SetR(47.4f);
        dComIfG_Ccsp()->Set(&field_0x1064[i + 1]);
    }
}

char const daObjVyasi::Act_c::M_arcname[] = "Vyasi";

/* 000005F4-000009B8       .text JointNodeCallBack__10daObjVyasiFP7J3DNodei */
BOOL daObjVyasi::JointNodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000009F4-000009FC       .text process_none_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_none_init() {
    return TRUE;
}

/* 000009FC-00000A00       .text process_none_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_main() {
    /* Nonmatching */
}

/* 00000A00-00000A64       .text process_sag_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_sag_init() {
    if (SetStopJointAnimation(mpBckData, 1.0f, 0.0f) != 0) {
        mpMorf->setPlaySpeed(0.0f);
        return TRUE;
    }
    return FALSE;
}

/* 00000A64-00000AD8       .text process_sag_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sag_main() {
    /* Nonmatching */
}

/* 00000AD8-00000CC0       .text process_sagWind_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_init() {
    /* Nonmatching */
}

/* 00000CC0-00000D20       .text process_sagWind_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_main() {
    /* Nonmatching */
}

/* 00000D20-00000D54       .text process_toNormal_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_init() {
    /* Nonmatching */
}

/* 00000D54-00000E10       .text process_toNormal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_main() {
    /* Nonmatching */
}

/* 00000E10-00000E74       .text process_normal_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_init() {
    /* Nonmatching */
}

/* 00000E74-00000ED0       .text process_normal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_main() {
    /* Nonmatching */
}

/* 00000ED0-00000FE4       .text process_init__Q210daObjVyasi5Act_cFi */
void daObjVyasi::Act_c::process_init(int) {
    /* Nonmatching */
}

/* 00000FE4-000010C8       .text process_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_main() {
    /* Nonmatching */
}

/* 000010C8-000010EC       .text solidHeapCB__Q210daObjVyasi5Act_cFP10fopAc_ac_c */
BOOL daObjVyasi::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->create_heap();
}

/* 000010EC-00001290       .text create_heap__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::create_heap() {
    /* Nonmatching */
    return true;
}

/* 00001290-000016E0       .text _create__Q210daObjVyasi5Act_cFv */
cPhs_State daObjVyasi::Act_c::_create() {
    fopAcM_ct(this, daObjVyasi::Act_c);

    cPhs_State res = dComIfG_resLoad(&mPhs, M_arcname);
    if (res == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            set_first_process();
            set_mtx();
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000.0f, 0.0f, -2000.0f, 2000.0f, 2000.0f, 2000.0f);
            fopAcM_setCullSizeFar(this, 2.0f);
            field_0x548.Init(0xFF, 0xFF, this);
            mCyl.Set(M_cyl_src);
            mCyl.SetStts(&field_0x548);
            mCyl.SetTgVec((cXyz&)cXyz::Zero);
            mCyl.OnTgNoHitMark();

            for (int i = 0; i < 5; i++) {
                field_0x6B4[i].Init(100, 0xFF, this);
                field_0x7E0[i].Set(M_cps_src);
                field_0x7E0[i].SetStts(&field_0x6B4[i]);
                field_0xDF8[i].mStart = current.pos;
                field_0xDF8[i].mEnd = current.pos;
                field_0xDF8[i].mRadius = 100.0f;
            }

            for (int i = 0; i < 8; i++) {
                field_0xE84[i].Init(100, 0xFF, this);
                field_0x1064[i].Set(M_sph_src);
                field_0x1064[i].SetStts(&field_0xE84[i]);
                mCyl.SetTgVec((cXyz&)cXyz::Zero);
                mCyl.OnTgNoHitMark();
            }

            J3DModel* model = mpMorf->getModel();
            J3DModelData* modelData = model->getModelData();
            model->setUserArea((uintptr_t)this);
            for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
                modelData->getJointNodePointer(i)->setCallBack(JointNodeCallBack);
            }

            for (u16 i = 0; i < 14; i++) {
                mJointQuat[i] = ZeroQuat;
            }

            field_0x4A8 = 1.0f;
            field_0x4AC = 1.0f;
            field_0x4B0 = 1.0f;
        } else {
            res = cPhs_ERROR_e;
        }
    }
    return res;
}

/* 00001D8C-00001DBC       .text _delete__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_delete() {
    /* Nonmatching */
}

/* 00001DBC-00001E5C       .text set_mtx__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00001E5C-000025A8       .text calc_dif_angle__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::calc_dif_angle() {
    /* Nonmatching */
}

/* 000025A8-00002880       .text quaternion_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::quaternion_main() {
    /* Nonmatching */
}

/* 00002880-00002938       .text leaf_scale_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::leaf_scale_main() {
    /* Nonmatching */
}

/* 00002938-000029BC       .text _execute__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_execute() {
    /* Nonmatching */
}

/* 000029BC-00002A6C       .text _draw__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjVyasi {
namespace {
/* 00002A6C-00002A8C       .text Mthd_Create__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_create();
}

/* 00002A8C-00002AB0       .text Mthd_Delete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_delete();
}

/* 00002AB0-00002AD4       .text Mthd_Execute__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_execute();
}

/* 00002AD4-00002AF8       .text Mthd_Draw__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_draw();
}

/* 00002AF8-00002B00       .text Mthd_IsDelete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVyasi

actor_process_profile_definition g_profile_Obj_Vyasi = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vyasi_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVyasi::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vyasi_e,
    /* Actor SubMtd */ &daObjVyasi::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
