#ifndef D_A_OBJ_SWHEAVY_H
#define D_A_OBJ_SWHEAVY_H

#include "d/d_a_obj.h"
#include "d/d_bg_w.h"

namespace daObjSwheavy {
    class Act_c : public fopAc_ac_c {
    public:
        struct Attr_c {
            u8 m00[0x4];
            int m04;
            float m08;
            float m0C;
            float m10;
            short m14;
            short m16;
            short m18;
            u8 m1A[0x1C - 0x1A];
        };
        const Attr_c& attr() const { return M_attr[mType]; }

        enum Prm_e {
            PRM_TYPE_W = 0x3,
            PRM_TYPE_S = 0x18,

            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x8,
        };

        BOOL is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void off_switch() const { fopAcM_offSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void on_switch() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        void rev_switch() const { fopAcM_revSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void calc_top_pos();
        void top_bg_aim_req(float, short);
        void set_push_flag();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        bool _execute();
        bool _draw();

        static const char M_arcname[6];
        static const Attr_c M_attr[5];

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel1;
        /* 0x29c */ J3DModel* mpModel2;
        /* 0x2A0 */ dBgW* mpBgW1;
        /* 0x2A4 */ dBgW* mpBgW2;
        /* 0x2A8 */ Mtx m2A8;
        /* 0x2D8 */ Mtx m2D8;
        /* 0x308 */ int mType;
        /* 0x30C */ int mMode;
        /* 0x310 */ bool m310;
        /* 0x311 */ u8 m311;
        /* 0x312 */ short m312;
        /* 0x314 */ bool m314;
        /* 0x315 */ bool m315;
        /* 0x316 */ u8 m316;
        /* 0x318 */ short m318;
        /* 0x31A */ bool m31A;
        /* 0x31B */ u8 m31B;
        /* 0x31C */ float m31C;
        /* 0x320 */ float m320;
        /* 0x324 */ float m324;
        /* 0x328 */ float m328;
        /* 0x32C */ float m32C;
        short m330;
        u8 m332[0x2];
        /* 0x334 */ float m334;
        /* 0x338 */ float m338;
        /* 0x33C */ float m33C;
    }; /* Size: 0x340 */

    // STATIC_ASSERT(sizeof(Act_c) == 0x340);
};

#endif /* D_A_OBJ_SWHEAVY_H */
