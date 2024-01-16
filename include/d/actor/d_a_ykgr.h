#ifndef D_A_YKGR_H
#define D_A_YKGR_H

#include "f_op/f_op_actor.h"

class JPABaseEmitter;
class JPABaseParticle;

class daYkgr_c : public fopAc_ac_c {
public:
    static void stop() {
        if (m_emitter) {
            m_alpha_flag = 0;
        }
    };
    
    static JPABaseEmitter* m_emitter;
    static u8 m_alpha_flag;
    
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
    void hide() {}
    void init() {}
    void setAimRate(float) {}
    void setAlpha(unsigned char) {}
    void set_mtx() {}
    void show() {}
    void start() {}

    void getPosRate();

public:
    /* Place member variables here */
};

class dPa_YkgrPcallBack {
public:
    void draw(JPABaseEmitter*, JPABaseParticle*);
    void setParam(float);
};

#endif /* D_A_YKGR_H */
