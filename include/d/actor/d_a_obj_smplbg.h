#ifndef D_A_OBJ_SMPLBG_H
#define D_A_OBJ_SMPLBG_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"

namespace daObjSmplbg {
    class Act_c : public dBgS_MoveBgActor {
    public:
    
        enum Prm_e {
            PRM_TYPE_W = 8,
            PRM_TYPE_S = 0,
        };

        static Mtx M_tmp_mtx;
        struct Attr_c {
            /* 0x00 */ u32 mHeapSize;
            /* 0x04 */ const char* mResName;
            /* 0x08 */ s16 mBDLFileIndex;
            /* 0x0A */ s16 mDZBFileIndex;
            /* 0x0C */ MoveBGActor_SetFunc mMoveBGProc;
            /* 0x10 */ u32 mFlags;
            /* 0x14 */ s16 mCullMinX;
            /* 0x16 */ s16 mCullMinY;
            /* 0x18 */ s16 mCullMinZ;
            /* 0x1A */ s16 mCullMaxX;
            /* 0x1C */ s16 mCullMaxY;
            /* 0x1E */ s16 mCullMaxZ;
            /* 0x20 */ f32 mEyeOffset;
        };
        
        static const Attr_c M_attr[];
        inline const Attr_c& attr() const { return M_attr[mType]; }

        void isStop() {}
        void offStop() {}
        void onStop() {}
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W , PRM_TYPE_S);}
        
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
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ int mType;
        /* 0x2D8 */ u8 field_0x2D8;
        /* 0x2D9 */ u8 field_0x2D9[0x2DC - 0x2D9];
    };  // Size: 0x2DC
};

#endif /* D_A_OBJ_SMPLBG_H */
