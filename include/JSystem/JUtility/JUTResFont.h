#ifndef JUTRESFONT_H
#define JUTRESFONT_H

#include "JSystem/JUtility/JUTFont.h"
#include "dolphin/gx/GXEnum.h"

class JKRHeap;

typedef bool (*IsLeadByte_func)(int);

class JUTResFont : public JUTFont {
public:
    virtual ~JUTResFont();
    virtual void setGX();
    virtual void setGX(JUtility::TColor, JUtility::TColor);
    virtual f32 drawChar_scale(f32, f32, f32, f32, int, bool);
    virtual const ResFONT* getResFont() const { return mResFont; }
    virtual int getFontType() const { return mInfoBlock->fontType; }
    virtual int getLeading() const { return mInfoBlock->leading; }
    virtual s32 getWidth() const { return mInfoBlock->width; }
    virtual s32 getAscent() const { return mInfoBlock->ascent; }
    virtual s32 getDescent() const { return mInfoBlock->descent; }
    virtual s32 getHeight() const { return getAscent() + getDescent(); }
    virtual void getWidthEntry(int, JUTFont::TWidth*) const;
    virtual int getCellWidth() const;
    virtual s32 getCellHeight() const;
    virtual bool isLeadByte(int) const;
    virtual void loadImage(int, _GXTexMapID);
    virtual void setBlock();

    JUTResFont(ResFONT const*, JKRHeap*);
    JUTResFont();
    void deleteMemBlocks_ResFont();
    void initialize_state();
    bool initiate(ResFONT const*, JKRHeap*);
    bool protected_initiate(ResFONT const*, JKRHeap*);
    void countBlock();
    void loadFont(int, _GXTexMapID, JUTFont::TWidth*);
    int getFontCode(int) const;
    int convertSjis(int, u16*) const;

    inline void delete_and_initialize() {
        deleteMemBlocks_ResFont();
        initialize_state();
    }

    static const int suAboutEncoding_ = 3;
    static IsLeadByte_func const saoAboutEncoding_[suAboutEncoding_];

    /* 0x1C */ int mWidth;
    /* 0x20 */ int mHeight;
    /* 0x24 */ _GXTexObj mTexObj;
    /* 0x44 */ int mTexPageIdx;
    /* 0x48 */ const ResFONT* mResFont;
    /* 0x4C */ ResFONT::INF1* mInfoBlock;
    /* 0x50 */ void** mpMemBlocks;
    /* 0x54 */ ResFONT::WID1** mpWidthBlocks;
    /* 0x58 */ ResFONT::GLY1** mpGlyphBlocks;
    /* 0x5C */ ResFONT::MAP1** mpMapBlocks;
    /* 0x60 */ u16 mWidthBlockNum;
    /* 0x62 */ u16 mGlyphBlockNum;
    /* 0x64 */ u16 mMapBlockNum;
    /* 0x66 */ u16 field_0x66;
    /* 0x68 */ u16 mMaxCode;
    /* 0x6C */ const IsLeadByte_func* mIsLeadByte;
};

#endif /* JUTRESFONT_H */
