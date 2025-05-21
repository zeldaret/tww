// daBomb_c::createHeap's asserts tell us that function is inside d_a_bomb3.inc instead of d_a_bomb.cpp.
// Furthermore, the symbol maps show that d_a_bomb.o's first .text section is 0 bytes large, with everything going in
// its second .text section, which suggests that d_a_bomb.cpp is empty except including d_a_bomb3.inc.

#include "d/actor/d_a_bomb.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_sea.h"
#include "d/d_kankyo_wether.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "d/res/res_vbakh.h"

#include "weak_data_1811.h" // IWYU pragma: keep

namespace {
    enum AttrSt_e {
        ATTR_STATE_0 = 0x00,
        ATTR_STATE_1 = 0x01,
        ATTR_STATE_2 = 0x02,
        ATTR_STATE_4 = 0x04,
        ATTR_STATE_8 = 0x08,
        ATTR_STATE_10 = 0x10,
        ATTR_STATE_20 = 0x20,
        ATTR_STATE_80 = 0x80,
        ATTR_STATE_100 = 0x100,
        ATTR_STATE_200 = 0x200,

        ATTR_STATE_1C = ATTR_STATE_10 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_21 = ATTR_STATE_20 | ATTR_STATE_1,
        ATTR_STATE_9C = ATTR_STATE_80 | ATTR_STATE_10 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_A1 = ATTR_STATE_80 | ATTR_STATE_20 | ATTR_STATE_1,
        ATTR_STATE_20C = ATTR_STATE_200 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_300 = ATTR_STATE_200 | ATTR_STATE_100
    };

    const AttrSt_e L_attrState[] = {
        ATTR_STATE_A1,
        ATTR_STATE_1C,
        ATTR_STATE_9C,
        ATTR_STATE_9C,
        ATTR_STATE_20C,
        ATTR_STATE_300,
        ATTR_STATE_200,
        ATTR_STATE_2,
        ATTR_STATE_21,
        ATTR_STATE_0,
    };
    
    bool chk_attrState(const daBomb_c* i_this, AttrSt_e mask) {
        return cLib_checkBit(L_attrState[i_this->prm_get_state()], mask); // register order is wrong in the and
    }
}

const daBomb_c::Attr_c daBomb_c::m_attrType[] = {
    {"Link", 0x8E0},
    {"VbakH", 0x8000},
    {"Link", 0x8E0},
};

/* 800D9364-800D977C       .text executeAfter__25daBomb_fuseSmokeEcallBackFP14JPABaseEmitter */
void daBomb_fuseSmokeEcallBack::executeAfter(JPABaseEmitter* emitter) {
    JGeometry::TVec3<f32> vec1;
    vec1.set(*field_0x0C);
    JGeometry::TVec3<f32> vec2;
    vec2.set(*mpPos);
    emitter->setGlobalTranslation(vec2);
    f32 temp = mpPos->abs(*field_0x0C);
    s16 temp2 = (20.0f - temp) * 0.5f + 10.0f;
    if(temp2 < 10) {
        temp2 = 10;
    }

    emitter->setLifeTime(temp2);
    
    JGeometry::TVec3<f32> vec3;
    vec3.z = 0.5f * (vec2.x - vec1.x);
    vec3.y = 0.5f * (vec2.y - vec1.y);
    vec3.x = 0.5f * (vec2.z - vec1.z);
    
    JGeometry::TVec3<f32> vec4;
    vec4.x = 0.5f * (vec1.x - field_0x10->x);
    vec4.y = 0.5f * (vec1.y - field_0x10->y);
    vec4.z = 0.5f * (vec1.z - field_0x10->z);
    
    f32 temp5 = mpPos->abs(*field_0x0C);

    if(temp5 * 0.1f > 1.0f) {
        f32 step = 1.0f / (temp5 * 0.1f);
        s16 temp7 = step * (field_0x04 - temp2);
        s16 temp8 = temp2 + temp7;

        for(f32 i = step; i < 1.0f; i += step, temp8 += temp7) {
            JGeometry::TVec3<f32> vec5;
            vec5.cubic<f32>(vec1, vec2, vec3, vec4, i);
            
            emitter->setLifeTime(temp8);
            JPABaseParticle* particle = emitter->createParticle();
            if(particle) {
                particle->setOffsetPosition(vec5);
            }
        }
    }

    field_0x04 = temp2;
}

/* 800D977C-800D97C4       .text execute__26daBomb_fuseSparksEcallBackFP14JPABaseEmitter */
void daBomb_fuseSparksEcallBack::execute(JPABaseEmitter* emitter) {
    JGeometry::TVec3<f32> pos(*mpPos);
    emitter->setGlobalTranslation(pos);
    
    JSUPtrLink* link = emitter->getParticleList()->getFirstLink();
    while(link != 0) {
        JSUPtrLink* next = link->getNext();

        JPABaseParticle* ptcl = (JPABaseParticle*)link->getObjectPtr();
        ptcl->setOffsetPosition(pos);

        link = next;
    }
}

/* 800D97C4-800D9950       .text draw_norm__8daBomb_cFv */
void daBomb_c::draw_norm() {
    J3DAnmTevRegKey* bombBrk = daPy_getPlayerLinkActorClass()->getBombBrk();
    s16 end = bombBrk->getFrameMax();
    f32 frame = end - mRestTime + 2;
    if(frame < 0.0f) {
        frame = 0.0f;
    }
    else if(frame >= end) {
        frame = end - 0.001f;
    }
    bombBrk->setFrame(frame);

    end = mBck0.getBckAnm()->getFrameMax();
    frame = end - mRestTime;
    if(frame < 0.0f) {
        frame = 0.0f;
    }
    else if(frame >= end) {
        frame = end - 0.001f;
    }

    mBck0.entry(mpModel->getModelData(), frame);
    dComIfGd_setListP1();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
}

