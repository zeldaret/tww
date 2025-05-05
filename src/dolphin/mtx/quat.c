
#include <dolphin/mtx/quat.h>
#include <dolphin/os/OS.h>
#include <math.h>

void C_QUATMultiply(const Quaternion* p, const Quaternion* q, Quaternion* pq) {
    Quaternion* r;
    Quaternion pqTmp;

    ASSERTMSGLINE(193, p, "QUATMultiply():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(194, q, "QUATMultiply():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(195, pq, "QUATMultiply():  NULL QuaternionPtr 'pq' ");

    if (p == pq || q == pq){
        r = &pqTmp;
    } else {
        r = pq;
    }

    r->w = (p->w * q->w) - (p->x * q->x) - (p->y * q->y) - (p->z * q->z);
    r->x = (p->w * q->x) + (p->x * q->w) + (p->y * q->z) - (p->z * q->y);
    r->y = (p->w * q->y) + (p->y * q->w) + (p->z * q->x) - (p->x * q->z);
    r->z = (p->w * q->z) + (p->z * q->w) + (p->x * q->y) - (p->y * q->x);

    if (r == &pqTmp) {
        *pq = pqTmp;
    }
}

#ifdef __MWERKS__
void PSQUATMultiply(const register Quaternion* p, const register Quaternion* q, register Quaternion* pq) {
    register f32 pxy, pzw;
    register f32 qxy, qzw;
    register f32 pnxy, pnzw, pnxny, pnznw;
    register f32 rxy, rzw;
    register f32 sxy, szw;

    asm {
        psq_l pxy, 0x0(p), 0, 0
        psq_l pzw, 0x8(p), 0, 0
        psq_l qxy, 0x0(q), 0, 0
        ps_neg pnxny, pxy
        psq_l qzw, 0x8(q), 0, 0
        ps_neg pnznw, pzw
        ps_merge01 pnxy, pnxny, pxy
        ps_muls0 rxy, pzw, qxy
        ps_muls0 rzw, pnxny, qxy
        ps_merge01 pnzw, pnznw, pzw
        ps_muls1 szw, pnxy, qxy
        ps_madds0 rxy, pnxy, qzw, rxy
        ps_muls1 sxy, pnzw, qxy
        ps_madds0 rzw, pnzw, qzw, rzw
        ps_madds1 szw, pnznw, qzw, szw
        ps_merge10 rxy, rxy, rxy
        ps_madds1 sxy, pxy, qzw, sxy
        ps_merge10 rzw, rzw, rzw
        ps_add rxy, rxy, sxy
        psq_st rxy, 0x0(pq), 0, 0
        ps_sub rzw, rzw, szw
        psq_st rzw, 0x8(pq), 0, 0
    }
}
#endif

void C_QUATNormalize(const Quaternion* src, Quaternion* unit) {
    f32 mag;
    ASSERTMSGLINE(407, src, "QUATNormalize():  NULL QuaternionPtr 'src' ");
    ASSERTMSGLINE(408, unit, "QUATNormalize():  NULL QuaternionPtr 'unit' ");

    mag = (src->x * src->x) + (src->y * src->y) + (src->z * src->z) + (src->w * src->w);
    if (mag >= 0.00001f) {
        mag = 1.0f / sqrtf(mag);

        unit->x = src->x * mag;
        unit->y = src->y * mag;
        unit->z = src->z * mag;
        unit->w = src->w * mag;
    } else {
        unit->x = unit->y = unit->z = unit->w = 0.0f;
    }
}

#ifdef __MWERKS__
void PSQUATNormalize(const register Quaternion* src, register Quaternion* unit) {
    register f32 sxy, szw;
    register f32 mag, rsqmag;
    register f32 diff;
    register f32 c_zero;
    register f32 nwork0, nwork1;

    register f32 epsilon = 0.00001f;
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;

    asm {
        psq_l sxy, 0x0(src), 0, 0
        ps_mul mag, sxy, sxy
        psq_l szw, 0x8(src), 0, 0
        ps_sub c_zero, epsilon, epsilon
        ps_madd mag, szw, szw, mag
        ps_sum0 mag, mag, mag, mag
        frsqrte rsqmag, mag
        ps_sub diff, mag, epsilon
        fmul nwork0, rsqmag, rsqmag
        fmul nwork1, rsqmag, c_half
        fnmsub nwork0, nwork0, mag, c_three
        fmul rsqmag, nwork0, nwork1
        ps_sel rsqmag, diff, rsqmag, c_zero
        ps_muls0 sxy, sxy, rsqmag
        ps_muls0 szw, szw, rsqmag
        psq_st sxy, 0x0(unit), 0, 0
        psq_st szw, 0x8(unit), 0, 0
    }
}
#endif

void C_QUATInverse(const Quaternion* src, Quaternion* inv) {
    f32 mag, norminv;
    ASSERTMSGLINE(498, src, "QUATInverse():  NULL QuaternionPtr 'src' ");
    ASSERTMSGLINE(499, inv, "QUATInverse():  NULL QuaternionPtr 'inv' ");

    mag = (src->x * src->x) + (src->y * src->y) + (src->z * src->z) + (src->w * src->w);
    if (mag == 0.0f) {
        mag = 1.0f;
    }

    norminv = 1.0f / mag;
    inv->x = -src->x * norminv;
    inv->y = -src->y * norminv;
    inv->z = -src->z * norminv;
    inv->w =  src->w * norminv;
}

#ifdef __MWERKS__
void PSQUATInverse(const register Quaternion* src, register Quaternion* inv) {
    register f32 sxy, szw;
    register f32 izz, iww;
    register f32 mag, nmag;
    register f32 norminv, nninv;
    register f32 nwork0;
    register f32 c_two;
    register f32 c_zero;
    register f32 c_one = 1.0f;

    asm {
        psq_l sxy, 0x0(src), 0, 0
        ps_mul mag, sxy, sxy
        ps_sub c_zero, c_one, c_one
        psq_l szw, 0x8(src), 0, 0
        ps_madd mag, szw, szw, mag
        ps_add c_two, c_one, c_one
        ps_sum0 mag, mag, mag, mag
        fcmpu cr0, mag, c_zero
        beq L_00000948
        fres norminv, mag
        ps_neg nmag, mag
        ps_nmsub nwork0, mag, norminv, c_two
        ps_mul norminv, norminv, nwork0
        b L_0000094C
    L_00000948:
        fmr norminv, c_one
    L_0000094C:
        ps_neg nninv, norminv
        ps_muls1 iww, norminv, szw
        ps_muls0 sxy, sxy, nninv
        psq_st iww, 0xc(inv), 1, 0
        ps_muls0 izz, szw, nninv
        psq_st sxy, 0x0(inv), 0, 0
        psq_st izz, 0x8(inv), 1, 0
    }
}
#endif

void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad) {
    f32 half, sh, ch;
    Vec nAxis;

    ASSERTMSGLINE(758, r, "QUATRotAxisRad():  NULL QuaternionPtr 'r' ");
    ASSERTMSGLINE(759, axis, "QUATRotAxisRad():  NULL VecPtr 'axis' ");

    VECNormalize(axis, &nAxis);

    half = rad * 0.5f;
    sh = sinf(half);
    ch = cosf(half);

    r->x = sh * nAxis.x;
    r->y = sh * nAxis.y;
    r->z = sh * nAxis.z;
    r->w = ch;
}

void C_QUATSlerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t) {
    f32 theta, sin_th, cos_th;
    f32 tp, tq;

    ASSERTMSGLINE(869, p, "QUATSlerp():  NULL QuaternionPtr 'p' ");
    ASSERTMSGLINE(870, q, "QUATSlerp():  NULL QuaternionPtr 'q' ");
    ASSERTMSGLINE(871, r, "QUATSlerp():  NULL QuaternionPtr 'r' ");
    
    cos_th = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;
    tq = 1.0f;

    if (cos_th < 0.0f) {
        cos_th = -cos_th;
        tq = -tq;
    }

    if (cos_th <= 0.99999f) {
        theta = acosf(cos_th);
        sin_th = sinf(theta);

        tp = sinf((1.0f - t) * theta) / sin_th;
        tq *= sinf(t * theta) / sin_th;
    } else {
        tp = 1.0f - t;
        tq *= t;
    }

    r->x = (tp * p->x) + (tq * q->x);
    r->y = (tp * p->y) + (tq * q->y);
    r->z = (tp * p->z) + (tq * q->z);
    r->w = (tp * p->w) + (tq * q->w);
}
