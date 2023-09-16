#ifndef D_NPC_H
#define D_NPC_H

enum dNpc_MessageStatus_e {
    dNpcMsgStts_MSG_PREPARING_e = 0x01,
    dNpcMsgStts_BOX_OPENING_e = 0x02,
    dNpcMsgStts_MSG_TYPING_e = 0x06,
    dNpcMsgStts_MSG_DISPLAYED_e = 0x0E,

    dNpcMsgStts_MSG_CONTINUES_e = 0x0F,
    dNpcMsgStts_MSG_ENDS_e = 0x10,
    
    dNpcMsgStts_BOX_CLOSING_e = 0x11,
    dNpcMsgStts_BOX_CLOSED_e = 0x12,
    dNpcMsgStts_MSG_DESTROYED_e = 0x13,
};

#endif // D_NPC_H
