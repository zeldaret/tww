#ifndef D_A_DAIOCTA_EYE_H
#define D_A_DAIOCTA_EYE_H

#include "SSystem/SComponent/c_math.h"
#include "d/d_cc_d.h"
#include "d/d_jnt_hit.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class daDaiocta_c;

class daDaiocta_Eye_c : public fopAc_ac_c {
public:
    enum Mode_e {
        MODE_WAIT   = 0x0,
        MODE_DAMAGE = 0x1,
        MODE_DEATH  = 0x2
    };

    typedef void (daDaiocta_Eye_c::*ModeProcFunc)(void);
public:
    void rndRotEye() {
        field_0x2E0 = cM_rndF(field_0x2F2);
        if (std::fabsf(field_0x2E0 - field_0x2E6.x) < field_0x2EC) {
            field_0x2E0 += field_0x2EC;
        }
        
        field_0x2E2 = cM_rndF(field_0x2F4);
        if (std::fabsf(field_0x2E2 - field_0x2E6.y) < field_0x2EE) {
            field_0x2E2 += field_0x2EE;
        }
        
        field_0x2E4 = cM_rndF(field_0x2F6);
        if (std::fabsf(field_0x2E4 - field_0x2E6.z) < field_0x2F0) {
            field_0x2E4 += field_0x2F0;
        }
    }

    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    void _coHit(fopAc_ac_c*);
    void setMtx();
    void checkTgHit();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDeathInit();
    void modeDeath();
    void modeProcCall();
    bool _execute();
    bool _draw();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const s32 m_heapsize;
    static const char m_arc_name[];
    static const s32 m_scale_damage_time;
public:
    /* 0x290 */ s32 field_0x290;
    /* 0x294 */ u8 field_0x294;
    /* 0x295 */ u8 field_0x295;
    /* 0x296 */ u8 field_0x296;
    /* 0x297 */ u8 field_0x297;
    /* 0x298 */ u8 field_0x298;
    /* 0x299 */ u8 field_0x299[0x29C - 0x299];
    /* 0x29C */ s32 field_0x29C;
    /* 0x2A0 */ request_of_phase_process_class field_0x2A0;
    /* 0x2A8 */ J3DModel* field_0x2A8;
    /* 0x2AC */ J3DAnmTevRegKey* field_0x2AC;
    /* 0x2B0 */ mDoExt_brkAnm field_0x2B0;
    /* 0x2C8 */ J3DAnmTextureSRTKey* field_0x2C8;
    /* 0x2CC */ mDoExt_btkAnm field_0x2CC;
    /* 0x2E0 */ s16 field_0x2E0;
    /* 0x2E2 */ s16 field_0x2E2;
    /* 0x2E4 */ s16 field_0x2E4;
    /* 0x2E6 */ csXyz field_0x2E6;
    /* 0x2EC */ s16 field_0x2EC;
    /* 0x2EE */ s16 field_0x2EE;
    /* 0x2F0 */ s16 field_0x2F0;
    /* 0x2F2 */ s16 field_0x2F2;
    /* 0x2F4 */ s16 field_0x2F4;
    /* 0x2F6 */ s16 field_0x2F6;
    /* 0x2F8 */ dCcD_Sph field_0x2F8;
    /* 0x424 */ dCcD_Stts field_0x424;
    /* 0x460 */ cXyz field_0x460;
    /* 0x46C */ int field_0x46C;
    /* 0x470 */ JntHit_c* field_0x470;
    /* 0x474 */ daDaiocta_c* field_0x474;
    /* 0x478 */ dPa_followEcallBack field_0x478;
    /* 0x48C */ cXyz field_0x48C;
    /* 0x48C */ csXyz field_0x498;
    /* 0x49E */ u8 field_0x49E[0x4A0 - 0x49E];
};  // Size: 0x4A0
STATIC_ASSERT(sizeof(daDaiocta_Eye_c) == 0x4A0);

class daDaiocta_Eye_HIO_c : public mDoHIO_entry_c {
public:
    daDaiocta_Eye_HIO_c();
public:
    s16 field_0x04;
    u8 field_0x06[0x08 - 0x06];
    f32 field_0x08;
    f32 field_0x0C;
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    s16 field_0x20;
    s16 field_0x22;
    s16 field_0x24;
    s16 field_0x26;
    s16 field_0x28;
    s16 field_0x2A;
    s16 field_0x2C;
    s16 field_0x2E;
    JntHit_HIO_c field_0x30;
};

#endif /* D_A_DAIOCTA_EYE_H */
