#ifndef D_EVENT_BIT_H
#define D_EVENT_BIT_H

enum dEventBit_e {
    dEvtBit_SHIP_RIDDEN_e = 0x2A08,
    dEvtBit_BARRIER_BREAK_e = 0x2C02,
    dEvtBit_LITHOGRAPH_1_e = 0x3508,
    dEvtBit_LITHOGRAPH_2_e = 0x3504,
    dEvtBit_LITHOGRAPH_3_e = 0x3502,
    dEvtBit_LITHOGRAPH_4_e = 0x3501,
    dEvtBit_LITHOGRAPH_5_e = 0x3680,
    dEvtBit_LITHOGRAPH_6_e = 0x3640,
    dEvtBit_LITHOGRAPH_7_e = 0x3620,
    dEvtBit_LITHOGRAPH_8_e = 0x3610,
    dEvtBit_LITHOGRAPH_9_e = 0x3608,
    dEvtBit_LITHOGRAPH_10_e = 0x3604,
};

enum dEventReg_e {
    dEvtReg_NOTE_TO_MOM_e = 0xAC03,
};

#endif /* D_EVENT_BIT_H */
