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

struct ShopItems_c__select_list_data {
    /* 0x00 */ s16 mLeftIdx;
    /* 0x02 */ s16 mRightIdx;
    /* 0x04 */ s16 mUpIdx;
    /* 0x06 */ s16 mDownIdx;
};

struct ShopItems_c__shop_cam_data {
    /* 0x00 */ Vec m00;
    /* 0x0C */ Vec m0C;
    /* 0x18 */ f32 m18;
};

class ShopCam_action_c {
public:
    typedef int (ShopCam_action_c::*ActionFunc)();
    
    ShopCam_action_c() {}
    
    void SetSelectIdx(s16) {}
    void setCamAction(ActionFunc func) { mCurrActionFunc = func; }
    BOOL checkCamAction(ActionFunc func) { return mCurrActionFunc == func; }
    void getItemZoomPos(f32) {
        
    }
    void setCamDataIdx(int idx) { mCamDataIdx = idx; }
    
    BOOL shop_cam_action_init();
    int shop_cam_action();
    BOOL rsh_talk_cam_action_init(fopAc_ac_c*, cXyz, cXyz, f32);
    int rsh_talk_cam_action();
    BOOL ds_normal_cam_action_init();
    int ds_normal_cam_action();
    void Save();
    void Reset();
    void move();

public:
    /* 0x00 */ ActionFunc mCurrActionFunc;
    /* 0x0C */ u8 m00[0x18 - 0x0C];
    /* 0x18 */ cXyz m18;
    /* 0x24 */ cXyz m24;
    /* 0x30 */ f32 m30;
    /* 0x34 */ cXyz mOrigCenter;
    /* 0x40 */ cXyz mOrigEye;
    /* 0x4C */ f32 mOrigFovy;
    /* 0x50 */ u8 m50[0x54 - 0x50];
    /* 0x54 */ s16 m54;
    /* 0x56 */ s16 mCamDataIdx;
};

class ShopItems_c {
public:
    ShopItems_c() {}
    ~ShopItems_c() {}
    
    BOOL isSoldOutItem(s16 i) { return m28[i] == 1; }
    BOOL isHide() { return mbIsHide; }
    s16 getItemDataIdx() { return mItemSetListGlobalIdx; }
    void setItemDataIdx(s16 idx) { mItemSetListGlobalIdx = idx; }
    void setItemSum(s16) {}
    void init() {}
    
    void createItem(int, int);
    BOOL Item_Select(int);
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
    /* 0x3E */ s16 mbIsHide;
    /* 0x40 */ s16 mNumItems;
    /* 0x42 */ s16 mItemSetListGlobalIdx;
};

class ShopCursor_c {
public:
    ShopCursor_c(J3DModelData*, J3DAnmTevRegKey*, f32);
    
    J3DModel* getModel(int idx) { return mpModels[idx]; }
    J3DAnmTevRegKey* getBrk() { return mpBrkData; }
    void hide() { m54 = 0; }
    void show() { m54 = 1; }
    void setScale(f32 param_1, f32 param_2, f32 param_3, f32 param_4, f32 param_5) {
        m48 = param_1;
        m4C = param_2;
        m50 = param_3;
        m38 = param_4;
        m3C = param_5;
    }
    
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
    /* 0x44 */ s16 m44;
    /* 0x46 */ u8 m46[0x48 - 0x46];
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ s32 m54;
};

s16 dShop_get_next_select(int, ShopItems_c*);
BOOL dShop_now_triggercheck(msg_class*, STControl*, ShopItems_c*, u32*, dShop_DefaultMsgCallback, void*);
BOOL dShop_maxCheck(int, int);
u8 dShop_BoughtErrorStatus(ShopItems_c*, int, int);
ShopCursor_c* ShopCursor_create(J3DModelData*, J3DAnmTevRegKey*, f32);

#endif /* D_SHOP_H */
