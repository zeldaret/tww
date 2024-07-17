#ifndef D_MESG_H
#define D_MESG_H

#include "dolphin/types.h"
#include "JSystem/JMessage/control.h"

class JUTFont;
class JKRExpHeap;

class sub_mesg_class;

class dMesg_outFont_c {
public:
    void getTimer() {}
    
    ~dMesg_outFont_c();
    void _create();
    void _delete();
    void _initialize();
    void _set(s16, s16, s16, u32, u8);
    void _draw();
    void _setAlpha(u8);
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
    void setMainFont(JUTFont*) {}
    void setNowFontSize(int) {}
    void setRubyFont(JUTFont*) {}
    
    dMesg_tControl();
    const char* do_word(u32);

public:
    /* 0x3C */ u8 field_0x3C[0x74 - 0x3C];
};

class dMesg_tSequenceProcessor {
public:
    void decWaitRest() {}
    void getNowColor() {}
    void getStopFlag() {}
    void resetWaitRest() {}
    void setMesg(sub_mesg_class*) {}
    void setNowColor(u32) {}
    void setShortCutFlag() {}
    void setWaitRest() {}
    
    dMesg_tSequenceProcessor(JMessage::TControl*);
    ~dMesg_tSequenceProcessor();
    void initialize(int);
    void do_begin(const void*, const char*);
    void do_end();
    void do_isReady();
    void do_jump_isReady();
    void do_jump(const void*, const char*);
    void do_branch_query(u16);
    void do_branch_queryResult();
    void do_branch(const void*, const char*);
    void do_character(int);
    void do_tag(u32, const void*, u32);
    void setCharacter();
    void ruby_character(char*, int);
    void do_systemTagCode(u16, const void*, u32);
};

class dMesg_tMeasureProcessor {
public:
    dMesg_tMeasureProcessor(JMessage::TControl*, int);
    ~dMesg_tMeasureProcessor();
    void do_character(int);
    void do_end();
    void do_tag(u32, const void*, u32);
    void do_systemTagCode(u16, const void*, u32);
};

class dMesg_tRenderingProcessor {
public:
    dMesg_tRenderingProcessor(JMessage::TControl*);
    ~dMesg_tRenderingProcessor();
    void do_begin(const void*, const char*);
    void do_end();
    void do_character(int);
    void do_tag(u32, const void*, u32);
    void do_systemTagCode(u16, const void*, u32);
};

class dMesg_screenData_c {
public:
    void deleteScreen() {}
    void getTextPosX(int) {}
    void getTextPosY(int) {}
    void resetTimer() {}
    void setFont(JUTFont*, JUTFont*) {}
    void setHeap(JKRExpHeap*) {}
    void setMesg(sub_mesg_class*) {}
    
    ~dMesg_screenData_c();
    void setCommonData();
    void initString(char*, int);
    void setString(char*, int);
    void shiftSet(int, int);
    void arwAnimeInit();
    void arwAnime();
    void dotAnimeInit();
    void dotAnime();
    void changeFont(JUTFont*);
    void setTextPosition(u8);
    void createScreen();
    void move();
    void draw();
};

class dMesg_screenDataTalk_c {
public:
    ~dMesg_screenDataTalk_c();
    void createScreen();
    void changeFont(JUTFont*);
    void openAnime();
    void closeAnime();
    void setTextPosition(u8);
    void draw();
};

class dMesg_screenDataItem_c {
public:
    ~dMesg_screenDataItem_c();
    void createScreen();
    void changeFont(JUTFont*);
    void deleteScreen();
    void openAnime();
    void closeAnime();
    void move();
    void draw();
    void ringMove();
    void lightMove();
    void cornerMove();
};

#endif /* D_MESG_H */
