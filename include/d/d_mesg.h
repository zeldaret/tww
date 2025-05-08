#ifndef D_MESG_H
#define D_MESG_H

#include "dolphin/types.h"
#include "JSystem/JMessage/control.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"

class J2DPicture;
class J2DScreen;
class JKRExpHeap;
class JUTFont;
class JPABaseEmitter;
class dMesg_outFont_c;
class dMesg_screenData_c;

class sub_mesg_class : public msg_class {
    public:
        /* 0x0FC */ JKRExpHeap* heap;
        /* 0x100 */ JKRExpHeap* field_0x100;
        /* 0x104 */ dMesg_outFont_c* outfont[18];
        /* 0x14C */ dMesg_screenData_c* screen;
        /* 0x150 */ u8 field_0x150[0x154 - 0x150];
        /* 0x154 */ char* text[4];
        /* 0x164 */ u8 field_0x164;
    };

class dMesg_outFont_c {
public:
    void getTimer() {}

    virtual ~dMesg_outFont_c();
    void _create();
    void _delete();
    void _initialize();
    bool _set(s16, s16, s16, u32, u8);
    void _draw();
    void _setAlpha(u8);

    /* 0x04 */ J2DPicture* icon;
    /* 0x08 */ J2DPicture* kage;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ u8 mAlpha;
    /* 0x19 */ u8 field_0x19;
};

class dMesg_tControl : public JMessage::TControl {
public:
    void getCharCode() {}
    void getCharSpace() {}
    void getInitFontSize() {}
    void getLineCount() {}
    void getLineLength(int) {}
    void getLineStart() {}
    void getMainFont() {}
    void getNowFontSize() {}
    void getRubyFont() {}
    void getTextBoxWidth() {}
    void isHeader() {}
    void setCharCode(int) {}
    void setCode16FgOff() {}
    void setHeaderOff() {}
    void setHeaderOn() {}
    void setLineCount(int) {}
    void setLineLength(int, f32) {}
    void setLineStart(int) {}
    void setMainFont(JUTFont* font) { mMainFont = font; }
    void setNowFontSize(int) {}
    void setRubyFont(JUTFont* font) { mRubyFont = font; }

    dMesg_tControl();
    const char* do_word(u32);

public:
    /* 0x3C */ JUTFont* mMainFont;
    /* 0x40 */ JUTFont* mRubyFont;
    /* 0x44 */ f32 field_0x44[4];
    /* 0x54 */ int field_0x54;
    /* 0x58 */ int field_0x58;
    /* 0x5C */ int field_0x5c;
    /* 0x60 */ int field_0x60;
    /* 0x64 */ int field_0x64;
    /* 0x68 */ int field_0x68;
    /* 0x6C */ int field_0x6c;
    /* 0x70 */ u8 field_0x70;
    /* 0x71 */ u8 field_0x71;
};

class dMesg_tSequenceProcessor : public JMessage::TSequenceProcessor {
public:
    void decWaitRest() {}
    void getNowColor() {}
    void getStopFlag() {}
    void resetWaitRest() {}
    void setMesg(sub_mesg_class* mesg) { mMesg = mesg; }
    void setNowColor(u32) {}
    void setShortCutFlag() {}
    void setWaitRest() {}

    dMesg_tSequenceProcessor(JMessage::TControl*);
    virtual ~dMesg_tSequenceProcessor() {}
    void initialize(int);
    virtual void do_begin(const void*, const char*);
    virtual void do_end();
    virtual bool do_isReady();
    virtual bool do_jump_isReady();
    virtual void do_jump(const void*, const char*);
    virtual void do_branch_query(u16);
    virtual int do_branch_queryResult();
    virtual void do_branch(const void*, const char*);
    virtual void do_character(int);
    virtual bool do_tag(u32, const void*, u32);
    void setCharacter();
    char* ruby_character(char*, int);
    virtual bool do_systemTagCode(u16, const void*, u32);

    /* 0x038 */ sub_mesg_class* mMesg;
    /* 0x03C */ const void* field_0x3c;
    /* 0x040 */ const char* field_0x40;
    /* 0x044 */ f32 field_0x44;
    /* 0x048 */ f32 field_0x48;
    /* 0x04C */ f32 field_0x4c;
    /* 0x050 */ f32 field_0x50;
    /* 0x054 */ f32 field_0x54;
    /* 0x058 */ int field_0x58;
    /* 0x05C */ int field_0x5c;
    /* 0x060 */ int field_0x60;
    /* 0x064 */ int field_0x64;
    /* 0x068 */ int field_0x68;
    /* 0x06C */ u32 field_0x6c;
    /* 0x070 */ int field_0x70;
    /* 0x074 */ int field_0x74;
    /* 0x078 */ int field_0x78;
    /* 0x07C */ int field_0x7c[4];
    /* 0x08C */ int field_0x8c;
    /* 0x090 */ int field_0x90;
    /* 0x094 */ char field_0x94;
    /* 0x095 */ u8 field_0x95;
    /* 0x096 */ u8 field_0x96;
    /* 0x097 */ char field_0x97[100];
    /* 0x0FB */ char field_0xfb[100];
    /* 0x15F */ u8 field_0x15f;
    /* 0x160 */ u8 field_0x160;
    /* 0x161 */ u8 field_0x161;
    /* 0x162 */ u8 field_0x162;
    /* 0x163 */ u8 field_0x163;
};

