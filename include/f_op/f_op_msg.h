#ifndef F_OP_F_OP_MSG_H
#define F_OP_F_OP_MSG_H

#include "SSystem/SComponent/c_xyz.h"
#include "f_pc/f_pc_leaf.h"

class fopAc_ac_c;

enum fopMsg_MessageStatus_e {
    fopMsgStts_MSG_PREPARING_e = 0x01,
    fopMsgStts_BOX_OPENING_e = 0x02,
    fopMsgStts_MSG_TYPING_e = 0x06,
    fopMsgStts_MSG_DISPLAYED_e = 0x0E,
    fopMsgStts_MSG_CONTINUES_e = 0x0F,
    fopMsgStts_MSG_ENDS_e = 0x10,
    fopMsgStts_BOX_CLOSING_e = 0x11,
    fopMsgStts_BOX_CLOSED_e = 0x12,
    fopMsgStts_MSG_DESTROYED_e = 0x13,
    fopMsgStts_UNK15_e = 0x15,
};

struct msg_method_class {
    /* 0x00 */ leafdraw_method_class base;
};

class msg_class : public leafdraw_class {
public:
    /* 0xC0 */ int mMsgType;
    /* 0xC4 */ create_tag_class draw_tag;
    /* 0xD8 */ msg_method_class* sub_method;
    /* 0xDC */ fopAc_ac_c* mpActor;
    /* 0xE0 */ cXyz mPos;
    /* 0xEC */ u32 mMsgNo;
    /* 0xF0 */ u32 field_0xf0;
    /* 0xF4 */ u32 field_0xf4;
    /* 0xF8 */ u16 mStatus;
    /* 0xFA */ u8 mSelectNum; // The index of the choice the player selected.
};  // Size: 0xFC

extern leafdraw_method_class g_fopMsg_Method;

#endif /* F_OP_F_OP_MSG_H */
