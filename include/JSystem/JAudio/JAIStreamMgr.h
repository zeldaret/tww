#ifndef JAISTREAMMGR_H
#define JAISTREAMMGR_H

#include "dolphin/dvd/dvd.h"
#include "JSystem/JAudio/JAISound.h"
#include "JSystem/JAudio/JASHeapCtrl.h"

class JAISound;

namespace JASystem {
    class TDSPChannel;
    namespace DSPInterface {
        class DSPBuffer;
    }
}

namespace JAInter {
    class Actor;
    struct streamUpdate_t {
        streamUpdate_t() { field_0x14 = 0; }
        
        /* 0x00 */ u8 field_0x0;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 field_0x2;
        /* 0x04 */ f32 field_0x4;
        /* 0x08 */ f32 field_0x8;
        /* 0x0C */ f32 field_0xc;
        /* 0x10 */ int field_0x10;
        /* 0x14 */ JAISound* field_0x14;
    };

    class StreamParameter {
    public:
        /* 0x000 */ u8 field_0x0;
        /* 0x004 */ int field_0x4;
        /* 0x008 */ int field_0x8;
        /* 0x00C */ int field_0xc;
        /* 0x010 */ int field_0x10;
        /* 0x014 */ JAInter::MoveParaSet field_0x14[20];
        /* 0x154 */ JAInter::MoveParaSet* pitch;
        /* 0x158 */ JAInter::MoveParaSet* pan;
        /* 0x15C */ streamUpdate_t* field_0x15c;
    };

    namespace StreamMgr {
        void init();
        void storeStreamBuffer(JAISound**, Actor*, u32, u32, u8, void*);
        void releaseStreamBuffer(JAISound*, u32);
        void processGFrameStream();
        void checkEntriedStream();
        void checkWaitStream();
        void checkRequestStream();
        void checkPlayingStream();

        struct flags_t {
            u8 flag1 : 1;
            u8 flag2 : 1;
            u8 flag3 : 1;
            u8 flag4 : 1;
            u8 flag5 : 1;
            u8 flag6 : 1;
            u8 flag7 : 1;
            u8 flag8 : 1;
        };

        extern LinkSound streamControl;
        extern flags_t flags;
        extern streamUpdate_t* streamUpdate;
        extern u8* streamList;
        extern u8* initOnCodeStrm;

        inline streamUpdate_t* getUpdateInfo() { return streamUpdate; }
    }

    namespace StreamLib {
        void Play_DirectPCM(JASystem::TDSPChannel*, s16*, u16, u32, s16, u16);
        int Get_DirectPCM_LoopRemain(JASystem::DSPInterface::DSPBuffer*);
        int Get_DirectPCM_Remain(JASystem::DSPInterface::DSPBuffer*);
        void init(bool);
        void allocBuffer(void*, s32);
        bool deallocBuffer();
        u32 getNeedBufferSize();
        void setAllocBufferCallback(void (*)(void));
        void setDeallocBufferCallback(void (*)(void));
        void sync(s32);
        void __DecodePCM();
        void __DecodeADPCM();
        void __Decode();
        void __LoadFin(s32, DVDFileInfo*);
        void LoadADPCM();
        void setVolume(f32);
        void setPitch(f32);
        void setPan(f32 param_1);
        void stop();
        void setPauseFlag(u8 param_1);
        void clearPauseFlag(u8 param_1);
        void setPrepareFlag(u8 param_1);
        void setOutputMode(u32 param_1);
        u8 getPlayingFlag();
        void setDecodedBufferBlocks(u32 param_1);
        void LoopInit();
        s32 directPlayWait(void* param_1);
        void start(char* param_1, u32 param_2, void* param_3);
        void __start();
        s32 callBack(void* param_1);

        struct StreamHeader {
            int field_0x0;
            int field_0x4;
            u16 field_0x8;
            u16 field_0xa;
            u16 field_0xc;
            u16 field_0xe;
            u32 field_0x10;
            u32 field_0x14;
            int field_0x18;
            int field_0x1c;
        };

        extern s16 filter_table[];
        extern s16 table4[];
        extern DVDFileInfo finfo;
        extern StreamHeader header;
        extern char Filename[];
        extern JASystem::Kernel::TSolidHeap streamHeap;
        extern u32 LOOP_BLOCKS;
        extern int LOOP_SAMPLESIZE;
        extern int outputmode;
        extern u32 adpcm_remain;
        extern u32 adpcm_loadpoint;
        extern u32 loadsize;
        extern s16* adpcm_buffer;
        extern s16*** loop_buffer;
        extern void** store_buffer;
        extern JASystem::TDSPChannel* assign_ch[2];
        extern u32 playside;
        extern int playback_samples;
        extern int loadup_samples;
        extern u32 adpcmbuf_state;
        extern u32 movieframe;
        extern bool stopflag;
        extern bool stopflag2;
        extern u8 playflag;
        extern u8 playflag2;
        extern u8 prepareflag;
        extern u8 dspch_deallockflag;
        extern f32 outvolume;
        extern f32 outpitch;
        extern f32 outpan;
        extern f32 stackvolume;
        extern f32 stackpitch;
        extern f32 stackpan;
        extern u8 outflag_volume;
        extern bool outflag_pan;
        extern bool outflag_pitch;
        extern int loop_start_flag;
        extern int outpause;
        extern int playmode;
        extern int shift_sample;
        extern int extra_sample;
        extern int DvdLoadFlag;
        extern u32 startInitFlag;
        extern int Mode;
        extern int sFillBlockSize;
        extern void* Head;
        extern bool bufferMode;
        extern u8 allocFlag;
        extern u8 dspFinishFlag;
        extern void (*allocCallback)();
        extern void (*deallocCallback)();
    }
}

#endif /* JAISTREAMMGR_H */
