#ifndef D_A_OBJ_SEARCH_H
#define D_A_OBJ_SEARCH_H

#include "f_op/f_op_actor.h"

class J3DNode;

namespace daObj_Search {
    class Act_c : public fopAc_ac_c {
    public:
        enum Proc_e {
            
        };
    
        void getFindFlag() {}
        void isSecond() {}
        void modeProcInit(int) {}
        void setBkControl(bool) {}
        void setChildId(unsigned int) {}
        void setFindFlag(bool) {}
    
        void _createHeap();
        void searchCreateHeap();
        void beamCreateHeap(int);
        void _nodeControl(J3DNode*, J3DModel*);
        void modeSearchRndInit();
        void modeSearchRnd();
        void modeSearchPathInit();
        void modeSearchPath();
        void modeStopInit();
        void modeStop();
        void modeToSearchInit();
        void modeToSearch();
        void modeToStopInit();
        void modeToStop();
        void modeFindInit();
        void modeFind();
        void modeFind2ndInit();
        void modeFind2nd();
        void modeSearchBdkInit();
        void modeSearchBdk();
        void modeProc(Proc_e, int);
        void attr() const;
        void SetArgData();
        void CreateInit();
        s32 _create();
        void smoke_set(float, int);
        BOOL _execute();
        void check_bk_control();
        void set_mtx_base();
        void set_mtx_light_A();
        void set_mtx_light_B();
        void set_moveBG_mtx_base();
        void set_moveBG_mtx_light_A();
        void set_moveBG_mtx_light_B();
        void bg_check();
        void player_check();
        void set_path_info();
        void is_path_info();
        BOOL _draw();
        BOOL _delete();
        BOOL _isdelete();
    
    public:
        /* Place member variables here */
    };

    class Bgc_c {
    public:
        void wall_pos(const daObj_Search::Act_c*, cXyz*, cXyz*, bool*, float*);
    };
};

#endif /* D_A_OBJ_SEARCH_H */
