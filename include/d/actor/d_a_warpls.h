#ifndef D_A_WARPLS_H
#define D_A_WARPLS_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JParticle/JPAEmitter.h"


class daWarpls_c : public fopAc_ac_c {
public:
    bool _delete();
    int CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx(); // weak
    bool _execute();
    void checkOrder();
    void eventOrder();
    bool setStatus();
    bool demo();
    int check_warp_link();
    int check_warp_distance();
    void warp_eff_start();
    inline bool _draw();
    
    static const char* m_arcname[];
    static const u32 m_heapsize[];    
    static const s16 m_brkidx[];    
    static const s16 m_bdlidx[];  
    static const s16 m_bckidx[];       
    static const float m_warp_distance;

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A0 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2A4 */ JPABaseEmitter* mpEmitter;  
    /* 0x2A8 */ s32 mSwitchNo;        
    /* 0x2AC */ s32 mSceneNo;      
    /* 0x2B0 */ s32 m2B0;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ s8 m2B7;
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ s16 m2BA;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE;
};  // Size: 0x2C0


namespace daWarpls_prm {
inline u8 getEvId(daWarpls_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 0x10) & 0xFF;
}
inline u8 getSceneNo(daWarpls_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 8) & 0xFF;
}
inline u8 getSwitchNo(daWarpls_c* i_this) {
    return fopAcM_GetParam(i_this) & 0xFF;
}
static inline u8 getType(daWarpls_c* i_this) {
    return (fopAcM_GetParam(i_this) >> 0x1C) & 0xFF;
}
}
#endif /* D_A_WARPLS_H */