/* 800D9950-800D9A48       .text draw_nut__8daBomb_cFv */
void daBomb_c::draw_nut() {
    if(chk_state(STATE_5) || chk_state(STATE_6)) {
        mBck0.entry(mpModel->getModelData());
        mBrk0.entry(mpModel->getModelData());
    }
    else {
        mBck1.entry(mpModel->getModelData());
        mBrk1.entry(mpModel->getModelData());
    }

    dComIfGd_setListP1();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
}

/* 800D9A48-800D9BC0       .text draw__8daBomb_cFv */
BOOL daBomb_c::draw() {
    if(chk_attrState(this, ATTR_STATE_20)) {
        return true;
    }
    if(chk_state(STATE_4) && field_0x77D == 1) {
        return true;
    }

    if(mDoLib_clipper::clip(j3dSys.getViewMtx(), current.pos, 80.0f)) {
        return true;
    }
    if(field_0x7C8 > 0) {
        return true;
    }
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    if(mType == 1) {
        draw_nut();
    }
    else {
        draw_norm();
    }

    if(fopAcM_GetModel(this) == 0 && mAcch.GetGroundH() != -G_CM3D_F_INF) {
        cM3dGPla* pNormal = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
        if(pNormal) {
            dComIfGd_setSimpleShadow(&current.pos, mAcch.GetGroundH(), 25.0f, pNormal->GetNP());
        }
    }

    return true;
}

/* 800D9BC0-800D9BE0       .text daBomb_Draw__FP8daBomb_c */
static BOOL daBomb_Draw(daBomb_c* i_this) {
    return i_this->draw();
}

