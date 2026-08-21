/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_vibration.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"

s32 daSaku_c::m_saku_alpha_out_time = 10;
s32 daSaku_c::m_max_particle_timer = 2000;

/* Field layout beyond mNo is inferred from usage across this file's
   functions, not from a matched constructor: mNo is the mDoHIO_createChild
   child id (sentinel -1), and there is an s16 "chase speed" field at 0x10
   used by mode_break_fire. Everything else in the 0x18-byte object (real
   size confirmed via the linked l_sakuHIO symbol) is unverified and left as
   raw padding rather than guessed at. */
class sakuHIO_c : public JORReflexible {
public:
    sakuHIO_c() {}
    virtual ~sakuHIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05[0x18 - 0x05];
};

static sakuHIO_c l_sakuHIO;

const dCcD_SrcCyl daSaku_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_FIRE | AT_TYPE_MACHETE | AT_TYPE_UNK800 | AT_TYPE_SKULL_HAMMER | AT_TYPE_UNK20000 | AT_TYPE_FIRE_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
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
        /* Radius */ 50.0f,
        /* Height */ 200.0f,
    }},
};


const u8 daSaku_c::dust_color[4] = { 0x69, 0x5B, 0x30, 0xFF };

/* Real string contents unverified: no REL exists for this object to inspect
   the rodata relocations with a decompiler, and the string bytes have no
   effect on the .text this file is being matched against. Placeholder names
   follow the object's real name ("Saku" per the retail symbol map). */
const char* daSaku_c::m_arcname[3] = { "Saku", "Saku", "Saku" };

