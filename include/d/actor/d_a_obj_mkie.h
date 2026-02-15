#ifndef D_A_OBJ_MKIE_H
#define D_A_OBJ_MKIE_H

#include "d/d_bg_s_movebg_actor.h"
#include "m_Do/m_Do_ext.h"

namespace daObjMkie {
class Act_c : public dBgS_MoveBgActor {
public:
    static Mtx M_tmp_mtx;
    static u32 prm_make(u8 eventId, int swNo) { return swNo << 0x10 | (eventId | 0x3000); };

    void setup(const cXyz* pos) {
        current.pos = *pos;
        mCcInit = 1;
    };

    struct Attr_c {
        const char* name;
        float mScale;
        Vec table[8][3];
    };

    enum Prm_e {
        PRM_CORRECT_W = 0x01,
        PRM_CORRECT_S = 0xc,

        PRM_EVID_W = 0x08,
        PRM_EVID_S = 0x0,

        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x10,

        PRM_TYPE_W = 0x01,
        PRM_TYPE_S = 0x08,

        PRM_FLAG_W = 0x01,
        PRM_FLAG_S = 0x0d,
    };

    BOOL prm_get_correct() const { return daObj::PrmAbstract<Prm_e>(this, PRM_CORRECT_W, PRM_CORRECT_S); }
    u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EVID_W, PRM_EVID_S); }
    int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    int prm_get_type() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }

    virtual BOOL CreateHeap();
    void init_cc();
    void set_cc_pos();
    virtual BOOL Create();
    cPhs_State Mthd_Create();
    virtual BOOL Delete();
    BOOL Mthd_Delete();
    void set_mtx();
    void init_mtx();
    BOOL chk_light();
    void eff_break();
    void sound_melt();
    void sound_break();
    void vib_break();
    void mode_wait();
    void mode_demoWait_init();
    void mode_demoWait();
    void mode_demo_init();
    void mode_demo();
    void mode_proc_call();
    virtual BOOL Execute(Mtx**);
    virtual BOOL Draw();

    static const char M_arcname[];
    static const dCcD_SrcTri M_tri_src;
    static const Attr_c M_attr[];

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mModelBase;
    /* 0x2D4 */ J3DModel* mModelVan;
    /* 0x2D8 */ mDoExt_brkAnm mBrkVan;
    /* 0x2F0 */ dCcD_Tri mTri[8];
    /* 0xD70 */ dCcD_Stts mStts[8];
    /* 0xF50 */ int mModeProc;
    /* 0xF54 */ int mType;
    /* 0xF58 */ bool mCcInit;
    /* 0xF59 */ bool mStatueDelete;
    /* 0xF5A */ bool mEvtPlaying;
    /* 0xF5B */ bool mBaseAnmPlaying;
    /* 0xF5C */ s16 mState;
    /* 0xF5E */ s16 mLightCnt;
    /* 0xF60 */ s16 mEvtIdx;
    /* 0xF62 */ bool mSwitch;
    /* 0xF63 */ bool mBroken;
}; // Size: 0xF64
}; // namespace daObjMkie

#endif /* D_A_OBJ_MKIE_H */
