#ifndef D_A_OBJ_PIRATESHIP_H
#define D_A_OBJ_PIRATESHIP_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"

namespace daObjPirateship {
    f32 getShipOffsetY(s16*, s16*, f32);
    
    class Act_c : public dBgS_MoveBgActor {
    public:
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void getKajiID() {}
    
        void set_mtx();
        void pirateCreate(int*);
        void partsCreate();
        void sound_proc();
        virtual BOOL CreateHeap();
        void CreateWave();
        void SetWave();
        void DeleteWave();
        virtual BOOL Create();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        virtual BOOL Delete();
        void demo_move();
    
    public:
        /* 0x2C8 */ u8 m2C8[0x2CC - 0x2C8];
        /* 0x2CC */ u8 m2CC;
        /* 0x2CD */ u8 m2CD[0x2CE - 0x2CD];
        /* 0x2CE */ u8 m2CE;
        /* 0x2CF */ u8 m2CF[0x2D0 - 0x2CF];
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ u8 m2D4[0x6D4 - 0x2D4];
    };

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_PIRATESHIP_H */
