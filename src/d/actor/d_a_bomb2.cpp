/**
 * d_a_bomb2.cpp
 * Object - Bomb Flower - Bomb
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_bomb2.h"
#include "d/actor/d_a_sea.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo_wether.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_vbakh.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_mtx.h"

namespace daBomb2 {
    namespace {
        struct Attr_c {
            /* 0x00 */ const char* resName;
            /* 0x04 */ u32 heapSize;
            /* 0x08 */ s16 field_0x8;
            /* 0x0A */ s16 field_0xA; // Appears to be the bomb timer cap
            /* 0x0C */ f32 gravity;
            /* 0x10 */ f32 maxFallSpeed;
            /* 0x14 */ f32 field_0x14;
            /* 0x18 */ f32 field_0x18;
            /* 0x1C */ f32 field_0x1C;
            /* 0x20 */ f32 field_0x20;
            /* 0x24 */ f32 field_0x24;
            /* 0x28 */ f32 field_0x28;
            /* 0x2C */ f32 field_0x2C;
            /* 0x30 */ f32 field_0x30;
            /* 0x34 */ f32 field_0x34;
            /* 0x38 */ f32 field_0x38;
            /* 0x3C */ f32 field_0x3C;
            /* 0x40 */ f32 field_0x40;
            /* 0x44 */ f32 field_0x44;
            /* 0x48 */ f32 field_0x48;
            /* 0x4C */ f32 field_0x4C;
            /* 0x50 */ f32 field_0x50;
            /* 0x54 */ f32 field_0x54;
            /* 0x58 */ f32 field_0x58;
            /* 0x5C */ f32 field_0x5C;
            /* 0x60 */ f32 field_0x60;
            /* 0x64 */ f32 field_0x64;
            /* 0x68 */ f32 field_0x68;
        };

        const Attr_c L_attr = {
            /* resName      */ "VbakH",
            /* heapSize     */ 0x920,
            /* field_0x8    */ 0x96,
            /* field_0xA    */ 0x1E,
            /* gravity      */ -2.9f,
            /* maxFallSpeed */ -100.0f,
            /* field_0x14   */ -0.6f,
            /* field_0x18   */ 19.5f,
            /* field_0x1C   */ 13.0f,
            /* field_0x20   */ 0.1f,
            /* field_0x24   */ 0.5f,
            /* field_0x28   */ 20.0f,
            /* field_0x2C   */ 25.0f,
            /* field_0x30   */ 0.002f,
            /* field_0x34   */ 0.0005f,
            /* field_0x38   */ 140.0f,
            /* field_0x3C   */ 100.0f,
            /* field_0x40   */ 180.0f,
            /* field_0x44   */ 50.0f,
            /* field_0x48   */ 2.0f,
            /* field_0x4C   */ 0.3f,
            /* field_0x50   */ 0.03f,
            /* field_0x54   */ 0.1f,
            /* field_0x58   */ 0.4f,
            /* field_0x5C   */ 0.5f,
            /* field_0x60   */ -0.005f,
            /* field_0x64   */ 1.5f,
            /* field_0x68   */ 0.6f,
        };

        inline static const Attr_c& attr() { return L_attr; }
    }
    
    void Env_c::set(const cXyz& pos) {
        mPntLight.mPos = pos;
        mPntLight.mPos.y += 100.0f;
        mPntLight.mColor.r = 200;
        mPntLight.mColor.g = 200;
        mPntLight.mColor.b = 160;
        mPntLight.mPower = 600.0f;
        mPntLight.mFluctuation = 100.0f;
        dKy_efplight_set(&mPntLight);

        mPntWind.mPos = pos;
        mPntWind.mDir.x = 0.0f;
        mPntWind.mDir.y = 1.0f;
        mPntWind.mDir.z = 0.0f;
        mPntWind.mRadius = 500.0f;
        mPntWind.field_0x20 = 0.0f;
        mPntWind.mStrength = 0.5f;
        dKyw_pntwind_set(&mPntWind);

        field_0x4C = 0;
        field_0x50 = 0.0f;
    }

    void Env_c::clean() {
        dKy_actor_addcol_set(0, 0, 0, 0.0f);
        dKy_efplight_cut(&mPntLight);
        dKyw_pntwind_cut(&mPntWind);
    }

    bool Env_c::is_end() const {
        return field_0x4C > 1;
    }

    /* 800DD4B0-800DD670       .text proc__Q27daBomb25Env_cFRC4cXyz */
    void Env_c::proc(const cXyz& param_1) {
        camera_class* camera = dComIfGp_getCamera(0);
        f32 temp2 = 0.0f;

        mPntLight.mPower = field_0x50 * 1500.0f;
        mPntWind.mStrength = field_0x50;
        f32 temp = param_1.abs(camera->mLookat.mEye);

        if(temp < 1500.0f) {
            temp2 = 1.0f - (temp * (1.0f / 1500.0f));
        }
        temp2 = field_0x50 * temp2;

        dKy_actor_addcol_amb_set(200, 180, 100, temp2);
        dKy_bg_addcol_amb_set(180, 160, 60, temp2);
        dKy_bg_addcol_dif_set(255, 225, 120, temp2);

        switch(field_0x4C) {
        case 0:
            cLib_addCalc(&field_0x50, 1.0f, 0.5f, 0.4f, 0.01f);
            if(field_0x50 >= 0.99f) {
                field_0x4C += 1;
            }

            break;
        case 1:
            cLib_addCalc(&field_0x50, 0.0f, 0.05f, 0.04f, 0.001f);
            if(field_0x50 <= 0.01f) {
                field_0x4C += 1;
            }

            break;
        }
    }

    void FuseSmokeCB_c::setOldPosP(const cXyz* param_1, const cXyz* param_2) {
        field_0x0C = param_1;
        field_0x10 = param_2;
        field_0x04 = 0x14;
    }

    void FuseSmokeCB_c::deleteCallBack() {
        if(mpEmitter) {
            mpEmitter->setEmitterCallBackPtr(NULL);
            mpEmitter->becomeInvalidEmitter();
        }
        mpEmitter = NULL;
    }

    /* 800DD6BC-800DD6C0       .text execute__Q27daBomb213FuseSmokeCB_cFP14JPABaseEmitter */
    void FuseSmokeCB_c::execute(JPABaseEmitter* emitter) {
    }

    /* 800DD6C0-800DDAE8       .text executeAfter__Q27daBomb213FuseSmokeCB_cFP14JPABaseEmitter */
    void FuseSmokeCB_c::executeAfter(JPABaseEmitter* emitter) {
        JGeometry::TVec3<f32> vec1;
        vec1.set(*field_0x0C);
        JGeometry::TVec3<f32> vec2;
        vec2.set(*mpPos);
        f32 f15 = attr().field_0x24;
        emitter->setGlobalTranslation(vec2);
        
        s16 r29 = 10.0f + (0.5f * (20.0f - mpPos->abs(*field_0x0C)));
        if (r29 < 0xA) {
            r29 = 0xA;
        }
        emitter->setLifeTime(r29);
        
        JGeometry::TVec3<f32> vec3;
        vec3.z = f15 * (vec2.x - vec1.x);
        vec3.y = f15 * (vec2.y - vec1.y);
        vec3.x = f15 * (vec2.z - vec1.z);
        
        JGeometry::TVec3<f32> vec4;
        vec4.x = f15 * (vec1.x - field_0x10->x);
        vec4.y = f15 * (vec1.y - field_0x10->y);
        vec4.z = f15 * (vec1.z - field_0x10->z);
        
        f32 f0 = mpPos->abs(*field_0x0C) * attr().field_0x20;
        if (f0 > 1.0f) {
            f32 f20 = 1.0f / f0;
            s16 r28 = f20 * (field_0x04 - r29);
            s16 lifetime = r29 + r28;
            for (f32 f19 = f20; f19 < 1.0f; f19 += f20, lifetime += r28) {
                JGeometry::TVec3<f32> vec5;
                vec5.cubic<f32>(vec1, vec2, vec3, vec4, f19);
                
                emitter->setLifeTime(lifetime);
                JPABaseParticle* particle = emitter->createParticle();
                if (particle) {
                    particle->setOffsetPosition(vec5);
                }
            }
        }
        
        field_0x04 = r29;
    }

    /* 800DDAE8-800DDAEC       .text draw__Q27daBomb213FuseSmokeCB_cFP14JPABaseEmitter */
    void FuseSmokeCB_c::draw(JPABaseEmitter*) {
    }

    void FuseSmokeCB_c::setup(JPABaseEmitter* param_1, const cXyz* param_2, const csXyz*, signed char) {
        mpPos = param_2;
        mpEmitter = param_1;
    }

    void FuseSparksCB_c::deleteCallBack() {
        if(mpEmitter) {
            mpEmitter->setEmitterCallBackPtr(NULL);
            mpEmitter->becomeInvalidEmitter();
        }
        mpEmitter = NULL;
    }

    void FuseSparksCB_c::execute(JPABaseEmitter* emitter) {
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

    void FuseSparksCB_c::draw(JPABaseEmitter*) {
        return;
    }

    void FuseSparksCB_c::setup(JPABaseEmitter* param_1, const cXyz* param_2, const csXyz*, signed char) {
        mpPos = param_2;
        mpEmitter = param_1;
    }

    BOOL Act_c::solidHeapCB(fopAc_ac_c* i_this) {
        return static_cast<Act_c*>(i_this)->create_heap();
    }

    /* 800DDBAC-800DDD90       .text create_heap_nut__Q27daBomb25Act_cFv */
    bool Act_c::create_heap_nut() {
        const char* resName = attr().resName;

        J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(attr().resName, VBAKH_BDL_VBAKM));
        JUT_ASSERT(0x303, mdl_data != NULL);
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000022);

        J3DAnmTransform* bck_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(resName, VBAKH_BCK_VBAKM));
        JUT_ASSERT(0x30D, bck_data != NULL);
        int temp = mBck0.init(mdl_data, bck_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);

        J3DAnmTevRegKey* brk_data = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(resName, VBAKH_BRK_VBAKM));
        JUT_ASSERT(0x314, brk_data != NULL);
        int temp3 = mBrk0.init(mdl_data, brk_data, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

        return mpModel && temp && temp3;
    }

    bool Act_c::create_heap() {
        return create_heap_nut();
    }

    void Act_c::crr_init() {
        mCir.SetWall(30.0f, 30.0f);
        mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
        mAcch.ClrWaterNone();
        mAcch.ClrRoofNone();
        mAcch.m_roof_crr_height = 50.0f;
        mAcch.OnLineCheck();
        field_0x51C = -G_CM3D_F_INF;
        field_0x520 = -G_CM3D_F_INF;
        field_0x524 = 0;
        mbWaterIn = 0;
        field_0x526 = 0;
        field_0x528 = -G_CM3D_F_INF;
    }

    dCcD_SrcSph Act_c::M_sph_src = {
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
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 30.0f,
        }},
    };

    void Act_c::cc_init() {
        mStts.Init(200, 0xFF, this);
        mSph.Set(M_sph_src);
        mSph.SetStts(&mStts);
    }

    void Act_c::start_explode_instant() {
        if(chk_water_in()) {
            eff_explode_water();
        }
        else {
            eff_explode();
        }

        mode_explode_init();
    }

    void Act_c::start_explode_interval() {
        eff_fuse_start();
        set_nut_exp_interval();
        mode_wait_init();
    }

    void Act_c::start_carry() {
        mode_carry_init();
    }

    /* 800DDF60-800DE024       .text start_proc_call__Q27daBomb25Act_cFv */
    void Act_c::start_proc_call() {
        typedef void(Act_c::*procFunc)();
        static procFunc start_proc[] = {
            &Act_c::start_explode_instant,
            &Act_c::start_explode_interval,
            &Act_c::start_carry
        };

        int proc = daObj::PrmAbstract(this, PRM_2_W, PRM_2_S);
        return (this->*start_proc[proc])();
    }

    /* 800DE024-800DE14C       .text create_init__Q27daBomb25Act_cFv */
    void Act_c::create_init() {
        crr_init();
        cc_init();
        
        fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

        fopAcM_setCullSizeBox(this, -36.0f, 0.0f, -36.0f, 36.0f, 66.0f, 36.0f);
        fopAcM_setCullSizeFar(this, 10.0f);

        if(daObj::PrmAbstract(this, PRM_1_W, PRM_1_S)) {
            off_carry();
        }
        else {
            on_carry();
        }

        gravity = attr().gravity;
        maxFallSpeed = attr().maxFallSpeed;
        bgCrrPos();
        speed.y = 0.0f;
        speedF = 0.0f;
        current.pos = home.pos;
        init_mtx();

        mBombTimer = attr().field_0x8;
        field_0x740 = 0;
        field_0x741 = 0;
        field_0x742 = 0;
        field_0x743 = 0;
        mWindVec = cXyz::Zero;

        start_proc_call();
    }

    cPhs_State Act_c::_create() {
        fopAcM_SetupActor(this, Act_c);

        cPhs_State status = dComIfG_resLoad(&mPhase, attr().resName);

        if(status == cPhs_COMPLEATE_e) {
            if(fopAcM_entrySolidHeap(this, solidHeapCB, attr().heapSize)) {
                create_init();
            }
            else {
                status = cPhs_ERROR_e;
            }
        }

        return status;
    }

    Act_c::Act_c() {}

    bool Act_c::_delete() {
        eff_fuse_end();
        mEnv.clean();
        dComIfG_resDelete(&mPhase, attr().resName);

        return true;
    }

    void Act_c::set_mtx() {
        mpModel->setBaseScale(scale);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::concat(field_0x754);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

        eff_fuse_move();
    }

    /* 800DE574-800DE5B0       .text init_mtx__Q27daBomb25Act_cFv */
    void Act_c::init_mtx() {
        tensor_init();
        eff_fuse_init();
        set_mtx();
    }

    /* 800DE5B0-800DE740       .text cc_set__Q27daBomb25Act_cFv */
    void Act_c::cc_set() {
        bool r3 = mState == 2;
        bool r4 = mState == 3;
        bool r31 = true;
        f32 radius = 200.0f;
        cXyz pos = current.pos;
        if (r3) {
            if (field_0x73C > 0) {
                field_0x73C--;
            }
            if (field_0x73C <= 0) {
                r31 = false;
            }
        } else if (r4) {
            r31 = false;
        } else if (r31) {
            radius = scale.x * 30.0f;
            static cXyz local_center(0.0f, 30.0f, 0.0f);
            mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
            mDoMtx_stack_c::scaleM(scale);
            mDoMtx_stack_c::multVec(&local_center, &pos);
        }
        
        if (r31) {
            mStts.Move();
            mSph.SetR(radius);
            mSph.SetC(pos);
            dComIfG_Ccsp()->Set(&mSph);
            dComIfG_Ccsp_SetMass(&mSph, 3);
        }
    }

    void Act_c::camera_lockoff() const {
        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
        camera->mCamera.ForceLockOff(fopAcM_GetID((Act_c*)this));
    }

    /* 800DE794-800DE854       .text posMoveF__Q27daBomb25Act_cFv */
    void Act_c::posMoveF() {
        if (mWindVec.abs2() > 0.01f) {
            cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
            cXyz* norm;
            f32 friction, no_grade_cos;
            if (triPla) {
                norm = triPla->GetNP();
                friction = 0.06f;
                no_grade_cos = cM_scos(0xA4F);
            } else {
                norm = NULL;
                friction = 0.0f;
                no_grade_cos = 0.0f;
            }
            daObj::posMoveF_grade(
                this, mStts.GetCCMoveP(), &mWindVec,
                attr().field_0x30, attr().field_0x34,
                norm, friction, no_grade_cos, NULL
            );
        } else {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
    }

    /* 800DE854-800DE8A8       .text bgCrrPos__Q27daBomb25Act_cFv */
    void Act_c::bgCrrPos() {
        mAcch.CrrPos(*dComIfG_Bgsp());
        bgCrrPos_lava();
        bgCrrPos_water();
        setRoomInfo();
    }

    /* 800DE8A8-800DE914       .text bgCrrPos_lava__Q27daBomb25Act_cFv */
    void Act_c::bgCrrPos_lava() {
        cXyz temp(current.pos.x, old.pos.y + 1.0f, current.pos.z);
        mGndChk.SetPos(&temp);

        field_0x51C = dComIfG_Bgsp()->GroundCross(&mGndChk);
    }

    /* 800DE914-800DEA0C       .text bgCrrPos_water__Q27daBomb25Act_cFv */
    void Act_c::bgCrrPos_water() {
        f32 f31 = mAcch.m_wtr.GetHeight();
        bool r31 = daSea_ChkArea(current.pos.x, current.pos.z);
        f32 f1 = daSea_calcWave(current.pos.x, current.pos.z);
        bool r4 = mAcch.ChkWaterIn();
        bool r3 = r31 && current.pos.y < f1;
        bool r5 = false;
        if (r4 && r3) {
            if (f31 > f1) {
                r3 = 0;
            } else {
                r4 = 0;
            }
        }
        if (r4) {
            field_0x520 = f31;
            r5 = true;
            field_0x526 = 0;
        } else if (r3) {
            field_0x520 = f1;
            r5 = true;
            field_0x526 = 1;
        } else {
            field_0x520 = -G_CM3D_F_INF;
            field_0x526 = 0;
        }
        mbWaterIn = r5;
    }

    bool Act_c::chk_water_in() const {
        return mbWaterIn;
    }

    bool Act_c::chk_lava_in() const {
        if(field_0x51C == -G_CM3D_F_INF) {
            return false;
        }

        return current.pos.y < field_0x51C;
    }

    void Act_c::setRoomInfo() {
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

    void Act_c::bound(f32 param_1) {
        if(mAcch.ChkWallHit()) {
            speedF *= 0.8f;
            current.angle.y = (mCir.GetWallAngleY() * 2) - (current.angle.y + 0x8000);
        }

        if(mAcch.ChkGroundLanding()) {
            daObj::make_land_effect(this, &mAcch.m_gnd, attr().field_0x68);
            param_1 *= attr().field_0x14;
            if(param_1 < attr().field_0x18) {
                field_0x741 = 0;
            }
            else {
                speedF *= 0.9f;
                if(param_1 > attr().field_0x1C) {
                    speed.y = attr().field_0x1C;
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

    void Act_c::set_nut_exp_interval() {
        if(mBombTimer > attr().field_0xA) {
            mBombTimer = attr().field_0xA;

            f32 frame = 0x87 - attr().field_0xA;
            mBck0.getFrameCtrl()->setFrame(frame);
            mBrk0.getFrameCtrl()->setFrame(frame);
        }
    }

    void Act_c::anm_play() {
        if(mBombTimer + 1 <= 0x87) {
            mBck0.play();
            mBrk0.play();
        }
    }

    /* 800DEC70-800DEFAC       .text set_wind_vec__Q27daBomb25Act_cFv */
    void Act_c::set_wind_vec() {
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
        
        f32 f30 = attr().field_0x40;
        cXyz sp48 = *mSph.GetTgRVecP();
        f32 f31 = sp48.abs2();
        if (f31 > SQUARE(f30)) {
            sp48 *= f30 / std::sqrtf(f31);
        }
        cCcD_ShapeAttr* hitShapeAttr = hitObj->GetShapeAttr();
        cXyz hitNormal = cXyz::Zero;
        f30 = 1.0f;
        f32 f29 = 1.0f;
        if (hitShapeAttr->GetNVec(current.pos, &hitNormal)) {
            hitNormal *= attr().field_0x44;
            mWindVec.abs2();
            fopAc_ac_c* hitActor = mSph.GetTgHitAc();
            if (hitActor && fopAcM_GetProfName(hitActor) == PROC_PLAYER) {
                s16 hitObjAngleY = cM_atan2s(hitNormal.x, hitNormal.z);
                f32 f2 = cM_scos(hitActor->shape_angle.y - hitObjAngleY);
                if (f2 > 0.0f) {
                    f30 = 1.0f + attr().field_0x48*f2;
                    f29 = 1.0f + attr().field_0x4C*f2;
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
            mWindVec.y += attr().field_0x38*f31 + f29*(attr().field_0x3C*f28);
        }
        field_0x7A8 = 2;
    }

    void Act_c::eff_explode() {
        if(!field_0x742) {
            field_0x742 = 1;

            camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            csXyz rot;
            rot.x = -cam->mAngle.x;
            rot.y = cam->mAngle.y + 0x8000;
            rot.z = 0;

            eff_explode_normal(&rot);
            se_explode();
            set_sound_env(0xFF, 0xA);
        }
    }

    void Act_c::eff_explode_normal(const csXyz* rotation) {
        dComIfGp_particle_setP1(dPa_name::ID_COMMON_LIGHT_FLASH, &current.pos, rotation, &scale);
        dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CLOUD, &current.pos, NULL, &scale);
        dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &current.pos, NULL, &scale);
        dComIfGp_particle_setToonP1(dPa_name::ID_COMMON_SMOKE_DEBRIS, &current.pos, NULL, &scale);
    }

    void Act_c::eff_explode_water() {
        if(!field_0x743) {
            fopKyM_createWpillar(&current.pos, 1.0f, 1.0f, 1);
            field_0x743 = 1;
            se_explode_water();
            set_sound_env(0xFF, 0xA);
        }
    }

    void Act_c::eff_fuse_init() {
        field_0x6C0 = cXyz::Zero;
        field_0x6CC = cXyz::Zero;
        field_0x6D8 = cXyz::Zero;
        field_0x744 = 0;
    }

    void Act_c::eff_fuse_start() {
        if(!field_0x744) {
            field_0x744 = 1;

            field_0x6C0.x = current.pos.x;
            field_0x6C0.y = current.pos.y + 60.0f;
            field_0x6C0.z = current.pos.z;
            field_0x6CC = field_0x6C0;
            field_0x6D8 = field_0x6C0;

            dComIfGp_particle_setP1(dPa_name::ID_COMMON_FUSE_SPARKS, &field_0x6C0, NULL, &scale, 0xFF, &mSparks);
            dComIfGp_particle_setToonP1(dPa_name::ID_COMMON_2012, &field_0x6C0, NULL, &scale, 0xDC, &mSmoke);
            mSmoke.setOldPosP(&field_0x6CC, &field_0x6D8);
        }
    }

    void Act_c::eff_fuse_move() {
        static cXyz fuse_offset(0.0f, 60.0f, 5.0f);
        
        field_0x6D8 = field_0x6CC;
        field_0x6CC = field_0x6C0;
        mDoMtx_stack_c::multVec(&fuse_offset, &field_0x6C0);

        if(field_0x744) {
            se_ignition();
        }
    }

    /* 800DF3DC-800DF41C       .text eff_fuse_end__Q27daBomb25Act_cFv */
    void Act_c::eff_fuse_end() {
        mSmoke.deleteCallBack();
        mSparks.deleteCallBack();

        field_0x744 = 0;
    }

    void Act_c::eff_water_splash() {
        cXyz pos(current.pos.x, field_0x520, current.pos.z);
        fopKyM_createWpillar(&pos, 0.5f, 0.75f, 0);

        se_fall_water();
        set_sound_env(0x64, 0x5);
    }

    /* 800DF488-800DF578       .text se_fall_water__Q27daBomb25Act_cFv */
    void Act_c::se_fall_water() {
        cBgS_PolyInfo* temp[2] = {
            field_0x526 ? NULL : &mAcch.m_wtr,
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

    void Act_c::se_explode() {
            fopAcM_seStart(this, JA_SE_OBJ_BOMB_EXPLODE, 0);
    }

    void Act_c::se_explode_water() {
            fopAcM_seStart(this, JA_SE_OBJ_BOMB_WATER, 0);
    }

    void Act_c::se_ignition() {
            fopAcM_seStart(this, JA_SE_OBJ_BOMB_IGNITION, 0);
    }

    void Act_c::set_sound_env(int param_1, int param_2) {
        dKy_Sound_set(current.pos, param_1, fopAcM_GetID(this), param_2);
    }

    bool Act_c::chk_exp_cc_nut() {
        bool fuse = false;
        bool explode = false;

        if(mSph.ChkTgHit()) {
            cCcD_Obj* obj = mSph.GetTgHitObj();
            if(obj) {
                if(obj->ChkAtType(AT_TYPE_BOMB)) {
                    fuse = true;
                }
                else if(!obj->ChkAtType(AT_TYPE_WIND)) {
                    explode = true;
                }
            }

            mSph.ClrTgHit();
        }


        if(mSph.ChkCoHit()) {
            if(field_0x741 || speed.abs() > attr().field_0x2C) {
                explode = true;
            }

            mSph.ClrCoHit();
        }

        if(explode) {
            eff_fuse_start();
            set_nut_exp_interval();
        }
        if(fuse) {
            eff_explode();
        }

        return fuse;
    }

    bool Act_c::chk_exp_cc() {
        if(mBombTimer > 0) {
            return chk_exp_cc_nut();
        }

        return false;
    }

    bool Act_c::chk_exp_bg_nut() {
        bool water = chk_water_in();
        bool lava = chk_lava_in();
        
        bool hit = mAcch.ChkWallHit() || mAcch.ChkGroundHit() || mAcch.ChkRoofHit();

        bool ret = false;
        if(lava) {
            eff_explode();
            ret = true;
        }
        else {
            if(water && speed.abs() > attr().field_0x28) {
                eff_explode_water();
                ret = true;
                
            }
            else if(hit) {
                if(field_0x741 || speed.abs() > attr().field_0x2C) {
                    eff_fuse_start();
                    set_nut_exp_interval();
                }
            }
        }

        return ret;
    }

    bool Act_c::chk_exp_bg() {
        return chk_exp_bg_nut();
    }

    bool Act_c::chk_exp_timer() {
        bool ret = false;
        if(mBombTimer > 0 && --mBombTimer == 0) {
            eff_explode();
            ret = true;
        }

        return ret;
    }

    /* 800DFAC0-800DFB94       .text chk_sink_bg_nut__Q27daBomb25Act_cFv */
    bool Act_c::chk_sink_bg_nut() {
        bool water = chk_water_in();

        bool ret = false;
        if(water && speed.abs() <= attr().field_0x28) {
            eff_water_splash();
            ret = true;
            
        }

        return ret;
    }

    bool Act_c::chk_sink_bg() {
        return chk_sink_bg_nut();
    }

    u8 Act_c::chk_exp_pre() {
        return chk_exp_cc() || chk_exp_timer();
    }

    u8 Act_c::chk_exp_post() {
        return chk_exp_bg();
    }

    u8 Act_c::chk_sink_post() {
        return chk_sink_bg();
    }

    /* 800DFC54-800DFD0C       .text set_real_shadow_flag__Q27daBomb25Act_cFv */
    void Act_c::set_real_shadow_flag() {
        bool r30 = false;
        if (mState == 1) {
            if (model) {
                r30 = true;
            } else {
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                if (player->getGrabActorID() == fopAcM_GetID(this) && player->getGrabUpStart()) {
                    r30 = true;
                }
            }
        }
        model = r30 ? mpModel : NULL;
    }

    /* 800DFD0C-800DFDB0       .text carry_fuse_start__Q27daBomb25Act_cFv */
    void Act_c::carry_fuse_start() {
        bool r30 = false;
        if (field_0x744 == 0) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            if (player->getGrabActorID() == fopAcM_GetID(this)) {
                if (player->getGrabUpEnd()) {
                    r30 = true;
                }
            } else {
                r30 = true;
            }
        }
        if (r30) {
            eff_fuse_start();
        }
    }

    void Act_c::on_carry() {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }

    void Act_c::off_carry() {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }

    void Act_c::mode_wait_init() {
        mState = 0;
        gravity = attr().gravity;
        mSph.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    }

    void Act_c::mode_wait() {
        if(chk_exp_pre()) {
            mode_explode_init();
            mode_explode();
        }
        else {
            if(fopAcM_checkCarryNow(this)) {
                mode_carry_init();
                mode_carry();
            }
            else {
                bool temp = daObj::PrmAbstract(this, PRM_1_W, PRM_1_S);
                f32 yVel = 0.0f;
                if(!temp) {
                    if(!field_0x745) {
                        posMoveF();
                    }

                    yVel = speed.y;
                    bgCrrPos();
                }

                if(chk_exp_post()) {
                    mode_explode_init();
                }
                else {
                    if(chk_sink_post()) {
                        mode_sink_init();
                    }
                    else {
                        if(!field_0x740) {
                            if(temp) {
                                off_carry();
                            }
                            else {
                                bound(yVel);
                                if(mAcch.ChkGroundHit()) {
                                    on_carry();
                                }
                                else {
                                    off_carry();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void Act_c::mode_carry_init() {
        mState = 1;
        speedF = 0.0f;
        speed = cXyz::Zero;
        off_carry();
        mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
    }

    void Act_c::mode_carry() {
        carry_fuse_start();
        if(chk_exp_pre()) {
            mode_explode_init();
            mode_explode();
        }
        else {
            if(!fopAcM_checkCarryNow(this)) {
                if(speedF > 0.0f) {
                    field_0x741 = 1;
                    field_0x7A8 = 2;
                }

                mode_wait_init();
                mode_wait();
            }
            else {
                cXyz temp = current.pos;
                bgCrrPos();
                current.pos = temp;
            }
        }
    }

    void Act_c::mode_explode_init() {
        mState = 2;
        camera_lockoff();
        eff_fuse_end();
        mEnv.set(current.pos);
        speedF = 0.0f;
        speed = cXyz::Zero;
        gravity = 0.0f;
        off_carry();
        mSph.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
        mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
        mSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
        fopAcM_cancelCarryNow(this);
        mBombTimer = 0;
        field_0x73C = 4;
        dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    }

    void Act_c::mode_explode() {
        mEnv.proc(current.pos);
        if(!field_0x73C && mEnv.is_end()) {
            field_0x740 = 1;
        }
    }

    void Act_c::mode_sink_init() {
        mState = 3;
        speed.y *= 0.8f;
        speedF *= 0.8f;
        mSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        mSph.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
        mSph.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
        off_carry();
        fopAcM_cancelCarryNow(this);
        field_0x698 = 4;
        fopAcM_getWaterY(&current.pos, &field_0x528);
    }

    void Act_c::mode_sink() {
        f32 temp;
        bool temp2 = fopAcM_getWaterY(&current.pos, &temp);
        if(temp2 && field_0x528 != -G_CM3D_F_INF && --field_0x698 > 0) {
            current.pos.y += temp - field_0x528;
            field_0x528 = temp;
            posMoveF();
        }
        else {
            field_0x740 = 1;
        }
    }

    void Act_c::mode_proc_call() {
        typedef void(Act_c::*procFunc)();
        static procFunc mode_proc[] = {
            &Act_c::mode_wait,
            &Act_c::mode_carry,
            &Act_c::mode_explode,
            &Act_c::mode_sink,
        };

        if(fopAcM_checkCarryNow(this) && mState != 1) {
            mode_carry_init();
        }

        (this->*mode_proc[mState])();
        set_real_shadow_flag();
    }

    void Act_c::tensor_init() {
        mDoMtx_identity(field_0x754);
        vib_init();
    }

    void Act_c::vib_init() {
        field_0x784 = 0.0f;
        field_0x788 = 0.0f;
        field_0x78C = 0.0f;
        field_0x790 = 0.0f;
        field_0x794 = 0.0f;
        field_0x798 = 0.0f;
        field_0x79C = 0.0f;
        field_0x7A0 = 0.0f;
        field_0x7A4 = 0.0f;
        field_0x7A8 = 0.0f;
    }

    /* 800E0430-800E04FC       .text vib_proc__Q27daBomb25Act_cFv */
    void Act_c::vib_proc() {
        f32 f5 = field_0x7A0 - attr().field_0x50 * (field_0x790 - field_0x788);
        f32 f6 = 1.0f / attr().field_0x5C;
        f32 f7 = 1.0f - field_0x7A4;
        f32 f0 = field_0x79C - attr().field_0x50 * (field_0x78C - field_0x784);
        field_0x794 += f0 * f6;
        field_0x798 += f5 * f6;
        field_0x794 *= f7;
        field_0x798 *= f7;
        field_0x78C += field_0x794;
        field_0x790 += field_0x798;
        field_0x79C = 0.0f;
        field_0x7A0 = 0.0f;
        if (field_0x7A8 > 0) {
            field_0x7A8--;
        }
    }

    void Act_c::set_vib_tensor() {
        cXyz temp(field_0x790, 1.0f, field_0x78C);
        Quaternion quat;
        daObj::quat_rotBaseY2(&quat, temp);
        mDoMtx_quat(&field_0x754[0], &quat);
    }

    /* 800E0554-800E0588       .text tensor_wait__Q27daBomb25Act_cFv */
    void Act_c::tensor_wait() {
        if(mAcch.ChkGroundHit()) {
            tensor_wait_ground();
        }
        else {
            tensor_wait_drop();
        }
    }

    void Act_c::tensor_wait_drop() {
        if(field_0x7A8 > 0) {
            field_0x79C = speed.z * attr().field_0x60;
            field_0x7A0 = speed.x * attr().field_0x60;
        }

        field_0x784 = 0.0f;
        field_0x788 = 0.0f;
        field_0x7A4 = attr().field_0x54;
    }

    void Act_c::tensor_wait_ground() {
        cM3dGPla* pNormal = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
        if(pNormal) {
            field_0x784 = pNormal->mNormal.z * attr().field_0x64;
            field_0x788 = pNormal->mNormal.x * attr().field_0x64;
        }
        else {
            field_0x784 = 0.0f;
            field_0x788 = 0.0f;
        }
        
        field_0x7A4 = attr().field_0x58;
    }

    void Act_c::tensor_carry() {
        field_0x784 = 0.0f;
        field_0x788 = 0.0f;
        field_0x7A4 = attr().field_0x58;
    }

    void Act_c::tensor_explode() {
        field_0x784 = 0.0f;
        field_0x788 = 0.0f;
        field_0x7A4 = attr().field_0x58;
    }

    void Act_c::tensor_sink() {
        field_0x784 = 0.0f;
        field_0x788 = 0.0f;
        field_0x7A4 = attr().field_0x58;
    }

    void Act_c::tensor_proc_call() {
        typedef void(Act_c::*procFunc)();
        static procFunc tensor_proc[] = {
            &Act_c::tensor_wait,
            &Act_c::tensor_carry,
            &Act_c::tensor_explode,
            &Act_c::tensor_sink,
        };

        if(!daObj::PrmAbstract(this, PRM_1_W, PRM_1_S)) {
            (this->*tensor_proc[mState])();
            vib_proc();
            set_vib_tensor();
        }
    }

    bool Act_c::_execute() {
        set_wind_vec();
        mode_proc_call();

        if(field_0x740) {
            fopAcM_delete(this);
        }
        else {
            tensor_proc_call();
            anm_play();

            attention_info.position.x = current.pos.x;
            attention_info.position.y = current.pos.y + 50.0f;
            attention_info.position.z = current.pos.z;
            eyePos = attention_info.position;

            set_mtx();
            cc_set();
        }

        return true;
    }

    bool Act_c::is_draw() {
        bool draw = false;
        if(mState != 2 && !field_0x743 && ! field_0x742) {
            draw = true;
        }

        return draw;
    }

    void Act_c::draw_nut() {
        J3DModelData* mdlData = (J3DModelData*)mpModel->getModelData();
        mBck0.entry(mdlData, mBck0.getFrame());
        mBrk0.entry(mdlData, mBrk0.getFrame());
        dComIfGd_setListP1();
        mDoExt_modelUpdateDL(mpModel);
        dComIfGd_setList();

        mBck0.remove(mdlData);
        mBrk0.remove(mdlData);
    }

    void Act_c::draw_shadow() {
        static const f32 mult[] = {
            2.08f,
            1.8f,
            1.5f,
            1.3f,
            1.15f,
            1.08f,
            1.04f,
            1.02f,
            1.01f,
            1.0f,
        };

        if(fopAcM_GetModel(this) == 0) {
            int framesLeft = mBck0.getEndFrame() - mBck0.getFrame();
            f32 scale = mult[cLib_minMaxLimit<int>(framesLeft, 0, 9)] * 25.0f;

            dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), scale, mAcch.m_gnd, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
        }
    }

    /* 800E0A0C-800E0A80       .text _draw__Q27daBomb25Act_cFv */
    bool Act_c::_draw() {
        if(is_draw()) {
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
            g_env_light.setLightTevColorType(mpModel, &tevStr);
            draw_nut();
            draw_shadow();
        }

        return true;
    }

    namespace {
        cPhs_State Mthd_Create(void* i_this) {
            return static_cast<Act_c*>(i_this)->_create();
        }

        BOOL Mthd_Delete(void* i_this) {
            return static_cast<Act_c*>(i_this)->_delete();
        }

        BOOL Mthd_Execute(void* i_this) {
            return static_cast<Act_c*>(i_this)->_execute();
        }

        BOOL Mthd_Draw(void* i_this) {
            return static_cast<Act_c*>(i_this)->_draw();
        }

        BOOL Mthd_IsDelete(void* i_this) {
            return TRUE;
        }
        
        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }
}

actor_process_profile_definition g_profile_Bomb2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Bomb2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBomb2::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Bomb2,
    /* Actor SubMtd */ &daBomb2::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
