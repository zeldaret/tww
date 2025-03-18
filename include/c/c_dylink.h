#ifndef C_C_DYLINK_H
#define C_C_DYLINK_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_phase.h"

struct cDylPhs {
    static cPhs_State phase_01(void*);
    static cPhs_State phase_02(s16*);
    static cPhs_State phase_03(void*);
    static cPhs_State Link(request_of_phase_process_class*, s16);
    static BOOL Unlink(request_of_phase_process_class*, s16);

};

struct DynamicNameTableEntry {
    s16 mKey;
    const char* name;
};

BOOL cDyl_InitAsyncIsDone();
void cDyl_InitAsync();

BOOL cDyl_IsLinked(s16 i_procName);
BOOL cDyl_Unlink(s16 i_procName);
cPhs_State cDyl_LinkASync(s16 i_procName);

#endif /* C_C_DYLINK_H */