/* 800D9BE0-800D9C8C       .text checkExplodeCc_norm__8daBomb_cFv */
bool daBomb_c::checkExplodeCc_norm() {
    bool explode = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(obj->ChkAtType(AT_TYPE_BOMB)) {
                explode = true;
            }
            else if(!obj->ChkAtType(AT_TYPE_WIND)) {
                explode = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(explode) {
        explode = procExplode_init();
    }
    else {
        explode = false;
    }

    return explode;
}

/* 800D9C8C-800D9DBC       .text checkExplodeCc_nut__8daBomb_cFv */
bool daBomb_c::checkExplodeCc_nut() {
    bool explode = false;
    bool hit = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(obj->ChkAtType(AT_TYPE_BOMB)) {
                explode = true;
            }
            else if(!obj->ChkAtType(AT_TYPE_WIND)) {
                hit = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(mSph.ChkCoHit()) {
        if(field_0x780) {
            hit = true;
        }

        mSph.ClrCoHit();
    }

    bool ret = false;
    if(explode) {
        ret = procExplode_init();
    }
    else if(hit) {
        change_state(STATE_1);
        setFuseEffect();
        if(30 < mRestTime) {
            mRestTime = 30;
            mBck1.setFrame(105.0f);
            mBrk1.setFrame(105.0f);
        }
    }

    return ret;
}

/* 800D9DBC-800D9E80       .text checkExplodeCc_cannon__8daBomb_cFv */
bool daBomb_c::checkExplodeCc_cannon() {
    bool explode = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(!obj->ChkAtType(AT_TYPE_WIND)) {
                explode = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(mSph.ChkCoHit()) {
        explode = true;
        mSph.ClrCoHit();
    }

    if(explode) {
        explode = procExplode_init();
    }
    else {
        explode = false;
    }

    return explode;
}

/* 800D9E80-800D9F30       .text checkExplodeCc__8daBomb_cFv */
bool daBomb_c::checkExplodeCc() {
    if(0 < mRestTime) {
        typedef bool(daBomb_c::*checkFunc)();
        static checkFunc proc[] = {
            &daBomb_c::checkExplodeCc_norm,
            &daBomb_c::checkExplodeCc_nut,
            &daBomb_c::checkExplodeCc_cannon
        };

        return (this->*proc[mType])();
    }

    return false;
}

/* 800D9F30-800D9FAC       .text checkExplodeTimer__8daBomb_cFv */
bool daBomb_c::checkExplodeTimer() {
    bool explode = false;
    if(!chk_attrState(this, ATTR_STATE_200)) {
        if(0 < mRestTime) {
            if(--mRestTime == 0) {
                explode = procExplode_init();
            }
        }
    }

    return explode;
}

/* 800D9FAC-800DA004       .text checkExplode__8daBomb_cFv */
bool daBomb_c::checkExplode() {
    return checkExplodeCc() || checkExplodeTimer();
}

/* 800DA004-800DA098       .text checkExplodeBg_norm__8daBomb_cFv */
bool daBomb_c::checkExplodeBg_norm() {
    bool sink = chk_water_sink();
    bool land = chk_water_land();
    bool burn = chk_lava_hit();

    if(sink) {
        field_0x781 = true;
    }
    if(land) {
        eff_water_splash();
    }
    if(burn) {
        return procExplode_init();
    }

    return false;
}

/* 800DA098-800DA1A4       .text checkExplodeBg_nut__8daBomb_cFv */
bool daBomb_c::checkExplodeBg_nut() {
    bool sink = chk_water_in();
    bool burn = chk_lava_hit();

    bool hit = mAcch.ChkWallHit() || mAcch.ChkGroundHit() || mAcch.ChkRoofHit();

    bool ret = false;
    if(burn) {
        ret = procExplode_init();
    }
    else {
        if(sink) {
            makeWaterEffect();
            field_0x781 = true;
        }
        else if(hit && field_0x780) {
            change_state(STATE_1);
            setFuseEffect();
            if(30 < mRestTime) {
                mRestTime = 30;
                mBck1.setFrame(105.0f);
                mBrk1.setFrame(105.0f);
            }
        }
    }

    return ret;
}

/* 800DA1A4-800DA284       .text checkExplodeBg_cannon__8daBomb_cFv */
bool daBomb_c::checkExplodeBg_cannon() {
    bool sink = chk_water_in();
    bool burn = chk_lava_hit();

    bool hit = mAcch.ChkWallHit() || mAcch.ChkGroundHit() || mAcch.ChkRoofHit();

    bool dead = chk_dead_zone();
    bool ret = false;
    if(burn || hit) {
        ret = procExplode_init();
    }
    else {
        if(sink) {
            makeWaterEffect();
            field_0x781 = true;
        }
        else if(dead) {
            field_0x781 = true;
        }
    }
    
    return ret;
}

/* 800DA284-800DA320       .text checkExplodeBg__8daBomb_cFv */
bool daBomb_c::checkExplodeBg() {
    typedef bool(daBomb_c::*checkFunc)();
    static checkFunc proc[] = {
        &daBomb_c::checkExplodeBg_norm,
        &daBomb_c::checkExplodeBg_nut,
        &daBomb_c::checkExplodeBg_cannon
    };

    return (this->*proc[mType])();
}

/* 800DA320-800DA3A0       .text water_tention__8daBomb_cFv */
void daBomb_c::water_tention() {
    if(chk_water_in()) {
        if(field_0x558 != -G_CM3D_F_INF && field_0x55C != -G_CM3D_F_INF) {
            f32 temp = field_0x558 - field_0x55C;
            current.pos.y += temp < 0.0f ? 0.8f * temp : 0.2f * temp;
        }
    }
}

/* 800DA3A0-800DA520       .text posMoveF__8daBomb_cFv */
void daBomb_c::posMoveF() {
    cM3dGPla* tri;
    bool temp = mNoGravityTime > 0;
    f32 origGravity;
    if(temp) {
        origGravity = gravity;
        gravity = 0.0f;
    }

    if(mType == 0 && chk_water_in()) {
        speed.y *= 0.9f;
        speedF *= 0.9f;
    }

    if(!chk_state(STATE_5) && !chk_state(STATE_6) && field_0x6F3 != 1) {
        water_tention();
        tri = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);

        if(mWindVec.abs2() > 0.01f) {
            f32 no_grade_cos;
            cXyz* norm;
            f32 friction;
            if(tri) {
                norm = tri->GetNP();
                friction = 0.06f;
                no_grade_cos = cM_scos(0xA4F);
            }
            else {
                norm = NULL;
                friction = 0.0f;
                no_grade_cos = 0.0f;
            }

            daObj::posMoveF_grade(this, mStts.GetCCMoveP(), &mWindVec, 0.002f, 0.0005f, norm, friction, no_grade_cos, NULL);
        }
        else {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
    }
    
    if(temp) {
        gravity = origGravity;
        mNoGravityTime--;
    }
}

/* 800DA520-800DA574       .text bgCrrPos__8daBomb_cFv */
void daBomb_c::bgCrrPos() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    bgCrrPos_lava();
    bgCrrPos_water();
    setRoomInfo();
}

/* 800DA574-800DA5E0       .text bgCrrPos_lava__8daBomb_cFv */
void daBomb_c::bgCrrPos_lava() {
    cXyz temp(current.pos.x, old.pos.y + 1.0f, current.pos.z);
    mGndChk.SetPos(&temp);

    field_0x554 = dComIfG_Bgsp()->GroundCross(&mGndChk);
}

/* 800DA5E0-800DA700       .text bgCrrPos_water__8daBomb_cFv */
void daBomb_c::bgCrrPos_water() {
    f32 f31 = mAcch.m_wtr.GetHeight();
    bool r31 = daSea_ChkArea(current.pos.x, current.pos.z);
    f32 f1 = daSea_calcWave(current.pos.x, current.pos.z);
    bool r4 = mAcch.ChkWaterIn();
    bool r3 = r31 && current.pos.y < f1;
    bool r5 = false;
    field_0x55C = field_0x558;
    if (r4 && r3) {
        if (f31 > f1) {
            r3 = 0;
        } else {
            r4 = 0;
        }
    }
    if (r4) {
        field_0x558 = f31;
        r5 = true;
        field_0x562 = 0;
    } else if (r3) {
        field_0x558 = f1;
        r5 = true;
        field_0x562 = 1;
    } else {
        field_0x558 = -G_CM3D_F_INF;
        field_0x562 = 0;
    }
    field_0x560 = r5 && !mbWaterIn;
    mbWaterIn = r5;
}

/* 800DA700-800DA708       .text chk_water_land__8daBomb_cFv */
bool daBomb_c::chk_water_land() {
    return field_0x560;
}

/* 800DA708-800DA710       .text chk_water_in__8daBomb_cFv */
bool daBomb_c::chk_water_in() {
    return mbWaterIn;
}

/* 800DA710-800DA768       .text chk_water_sink__8daBomb_cFv */
bool daBomb_c::chk_water_sink() {
    bool water = chk_water_in();

    return water && field_0x558 - current.pos.y > 30.0f;
}

/* 800DA768-800DA794       .text chk_lava_hit__8daBomb_cFv */
bool daBomb_c::chk_lava_hit() {
    if(field_0x554 == -G_CM3D_F_INF) {
        return false;
    }

    return current.pos.y < field_0x554;
}

/* 800DA794-800DA7CC       .text chk_dead_zone__8daBomb_cFv */
bool daBomb_c::chk_dead_zone() {
    return mAcch.GetGroundH() == -G_CM3D_F_INF && field_0x558 == -G_CM3D_F_INF && field_0x554 == -G_CM3D_F_INF;
}

/* 800DA7CC-800DA8C8       .text bound__8daBomb_cFf */
void daBomb_c::bound(f32 param_1) {
    if(mAcch.ChkWallHit()) {
        speedF *= 0.8f;
        current.angle.y = (mCir.GetWallAngleY() * 2) - (current.angle.y + 0x8000);
    }

    if(mAcch.ChkGroundLanding()) {
        daObj::make_land_effect(this, &mAcch.m_gnd, 0.6f);
        param_1 *= -0.6f;
        if(param_1 < 19.5f) {
            field_0x780 = 0;
        }
        else {
            speedF *= 0.9f;
            if(param_1 > 13.0f) {
                speed.y = 13.0f;
            }
            else {
                speed.y = param_1;
            }
        }
    }
    else {
        if(mAcch.ChkGroundHit()) {
            cLib_addCalc(&speedF, 0.0f, 0.5f, 5.0f, 1.0f);
        }
    }
}

/* 800DA8C8-800DA9DC       .text set_real_shadow_flag__8daBomb_cFv */
void daBomb_c::set_real_shadow_flag() {
    bool r31 = chk_state(STATE_2);
    bool r3 = chk_state(STATE_3);
    bool r30 = false;
    if (field_0x7C8 <= 1 && (r31 || r3)) {
        if (model) {
            r30 = true;
        } else if (r3) {
            r30 = true;
        } else if (field_0x7C8 == 1) {
            r30 = true;
        } else {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            if (player->getGrabActorID() == fopAcM_GetID(this) && player->getGrabUpStart()) {
                r30 = true;
            }
        }
    }
    if (field_0x7C8 > 0) {
        field_0x7C8--;
    }
    model = r30 ? mpModel : NULL;
}

/* 800DA9DC-800DAA60       .text setRoomInfo__8daBomb_cFv */
void daBomb_c::setRoomInfo() {
    s32 roomNo;
    if(mAcch.GetGroundH() != -G_CM3D_F_INF) {
        roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    }
    else {
        roomNo = dComIfGp_roomControl_getStayNo();
    }

    tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
    current.roomNo = roomNo;
}

/* 800DAA60-800DAB28       .text makeFireEffect__8daBomb_cFR4cXyzR5csXyz */
void daBomb_c::makeFireEffect(cXyz& pos, csXyz& rotation) {
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    cXyz scale;
    scale.setall(0.3f);
    csXyz rot;
    rot.x = -cam->mAngle.x;
    rot.y = cam->mAngle.y + 0x8000;
    rot.z = 0;

    rotation.x = rotation.x + 0x4000;
    rotation.z = rotation.z;
    dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &pos, &rotation, &scale);

    dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
}

/* 800DAB28-800DAC40       .text makeWaterEffect__8daBomb_cFv */
void daBomb_c::makeWaterEffect() {
    if(field_0x77D == 0) {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_WATER, 0);
        fopKyM_createWpillar(&current.pos, 1.0f, 1.0f, 1);
        mSph.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
        mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
        mSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
        mSph.SetR(200.0f);
        mSph.SetC(current.pos);
        if(mMassCounter != g_Counter.mCounter0) {
            dComIfG_Ccsp()->Set(&mSph);
            //using inline breaks match
            //dComIfG_Ccsp()->SetMass(&mSph, 3);
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
            mMassCounter = g_Counter.mCounter0;
            field_0x782 = 1;
        }

        field_0x77D = 1;
    }
}

