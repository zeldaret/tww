//
// __ppc_eabi_init
//

#include "global.h"
#include "dolphin/base/PPCArch.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Forward References:
//

void __init_user();
void __init_cpp();
void _ExitProcess();

//
// External References:
//

typedef void (*voidfunctionptr)(); // pointer to function returning void
extern voidfunctionptr _ctors[];

void __init_user(void) {
    __init_cpp();
}

#pragma peephole off
void __init_cpp(void) {
    /**
     *	call static initializers
     */
    voidfunctionptr* constructor;
    for (constructor = _ctors; *constructor; constructor++) {
        (*constructor)();
    }
}
#pragma peephole reset

void _ExitProcess(void) {
    PPCHalt();
}

#ifdef __cplusplus
}
#endif