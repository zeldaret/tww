#ifndef F_AP_GAME_H
#define F_AP_GAME_H

#include "JSystem/JUtility/TColor.h"

void fapGm_After();
void fapGm_Create();
void fapGm_Execute();

class fapGm_HIO_c {
public:
    /* 80018944 */ fapGm_HIO_c();
    /* 80018AE0 */ virtual ~fapGm_HIO_c();

    u32 pad[0x58];
};  // Size: 0x40

extern fapGm_HIO_c g_HIO;

#endif /* F_AP_GAME_H */
