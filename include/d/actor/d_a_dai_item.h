#ifndef D_A_DAI_ITEM_H
#define D_A_DAI_ITEM_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_acch.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cloth_packet.h"

class daStandItem_c : public fopAc_ac_c {
public:
    void getItemNo() const {}

    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void _execute();
    void itemProc();
    void actionFobj00();
    void actionFobj01();
    void actionFobj02();
    void actionFobj03();
    void actionFobj04();
    void actionFobj05();
    void actionFobj06();
    void actionFobj07();
    void actionFobj08();
    void actionFobj09();
    void actionFobj10();
    void actionFobj11();
    void animTest();
    void animTestForOneTime();
    void execAction();
    void mode_carry_init();
    void mode_carry();
    void mode_wait_init();
    void mode_wait();
    void mode_drop_init();
    void mode_drop();
    void _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhsDai;
    /* 0x298 */ request_of_phase_process_class mPhsCloth;
    /* 0x2A0 */ J3DModel* mpModel;
    /* 0x2A4 */ mDoExt_bckAnm* mpBckAnm;
    /* 0x2A8 */ u8 m2A8[0x310 - 0x2A8];
    /* 0x310 */ int m310;
    /* 0x314 */ u8 m314[0x414 - 0x314];
    /* 0x414 */ dBgS_Acch mAcch;
    /* 0x5D8 */ dBgS_AcchCir mAcchCir;
    /* 0x618 */ u8 mItemNo;
    /* 0x619 */ u8 mItemType;
    /* 0x61A */ u8 m61A[0x61C - 0x61A];
    /* 0x61C */ int mTimer;
    /* 0x620 */ int mMode;
    /* 0x624 */ u8 m624;
    /* 0x625 */ u8 m625[0x628 - 0x625];
    /* 0x628 */ s16 mBckPlayTimer;
    /* 0x62A */ s16 mBckStopTimer;
    /* 0x62C */ f32 mBckSpeed;
    /* 0x630 */ Mtx m630;
    /* 0x660 */ Mtx m660;
    /* 0x690 */ JPABaseEmitter* m690;
    /* 0x694 */ JPABaseEmitter* m694;
    /* 0x698 */ JPABaseEmitter* m698;
    /* 0x69C */ dCloth_packet_c* mpCloth;
    /* 0x6A0 */ u8 mClothType;
    /* 0x6A1 */ u8 m6A1[0x6A2 - 0x6A1];
    /* 0x6A2 */ s16 m6A2;
    /* 0x6A4 */ cXyz m6A4;
    /* 0x6B0 */ u8 mbBckDidPlay;
    /* 0x6B1 */ u8 m6B1;
    /* 0x6B2 */ s16 m6B2;
    /* 0x6B4 */ s16 m6B4;
    /* 0x6B6 */ u8 m6B6[0x6BC - 0x6B6];
    /* 0x6BC */ f32 m6BC;
    /* 0x6C0 */ u8 m6C0[0x6C4 - 0x6C0];
    /* 0x6C4 */ f32 m6C4;
};

#endif /* D_A_DAI_ITEM_H */
