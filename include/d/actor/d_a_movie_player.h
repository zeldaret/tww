#ifndef D_A_MOVIE_PLAYER_H
#define D_A_MOVIE_PLAYER_H

#include "f_op/f_op_actor.h"
#include "d/d_drawlist.h"
#include "dolphin/dvd/dvd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 THPSample;
typedef s16 THPCoeff;
typedef f32 THPQuantTab[64];

typedef struct _THPHuffmanTab {
    u8 quick[32];
    u8 increment[32];
    u8* Vij;
    s32 maxCode[18];
    s32 valPtr[18];
    u8 Vij1;
    u8 pad[11];
} THPHuffmanTab;

typedef struct _THPComponent {
    u8 quantizationTableSelector;
    u8 DCTableSelector;
    u8 ACTableSelector;
    THPCoeff predDC;
} THPComponent;

typedef struct _THPFileInfo {
    THPQuantTab quantTabs[3];
    THPHuffmanTab huffmanTabs[4];
    THPComponent components[3];
    u16 xPixelSize;
    u16 yPixelSize;
    u16 MCUsPerRow;
    u16 decompressedY;
    u8* c;
    u32 currByte;
    u32 cnt;
    u8 validHuffmanTabs;
    u8 RST;
    u16 nMCU;
    u16 currMCU;
    u8* dLC[3];
} THPFileInfo;

typedef struct THPAudioRecordHeader {
    u32 offsetNextChannel;
    u32 sampleSize;
    s16 lCoef[8][2];
    s16 rCoef[8][2];
    s16 lYn1;
    s16 lYn2;
    s16 rYn1;
    s16 rYn2;
} THPAudioRecordHeader;

typedef struct THPAudioDecodeInfo {
    u8* encodeData;
    u32 offsetNibbles;
    u8 predictor;
    u8 scale;
    s16 yn1;
    s16 yn2;
} THPAudioDecodeInfo;

static u32 THPAudioDecode(s16* audioBuffer, u8* audioFrame, s32 flag);
static s32 __THPAudioGetNewSample(THPAudioDecodeInfo* info);
static void __THPAudioInitialize(THPAudioDecodeInfo* info, u8* ptr);

s32 __THPAudioGetNewSample(THPAudioDecodeInfo*);
void __THPAudioInitialize(THPAudioDecodeInfo*, u8*);

static void __THPSetupBuffers(void);
static u8 __THPReadFrameHeader(void);
static u8 __THPReadScaneHeader(void);
static u8 __THPReadQuantizationTable(void);
static u8 __THPReadHuffmanTableSpecification(void);
static void __THPHuffGenerateSizeTable(void);
static void __THPHuffGenerateCodeTable(void);
static void __THPHuffGenerateDecoderTables(u8 tabIndex);
static void __THPRestartDefinition(void);
static void __THPPrepBitStream(void);
static void __THPDecompressYUV(void* tileY, void* tileU, void* tileV);
static void __THPGQRRestore(void);
static void __THPDecompressiMCURow512x448(void);
static void __THPDecompressiMCURow640x480(void);
static void __THPDecompressiMCURowNxN(void);
static void __THPInverseDCTNoYPos(THPCoeff* in, u32 xPos);
static void __THPHuffDecodeDCTCompY(THPFileInfo* info, THPCoeff* block);
static void __THPHuffDecodeDCTCompU(THPFileInfo* info, THPCoeff* block);
static void __THPHuffDecodeDCTCompV(THPFileInfo* info, THPCoeff* block);

static void __THPInverseDCTY8(THPCoeff* in, u32 xPos);
static void __THPGQRSetup();
static s32 __THPHuffDecodeTab(THPFileInfo* info, THPHuffmanTab* h);

#ifdef __cplusplus
}
#endif

class daMP_c : public fopAc_ac_c {
public:
    u32 daMP_c_Get_arg_data();
    int daMP_c_Init();
    BOOL daMP_c_Finish();
    BOOL daMP_c_Main();
    BOOL daMP_c_Draw();
    static int daMP_c_Callback_Init(fopAc_ac_c*);
    static BOOL daMP_c_Callback_Finish(daMP_c*);
    static BOOL daMP_c_Callback_Main(daMP_c*);
    static BOOL daMP_c_Callback_Draw(daMP_c*);

public:
    /* 0x290 */ u32 (*mpCallBack1)();
    /* 0x294 */ u32 (*mpCallBack2)(f32);
};

class daMP_Dlst_base_c : public dDlst_base_c {
    void draw();
};

struct daMP_THPReadBuffer {
    /* 0x00 */ void* m00;
    /* 0x04 */ s32 m04;
};

struct daMP_Player_c { // Fake name
    /* 0x00 */ DVDFileInfo mFileInfo;
    /* 0x3C */ u8 m3C[0x50 - 0x3C];
    /* 0x50 */ u32 m50;
    /* 0x54 */ u8 m54[0x64 - 0x54];
    /* 0x64 */ s32 m64;
    /* 0x68 */ u8 m68[0xA6 - 0x68];
    /* 0xA6 */ u8 mA6;
    /* 0xA7 */ u8 mA7[0xA8 - 0xA7];
    /* 0xA8 */ s32 mA8;
    /* 0xAC */ u8 mAC[0xB8 - 0xAC];
    /* 0xB8 */ s32 mB8;
    /* 0xBC */ s32 mBC;
    /* 0xC0 */ s32 mC0;
};

struct THPVideoInfo {
    /* 0x00 */ u8 m00[0x0C - 0x00];
};

struct THPAudioInfo {
    /* 0x00 */ u8 m00[0x10 - 0x00];
};

inline s32 daMP_NEXT_READ_SIZE(daMP_THPReadBuffer* readBuf) {
    return *(s32*)readBuf->m00;
}

void daMP_PrepareReady(int);

#endif /* D_A_MOVIE_PLAYER_H */
