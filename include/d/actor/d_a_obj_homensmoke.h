#ifndef D_A_OBJ_HOMENSMOKE_H
#define D_A_OBJ_HOMENSMOKE_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"

namespace daObjHomensmoke {
    class Act_c : public fopAc_ac_c {
    public:
        int param_get_arg0() const { return daObj::PrmAbstract(this, 1, 0) & 0x1; }
        int param_get_axis() const { return daObj::PrmAbstract(this, 1, 1) & 0x1; }
    
        virtual ~Act_c() {}
        void set_mtx();
        cPhs_State _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ /* vtable */
        /* 0x294 */ u8 m294[0x29C - 0x294];
        /* 0x29C */ Mtx mMtx;
        /* 0x2CC */ int mType;
#if VERSION == VERSION_DEMO
        /* 0x2D0 */ JPABaseEmitter* m2D0;
#endif
        /* 0x2D0 */ dPa_smokeEcallBack mSmokeCb;
        /* 0x2F0 */ BOOL mbInitialized;
        /* 0x2F4 */ cXyz mSmokePos;
    };
};

#endif /* D_A_OBJ_HOMENSMOKE_H */
