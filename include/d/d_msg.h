
#ifndef D_MSG_H
#define D_MSG_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"

class msg_class;
class sub_msg_class;

class sub_msg_class : public msg_class {
public:
    /* 0x00FC */ JKRExpHeap* mpHeap;
    /* 0x0100 */ mesg_entry mMesgEntry;
    /* 0x0118 */ mesg_header* head_p;
    /* 0x011C */ fopMsgM_pane_class m011C[4];
    /* 0x01FC */ fopMsgM_pane_class m01FC;
    /* 0x0234 */ fopMsgM_pane_class m0234;
    /* 0x026C */ fopMsgM_pane_class m026C[10];
    /* 0x049C */ fopMsgM_pane_class m049C;
    /* 0x04D4 */ fopMsgM_pane_class mPane_Arrow;
    /* 0x050C */ fopMsgM_pane_class m050C;
    /* 0x0544 */ fopMsgM_pane_class m0544[4];
    /* 0x0624 */ fopMsgM_pane_class m0624[10];
    /* 0x0854 */ u8 m854[0x8C4 - 0x854];
    /* 0x08C4 */ fopMsgM_pane_class m08C4[6];
    /* 0x0A14 */ fopMsgM_pane_class m0A14[6];
    /* 0x0B64 */ fopMsgM_pane_class m0B64[6];
    /* 0x0CB4 */ fopMsgM_pane_class m0CB4[6];
    /* 0x0E04 */ fopMsgM_msgDataProc_c mMsgDataProc;
    /* 0x10A4 */ fopMsgM_msgGet_c mMsgGet;
    /* 0x10B4 */ JPABaseEmitter* m10B4[2];
    /* 0x10BC */ JUtility::TColor m10BC;
    /* 0x10C0 */ JUtility::TColor m10C0;
    /* 0x10C4 */ JUtility::TColor m10C4;
    /* 0x10C8 */ JUtility::TColor m10C8;
    /* 0x10CC */ ResTIMG* buffer_p;
    /* 0x10D0 */ f32 m10D0;
    /* 0x10D4 */ f32 m10D4;
    /* 0x10D8 */ int m10D8;
    /* 0x10DC */ int m10DC;
    /* 0x10E0 */ cXyz m10E0;
    /* 0x10EC */ f32 m10EC;
    /* 0x10F0 */ f32 m10F0;
    /* 0x10F4 */ u8 m10F4[0x10F8 - 0x10F4];
    /* 0x10F8 */ int m10F8;
    /* 0x10FC */ int m10FC;
    /* 0x1100 */ int m1100;
    /* 0x1104 */ int m1104;
    /* 0x1108 */ int m1108;
    /* 0x110C */ int m110C;
    /* 0x1110 */ int m1110;
    /* 0x1114 */ int m1114;
    /* 0x1118 */ int mMesgCameraTagInfo;
    /* 0x111C */ char* mpMesgStr;
    /* 0x1120 */ char* output_text;
    /* 0x1124 */ char* output_rub;
    /* 0x1128 */ char* output_textSdw;
    /* 0x112C */ char* output_rubSdw;
    /* 0x1130 */ char* select_text;
    /* 0x1134 */ char* select_rub;
    /* 0x1138 */ char* select_textSdw;
    /* 0x113C */ char* select_rubSdw;
    /* 0x1140 */ int mMsgID;
    /* 0x1144 */ int m1144;
    /* 0x1148 */ u8 m1148[0x1164 - 0x1148];
    /* 0x1164 */ int m1164;
    /* 0x1168 */ u8 m1168;
    /* 0x1169 */ u8 m1169;
    /* 0x116A */ u8 m116A;
    /* 0x116B */ u8 m116B;
};

class dDlst_2DMSG_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMSG_c();
    virtual void draw();
    void outFontDraw();

    sub_msg_class* field_0x4;
};

class dDlst_2Dtact_c : public dDlst_base_c {
public:
    virtual ~dDlst_2Dtact_c();
    virtual void draw();

    u8 field_0x4[4];
    void* field_0x8;
};

extern JKRHeap* dMsg_getAgbWorkArea();

#endif /* D_MSG_H */
