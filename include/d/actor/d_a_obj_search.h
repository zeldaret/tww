#ifndef D_A_OBJ_SEARCH_H
#define D_A_OBJ_SEARCH_H

#include "SSystem/SComponent/c_angle.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_path.h"
#include "f_op/f_op_actor.h"

class J3DNode;

namespace daObj_Search {

    class Act_c;

    class Bgc_c {
    public:
        Bgc_c();
        void wall_pos(const daObj_Search::Act_c*, cXyz*, cXyz*, bool*, float*);

        /* 0x00 */ dBgS_LinChk field_0x00;
        /* 0x6c */ cXyz field_0x6c; 
    };

    class Act_c : public fopAc_ac_c {
    public:
        enum Proc_e {
            PROC_INIT_e = 0,
            PROC_EXEC_e = 1
        };

        enum Mode_e {
            MODE_SEARCH_RND_e = 0,
            MODE_SEARCH_PATH_e = 1,
            MODE_STOP_e = 2,
            MODE_TO_SEARCH_e = 3,
            MODE_TO_STOP_e = 4,
            MODE_FIND_e = 5,
            MODE_FIND_2ND_e = 6,
            MODE_SEARCH_BDK_e = 7,
        };

        struct ModeEntry {
            typedef void (Act_c::*ModeProcFunc)(void);
            ModeProcFunc mInitFunc;
            ModeProcFunc mUpdFunc;
            const char* name;
        };

        static bool getFindFlag() { return m_find_flag == true; }
        static void setFindFlag(bool flag) { m_find_flag = flag; }
        
        static bool m_find_flag;
        
        void isSecond() {}
        void modeProcInit(int) {}
        void setBkControl(bool control) { mBkControl = control; }
        void setChildId(fpc_ProcID id) { mChildId = id; }
        
        BOOL _createHeap();
        bool searchCreateHeap();
        bool beamCreateHeap(int);
        static void _nodeControl(J3DNode*, J3DModel*);
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
        cPhs_State _create();
        void smoke_set(float, int);
        bool _execute();
        void check_bk_control();
        void set_mtx_base();
        void set_mtx_light_A();
        void set_mtx_light_B();
        void set_moveBG_mtx_base();
        void set_moveBG_mtx_light_A();
        void set_moveBG_mtx_light_B();
        void bg_check();
        void player_check();
        bool set_path_info();
        bool is_path_info();
        bool _draw();
        bool _delete();
        BOOL _isdelete();

        static const char M_arcname[];
    
    public:
        /* 0x290 */ s32 mMode;
        /* 0x294 */ u8 field_0x294[0x30C - 0x294];
        /* 0x30C */ dCcD_Cps field_0x30C[2];
        /* 0x57C */ dCcD_Stts field_0x57C[2];
        /* 0x5F4 */ J3DModel* field_0x5F4;
        /* 0x5F8 */ J3DModel* field_0x5F8;
        /* 0x5FC */ J3DModel* field_0x5FC;
        /* 0x600 */ cXyz field_0x600;
        /* 0x60C */ cXyz field_0x60C;
        /* 0x618 */ Vec field_0x618;
        /* 0x624 */ cXyz field_0x624;
        /* 0x630 */ cXyz field_0x630;
        /* 0x63C */ cXyz field_0x63C;
        /* 0x648 */ cXyz field_0x648;
        /* 0x654 */ u8 field_0x654[0x664 - 0x654];
        /* 0x664 */ bool mBkControl;
        /* 0x665 */ u8 field_0x665[0x668 - 0x665];
        /* 0x668 */ dBgW* field_0x668;
        /* 0x66C */ dBgW* field_0x66C;
        /* 0x670 */ dBgW* mpBgW;
        /* 0x674 */ u8 field_0x674[0x704 - 0x674];
        /* 0x704 */ csXyz field_0x704[2];
        /* 0x710 */ u8 field_0x710[0x77E - 0x710];
        /* 0x77E */ s16 field_0x77E;
        /* 0x780 */ LIGHT_INFLUENCE field_0x780;
        /* 0x7A0 */ u8 field_0x7A0[0x7B6 - 0x7A0];
        /* 0x7B6 */ bool field_0x7B6;
        /* 0x7B7 */ bool field_0x7B7;
        /* 0x7B8 */ bool field_0x7B8;
        /* 0x7B9 */ u8 field_0x7B9[0x7E2 - 0x7B9];
        /* 0x7E2 */ u8 field_0x7E2;
        /* 0x7E3 */ u8 field_0x7E3[0x808 - 0x7E3];
        /* 0x808 */ dPa_smokeEcallBack field_0x808;
        /* 0x828 */ u8 field_0x828[0x82C - 0x828];
        /* 0x82C */ u8 field_0x82C;
        /* 0x82D */ u8 field_0x82D;
        /* 0x82E */ u8 field_0x82E[0x830 - 0x82E];
        /* 0x830 */ int field_0x830;
        /* 0x834 */ bool field_0x834;
        /* 0x835 */ u8 field_0x835[0x837 - 0x835];
        /* 0x837 */ u8 field_0x837;
        /* 0x838 */ cXyz field_0x838;
        /* 0x844 */ u8 field_0x844[0x848 - 0x844];
        /* 0x848 */ dPath* field_0x848;
#if VERSION == VERSION_DEMO
                    u8 pad84C;
#endif
        /* 0x84C */ fpc_ProcID mChildId;
        /* 0x850 */ u8 field_0x850[0x854 - 0x850];
        /* 0x854 */ request_of_phase_process_class mPhs;
        /* 0x85C */ int field_0x85C;
        /* 0x860 */ bool field_0x860;
        /* 0x861 */ u8 field_0x861[0x864 - 0x861];
        /* 0x864 */ dBgS_LinChk field_0x864;
        /* 0x8D0 */ u8 field_0x8D0;
        /* 0x8D1 */ u8 field_0x8D1[0x908 - 0x8D1];
    };

    namespace Mthd {
        cPhs_State Create(void* impl);
        bool Delete(void* impl);
        bool Execute(void* impl);
        bool Draw(void* impl);
        BOOL IsDelete(void* impl);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_SEARCH_H */