/* 800DAC40-800DAD6C       .text setFuseEffect__8daBomb_cFv */
void daBomb_c::setFuseEffect() {
    if(field_0x77E == 0) {
        field_0x77E = 1;
        mFusePos.x = current.pos.x;
        mFusePos.y = current.pos.y + 60.0f;
        mFusePos.z = current.pos.z;
        mFusePos2 = mFusePos;
        mFusePos3 = mFusePos;

        dComIfGp_particle_setP1(dPa_name::ID_COMMON_FUSE_SPARKS, &mFusePos, NULL, &scale, 0xFF, &mSparks);
        dComIfGp_particle_setToonP1(dPa_name::ID_COMMON_2012, &mFusePos, NULL, &scale, 0xDC, &mSmoke);
        mSmoke.field_0x0C = &mFusePos2;
        mSmoke.field_0x10 = &mFusePos3;
        mSmoke.field_0x04 = 0x14;
    }
}

/* 800DAD6C-800DAE54       .text eff_explode_normal__8daBomb_cFPC5csXyz */
void daBomb_c::eff_explode_normal(const csXyz* rotation) {
    dComIfGp_particle_setP1(dPa_name::ID_COMMON_LIGHT_FLASH, &current.pos, rotation, &scale);
    dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CLOUD, &current.pos, NULL, &scale);
    dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &current.pos, NULL, &scale);
    dComIfGp_particle_setToonP1(dPa_name::ID_COMMON_SMOKE_DEBRIS, &current.pos, NULL, &scale);
}

/* 800DAE54-800DAF94       .text eff_explode_cheap__8daBomb_cFPC5csXyz */
void daBomb_c::eff_explode_cheap(const csXyz* rotation) {
    JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_LIGHT_FLASH, &current.pos, rotation, &scale);
    if(emitter) {
        emitter->setLifeTime(0xC);
        JGeometry::TVec3<f32> vec(0.5f, 0.67f, 1.0f);
        emitter->setGlobalParticleScale(vec);
    }

    dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_232A, &current.pos, NULL, &scale);
    emitter = dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &current.pos, NULL, &scale);
    if(emitter) {
        emitter->setLifeTime(0x46);
    }
    
    emitter = dComIfGp_particle_setToonP1(dPa_name::ID_COMMON_SMOKE_DEBRIS, &current.pos, NULL, &scale);
    if(emitter) {
        emitter->setLifeTime(0x46);
        emitter->setAwayFromAxisSpeed(25.0f);
        emitter->setDirectionalSpeed(35.0f);
    }
}

