#ifndef D_A_YKGR_H
#define D_A_YKGR_H

#include "f_op/f_op_actor.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "f_op/f_op_camera_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_hostIO.h"

struct dPath;
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
    void hide() {
        if (m_emitter == NULL) {
            return;
        }
        m_emitter->stopDrawParticle();
        return;
    }
    void setAimRate(float) {}
    void setAlpha(unsigned char alpha) { m_alpha = alpha; }
    inline void set_mtx();
    void show() {
        if (m_emitter == NULL) {
            return;
        }
        m_emitter->playDrawParticle();
        return;
    }
    void start() {
        if (m_emitter != NULL) {
            m_alpha_flag = 1;
        }
    }

    f32 getPosRate();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ Mtx mMtx;
    /* 0x2C8 */ u8 m2C8[0x2CC - 0x2C8];
    /* 0x2CC */ f32 m2CC;
    /* 0x2D0 */ f32 m2D0;
}; // size = 0x2D4

class dPa_YkgrPcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_YkgrPcallBack() {
        m04 = 0.5f;
        m08 = 0.0f;
        m0C = 0.0f;
        m10 = 0.0f;
        m14 = 0.5f;
        m18 = 0.0f;
        m1C = true;
    }
    ~dPa_YkgrPcallBack() {}

    void draw(JPABaseEmitter*, JPABaseParticle*);
    void setParam(float);

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ s8 m1C;
}; // size = 0x20

#endif /* D_A_YKGR_H */
