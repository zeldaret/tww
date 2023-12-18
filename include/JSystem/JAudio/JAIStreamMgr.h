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
    namespace StreamMgr {
        void init();
        void storeStreamBuffer(JAISound**, Actor*, u32, u32, u8, void*);
        void releaseStreamBuffer(JAISound*, u32);
        void processGFrameStream();
        void checkEntriedStream();
        void checkWaitStream();
        void checkRequestStream();
        void checkPlayingStream();

        extern LinkSound streamControl;
        extern u8 flags;
        extern int streamUpdate;
        extern u8* streamList;
        extern u8* initOnCodeStrm;
    }

    namespace StreamLib {
        void Play_DirectPCM(JASystem::TDSPChannel*, s16*, u16, u32, s16, u16);
        int Get_DirectPCM_LoopRemain(JASystem::DSPInterface::DSPBuffer*);
        int Get_DirectPCM_Remain(JASystem::DSPInterface::DSPBuffer*);
        void init(bool);
        void allocBuffer(void*, s32);
        bool deallocBuffer();
        int getNeedBufferSize();
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

        extern s16 filter_table[];
        extern s16 table4[];
        extern DVDFileInfo finfo;
        extern u32 header[];
        extern char Filename[];
        extern JASystem::Kernel::TSolidHeap streamHeap;
        extern u32 LOOP_BLOCKS;
        extern int LOOP_SAMPLESIZE;
        extern int outputmode;
        extern int adpcm_remain;
        extern int adpcm_loadpoint;
        extern int loadsize;
        extern int adpcm_buffer;
        extern int loop_buffer;
        extern int store_buffer;
        extern JASystem::TDSPChannel* assign_ch[2];
        extern int playside;
        extern int playback_samples;
        extern int loadup_samples;
        extern u32 adpcmbuf_state;
        extern int movieframe;
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