/* 800DAF94-800DB024       .text eff_explode__8daBomb_cFv */
void daBomb_c::eff_explode() {
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    csXyz rot;
    rot.x = -cam->mAngle.x;
    rot.y = cam->mAngle.y + 0x8000;
    rot.z = 0;

    if(prm_get_cheapEff()) {
        eff_explode_cheap(&rot);
    }
    else {
        eff_explode_normal(&rot);
    }
}

/* 800DB024-800DB630       .text procExplode_init__8daBomb_cFv */
BOOL daBomb_c::procExplode_init() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.ForceLockOff(fopAcM_GetID(this));

    BOOL temp;
    if(chk_state(STATE_8)) {
        f32 temp2;
        temp = fopAcM_getWaterY(&current.pos, &temp2);
        if(temp) {
            cXyz temp3;
            dBgS_ObjGndChk gndCheck;
            temp3.set(current.pos.x, current.pos.y + 1.0f, current.pos.z);
            gndCheck.SetPos(&temp3);

            if(dComIfG_Bgsp()->GroundCross(&gndCheck) > temp2 || current.pos.y > temp2 + 50.0f) {
                temp = FALSE;
            }
        }
    }
    else {
        temp = FALSE;
    }

    if(!temp) {
        eff_explode();
    }
    else {
        fopKyM_createWpillar(&current.pos, 1.0f, 1.0f, 1);
    }

    if(mSmoke.mpEmitter) {
        mSmoke.mpEmitter->setEmitterCallBackPtr(NULL);
        mSmoke.mpEmitter->becomeInvalidEmitter();
    }
    mSmoke.mpEmitter = NULL;

    if(mSparks.mpEmitter) {
        mSparks.mpEmitter->setEmitterCallBackPtr(NULL);
        mSparks.mpEmitter->becomeInvalidEmitter();
    }
    mSparks.mpEmitter = NULL;

    mPntLight.mPos = current.pos;
    mPntLight.mPos.y += 100.0f;
    mPntLight.mColor.r = 200;
    mPntLight.mColor.g = 200;
    mPntLight.mColor.b = 160;
    mPntLight.mPower = 600.0f;
    mPntLight.mFluctuation = 100.0f;
    dKy_efplight_set(&mPntLight);

    mPntWind.mPos = current.pos;
    mPntWind.mDir.x = 0.0f;
    mPntWind.mDir.y = 1.0f;
    mPntWind.mDir.z = 0.0f;
    mPntWind.mRadius = 500.0f;
    mPntWind.field_0x20 = 0.0f;
    mPntWind.mStrength = 0.5f;
    dKyw_pntwind_set(&mPntWind);

    field_0x774 = 0;
    field_0x778 = 0.0f;
    mFunc = &daBomb_c::procExplode;
    speedF = 0.0f;
    speed = cXyz::Zero;
    gravity = 0.0f;

    if(!chk_state(STATE_8)) {
        change_state(STATE_0);
    }

    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

    if(field_0x6F0) {
        daPy_getPlayerLinkActorClass()->decrementBombCnt();
        field_0x6F0 = 0;
    }

    mSph.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
    mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
    mSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
    mSph.SetR(200.0f);
    mSph.SetC(current.pos);
    if(mMassCounter != g_Counter.mCounter0) {
        dComIfG_Ccsp()->Set(&mSph);
        //using inline breaks match
        //dComIfG_Ccsp()->SetMass(&mSph, 3);
        g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
        field_0x782 = 1;
        mMassCounter = g_Counter.mCounter0;
    }

    if(temp) {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_WATER, 0);
    }
    else {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_EXPLODE, 0);
    }

    fopAcM_cancelCarryNow(this);
    dKy_Sound_set(current.pos, 0xFF, fopAcM_GetID(this), 0xA);

    mRestTime = 0;
    field_0x6FE = 2;
    dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));

    se_cannon_fly_stop();

    return true;
}

/* 800DB630-800DB880       .text procExplode__8daBomb_cFv */
bool daBomb_c::procExplode() {
    camera_class* camera = dComIfGp_getCamera(0);
    f32 temp2 = 0.0f;

    mPntLight.mPower = field_0x778 * 1500.0f;
    mPntWind.mStrength = field_0x778;
    f32 temp = current.pos.abs(camera->mLookat.mEye);

    if(temp < 1500.0f) {
        temp2 = 1.0f - (temp / 1500.0f);
    }

    dKy_actor_addcol_amb_set(200, 180, 100, field_0x778 * temp2);
    dKy_bg_addcol_amb_set(180, 160, 60, field_0x778 * temp2);
    dKy_bg_addcol_dif_set(255, 225, 120, field_0x778 * temp2);

    switch(field_0x774) {
    case 0:
        cLib_addCalc(&field_0x778, 1.0f, 0.5f, 0.4f, 0.01f);
        if(field_0x778 >= 0.99f) {
            field_0x774 += 1;
        }

        break;
    case 1:
        cLib_addCalc(&field_0x778, 0.0f, 0.05f, 0.04f, 0.001f);
        if(field_0x778 <= 0.01f) {
            field_0x774 += 1;
        }

        break;
    }

    if(field_0x6FE) {
        field_0x6FE -= 1;
        mSph.SetC(current.pos);
        if(mMassCounter != g_Counter.mCounter0) {
            dComIfG_Ccsp()->Set(&mSph);
            //using inline breaks match
            //dComIfG_Ccsp()->SetMass(&mSph, 3);
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
            mMassCounter = g_Counter.mCounter0;
            field_0x782 = 1;
        }
    }
    else {
        if(1 < field_0x774) {
            field_0x781 = 1;
        }
    }

    return true;
}

