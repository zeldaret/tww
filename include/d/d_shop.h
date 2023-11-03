#ifndef D_SHOP_H
#define D_SHOP_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class msg_class;
class STControl;

typedef u32 (*dShop_DefaultMsgCallback)(void*);

enum ShopItems_c__BuyConditions {
    Shop_BuyCond_MUST_OWN_ITEM_e     = 0x01,
    Shop_BuyCond_MUST_NOT_OWN_ITEM_e = 0x02,
    Shop_BuyCond_MAXIMUM_e           = 0x04,
    Shop_BuyCond_ANY_BOTTLE_e        = 0x08,
    Shop_BuyCond_EMPTY_BOTTLE_e      = 0x10,
    Shop_BuyCond_RUPEES_e            = 0x20,
};

struct ShopItems_c__ItemData {
    /* 0x00 */ int mItemNo;
    /* 0x04 */ int mMustNotOwnItemNo;
    /* 0x08 */ int mMustOwnItemNo;
    /* 0x0C */ u8 mBuyConditions;
};

struct __shop_items_set_data {
    /* 0x00 */ ShopItems_c__ItemData* mpItemData;
    /* 0x04 */ u32 mShowMsgID;
    /* 0x08 */ u32 mBuyMsgID;
    /* 0x0C */ u32 m0C;
    /* 0x10 */ int mCount;
};

class ShopCam_action_c {
public:
    typedef int (ShopCam_action_c::*ActionFunc)();
    
    ShopCam_action_c() {}
    
    void SetSelectIdx(s16) {}
    void setCamAction(ActionFunc) {}
    void checkCamAction(ActionFunc) {}
    void getItemZoomPos(f32) {}
    void setCamDataIdx(int) {}
    
    void shop_cam_action_init();
    void shop_cam_action();
    void rsh_talk_cam_action_init(fopAc_ac_c*, cXyz, cXyz, f32);
    void rsh_talk_cam_action();
    void ds_normal_cam_action_init();
    void ds_normal_cam_action();
    void Save();
    void Reset();
    void move();

public:
    /* 0x00 */ u8 m00[0x18 - 0x00];
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ u8 m34[0x54 - 0x34];
    /* 0x54 */ s16 m54;
    /* 0x56 */ s16 m56;
};

class ShopItems_c {
public:
    ShopItems_c() {}
    ~ShopItems_c() {}
    
    BOOL isSoldOutItem(s16 i) { return m28[i] == 1; }
    BOOL isHide() {}
    s16 getItemDataIdx() {}
    void setItemDataIdx(s16) {}
    
    void createItem(int, int);
    void Item_Select(int);
    BOOL Item_Wait(int);
    BOOL Item_ZoomUp(cXyz&);
    BOOL Item_Move();
    cXyz getSelectItemPos();
    cXyz getSelectItemBasePos();
    void hideSelectItem();
    void SoldOutItem(int);
    u8 getItemNo(int);
    void showItem();
    u8 getSelectItemNo();
    u32 getSelectItemShowMsg();
    u32 getSelectItemBuyMsg();
    void setItemSetDataList();
    void setItemSetDataList(__shop_items_set_data**);
    BOOL isSoldOutItemAll();

public:
    /* 0x00 */ s16 mSelectedItemIdx;
    /* 0x02 */ u8 m02[0x04 - 0x02];
    /* 0x04 */ u32 mItemActorProcessIds[4];
    /* 0x14 */ u8 m14[0x24 - 0x14];
    /* 0x24 */ __shop_items_set_data** mpItemSetList;
    /* 0x28 */ u8 m28[4];
    /* 0x2C */ u8 m2C[0x30 - 0x2C];
    /* 0x30 */ cXyz m30;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ s16 mNumItems;
    /* 0x42 */ s16 mItemSetListGlobalIdx;
};

class ShopCursor_c {
public:
    ShopCursor_c(J3DModelData*, J3DAnmTevRegKey*, f32);
    
    void getModel(int) {}
    void getBrk() {}
    void hide() {}
    void show() {}
    void setScale(f32, f32, f32, f32, f32) {}
    
    void anm_play();
    void draw();
    void setPos(cXyz&);

public:
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ J3DModel* mpModels[4];
    /* 0x1C */ J3DAnmTevRegKey* mpBrkData;
    /* 0x20 */ mDoExt_brkAnm mBrkAnm;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ u16 m44;
    /* 0x46 */ u8 m46[0x48 - 0x46];
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ u32 m54;
};

static void dShop_get_next_select(int, ShopItems_c*);
static void dShop_now_triggercheck(msg_class*, STControl*, ShopItems_c*, u32*, dShop_DefaultMsgCallback, void*);
static void dShop_maxCheck(int, int);
static void dShop_BoughtErrorStatus(ShopItems_c*, int, int);
static void ShopCursor_create(J3DModelData*, J3DAnmTevRegKey*, f32);

#endif /* D_SHOP_H */
