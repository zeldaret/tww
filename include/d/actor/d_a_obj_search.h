#ifndef D_A_OBJ_SEARCH_H
#define D_A_OBJ_SEARCH_H

#include "SSystem/SComponent/c_angle.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
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

        struct Attr_c {
            /* 0x00 */ u8 mSkipExecute;
            /* 0x01 */ u8 mSkipDraw;
            /* 0x02 */ s16 m02;
            /* 0x04 */ f32 m04;
            /* 0x08 */ s16 m08;
            /* 0x0A */ u8 m0A[0x10 - 0x0A];
            /* 0x10 */ f32 m10;
            /* 0x14 */ f32 m14;
            /* 0x18 */ f32 m18;
            /* 0x1C */ f32 m1C;
            /* 0x20 */ f32 m20;
            /* 0x24 */ u8 m24;
            /* 0x25 */ u8 m25[0x28 - 0x25];
            /* 0x28 */ f32 mCpsR;
            /* 0x2C */ u8 m2C[0x38 - 0x2C];
            /* 0x38 */ u8 m38;
            /* 0x39 */ u8 m39;
            /* 0x3A */ u8 m3A[2];
            /* 0x3C */ s16 m3C;
            /* 0x3E */ u8 m3E;
            /* 0x3F */ u8 m3F[0x42 - 0x3F];
            /* 0x42 */ u8 m42;
            /* 0x43 */ u8 m43;
            /* 0x44 */ u8 m44;
            /* 0x45 */ u8 m45;
            /* 0x46 */ u8 m46;
            /* 0x47 */ u8 m47;
            /* 0x48 */ u8 m48[0x4C - 0x48];
            /* 0x4C */ f32 m4C;
            /* 0x50 */ s16 m50;
            /* 0x52 */ u8 m52[0x54 - 0x52];
            /* 0x54 */ f32 m54;
            /* 0x58 */ f32 m58;
            /* 0x5C */ s16 m5C;
            /* 0x5E */ s16 m5E;
        };

        static bool getFindFlag() { return m_find_flag == true; }
        static void setFindFlag(bool flag) { m_find_flag = flag; }
        
        static bool m_find_flag;
        static const Attr_c m_attr;

        
        bool isSecond() { return field_0x860 != false; }
        void modeProcInit(int newMode) { modeProc(PROC_INIT_e, newMode); }
        void setBkControl(bool control) { mBkControl = control; }
        void setChildId(fpc_ProcID id) { mChildId = id; }
        
        BOOL _createHeap();
        bool searchCreateHeap();
        bool beamCreateHeap(int);
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
        const Attr_c& attr() const;
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
        bool player_check();
        bool set_path_info();
        bool is_path_info();
        bool _draw();
        bool _delete();
        BOOL _isdelete();

        static const char m_arc_name[];
    
    public:
        /* 0x290 */ s32 mMode;
        /* 0x294 */ Bgc_c field_0x294;
        /* 0x30C */ dCcD_Cps field_0x30C[2];
        /* 0x57C */ dCcD_Stts field_0x57C[2];
        /* 0x5F4 */ J3DModel* field_0x5F4;
        /* 0x5F8 */ J3DModel* field_0x5F8[2];
        /* 0x600 */ cXyz field_0x600;
        /* 0x60C */ cXyz field_0x60C[2];
        /* 0x624 */ cXyz field_0x624[2];
        /* 0x63C */ cXyz field_0x63C[2];
        /* 0x654 */ f32 field_0x654;
        /* 0x658 */ f32 field_0x658;
        /* 0x65C */ f32 field_0x65C;
        /* 0x660 */ f32 field_0x660;
        /* 0x664 */ bool mBkControl;
        /* 0x665 */ u8 field_0x665[0x668 - 0x665];
        /* 0x668 */ dBgW* field_0x668[2];
        /* 0x670 */ dBgW* mpBgW;
        /* 0x674 */ Mtx field_0x674[2];
        /* 0x6D4 */ Mtx field_0x6D4;
        /* 0x704 */ u8 field_0x704[0x706 - 0x704];
        /* 0x706 */ csXyz field_0x706[2];
        /* 0x712 */ u8 field_0x712[0x71C - 0x712];
        /* 0x71C */ Mtx field_0x71C[2];
        /* 0x77C */ bool field_0x77C[2];
        /* 0x77E */ s16 field_0x77E;
        /* 0x780 */ LIGHT_INFLUENCE field_0x780;
        /* 0x7A0 */ int field_0x7A0;
        /* 0x7A4 */ int field_0x7A4;
        /* 0x7A8 */ s16 field_0x7A8;
        /* 0x7AA */ s16 field_0x7AA;
        /* 0x7AC */ s16 field_0x7AC;
        /* 0x7AE */ s16 field_0x7AE;
        /* 0x7B0 */ s16 field_0x7B0;
        /* 0x7B2 */ s16 field_0x7B2;
        /* 0x7B4 */ s16 field_0x7B4;
        /* 0x7B6 */ bool field_0x7B6;
        /* 0x7B7 */ bool field_0x7B7;
        /* 0x7B8 */ bool field_0x7B8;
        /* 0x7B9 */ u8 field_0x7B9[0x7BC - 0x7B9];
        /* 0x7BC */ dLib_circle_path_c field_0x7BC;
        /* 0x7E0 */ s16 field_0x7E0;
        /* 0x7E2 */ u8 field_0x7E2;
        /* 0x7E3 */ u8 field_0x7E3[0x7F4 - 0x7E3];
        /* 0x7F4 */ cXyz field_0x7F4;
        /* 0x800 */ csXyz field_0x800;
        /* 0x806 */ u8 field_0x806[0x808 - 0x806];
        /* 0x808 */ dPa_smokeEcallBack field_0x808;
        /* 0x828 */ int field_0x828;
        /* 0x82C */ u8 field_0x82C;
        /* 0x82D */ u8 field_0x82D;
        /* 0x82E */ u8 field_0x82E[0x830 - 0x82E];
        /* 0x830 */ int field_0x830;
        /* 0x834 */ bool field_0x834;
        /* 0x835 */ u8 field_0x835;
        /* 0x836 */ u8 field_0x836;
        /* 0x837 */ u8 field_0x837;
        /* 0x838 */ cXyz field_0x838;
        /* 0x844 */ s8 field_0x844;
        /* 0x845 */ u8 field_0x845[0x848 - 0x845];
        /* 0x848 */ dPath* field_0x848;
