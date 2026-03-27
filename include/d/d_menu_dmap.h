#ifndef D_MENU_DMAP_H
#define D_MENU_DMAP_H

#include "d/d_menu_collect.h"
#include "dolphin/types.h"

class J2DPane;
struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Dmap_c : public dMenu_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    virtual void draw() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setTextArea(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        name[0] = name0;
        name[1] = name1;
        note[0] = note0;
        note[1] = note1;
        dummy[0] = dummy0;
        dummy[1] = dummy1;
    }

    void changeFloorTexture(J2DPane*, int);
    void screenSet();
    void initialize();
    void treasureSet();
    void treasureDraw();
    void paneMove(float);
    void paneAlpha(float);
    void decAlpha(float);
    void cursorMove();
    void cursorAnime();
    void noteInit();
    bool noteCheck();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void noteOpenProc(short);
    void itemScale();
    void floorInit();
    void mapMove();
    void mapOffsetY();
    void itemnameMove();
    void dnameSet();
    void itemnameSet();
    void itemnoteSet();
    void outFontInit();
    void linkAnime();
    void bossAnime();
    void bossEyeAnime();
    virtual void _create();
    virtual void _delete();
    virtual void _move();
    virtual void _draw();
    virtual bool _open();
    virtual bool _close();

public:
    /* 0x0004 */ u8 field_0x0004[0x972 - 0x4];
    /* 0x0972 */ s16 field_0x0972;
    /* 0x0974 */ u8 field_0x0974[0x14B4 - 0x974];
    /* 0x14B4 */ JUtility::TColor color_0x14B4;
    /* 0x14B8 */ JUtility::TColor color_0x14B8;
    /* 0x14BC */ JUtility::TColor color_0x14BC;
    /* 0x14C0 */ JUtility::TColor color_0x14C0;
    /* 0x14C4 */ JUtility::TColor color_0x14C4;
    /* 0x14C8 */ JUtility::TColor color_0x14C8;
    /* 0x14CC */ u8 field_0x14CC[0x1B08 - 0x14CC];
    /* 0x1B08 */ fopMsgM_msgDataProc_c* mpMsgProc;
    /* 0x1B0C */ u8 field_0x1B0C[0x1DA8 - 0x1B0C];
    /* 0x1DA8 */ char* name[2];
    /* 0x1DB0 */ char* note[2];
    /* 0x1DB8 */ char* dummy[2];
    /* 0x1DC0 */ u8 padding_0x1DC0[0x1E38 - 0x1DC0];
}; // Size: 0x1E38

class dMd_HIO_c {
public:
    dMd_HIO_c();
};

#endif /* D_MENU_DMAP_H */
