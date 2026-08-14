#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DModel;
class dChain_packet_c;
struct dBgW;
struct dPath;

class daBalancelift_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void calc_quat();
    void set_mtx();
    void calc_weight();
    BOOL CreateHeap();
    int CreateInit();

    static const char M_arcname[];

public:
    /* 0x290 */ cXyz field_0x290;
    /* 0x29C */ cXyz field_0x29C;
    /* 0x2A8 */ cXyz field_0x2A8;
    /* 0x2B4 */ cXyz field_0x2B4;
    /* 0x2C0 */ cXyz field_0x2C0;
    /* 0x2CC */ Quaternion field_0x2CC;
    /* 0x2DC */ Quaternion field_0x2DC;
    /* 0x2EC */ cXyz field_0x2EC;
    /* 0x2F8 */ cXyz field_0x2F8;
    /* 0x304 */ cXyz field_0x304;
    /* 0x310 */ f32 field_0x310;
    /* 0x314 */ s16 field_0x314;
    /* 0x316 */ u8 field_0x316[0x318 - 0x316];
    /* 0x318 */ s16* field_0x318;
    /* 0x31C */ s16 field_0x31C;
    /* 0x31E */ s16 field_0x31E;
    /* 0x320 */ s16* field_0x320;
    /* 0x324 */ request_of_phase_process_class mPhase;
    /* 0x32C */ J3DModel* M_mdl;
    /* 0x330 */ Mtx field_0x330;
    /* 0x360 */ dPath* field_0x360;
    /* 0x364 */ dBgW* pm_bgw;
    /* 0x368 */ f32 field_0x368;
    /* 0x36C */ cXyz field_0x36C[4];
    /* 0x39C */ mDoExt_3DlineMat0_c field_0x39C;
    /* 0x3B8 */ dChain_packet_c* m_chain;
    /* 0x3BC */ dCcD_Stts mStts;
    /* 0x3F8 */ dCcD_Cyl mCyl;
};

STATIC_ASSERT(sizeof(daBalancelift_c) == 0x528);

class daBalancelift_HIO_c : public JORReflexible {
public:
    daBalancelift_HIO_c();
    virtual ~daBalancelift_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05[3];
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};

#endif /* D_A_OBJ_BALANCELIFT_H */