#if VERSION == VERSION_DEMO
        u8 pad84C;
#endif
        /* 0x84C */ fpc_ProcID mChildId;
        /* 0x850 */ int field_0x850;
        /* 0x854 */ request_of_phase_process_class mPhs;
        /* 0x85C */ int field_0x85C;
        /* 0x860 */ bool field_0x860;
        /* 0x861 */ u8 field_0x861[0x864 - 0x861];
        /* 0x864 */ dBgS_ObjLinChk field_0x864;
        /* 0x8D0 */ u8 field_0x8D0;
        /* 0x8D1 */ u8 field_0x8D1[0x8D4 - 0x8D1];
        /* 0x8D4 */ cXyz field_0x8D4;
        /* 0x8E0 */ s16 field_0x8E0;
        /* 0x8E2 */ u8 field_0x8E2[0x8E4 - 0x8E2];
        /* 0x8E4 */ f32 field_0x8E4;
        /* 0x8E8 */ f32 field_0x8E8;
        /* 0x8EC */ s16 field_0x8EC;
        /* 0x8EE */ u8 field_0x8EE;
        /* 0x8EF */ int field_0x8EF;
        /* 0x8F3 */ cXyz field_0x8F3;
        /* 0x8FF */ int field_0x8FF;
        /* 0x903 */ int field_0x903;
        /* 0x907 */ u8 field_0x907[0x908 - 0x907];
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