/* 800DB880-800DB92C       .text procCarry_init__8daBomb_cFv */
bool daBomb_c::procCarry_init() {
    if(chk_attrState(this, ATTR_STATE_100)) {
        setFuseEffect();
    }

    mFunc = &daBomb_c::procCarry;
    change_state(STATE_2);
    speedF = 0.0f;
    speed.set(cXyz::Zero);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);

    return true;
}

/* 800DB92C-800DB9DC       .text procCarry__8daBomb_cFv */
bool daBomb_c::procCarry() {
    if(!fopAcM_checkCarryNow(this)) {
        if(speedF > 0.0f) {
            field_0x780 = 1;
        }

        procWait_init();
        return procWait();
    }
    else {
        if(checkExplode()) {
            return true;
        }
        else {
            cXyz curPos(current.pos);
            bgCrrPos();
            current.pos.set(curPos);

            return true;
        }
    }
}

/* 800DB9DC-800DBA50       .text procWait_init__8daBomb_cFv */
bool daBomb_c::procWait_init() {
    mFunc = &daBomb_c::procWait;
    if(chk_attrState(this, ATTR_STATE_80)) {
        change_state(STATE_1);
    }

    mSph.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    return true;
}

/* 800DBA50-800DBBA0       .text procWait__8daBomb_cFv */
bool daBomb_c::procWait() {
    if(checkExplode()) {
        return true;
    }
    else {
        if(fopAcM_checkCarryNow(this)) {
            return procCarry_init();
        }
        else {
            posMoveF();
            f32 y_vel = speed.y;
            bgCrrPos();
            bool temp = false;
            if(checkExplodeBg()) {
                temp = true;
            }
            else {
                if(chk_state(STATE_4)) {
                    if(waitState_cannon()) {
                        temp = true;
                    }
                }
                else {
                    if(chk_state(STATE_7)) {
                        waitState_bomtyu();
                    }
                }
            }

            if(!temp && !field_0x781) {
                bound(y_vel);
                if((mAcch.ChkGroundHit() || chk_state(STATE_5)) && !mAcch.ChkGroundLanding()) {
                    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
                }
                else {
                    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
                }
            }

            return true;
        }
    }
}

/* 800DBBA0-800DBBC4       .text waitState_cannon__8daBomb_cFv */
bool daBomb_c::waitState_cannon() {
    se_cannon_fly_set();

    return false;
}

/* 800DBBC4-800DBC4C       .text waitState_bomtyu__8daBomb_cFv */
void daBomb_c::waitState_bomtyu() {
    cLib_chaseF(&scale.x, 1.0f, 0.05f);
    cLib_chaseF(&scale.y, 1.0f, 0.05f);
    cLib_chaseF(&scale.z, 1.0f, 0.05f);
    if(mBombFire) {
        setFuseEffect();
        mBombFire = 0;
        field_0x6F4 = 1;
        change_state(STATE_1);
    }
}

// assuming this was here and got stripped, given the leftover ptmf in .data and the other proc/proc_init pairs
bool daBomb_c::procSink_init() {
    mFunc = &daBomb_c::procSink;

    return true;
}

/* 800DBC4C-800DBC5C       .text procSink__8daBomb_cFv */
bool daBomb_c::procSink() {
    field_0x781 = 1;

    return true;
}

/* 800DBC5C-800DBF24       .text execute__8daBomb_cFv */
BOOL daBomb_c::execute() {
    static cXyz fuse_offset(0.0f, 60.0f, 5.0f);

    if(chk_state(STATE_4) && !field_0x77C) {
        field_0x77C = 1;
        cXyz pos(current.pos);
        pos.y += 20.0f;
        makeFireEffect(pos, shape_angle);
    }
    
    set_wind_vec();
    if(mFunc) {
        (this->*mFunc)();
    }

    if(field_0x781) {
        fopAcM_delete(this);
    }
    else {
        set_real_shadow_flag();
        if(mType == 1) {
            anm_play_nut();
        }

        mStts.Move();
        attention_info.position.x = current.pos.x;
        attention_info.position.y = current.pos.y + 50.0f;
        attention_info.position.z = current.pos.z;
        eyePos = attention_info.position;
        if(!chk_attrState(this, ATTR_STATE_20)) {
            set_mtx();
            mFusePos3 = mFusePos2;
            mFusePos2 = mFusePos;
            mDoMtx_stack_c::multVec(&fuse_offset, &mFusePos);
            cXyz pos;
            pos.x = current.pos.x;
            pos.y = current.pos.y + 30.0f;
            pos.z = current.pos.z;
            mSph.SetC(pos);
            mSph.SetR(scale.x * 30.0f);
            if(mMassCounter != g_Counter.mCounter0) {
                dComIfG_Ccsp()->Set(&mSph);
                //using inline breaks match
                //dComIfG_Ccsp()->SetMass(&mSph, 3);
                g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
                mMassCounter = g_Counter.mCounter0;
            }
        }

        if(chk_attrState(this, ATTR_STATE_10) || field_0x6F4 == 1) {
            fopAcM_seStart(this, JA_SE_OBJ_BOMB_IGNITION, 0);
        }
    }

    if(field_0x782) {
        field_0x784++;
    }

    return true;
}

/* 800DBF24-800DBF44       .text daBomb_Execute__FP8daBomb_c */
static BOOL daBomb_Execute(daBomb_c* i_this) {
    return i_this->execute();
}