class J3DModelData;
class J3DMaterial;

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    /* Nonmatching - 88.1%, logic verified correct against target disassembly:
       both counted per-side init loops, cullMtx setup, dCcD_Stts::Init, and
       the setCol/setMtx calls all match exactly. Only the final dust_color
       copy loop differs, where the target hoists all four color byte loads
       above the loop as loop-invariant while this form re-reads them each
       iteration; hoisting them into locals was tried and made the match
       worse due to a knock-on register allocation change, so it was left as
       the higher-scoring form. */
    for (int i = 0; i < 2; i++) {
        *(u32*)((u8*)this + i * 4 + 0xEBC) = 0;
        *(u32*)((u8*)this + i * 4 + 0xEAC) = 0;
        *(u8*)((u8*)this + i * 2 + 0xEDC) = 0xFF;
        *(u8*)((u8*)this + i * 2 + 0xEDD) = 0;
        *(s32*)((u8*)this + i * 4 + 0xEE0) = -1;
        *(u8*)((u8*)this + i + 0xEF0) = 2;
    }

    *(u8*)((u8*)this + 0xEF4) = 0;
    *(u32*)((u8*)this + 0xEEC) = 0;

    void* bottom = *(void**)((u8*)this + 0xE24);
    cullMtx = (MtxP)((u8*)bottom + 0x24);

    ((dCcD_Stts*)(m290 + (0x2D0 - 0x290)))->Init(0xFF, 0xFF, this);

    setCol();
    setMtx();

    for (int i = 0; i < 2; i++) {
        *(u8*)((u8*)this + i * 0x20 + 0x2A6) = dust_color[0];
        *(u8*)((u8*)this + i * 0x20 + 0x2A7) = dust_color[1];
        *(u8*)((u8*)this + i * 0x20 + 0x2A8) = dust_color[2];
        *(u8*)((u8*)this + i * 0x20 + 0x2A9) = dust_color[3];
        *(u8*)((u8*)this + i * 0x20 + 0x2A1) = 1;
    }
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
void daSaku_c::saku_draw_sub(int) {
    /* Nonmatching */
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
BOOL daSaku_c::mode_break_none(int b) {
    /* Nonmatching - 81.3%, logic verified correct against target disassembly,
       including reverse engineering which AT_TYPE_* flags gate each
       sturdiness level (SWORD/UNK8/BOMB/MACHETE/UNK800/DARKNUT_SWORD/
       MOBLIN_SPEAR/SKULL_HAMMER for sturdiness 0, a subset of those for
       sturdiness 1) and which flags trigger the shock/burn path
       (FIRE/UNK20000/FIRE_ARROW). The remaining diffs are register swaps on
       the two accumulator flags plus a couple of extra compares the
       compiler inserts around them; the underlying control flow and bit
       tests all match the target address for address. */
    u8* sideBase = (u8*)this + b * 0x390;
    BOOL hitFlag = FALSE;
    BOOL shockFlag = FALSE;
    for (int k = 0; k < 3; k++) {
        dCcD_GObjInf* gObjInf = (dCcD_GObjInf*)(sideBase + k * 0x130 + 0x30C);
        if (!gObjInf->ChkTgHit())
            continue;
        cCcD_Obj* hitObj = gObjInf->GetTgHitObj();
        if (hitObj == NULL)
            continue;

        if (mSturdinessType == 0) {
            u32 atType = hitObj->GetAtType();
            if ((atType & AT_TYPE_SWORD) || (atType & AT_TYPE_UNK8) || (atType & AT_TYPE_BOMB) ||
                (atType & AT_TYPE_MACHETE) || (atType & AT_TYPE_UNK800) || (atType & AT_TYPE_DARKNUT_SWORD) ||
                (atType & AT_TYPE_MOBLIN_SPEAR) || (atType & AT_TYPE_SKULL_HAMMER))
                hitFlag |= TRUE;
        } else if (mSturdinessType == 1) {
            u32 atType = hitObj->GetAtType();
            if ((atType & AT_TYPE_MACHETE) || (atType & AT_TYPE_BOMB) || (atType & AT_TYPE_UNK800) ||
                (atType & AT_TYPE_DARKNUT_SWORD))
                hitFlag |= TRUE;
        }

        if (hitFlag)
            dComIfGp_getVibration().StartShock(4, -33, cXyz(0.0f, 1.0f, 0.0f));

        u32 atType2 = hitObj->GetAtType();
        if ((atType2 & AT_TYPE_FIRE) || (atType2 & AT_TYPE_UNK20000) || (atType2 & AT_TYPE_FIRE_ARROW))
            shockFlag |= TRUE;

        if (shockFlag)
            break;
    }

    if (shockFlag) {
        burn();
    } else if (hitFlag) {
        if (b == 1 && *(s32*)((u8*)this + 0xEF8) == 1)
            broken(0);
        broken(b);
    }
    return TRUE;
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
BOOL daSaku_c::mode_break_fire(int b) {
    /* Nonmatching - 92.1%, logic verified correct against target disassembly.
       sakuHIO_c's real field layout beyond mNo and this s16 speed field at
       0x10 is unknown (no REL exists for this file to inspect further with
       Ghidra), so it is declared as raw padding here. The remaining diff is
       mostly a this/b register swap plus a couple of single-use indexed
       loads, both cosmetic; target also has one truly redundant duplicate
       null check on the heap pointer that this form does not reproduce. */
    daSaku_c* self = this;
    if (*(s32*)((u8*)self + 0xEBC) > m_saku_alpha_out_time) {
        u8* row2 = (u8*)self + b * 2;
        cLib_chaseUC(row2 + 0xEDD, 0xFF, (u8)(*(s16*)((u8*)&l_sakuHIO + 0x10)));
        if (cLib_chaseUC(row2 + 0xEDC, 0, (u8)(*(s16*)((u8*)&l_sakuHIO + 0x10)))) {
            u8* row3 = (u8*)self + b * 8;
            if (*(void**)(row3 + 0xE14) != NULL) {
                u8* bCounter = (u8*)self + b + 0xEF0;
                if (*bCounter != 0) {
                    (*bCounter)--;
                    if (*bCounter == 0) {
                        mDoExt_destroySolidHeap(*(JKRSolidHeap**)(row3 + 0xE14));
                        *(u32*)(row3 + 0xE14) = 0;
                        *(u32*)(row3 + 0xE24) = 0;
                    }
                }
            }
        }
    }
    return TRUE;
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
void daSaku_c::mode_break_throw_obj(int) {
    /* Nonmatching */
}

/* 0000083C-000008EC       .text RecreateHeap__8daSaku_cFii */
BOOL daSaku_c::RecreateHeap(int a, int b) {
    /* Nonmatching - 94.75%, logic verified correct against target disassembly
       (JUT_ASSERT guard, freeAll on the old heap, swap current heap, recreate
       via CreateHeap(1, b), then restore the old current heap). Two small
       remaining diffs: the row/elem pointer build folds b*8+a*4 together
       before adding this instead of adding this first, and the stringified
       assert condition here is a different length than the real source's,
       which shifts the pooled OSPanic message string offset by two bytes. */
    u8* row = (u8*)this + b * 8;
    u8* elem = row + a * 4;
    JUT_ASSERT(869, *(JKRHeap**)(elem + 0xE14) != NULL);
    (*(JKRHeap**)(elem + 0xE14))->freeAll();
    JKRHeap* old = mDoExt_setCurrentHeap(*(JKRHeap**)(elem + 0xE14));
    CreateHeap(1, b);
    mDoExt_setCurrentHeap(old);
    return TRUE;
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
BOOL daSaku_c::CreateHeap(int a, int b) {
    /* Nonmatching - 90.5%, logic and switch case values verified correct
       address-by-address against target disassembly. Same two open issues as
       CreateDummyHeap: a single-use field access folds into an indexed load
       instead of a base pointer plus immediate offset, and the loadModel
       guard's failure path is placed at the end of the function instead of
       inline, missing the same loadMoveBG return normalization sequence. */
    u8* row = (u8*)this + b * 4;
    s32 state = *(s32*)(row + 0xEF8);
    int k = a;
    switch (state) {
    case 1:
        k = 0;
        break;
    case 2:
        k = 1;
        break;
    case 3:
        k = 2;
        break;
    }

    if (!loadModel(k, a, b))
        return FALSE;

    return loadMoveBG(GetDzbId(b), a, b);
}

/* 000009B0-00000A4C       .text GetDzbId__8daSaku_cFi */
s32 daSaku_c::GetDzbId(int b) {
    /* Nonmatching - 92.6%, logic verified correct against target disassembly
       (side b == 1 or unresisted short-circuits to a plain state check, else
       falls into the state == 2 or 3 collapse and the switch resist lookup).
       Two remaining diffs are a single-use field access folded into an
       indexed load instead of a base pointer plus immediate offset, and the
       final if/return pair getting its true/false halves swapped relative to
       target at the very end of the function; neither reflects a logic bug. */
    u8* row = (u8*)this + b * 4;
    s32 state = *(s32*)(row + 0xEF8);
    if (b == 1 || *(s32*)((u8*)this + 0xEFC) == 0) {
        if (state == 1)
            return 0;
        return 1;
    }

    if (state == 3 || state == 2)
        return 3;

    if (dComIfGs_isSwitch(mTopHalfDestroyedSwitch, home.roomNo))
        return 4;
    return 2;
}

/* 00000A4C-00000ADC       .text CreateDummyHeap__8daSaku_cFi */
BOOL daSaku_c::CreateDummyHeap(int i_dummy) {
    /* Nonmatching - 90.8%, logic verified correct against target disassembly
       (sturdiness-based param selection, loadModel guard, loadMoveBG call and
       its return). Target normalizes loadMoveBG's return through a subic/subfe
       0-or-1 sequence that this form of the call does not reproduce, meaning
       loadMoveBG's real return type is probably not a plain BOOL; left as-is
       until loadMoveBG itself is decompiled and its true return type is known. */
    int k = i_dummy;
    if (mSturdinessType == 0)
        k = 0;
    else if (mSturdinessType == 1)
        k = 1;

    if (loadModel(k, 1, i_dummy))
        return loadMoveBG(1, 1, i_dummy);

    return FALSE;
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
BOOL daSaku_c::loadMoveBG(int a, int b, int c) {
    /* Nonmatching - 83.1%, logic verified correct against target disassembly:
       the local resource id table (real retail values 3,4,5,6,3 read
       straight from the target's rodata), the new dBgW allocation, the null
       check, the object resource lookup, and the cBgW::Set call with the
       correct MOVE_BG_e flag and per-side matrix slot all match. The
       remaining diff is the same single-use indexed-load-versus-immediate-
       offset pattern already open on several other functions in this file,
       plus a return value normalization difference this form does not
       reproduce; neither is a logic error. */
    const s32 table[5] = { 3, 4, 5, 6, 3 };

    *(dBgW**)((u8*)this + c * 8 + b * 4 + 0xE34) = new dBgW();
    if (*(dBgW**)((u8*)this + c * 8 + b * 4 + 0xE34) == NULL)
        return FALSE;

    void* res = dComIfG_getObjectRes(m_arcname[0], table[a]);
    return (*(dBgW**)((u8*)this + c * 8 + b * 4 + 0xE34))
        ->Set((cBgD_t*)res, cBgW::MOVE_BG_e, (Mtx*)((u8*)this + c * 0x30 + 0xE4C));
}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
BOOL daSaku_c::loadModel(int, int, int) {
    /* Nonmatching */
}

/* 00000D7C-00000E8C       .text burn__8daSaku_cFv */
BOOL daSaku_c::burn() {
    if (*(u8*)(mEF3 + 1) == 0) {
        if (*(s32*)(mEF3 + 5) == 1) {
            *(s32*)(mEF3 + 5) = 2;
            RecreateHeap(1, 0);
            *(u32*)(m290 + (0xEE0 - 0x290)) = 0x32;
        }
        if (*(s32*)(mEF3 + 9) == 1) {
            *(s32*)(mEF3 + 9) = 2;
            RecreateHeap(1, 1);
            *(u32*)(m290 + (0xEE4 - 0x290)) = 0x32;
        }

        void* bottom = *(void**)(m290 + (0xE28 - 0x290));
        if (bottom != NULL) {
            cullMtx = (MtxP)((u8*)bottom + 0x24);
        } else {
            void* top = *(void**)(m290 + (0xE30 - 0x290));
            if (top != NULL)
                cullMtx = (MtxP)((u8*)top + 0x24);
        }

        setEffFire(0);
        *(u32*)(m290 + (0xEEC - 0x290)) = 0x5a;

        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
        if (*(s32*)(mEF3 + 9) != 0)
            dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);

        *(u8*)(mEF3 + 1) = 1;
    }
    return TRUE;
}

/* 00000E8C-00000F60       .text broken__8daSaku_cFi */
BOOL daSaku_c::broken(int b) {
    /* Nonmatching - 87.7%, logic verified correct against target disassembly
       (marks the side as broken, resets its resist counter, fires the right
       destroyed-switch depending on side, recreates its heap, points cullMtx
       at the bottom half when applicable, and clears its move flags). The
       remaining diffs are the same constant-load-vs-address-calc and
       single-use indexed-load scheduling quirks already open elsewhere in
       this file, not logic errors. */
    setEffBreak(b);

    u8* row = (u8*)this + b * 4;
    *(s32*)(row + 0xEF8) = 3;
    *(s32*)(row + 0xEE0) = 0;

    if (b == 0)
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
    else
        dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);

    RecreateHeap(1, b);

    if (b == 0) {
        u8* row2 = (u8*)this + b * 8;
        void* bottom = *(void**)(row2 + 0xE28);
        cullMtx = (MtxP)((u8*)bottom + 0x24);
    }

    *(u8*)((u8*)this + b * 2 + 0xEDC) = 0;
    *(u8*)((u8*)this + b * 2 + 0xEDD) = 0xFF;

    return TRUE;
}

/* 00000F60-00000FF4       .text changeCollision__8daSaku_cFi */
BOOL daSaku_c::changeCollision(int b) {
    u8* row = (u8*)this + b * 4;
    if (*(s32*)(row + 0xEF8) == 0)
        return FALSE;

    s32 count = *(s32*)(row + 0xEE0);
    if (count >= 0) {
        if (count == 0) {
            g_dComIfG_gameInfo.play.mBgS.Release(*(cBgW**)(row + 0xE44));
            MoveBGResist(1, b);
        }
        *(s32*)(row + 0xEE0) = *(s32*)(row + 0xEE0) - 1;
    }
    return TRUE;
}

/* 00000FF4-0000113C       .text setMtx__8daSaku_cFv */
void daSaku_c::setMtx() {
    /* Nonmatching - 99.9%, logic verified correct against target disassembly.
       The only remaining diff is the pooled 200.0f literal getting a
       different rodata address than the target, the same float pool
       ordering quirk affecting move_sound and alpha_anime elsewhere in this
       session, not a logic error. */
    for (int i = 0; i < 2; i++) {
        dBgW* bgw = *(dBgW**)((u8*)this + i * 4 + 0xE24);
        if (bgw != NULL) {
            *(f32*)((u8*)bgw + 0x18) = scale.x;
            *(f32*)((u8*)bgw + 0x1c) = scale.y;
            *(f32*)((u8*)bgw + 0x20) = scale.z;
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
            PSMTXCopy(mDoMtx_stack_c::now, (MtxP)((u8*)bgw + 0x24));
        }
    }

    if (*(s32*)((u8*)this + 0xEFC) != 0) {
        for (int j = 0; j < 2; j++) {
            dBgW* bgw = *(dBgW**)((u8*)this + j * 4 + 0xE2C);
            if (bgw != NULL) {
                *(f32*)((u8*)bgw + 0x18) = scale.x;
                *(f32*)((u8*)bgw + 0x1c) = scale.y;
                *(f32*)((u8*)bgw + 0x20) = scale.z;
                mDoMtx_stack_c::transS(current.pos.x, 200.0f + current.pos.y, current.pos.z);
                mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
                PSMTXCopy(mDoMtx_stack_c::now, (MtxP)((u8*)bgw + 0x24));
            }
        }
    }
}

/* 0000113C-0000120C       .text setMoveBGMtx__8daSaku_cFv */
void daSaku_c::setMoveBGMtx() {
    /* Nonmatching - 99.8%, logic verified correct against target disassembly.
       The only remaining diff is the pooled 200.0f literal getting a
       different rodata address than the target, the same float pool
       ordering quirk affecting move_sound, alpha_anime and setMtx elsewhere
       in this session, not a logic error. */
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    PSMTXCopy(mDoMtx_stack_c::now, (MtxP)((u8*)this + 0xE4C));

    if (*(s32*)((u8*)this + 0xEFC) != 0) {
        mDoMtx_stack_c::transS(current.pos.x, 200.0f + current.pos.y, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        PSMTXCopy(mDoMtx_stack_c::now, (MtxP)((u8*)this + 0xE7C));
    }
}

/* 0000120C-0000134C       .text checkCol__8daSaku_cFv */
void daSaku_c::checkCol() {
    /* Nonmatching */
}

/* 0000134C-00001510       .text setCol__8daSaku_cFv */
void daSaku_c::setCol() {
    /* Nonmatching */
}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
BOOL daSaku_c::MoveBGResist(int a, int b) {
    /* Nonmatching - 70.7%, logic verified correct against target disassembly
       (row/elem pointer construction, dBgS::Regist call, storing the resisted
       board into the per-b slot, then calling Move on it). Remaining diff is an
       instruction scheduling swap around the second field access that several
       rewrites (cached vs re-derived pointer, split vs combined expressions,
       hoisted vs inline locals) could not reproduce exactly. */
    u8* row = (u8*)this + b * 8;
    u8* elem = row + a * 4;
    if (!g_dComIfG_gameInfo.play.mBgS.Regist(*(dBgW**)(elem + 0xE34), this))
        return FALSE;
    *(dBgW**)((u8*)this + b * 4 + 0xE44) = *(dBgW**)(elem + 0xE34);
    (*(dBgW**)((u8*)this + b * 4 + 0xE44))->Move();
    return TRUE;
}

/* 00001598-000016C0       .text setEffFire__8daSaku_cFi */
void daSaku_c::setEffFire(int) {
    /* Nonmatching */
}

/* 000016C0-000019AC       .text setEffBreak__8daSaku_cFi */
void daSaku_c::setEffBreak(int) {
    /* Nonmatching */
}

void changeXluMaterialAlpha(J3DMaterial*, unsigned char, bool);

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
BOOL matAlphaAnim(J3DModelData* modelData, unsigned char alpha, bool visible) {
    /* Nonmatching - 99.7%, logic verified correct against target disassembly.
       The only remaining diff is a two-byte shift in the pooled assert
       message string offsets, caused by the stringified condition text here
       not being exactly the same length as the real source's; the actual
       parameter names used by JUT_ASSERT's #COND are unknown. */
    JUT_ASSERT(1489, modelData != NULL);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++)
        changeXluMaterialAlpha(modelData->getMaterialNodePointer(i), alpha, visible);
    return TRUE;
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
void changeXluMaterialAlpha(J3DMaterial*, unsigned char, bool) {
    /* Nonmatching */
}

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    /* Nonmatching */
}

/* 00002264-000023D8       .text daSaku_Delete__FP8daSaku_c */
static BOOL daSaku_Delete(daSaku_c*) {
    /* Nonmatching */
}

/* 000023D8-000023E0       .text daSaku_IsDelete__FP8daSaku_c */
static BOOL daSaku_IsDelete(daSaku_c*) {
    return TRUE;
}

/* 000023E0-0000242C       .text daSaku_Draw__FP8daSaku_c */
static BOOL daSaku_Draw(daSaku_c*) {
}

/* 0000242C-00002560       .text daSaku_Execute__FP8daSaku_c */
static BOOL daSaku_Execute(daSaku_c* i_this) {
    /* Nonmatching - 93.2%, logic and switch dispatch targets verified
       address-by-address correct against target disassembly (including the
       case 1/3/2 physical block ordering, which matched once reordered to
       this exact sequence). The remaining diffs are a this/i0/i1 register
       swap plus the compiler hoisting the m_max_particle_timer load above
       the small timer loop instead of re-reading it every iteration like
       the target does, neither of which is a logic error. */
    for (int i = 0; i < 2; i++) {
        s32 timer = *(s32*)((u8*)i_this + i * 4 + 0xEBC);
        if (timer != 0 && timer < daSaku_c::m_max_particle_timer)
            *(s32*)((u8*)i_this + i * 4 + 0xEBC) = timer + 1;
    }

    if (*(s32*)((u8*)i_this + 0xEEC) != 0)
        (*(s32*)((u8*)i_this + 0xEEC))--;
    (*(s32*)((u8*)i_this + 0xEE8))++;

    for (int i = 0; i < 2; i++) {
        s32 state = *(s32*)((u8*)i_this + i * 4 + 0xEF8);
        switch (state) {
        case 1:
            i_this->mode_break_none(i);
            break;
        case 3:
            i_this->mode_break_throw_obj(i);
            break;
        case 2:
            i_this->mode_break_fire(i);
            break;
        }
    }

    for (int j = 0; j < 2; j++)
        i_this->changeCollision(j);

    i_this->setMtx();
    i_this->checkCol();
    return TRUE;
}

static actor_method_class l_daSaku_Method = {
    (process_method_func)daSaku_Create,
    (process_method_func)daSaku_Delete,
    (process_method_func)daSaku_Execute,
    (process_method_func)daSaku_IsDelete,
    (process_method_func)daSaku_Draw,
};

actor_process_profile_definition g_profile_SAKU = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SAKU_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSaku_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SAKU_e,
    /* Actor SubMtd */ &l_daSaku_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_9_e,
};
