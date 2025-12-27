#ifndef D_A_IKARI_H
#define D_A_IKARI_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daObjIkariHIO_c : public mDoHIO_entry_c {
public:
    daObjIkariHIO_c() {
        unk[0] = 0;
        unk[1] = 0;
        mWindPowerScale = 0.1f;
    }
    virtual ~daObjIkariHIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ u8 unk[2];
    /* 0x08 */ f32 mWindPowerScale;
};

class daIkari_c : public fopAc_ac_c {
public:
    void setMtx();
    BOOL _createHeap();
    void getArg();
    bool _execute();
    bool _draw();
    cPhs_State _create();
    bool _delete();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ u8 mEnvType;
    /* 0x29D */ u8 mModelType;
    /* 0x29E */ u8 m29E[0x2A0 - 0x29E];
    /* 0x2A0 */ int mTimer;

    static const char M_arcname[6];
};

#endif /* D_A_IKARI_H */
