#ifndef DSPTASK_H
#define DSPTASK_H

#include "dolphin/dsp.h"

void DspHandShake(void*);
void DspBoot(DSPCallback);
int DSPSendCommands2(u32*, u32, void (*)(u16));
void DspInitWork();
int DspStartWork(u32, void (*)(u16));
void DspFinishWork(u16);

#endif /* DSPTASK_H */