class dMesg_tMeasureProcessor : public JMessage::TSequenceProcessor {
public:
    dMesg_tMeasureProcessor(JMessage::TControl*, int);
    virtual ~dMesg_tMeasureProcessor() {}
    virtual void do_character(int);
    virtual void do_end();
    virtual bool do_tag(u32, const void*, u32);
    virtual bool do_systemTagCode(u16, const void*, u32);

    /* 0x38 */ f32 field_0x38[4];
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ int field_0x4c;
    /* 0x50 */ int field_0x50;
    /* 0x54 */ u8 field_0x54;
};

class dMesg_tRenderingProcessor : public JMessage::TRenderingProcessor {
public:
    dMesg_tRenderingProcessor(JMessage::TControl*);
    virtual ~dMesg_tRenderingProcessor() {}
    virtual void do_begin(const void*, const char*);
    virtual void do_end();
    virtual void do_character(int);
    virtual bool do_tag(u32, const void*, u32);
    virtual bool do_systemTagCode(u16, const void*, u32);
};

class dMesg_screenData_c : public dDlst_base_c {
public:
    void deleteScreen() {}
    void getTextPosX(int) {}
    void getTextPosY(int) {}
    void resetTimer() {}
    void setFont(JUTFont* font1, JUTFont* font2) {
        field_0x10 = font1;
        field_0x14 = font2;
    }
    void setHeap(JKRExpHeap* heap) { mHeap = heap; }
    void setMesg(sub_mesg_class* mesg) { mMesg = mesg; }

    virtual ~dMesg_screenData_c() {}
    virtual void draw() {}
    virtual void createScreen() {}
    virtual void changeFont(JUTFont*) {}
    virtual void move() {}
    virtual bool openAnime() = 0;
    virtual bool closeAnime() = 0;
    virtual void setTextPosition(u8) {}
    void setCommonData();
    void initString(char*, int);
    void setString(char*, int);
    void shiftSet(int, int);
    void arwAnimeInit();
    void arwAnime();
    void dotAnimeInit();
    void dotAnime();

    /* 0x004 */ JKRExpHeap* mHeap;
    /* 0x008 */ sub_mesg_class* mMesg;
    /* 0x00C */ J2DScreen* scrn;
    /* 0x010 */ JUTFont* field_0x10;
    /* 0x014 */ JUTFont* field_0x14;
    /* 0x018 */ fopMsgM_pane_class field_0x18;
    /* 0x050 */ fopMsgM_pane_class field_0x50;
    /* 0x088 */ fopMsgM_pane_class field_0x88[4];
    /* 0x168 */ fopMsgM_pane_class field_0x168;
    /* 0x1A0 */ u8 field_0x1a0[0x1A4 - 0x1A0];
    /* 0x1A4 */ int field_0x1a4;
    /* 0x1A8 */ s16 field_0x1a8;
    /* 0x1AA */ u8 field_0x1aa[0x1AC - 0x1AA];
    /* 0x1AC */ JUtility::TColor field_0x1ac;
    /* 0x1B0 */ JUtility::TColor field_0x1b0;
};

class dMesg_screenDataTalk_c : public dMesg_screenData_c {
public:
    virtual ~dMesg_screenDataTalk_c() {}
    virtual void createScreen();
    virtual void changeFont(JUTFont*);
    virtual bool openAnime();
    virtual bool closeAnime();
    virtual void setTextPosition(u8);
    virtual void draw();

    /* 0x1B4*/ f32 field_0x1b4;
};

class dMesg_screenDataItem_c : public dMesg_screenData_c {
public:
    virtual ~dMesg_screenDataItem_c() {}
    virtual void createScreen();
    virtual void changeFont(JUTFont*);
    virtual void deleteScreen();
    virtual bool openAnime();
    virtual bool closeAnime();
    virtual void move();
    virtual void draw();
    void ringMove();
    void lightMove();
    void cornerMove();

    /* 0x1B4 */ fopMsgM_pane_class field_0x1b4;
    /* 0x1EC */ fopMsgM_pane_class field_0x1ec;
    /* 0x224 */ fopMsgM_pane_class field_0x224[8];
    /* 0x3E4 */ JPABaseEmitter* field_0x3e4;
    /* 0x3E8 */ f32 field_0x3e8;
    /* 0x3EC */ ResTIMG* texBuffer;
};

#endif /* D_MESG_H */
