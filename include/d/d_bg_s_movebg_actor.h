#ifndef D_BG_S_MOVEBG_ACTOR_H
#define D_BG_S_MOVEBG_ACTOR_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

class dBgW;
typedef void (*MoveBGActor_SetFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_Typical(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_RotY(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_TypicalRotY(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
void dBgS_MoveBGProc_Trans(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);

class dBgS_MoveBgActor : public fopAc_ac_c {
public:
    /* 0x290 */ dBgW* mpBgW;
    /* 0x294 */ Mtx mBgMtx;
    /* 0x2C4 */ /* vtable */

    dBgS_MoveBgActor();
    BOOL MoveBGCreateHeap();
    cPhs_State MoveBGCreate(char const* resName, int resIndex, MoveBGActor_SetFunc callback, u32 resSize);
    BOOL MoveBGDelete();
    BOOL MoveBGExecute();

    BOOL MoveBGDraw() { return Draw(); }
    BOOL MoveBGIsDelete() { return IsDelete(); }

    virtual BOOL CreateHeap() { return TRUE; }
    virtual BOOL Create() { return TRUE; }
    virtual BOOL Execute(Mtx**) { return TRUE; }
    virtual BOOL Draw() { return TRUE; }
    virtual BOOL Delete() { return TRUE; }
    virtual BOOL IsDelete() { return TRUE; }
    virtual BOOL ToFore() { return TRUE; }
    virtual BOOL ToBack() { return TRUE; }

    static const char* m_name;
    static int m_dzb_id;
    static MoveBGActor_SetFunc m_set_func;
};  // Size: 0x2C8

STATIC_ASSERT(sizeof(dBgS_MoveBgActor) == 0x2C8);

#endif /* D_BG_S_MOVEBG_ACTOR_H */
