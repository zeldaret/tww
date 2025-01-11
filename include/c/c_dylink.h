#ifndef C_C_DYLINK_H
#define C_C_DYLINK_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_phase.h"

struct cDylPhs {
    static int phase_01(void*);
    static int phase_02(s16*);
    static int phase_03(void*);
    static int Link(request_of_phase_process_class*, s16);
    static int Unlink(request_of_phase_process_class*, s16);

};

struct DynamicNameTableEntry {
    s16 mKey;
    const char* name;
};

int cDyl_InitAsyncIsDone();
void cDyl_InitAsync();

s32 cDyl_IsLinked(s16 i_procName);
s32 cDyl_Unlink(s16 i_procName);
s32 cDyl_LinkASync(s16 i_procName);

#endif /* C_C_DYLINK_H */