/* 800DBF44-800DC250       .text set_wind_vec__8daBomb_cFv */
void daBomb_c::set_wind_vec() {
    mWindVec *= 0.95f;
    if (mWindVec.abs2() < 0.1f)
        mWindVec.setall(0.0f);
    if (!mSph.ChkTgHit())
        return;
    cCcD_Obj* hitObj = mSph.GetTgHitObj();
    if (hitObj == NULL)
        return;
    if (!hitObj->ChkAtType(AT_TYPE_WIND))
        return;
    cXyz sp48 = *mSph.GetTgRVecP();
    f32 f31 = sp48.abs2();
    if (f31 > 180.0f*180.0f) {
        sp48 *= 180.0f / std::sqrtf(f31);
    }
    cCcD_ShapeAttr* hitShapeAttr = hitObj->GetShapeAttr();
    cXyz hitNormal = cXyz::Zero;
    f32 f30 = 1.0f;
    f32 f29 = 1.0f;
    if (hitShapeAttr->GetNVec(current.pos, &hitNormal)) {
        hitNormal *= 50.0f;
        mWindVec.abs2();
        fopAc_ac_c* hitActor = mSph.GetTgHitAc();
        if (hitActor && fopAcM_GetProfName(hitActor) == PROC_PLAYER) {
            s16 hitObjAngleY = cM_atan2s(hitNormal.x, hitNormal.z);
            f32 f2 = cM_scos(hitActor->shape_angle.y - hitObjAngleY);
            if (f2 > 0.0f) {
                f30 = 1.0f + 2.0f*f2;
                f29 = 1.0f + 0.3f*f2;
            }
        }
    }
    f32 f28;
    if (f31 > 0.01f) {
        f31 = 0.9f;
        f28 = 0.1f;
    } else {
        f31 = 0.0f;
        f28 = 1.0f;
    }
    mWindVec = sp48 * f31 + hitNormal * f28 * f30;
    if (std::fabsf(mWindVec.y) < 5.0f) {
        mWindVec.y += f29*(100.0f*f28) + 140.0f*f31;
    }
}

/* 800DC250-800DC2D0       .text anm_play_nut__8daBomb_cFv */
void daBomb_c::anm_play_nut() {
    if(chk_state(STATE_5) || chk_state(STATE_6)) {
        mBck0.play();
        mBrk0.play();
    }
    else {
        if(mRestTime + 2 <= 0x87) {
            mBck1.play();
            mBrk1.play();
        }
    }
}

/* 800DC2D0-800DC384       .text set_mtx__8daBomb_cFv */
void daBomb_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    if(prm_get_angXZero()) {
        mDoMtx_stack_c::ZXYrotM(0, shape_angle.y, shape_angle.z);
    }
    else {
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    }

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 800DC384-800DC3A4       .text init_mtx__8daBomb_cFv */
void daBomb_c::init_mtx() {
    set_mtx();
}

/* 800DC3A4-800DC400       .text se_cannon_fly_set__8daBomb_cFv */
void daBomb_c::se_cannon_fly_set() {
    mDoAud_seStart(JA_SE_LK_SHIP_CANNON_FLY, &current.pos);
    field_0x77F = 1;
}

/* 800DC400-800DC44C       .text se_cannon_fly_stop__8daBomb_cFv */
void daBomb_c::se_cannon_fly_stop() {
    if(field_0x77F) {
        mDoAud_seStopActor(&current.pos, -1);
        field_0x77F = 0;
    }
}

/* 800DC44C-800DC568       .text eff_water_splash__8daBomb_cFv */
void daBomb_c::eff_water_splash() {
    cXyz pos(current.pos.x, field_0x558, current.pos.z);
    fopKyM_createWpillar(&pos, 0.5f, 0.75f, 0);

    cBgS_PolyInfo* temp[2] = {
        field_0x562 ? NULL : &mAcch.m_wtr,
        &mAcch.m_gnd,
    };
    
    u32 mtrlSndId = 0x13;
    for (int i = 0; i < ARRAY_SIZE(temp); i++) {
        if (temp[i] == NULL)
            continue;
        int bg_index = temp[i]->GetBgIndex();
        if (bg_index >= 0 && bg_index < 0x100) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(*temp[i]);
            break;
        }
    }

    fopAcM_seStart(this, JA_SE_OBJ_FALL_WATER_S, mtrlSndId);
}

/* 800DC568-800DC570       .text daBomb_IsDelete__FP8daBomb_c */
static BOOL daBomb_IsDelete(daBomb_c*) {
    return TRUE;
}

/* 800DC570-800DC67C       .text bombDelete__8daBomb_cFv */
bool daBomb_c::bombDelete() {
    if(mSmoke.mpEmitter) {
        mSmoke.mpEmitter->setEmitterCallBackPtr(NULL);
        mSmoke.mpEmitter->becomeInvalidEmitter();
    }
    mSmoke.mpEmitter = NULL;

    if(mSparks.mpEmitter) {
        mSparks.mpEmitter->setEmitterCallBackPtr(NULL);
        mSparks.mpEmitter->becomeInvalidEmitter();
    }
    mSparks.mpEmitter = NULL;

    if(field_0x6F0) {
        daPy_getPlayerLinkActorClass()->decrementBombCnt();
    }

    se_cannon_fly_stop();
    if(mType == 1) {
        dComIfG_resDelete(&mPhase, m_attrType[mType].resName);
    }

    dKy_actor_addcol_set(0, 0, 0, 0.0f);
    dKy_efplight_cut(&mPntLight);
    dKyw_pntwind_cut(&mPntWind);

    return true;
}

/* 800DC67C-800DC6A0       .text daBomb_Delete__FP8daBomb_c */
static BOOL daBomb_Delete(daBomb_c* i_this) {
    i_this->bombDelete();
    return true;
}

