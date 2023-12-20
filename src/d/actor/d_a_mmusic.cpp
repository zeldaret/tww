//
// Generated by dtk
// Translation Unit: d_a_mmusic.cpp
//

#include "d/actor/d_a_mmusic.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_mtx.h"

namespace daMmusic {
    namespace {
        struct Attr_c {
            /* 0x00 */ u32 mTimer;
            /* 0x04 */ u16 field_0x04;
        };

        static const Attr_c L_attr = {
            120, 180,
        };

        inline const Attr_c & attr() { return L_attr; }
    }
}

/* 00000078-0000009C       .text solidHeapCB__Q28daMmusic5Act_cFP10fopAc_ac_c */
BOOL daMmusic::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 0000009C-000000A4       .text create_heap__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::create_heap() {
    return true;
}

/* 000000A4-0000013C       .text Macore_is_playing__Q28daMmusic5Act_cFv */
BOOL daMmusic::Act_c::Macore_is_playing() {
    if (dComIfGs_isStageBossEnemy(7) ||
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x2910) ||
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x2e02) ||
        g_dComIfG_gameInfo.save.mSavedata.mEvent.isEventBit(0x1610) ||
        !dComIfGs_checkGetItem(LV3_SWORD))
        return FALSE;

    return TRUE;
}

/* 0000013C-000001A4       .text set_mtx__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 000001A4-00000268       .text _create__Q28daMmusic5Act_cFv */
s32 daMmusic::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    s32 ret = cPhs_COMPLEATE_e;
    if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
        set_mtx();
        fopAcM_SetMtx(this, mMtx);
        field_0x298 = Macore_is_playing();
        fopAcM_setCullSizeSphere(this, 0.0f, 0.0f, 0.0f, 300.0f);
        init_se();
    } else {
        ret = cPhs_ERROR_e;
    }
    return ret;
}

/* 00000268-000002B4       .text _delete__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_delete() {
    if (mpEmitter != NULL) {
        mpEmitter->becomeInvalidEmitter();
        mpEmitter = NULL;
    }
    delete_se();
    return true;
}

/* 000002B4-000002C0       .text init_se__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::init_se() {
    mTimer = 120;
}

/* 000002C0-000003D0       .text manage_se__Q28daMmusic5Act_cFi */
void daMmusic::Act_c::manage_se(int cull) {
    if (!mDoAud_checkCbPracticePlay()) {
        if (mTimer > 0)
            mTimer--;

        if (mTimer == 0) {
            mDoAud_cbPracticePlay(&current.pos);
            mTimer = cM_rndF(1.0f) * 60.0f + 120.0f;
        } else if (cull == 0 && field_0x29c == 1) {
            mpEmitter->stopCreateParticle();
            field_0x29c = 0;
        }
    } else {
        if (cull == 0 && field_0x29c == 0) {
            mpEmitter->playCreateParticle();
            field_0x29c = 1;
        }
    }
}

/* 000003D0-000003FC       .text delete_se__Q28daMmusic5Act_cFv */
void daMmusic::Act_c::delete_se() {
    mDoAud_cbPracticeStop();
}

/* 000003FC-00000554       .text _execute__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_execute() {
    if (mpEmitter == NULL && field_0x298 == 1) {
        set_mtx();
        cXyz scale(1.0f, 1.0f, 1.0f);
        JPABaseEmitter* emtr = dComIfGp_particle_set(0x826c, &current.pos);
        mpEmitter = emtr;
        if (emtr != NULL) {
            mpEmitter->setGlobalRTMatrix(mMtx);
            field_0x298 = 0;
            field_0x29c = 1;
        }
    } else if (mpEmitter != NULL) {
        int cull = fopAcM_cullingCheck(this);
        if (cull == 1) {
            if (field_0x29c == 1) {
                mpEmitter->stopCreateParticle();
                field_0x29c = 0;
            }
        } else {
            if (field_0x29c == 0) {
                mpEmitter->playCreateParticle();
                field_0x29c = 1;
            }
        }
        manage_se(cull);
    } else {
        field_0x298 = Macore_is_playing();
    }

    return TRUE;
}

/* 00000554-0000055C       .text _draw__Q28daMmusic5Act_cFv */
bool daMmusic::Act_c::_draw() {
    return true;
}

namespace daMmusic {
    namespace {
        s32 Mthd_Create(void* i_this) {
            return ((Act_c*)i_this)->_create();
        }

        BOOL Mthd_Delete(void* i_this) {
            return ((Act_c*)i_this)->_delete();
        }

        BOOL Mthd_Execute(void* i_this) {
            return ((Act_c*)i_this)->_execute();
        }

        BOOL Mthd_Draw(void* i_this) {
            return ((Act_c*)i_this)->_draw();
        }

        BOOL Mthd_IsDelete(void* i_this) {
            return TRUE;
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

actor_process_profile_definition g_profile_Mmusic = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Mmusic,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daMmusic::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00F6,
    /* Actor SubMtd */ &daMmusic::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
