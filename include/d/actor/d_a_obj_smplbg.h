#ifndef D_A_OBJ_SMPLBG_H
#define D_A_OBJ_SMPLBG_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"

namespace daObjSmplbg {
    class Act_c : public dBgS_MoveBgActor {
    public:
    
        // idk what to name this
        enum Prm_e {
            PRM_1_W = 8,
            PRM_1_S = 0,
        };

        static Mtx M_tmp_mtx;
        struct Attr_c {
            /* 0x00 */ u32 field_0x00;
            /* 0x04 */ const char* resName;
            /* 0x08 */ short field_0x08;             
            /* 0x0A */ short field_0x0A;
            /* 0x0C */ void (*moveBGProc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
            /* 0x10 */ u32 field_0x10;
            /* 0x14 */ short field_0x14;
            /* 0x16 */ short field_0x16;
            /* 0x18 */ short field_0x18;
            /* 0x1A */ short field_0x1A;
            /* 0x1C */ short field_0x1C;
            /* 0x1E */ short field_0x1E;             
            /* 0x20 */ float field_0x20;
        };
        
        static const Attr_c M_attr[1];
        inline const Attr_c& attr() const { return M_attr[mType]; }

        void isStop() {}
        void offStop() {}
        void onStop() {}
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_1_W , PRM_1_S);}
        
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void exec_qtkhd();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* 0x290 */ u8 field_0x290[0x2C8 - 0x290];
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ int mType;
        /* 0x2D8 */ u8 field_0x2D8[0x2DC - 0x2D8];
};  // Size: 0x2DC
};

#endif /* D_A_OBJ_SMPLBG_H */
