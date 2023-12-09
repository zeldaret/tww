#ifndef D_A_SHOP_ITEM_H
#define D_A_SHOP_ITEM_H

#include "d/actor/d_a_itembase.h"
#include "d/d_cloth_packet.h"

struct daShopItem_c_m_data {
    /* 0x00 */ Vec mScale;
    /* 0x0C */ Vec field_0x0C;
    /* 0x18 */ SVec field_0x18;
};

class daShopItem_c : public daItemBase_c {
public:
    inline BOOL _delete();
    void setTevType(int) {}

    char* getShopArcname();
    s16 getShopBmdIdx();
    void CreateInit();
    inline int _create();
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

    /* 0x63C */ request_of_phase_process_class field_0x63C;
    /* 0x644 */ dCloth_packet_c* field_0x644;
    /* 0x648 */ u8 field_0x648;
    /* 0x64C */ Mtx field_0x64C;
    /* 0x67C */ TevType tevType;
};

#endif /* D_A_SHOP_ITEM_H */
