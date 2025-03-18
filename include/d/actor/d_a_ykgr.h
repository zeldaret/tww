#ifndef D_A_YKGR_H
#define D_A_YKGR_H

#include "f_op/f_op_actor.h"

class dPath;
class JPABaseEmitter;
class JPABaseParticle;

class daYkgr_c : public fopAc_ac_c {
public:
    static void init() {
        m_emitter = NULL;
        m_flag = 0;
        m_alpha_flag = 1;
        m_alpha = 0xFF;
    }

    static void stop() {
        if (m_emitter) {
            m_alpha_flag = 0;
        }
    };
    
    static u8 m_flag;
    static u8 m_alpha_flag;
    static u8 m_alpha;
    static f32 m_aim_rate;
    static dPath* m_path;
    static JPABaseEmitter* m_emitter;

    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void hide() {}
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
