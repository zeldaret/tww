#ifndef D_A_SHOP_ITEM_H
#define D_A_SHOP_ITEM_H

#include "d/actor/d_a_itembase.h"

class dCloth_packet_c;

struct daShopItem_c_m_data {
    /* 0x00 */ Vec mScale;
    /* 0x0C */ Vec field_0x0C;
    /* 0x18 */ SVec field_0x18;
};

class daShopItem_c : public daItemBase_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    void setTevType(int type) { mTevType = type; }

    char* getShopArcname();
    s16 getShopBmdIdx();
    void CreateInit();
    bool _execute();
    void set_mtx();
    bool _draw();

    //virtual funcs
    void setListStart() {}
    void settingBeforeDraw();
    void setTevStr();
    BOOL clothCreate();

    //funcs in d_a_shop_item_static
    cXyz* getScaleP();
    csXyz* getRotateP();
    cXyz* getPosP();
    cXyz getCenter();

    const daShopItem_c_m_data* getData() { return mData; }

    static const char m_cloth_arcname[];
    static const f32 m_cullfar_max;
    static const u8 mModelType[255];
    static const daShopItem_c_m_data mData[255];

    /* 0x63C */ request_of_phase_process_class mPhase;
    /* 0x644 */ dCloth_packet_c* field_0x644;
    /* 0x648 */ u8 field_0x648;
    /* 0x64C */ Mtx field_0x64C;
    /* 0x67C */ int mTevType;
};

#endif /* D_A_SHOP_ITEM_H */
