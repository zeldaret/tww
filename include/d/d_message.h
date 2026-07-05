#ifndef D_MESSAGE_H
#define D_MESSAGE_H

#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"

class sub_msg2_class;

class dDlst_2DMSG2_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMSG2_c() {}

    void setActorP(sub_msg2_class* i_actorp) { actorP = i_actorp; }
    
    void draw();
    void outFontDraw();

    /* 0x4 */ sub_msg2_class* actorP;
};

class dDlst_2DCopy_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DCopy_c() {}
    void draw();

    /* 0x4 */ u8 field_0x4[0x8 - 0x4];
    /* 0x8 */ void* copyTex;
};

struct sub_msg2_class {
    /* 0x000 */ msg_class msg;
    /* 0x0FC */ u8 field_0x0FC[0x100 - 0x0FC];
    /* 0x100 */ JKRExpHeap* Heap;
    /* 0x104 */ JMSMesgEntry_c mesgEntry;
    /* 0x11C */ fopMsgM_msgDataProc_c msgDataProc[3];
    /* 0x8FC */ fopMsgM_msgGet_c msgGet;
    /* 0x90C */ mesg_header* head_p;
    /* 0x910 */ fopMsgM_pane_class text_pane[3];
    /* 0x9B8 */ fopMsgM_pane_class textSdw_pane[3];
    /* 0xA60 */ fopMsgM_pane_class ruby_pane[3];
    /* 0xB08 */ fopMsgM_pane_class rubySdw_pane[3];
    /* 0xBB0 */ fopMsgM_pane_class field_0xbb0;
    /* 0xBE8 */ fopMsgM_pane_class field_0xbe8;
    /* 0xC20 */ fopMsgM_pane_class field_0xc20;
    /* 0xC58 */ fopMsgM_pane_class field_0xc58;
    /* 0xC90 */ fopMsgM_pane_class field_0xc90;
    /* 0xCC8 */ fopMsgM_pane_class field_0xcc8;
    /* 0xD00 */ fopMsgM_pane_class field_0xd00[3];
    /* 0xDA8 */ fopMsgM_pane_class field_0xda8[3];
    /* 0xE50 */ JUTFont* mx;
    /* 0xE54 */ JUTFont* rx;
    /* 0xE58 */ ResTIMG* Tex[2];
    /* 0xE60 */ char* message;
    /* 0xE64 */ char* output_text[3];
    /* 0xE70 */ char* output_ruby[3];
    /* 0xE7C */ char* output_textSdw[3];
    /* 0xE88 */ char* output_rubySdw[3];
    /* 0xE94 */ f32 field_0xe94;
    /* 0xE98 */ int field_0xe98;
    /* 0xE9C */ u8 field_0xe9c;
    /* 0xE9D */ u8 field_0xe9d;
    /* 0xE9E */ u8 field_0xe9e;
    /* 0xEA0 */ u32 mesgNumber;
    /* 0xEA4 */ u16 colorNo;
    /* 0xEA8 */ f32 field_0xea8;
    /* 0xEAC */ f32 field_0xeac;
    /* 0xEB0 */ int field_0xeb0;
    /* 0xEB4 */ int field_0xeb4;
    /* 0xEB8 */ int field_0xeb8;
    /* 0xEBC */ int field_0xebc;
    /* 0xEC0 */ u8 field_0xec0;
    /* 0xEC4 */ int field_0xec4;
    /* 0xEC8 */ int field_0xec8;
    /* 0xECC */ int field_0xecc[3];
    /* 0xED8 */ u8 field_0xED8[0xEDD - 0xED8];
    /* 0xEDD */ u8 field_0xedd;
    /* 0xEDE */ u8 field_0xede;
    /* 0xEDF */ u8 field_0xedf[4][3];
};

#endif /* D_MESSAGE_H */
