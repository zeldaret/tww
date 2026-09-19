/**
 * dispatch.c
 * Description:
 */

#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/dispatch.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/utils/common/MWTrace.h"

u32 gTRKDispatchTableSize;

struct DispatchEntry {
	int (*fn)(TRKBuffer*);
};

extern int TRKDoUnsupported(TRKBuffer*);
extern int TRKDoConnect(TRKBuffer*);
extern int TRKDoDisconnect(TRKBuffer*);
extern int TRKDoReset(TRKBuffer*);
extern int TRKDoVersions(TRKBuffer*);
extern int TRKDoSupportMask(TRKBuffer*);
extern int TRKDoCPUType(TRKBuffer*);
extern int TRKDoReadMemory(TRKBuffer*);
extern int TRKDoWriteMemory(TRKBuffer*);
extern int TRKDoReadRegisters(TRKBuffer*);
extern int TRKDoWriteRegisters(TRKBuffer*);
extern int TRKDoFlushCache(TRKBuffer*);
extern int TRKDoContinue(TRKBuffer*);
extern int TRKDoStep(TRKBuffer*);
extern int TRKDoStop(TRKBuffer*);

struct DispatchEntry gTRKDispatchTable[33] = {
	{ &TRKDoUnsupported },   { &TRKDoConnect },        { &TRKDoDisconnect },
	{ &TRKDoReset },         { &TRKDoVersions },       { &TRKDoSupportMask },
	{ &TRKDoCPUType },       { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoReadMemory },     { &TRKDoWriteMemory },
	{ &TRKDoReadRegisters }, { &TRKDoWriteRegisters }, { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoFlushCache },     { &TRKDoUnsupported },
	{ &TRKDoContinue },      { &TRKDoStep },           { &TRKDoStop },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },
};

DSError TRKInitializeDispatcher() {
	gTRKDispatchTableSize = 32;
    return DS_NoError;
}

BOOL TRKDispatchMessage(TRKBuffer* buffer) {
    DSError error;
	u8 command;

	error = DS_DispatchError;
	TRKSetBufferPosition(buffer, 0);
	TRKReadBuffer1_ui8(buffer, &command);
	if (command < gTRKDispatchTableSize) {
		error = gTRKDispatchTable[command].fn(buffer);
	}
	return error;
}
