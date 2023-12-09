#ifndef D_A_RACE_ITEM_H
#define D_A_RACE_ITEM_H

#include "d/actor/d_a_itembase.h"

class daRaceItem_c : public daItemBase_c {
public:
    void setListStart() {}
    BOOL draw() { return DrawBase(); }

    void set_mtx();
    BOOL Delete();
    s32 create();
    BOOL CreateInit();
    void checkGet();
    inline BOOL execute();

    // race_item_static functions
    void raceItemForceGet();
    void raceItemGet();
    void normalItemGet();
    BOOL startOffsetPos();
    BOOL endOffsetPos(f32, cXyz*, f32, f32, csXyz*);
    BOOL checkOffsetPos();
    void set_mtx(cXyz*);
public:
    /* 0x63C */ s32 field_0x63C;
    /* 0x640 */ u32 field_0x640;
    /* 0x644 */ u8 field_0x644;
    /* 0x645 */ u8 field_0x645;
};

#endif /* D_A_RACE_ITEM_H */
