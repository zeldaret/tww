#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"

namespace daObjBuoyflag {
    enum Type_e {
        
    };
    enum Texture_e {
        
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        void setup(MtxP mtx) {
            cMtx_copy(mtx, m1090);
        }
        static s32 make_norm(unsigned int parentPId, cXyz* pos, int roomNo, csXyz* angle) {
            u32 params = prm_make(static_cast<Type_e>(0), static_cast<Texture_e>(0), false); // TODO: placeholder
            return fopAcM_createChild(
                PROC_Obj_Buoyflag, parentPId,
                params, pos,
                roomNo, angle, NULL, -1, NULL
            );
        }
        static u32 prm_make(daObjBuoyflag::Type_e, daObjBuoyflag::Texture_e, bool) {
            // TODO: placeholder function
            return 0;
        }
    public:
        /* 0x0290 */ u8 temp[0x1090 - 0x290];
        /* 0x1090 */ Mtx m1090;
    };
};

#endif /* D_A_OBJ_BUOYFLAG_H */
