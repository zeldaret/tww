#ifndef JASSEQPARSER_H
#define JASSEQPARSER_H

#include "dolphin/types.h"

namespace JASystem {
    class TTrack;
    class TSeqParser {
    public:
        typedef int (TSeqParser::*CmdFunc)(JASystem::TTrack*, u32*);
        
        int cmdOpenTrack(TTrack*, u32*);
        int cmdOpenTrackBros(TTrack*, u32*);
        int cmdCall(TTrack*, u32*);
        int cmdRet(TTrack*, u32*);
        int cmdJmp(TTrack*, u32*);
        int cmdLoopS(TTrack*, u32*);
        int cmdLoopE(TTrack*, u32*);
        int cmdReadPort(TTrack*, u32*);
        int cmdWritePort(TTrack*, u32*);
        int cmdParentWritePort(TTrack*, u32*);
        int cmdChildWritePort(TTrack*, u32*);
        int cmdCheckPortImport(TTrack*, u32*);
        int cmdCheckPortExport(TTrack*, u32*);
        int cmdWait(TTrack*, u32*);
        int cmdSetLastNote(TTrack*, u32*);
        int cmdTimeRelate(TTrack*, u32*);
        int cmdSimpleOsc(TTrack*, u32*);
        int cmdSimpleEnv(TTrack*, u32*);
        int cmdSimpleADSR(TTrack*, u32*);
        int cmdTranspose(TTrack*, u32*);
        int cmdCloseTrack(TTrack*, u32*);
        int cmdOutSwitch(TTrack*, u32*);
        int cmdUpdateSync(TTrack*, u32*);
        int cmdBusConnect(TTrack*, u32*);
        int cmdPauseStatus(TTrack*, u32*);
        int cmdVolumeMode(TTrack*, u32*);
        int cmdSetInterrupt(TTrack*, u32*);
        int cmdDisInterrupt(TTrack*, u32*);
        int cmdClrI(TTrack*, u32*);
        int cmdSetI(TTrack*, u32*);
        int cmdRetI(TTrack*, u32*);
        int cmdIntTimer(TTrack*, u32*);
        int cmdSyncCPU(TTrack*, u32*);
        int cmdFlushAll(TTrack*, u32*);
        int cmdFlushRelease(TTrack*, u32*);
        int cmdTimeBase(TTrack*, u32*);
        int cmdTempo(TTrack*, u32*);
        int cmdFinish(TTrack*, u32*);
        int cmdNop(TTrack*, u32*);
        int cmdPanPowSet(TTrack*, u32*);
        int cmdFIRSet(TTrack*, u32*);
        int cmdEXTSet(TTrack*, u32*);
        int cmdPanSwSet(TTrack*, u32*);
        int cmdOscRoute(TTrack*, u32*);
        int cmdVibDepth(TTrack*, u32*);
        int cmdVibDepthMidi(TTrack*, u32*);
        int cmdVibPitch(TTrack*, u32*);
        int cmdIIRSet(TTrack*, u32*);
        int cmdIIRCutOff(TTrack*, u32*);
        int cmdOscFull(TTrack*, u32*);
        int cmdCheckWave(TTrack*, u32*);
        int cmdPrintf(TTrack*, u32*);
        int Cmd_Process(TTrack*, u8, u16);
        int RegCmd_Process(TTrack*, int, int);
        int cmdSetParam(TTrack*, u8);
        int cmdWait(TTrack*, u8);
        int cmdNoteOff(TTrack*, u8);
        int cmdNoteOn(TTrack*, u8);
        bool conditionCheck(TTrack*, u8);
        int parseSeq(TTrack*);

        static CmdFunc sCmdPList[];
    };

    struct Arg_s { // Fake name
        u16 m00;
        u16 m02;
    };
    extern const Arg_s Arglist[0x40];
}

#endif /* JASSEQPARSER_H */
