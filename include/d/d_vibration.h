#ifndef D_D_VIBRATION_H
#define D_D_VIBRATION_H

#include "SSystem/SComponent/c_xyz.h"

class dVibration_c {
public:
    dVibration_c();
    ~dVibration_c();

    int Run();
    bool StartShock(int i_strength, int, cXyz);
    bool StartQuake(u8 const*, int, int, cXyz);
    bool StartQuake(int, int, cXyz);
    int StopQuake(int);
    void Kill();
    bool CheckQuake();
    void setDefault();
    void Init();
    void Pause();
    void Remove();

    u8 temp[0x84];
};  // Size: 0x84

#endif /* D_D_VIBRATION_H */