/* 800DC6A0-800DCADC       .text createHeap__8daBomb_cFv */
BOOL daBomb_c::createHeap() {
    BOOL ret;
    if(mType == 1) {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BDL_VBAKM));
        JUT_ASSERT(0x9A5, modelData != NULL);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        
        J3DAnmTransform* bck0_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BCK_VBAMX));
        JUT_ASSERT(0x9AE, bck0_data != NULL);
        int temp = mBck0.init(modelData, bck0_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
        
        J3DAnmTransform* bck1_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BCK_VBAKM));
        JUT_ASSERT(0x9B4, bck1_data != NULL);
        int temp2 = mBck1.init(modelData, bck1_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
        
        J3DAnmTevRegKey* brk0_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BRK_VBAMX));
        JUT_ASSERT(0x9BB, brk0_data != NULL);
        int temp3 = mBrk0.init(modelData, brk0_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
        
        J3DAnmTevRegKey* brk1_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_attrType[mType].resName, VBAKH_BRK_VBAKM));
        JUT_ASSERT(0x9C1, brk1_data != NULL);
        int temp4 = mBrk1.init(modelData, brk1_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

        return mpModel && temp && temp2 && temp3 && temp4;
    }
    else {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_attrType[mType].resName, LINK_BDL_BOMB));
        JUT_ASSERT(0x9CE, modelData != NULL);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

        if(!mpModel) {
            return false;
        }
        else {
            J3DAnmTransform* bck0_data = (J3DAnmTransform*)dComIfG_getObjectRes(m_attrType[mType].resName, LINK_BCK_BOMB);
            int temp = mBck0.init(modelData, bck0_data, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);

            return temp ? TRUE : FALSE;
        }
    }
}

/* 800DCADC-800DCAFC       .text daBomb_createHeap__FP10fopAc_ac_c */
static BOOL daBomb_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daBomb_c*>(i_this)->createHeap();
}

/* 800DCAFC-800DCC0C       .text create__8daBomb_cFv */
cPhs_State daBomb_c::create() {
    int state = prm_get_state();
    if(state == 5 || state == 6) {
        mType = 1;
    }
    else if(state == 4) {
        mType = 2;
    }
    else {
        mType = 0;
    }

    fopAcM_SetupActor(this, daBomb_c);

    cPhs_State status;
    if(mType == 1) {
        status = dComIfG_resLoad(&mPhase, m_attrType[mType].resName);
    }
    else {
        status = cPhs_COMPLEATE_e;
    }

    if(status == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(this, daBomb_createHeap, attrType().heapSize)) {
            create_init();
        }
        else {
            status = cPhs_ERROR_e;
        }
    }

    return status;
}

/* 800DCEF8-800DCF18       .text daBomb_Create__FP10fopAc_ac_c */
static cPhs_State daBomb_Create(fopAc_ac_c* i_this) {
    return static_cast<daBomb_c*>(i_this)->create();
}

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOMB,
        /* SrcObjAt  Atp     */ 0x04,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
    },
};

/* 800DCF18-800DD1A4       .text create_init__8daBomb_cFv */
void daBomb_c::create_init() {
    mCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mCir, &speed, &current.angle, &shape_angle);
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();
    mAcch.m_roof_crr_height = 50.0f;
    mAcch.OnLineCheck();

    field_0x554 = -G_CM3D_F_INF;
    field_0x558 = -G_CM3D_F_INF;
    field_0x55C = -G_CM3D_F_INF;
    field_0x560 = 0;
    mbWaterIn = 0;
    field_0x562 = 0;
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    
    mStts.Init(200, 0xFF, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mStts);
    if(chk_state(STATE_8)) {
        mSph.GetObjAt().SetAtp(2);
    }

    gravity = -2.9f;
    maxFallSpeed = -100.0f;
    mRestTime = 0x96;
    mInitialState = prm_get_state();
    if(!chk_state(STATE_4)) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }

    field_0x77C = 0;
    field_0x77D = 0;
    field_0x77E = 0;
    field_0x6F4 = 0;
    field_0x77F = 0;
    field_0x780 = 0;
    field_0x781 = 0;
    field_0x782 = 0;
    field_0x784 = 0;

    mWindVec.set(cXyz::Zero);

    mMassCounter = g_Counter.mCounter0 - 1;
    if(chk_attrState(this, ATTR_STATE_2)) {
        scale.setall(0.0f);
    }
    if(chk_attrState(this, ATTR_STATE_4)) {
        setFuseEffect();
    }
    if(chk_attrState(this, ATTR_STATE_8)) {
        bgCrrPos();
    }
    
    if(chk_state(STATE_3)) {
        field_0x6F0 = 1;
        field_0x7C8 = 2;
    }
    else {
        field_0x7C8 = 0;
    }
    
    if(chk_attrState(this, ATTR_STATE_1)) {
        procExplode_init();
    }
    else {
        procWait_init();
    }

    cull.box.min.x = -36.0f;
    cull.box.min.y = 0.0f;
    cull.box.min.z = -36.0f;
    cull.box.max.x = 36.0f;
    cull.box.max.y = 66.0f;
    cull.box.max.z = 36.0f;
    fopAcM_setCullSizeFar(this, 10.0f);

    init_mtx();
}

static actor_method_class l_daBomb_Method = {
    (process_method_func)daBomb_Create,
    (process_method_func)daBomb_Delete,
    (process_method_func)daBomb_Execute,
    (process_method_func)daBomb_IsDelete,
    (process_method_func)daBomb_Draw,
};

actor_process_profile_definition g_profile_BOMB = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOMB,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBomb_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOMB,
    /* Actor SubMtd */ &l_daBomb_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
