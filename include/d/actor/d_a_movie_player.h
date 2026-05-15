#ifndef D_A_MOVIE_PLAYER_H
#define D_A_MOVIE_PLAYER_H

#include "dolphin/thp.h"
#include "f_op/f_op_actor.h"
#include "d/d_drawlist.h"
#include "dolphin/dvd/dvd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 THPSample;
typedef s16 THPCoeff;
typedef f32 THPQuantTab[64];

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
    cPhs_State daMP_c_Init();
    BOOL daMP_c_Finish();
    BOOL daMP_c_Main();
    BOOL daMP_c_Draw();
    static int daMP_c_Callback_Init(fopAc_ac_c*);
    static BOOL daMP_c_Callback_Finish(daMP_c*);
    static BOOL daMP_c_Callback_Main(daMP_c*);
    static BOOL daMP_c_Callback_Draw(daMP_c*);

public:
    /* 0x290 */ u32 (*mpGetMovieRestFrame)();
    /* 0x294 */ u32 (*mpSetPercentMovieVol)(f32);
#if VERSION == VERSION_PAL
    /* 0x29C */ u32 (*mpTHPGetTotalFrame)(void);
#endif
};

class daMP_Dlst_base_c : public dDlst_base_c {
    void draw();
};

struct daMP_THPReadBuffer {
    /* 0x00 */ u8* ptr;
    /* 0x04 */ s32 frameNumber;
    /* 0x08 */ BOOL isValid;
};

struct daMP_Player_c { // Fake name
    /* 0x000 */ DVDFileInfo fileInfo;
    /* 0x03C */ THPHeader header;
    /* 0x06C */ THPFrameCompInfo compInfo;
    /* 0x080 */ THPVideoInfo videoInfo;
    /* 0x08C */ THPAudioInfo audioInfo;
    /* 0x09C */ void* thpWork;
    /* 0x0A0 */ BOOL open;
    /* 0x0A4 */ u8 state;
    /* 0x0A5 */ u8 internalState;
    /* 0x0A6 */ u8 playFlag;
    /* 0x0A7 */ u8 audioExist;
    /* 0x0A8 */ s32 dvdError;
    /* 0x0AC */ s32 videoError;
    /* 0x0B0 */ BOOL onMemory;
    /* 0x0B4 */ u8* movieData;
    /* 0x0B8 */ s32 initOffset;
    /* 0x0BC */ s32 initReadSize;
    /* 0x0C0 */ s32 initReadFrame;
    /* 0x0C4 */ u32 curField;
    /* 0x0C8 */ s64 retaceCount;
    /* 0x0D0 */ s32 prevCount;
    /* 0x0D4 */ s32 curCount;
    /* 0x0D8 */ s32 videoDecodeCount;
    /* 0x0DC */ f32 curVolume;
    /* 0x0E0 */ f32 targetVolume;
    /* 0x0E4 */ f32 deltaVolume;
    /* 0x0E8 */ s32 rampCount;
    /* 0x0EC */ s32 curAudioTrack;
    /* 0x0F0 */ s32 curVideoNumber;
    /* 0x0F4 */ s32 curAudioNumber;
    /* 0x0F8 */ THPTextureSet* dispTextureSet;
    /* 0x0FC */ THPAudioBuffer* playAudioBuffer;
    /* 0x100 */ daMP_THPReadBuffer readBuffer[10];
    /* 0x000 */ THPTextureSet textureSet[THP_TEXTURE_SET_COUNT];
    /* 0x000 */ THPAudioBuffer audioBuffer[THP_AUDIO_BUFFER_COUNT];
};

#endif /* D_A_MOVIE_PLAYER_H */
