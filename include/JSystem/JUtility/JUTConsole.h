#ifndef JUTCONSOLE_H
#define JUTCONSOLE_H

#include "JSystem/JGadget/linklist.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JUtility/JUTFont.h"
#include "stdarg.h"

class JUTConsole : public JKRDisposer {
public:
    enum EConsoleType {
        ACTIVE = 0,
        INACTIVE = 1,
        CONSOLE_TYPE_2 = 2,
    };

    enum OutputFlag {
        /* 0x0 */ OUTPUT_NONE,
        /* 0x1 */ OUTPUT_OSREPORT,
        /* 0x2 */ OUTPUT_CONSOLE,
        /* 0x3 */ OUTPUT_OSR_AND_CONSOLE,
    };

    static JUTConsole* create(uint, void*, u32);
    static JUTConsole* create(uint, uint, JKRHeap*);
    JUTConsole(uint, uint, bool);
    static size_t getObjectSizeFromBufferSize(uint, uint);
    static size_t getLineFromObjectSize(u32, uint);
    void clear();
    void doDraw(JUTConsole::EConsoleType) const;
    void print_f(char const*, ...);
    void print(char const*);
    void dumpToTerminal(uint);
    void scroll(int);
    int getUsedLine() const;
    int getLineOffset() const;

    virtual ~JUTConsole();

    void setOutput(uint output) { mOutput = output; }
    void setPosition(int x, int y) {
        mPositionX = x;
        mPositionY = y;
    }
    void setFontSize(f32 x, f32 y) {
        mFontSizeX = x;
        mFontSizeY = y;
    }
    void setHeight(u32 height) {
        mHeight = height;
        if (mHeight > mMaxLines) {
            mHeight = mMaxLines;
        }
    }

    void setFont(JUTFont* p_font) {
        mFont = p_font;
        setFontSize(p_font->getWidth(), p_font->getHeight());
    }

    u32 getOutput() const { return mOutput; }
    int getPositionY() const { return mPositionY; }
    int getPositionX() const { return mPositionX; }
    u32 getHeight() const { return mHeight; }

    bool isVisible() const { return mVisible; }
    void setVisible(bool visible) { mVisible = visible; }

    u8 getLineAttr(int param_0) { return mBuf[(field_0x20 + 2) * param_0]; }
    void setLineAttr(int param_0, u8 param_1) { mBuf[(field_0x20 + 2) * param_0] = param_1; }
    u8* getLinePtr(int param_0) const { return &mBuf[(field_0x20 + 2) * param_0] + 1; }
    int diffIndex(int param_0, int param_1) const {
        int diff = param_1 - param_0;
        if (diff >= 0) {
            return diff;
        }
        return diff += mMaxLines;
    }

    int prevIndex(int index) const {
        return --index < 0 ? index = mMaxLines - 1 : index;
    }

    int nextIndex(int index) const {
        return ++index >= mMaxLines ? 0 : index;
    }

    void scrollToLastLine() { scroll(mMaxLines); }
    void scrollToFirstLine() { scroll(-mMaxLines); }

public:
    /* 0x18 */ JGadget::TLinkListNode mLinkNode;

private:
    /* 0x20 */ u32 field_0x20;
    /* 0x24 */ s32 mMaxLines;
    /* 0x28 */ u8* mBuf;
    /* 0x2C */ bool field_0x2c;
    /* 0x30 */ s32 field_0x30;
    /* 0x34 */ s32 field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ int mPositionX;
    /* 0x44 */ int mPositionY;
    /* 0x48 */ u32 mHeight;
    /* 0x4C */ JUTFont* mFont;
    /* 0x50 */ f32 mFontSizeX;
    /* 0x54 */ f32 mFontSizeY;
    /* 0x58 */ int mOutput;
    /* 0x5C */ JUtility::TColor field_0x5c;
    /* 0x60 */ JUtility::TColor field_0x60;
    /* 0x64 */ bool mVisible;
    /* 0x65 */ bool field_0x65;
    /* 0x66 */ bool field_0x66;
    /* 0x67 */ bool field_0x67;
};  // Size: 0x68

class JUTConsoleManager {
public:
    JUTConsoleManager();
    static JUTConsoleManager* createManager(JKRHeap*);
    void appendConsole(JUTConsole*);
    void removeConsole(JUTConsole*);
    void draw() const;
    void drawDirect(bool) const;
    void setDirectConsole(JUTConsole*);

    JUTConsole* getDirectConsole() const { return mDirectConsole; }

    static JUTConsoleManager* getManager() { return sManager; }

    static JUTConsoleManager* sManager;

    typedef JGadget::TLinkList<JUTConsole, -offsetof(JUTConsole, mLinkNode)> ConsoleList;

private:
    /* 0x00 */ ConsoleList soLink_;
    /* 0x0C */ JUTConsole* mActiveConsole;
    /* 0x10 */ JUTConsole* mDirectConsole;
};  // Size: 0x14

extern "C" void JUTConsole_print_f_va_(JUTConsole*, const char*, va_list);
extern "C" void JUTSetReportConsole(JUTConsole*);
extern "C" JUTConsole* JUTGetReportConsole();
extern "C" void JUTSetWarningConsole(JUTConsole*);
extern "C" JUTConsole* JUTGetWarningConsole();
extern "C" void JUTReportConsole_f_va(const char*, va_list);
extern "C" void JUTReportConsole_f(const char*, ...);
extern "C" void JUTWarningConsole(const char* message);
extern "C" void JUTWarningConsole_f_va(const char*, va_list);
extern "C" void JUTWarningConsole_f(const char* message, ...);
extern "C" void JUTReportConsole(const char* message);

#endif /* JUTCONSOLE_H */
