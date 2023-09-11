#ifndef M_DO_AUDIO_H
#define M_DO_AUDIO_H

void mDoAud_setSceneName(const char*, s32, s32);
void mDoAud_Execute();

class JKRSolidHeap;
extern JKRSolidHeap* g_mDoAud_audioHeap;

#endif /* M_DO_AUDIO_H */
