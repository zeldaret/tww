#include "dolphin/gx/GXDraw.h"
#include "dolphin/gx/GX.h"
#include "math.h"

static GXVtxDescList vcd[27];
static GXVtxAttrFmtList vat[27];

void GetVertState(void) {
    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(GX_VTXFMT3, vat);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
}

void RestoreVertState(void) {
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(GX_VTXFMT3, vat);
}

// doesn't fully match debug
void GXDrawCylinder(u8 numEdges) {
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;

    s32 i;

    f32 sp1A0[100];
    f32 sp10[100];

    temp_f31 = 1.0f;
    temp_f30 = -temp_f31;

    GetVertState();
    for (i = 0; i <= numEdges; i++) {
        temp_f29 = (i * 2.0f * 3.141593f) / numEdges;
        sp1A0[i] = cosf(temp_f29);
        sp10[i] = sinf(temp_f29);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numEdges + 1) * 2);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(sp1A0[i], sp10[i], temp_f30);
        GXNormal3f32(sp1A0[i], sp10[i], 0.0f);
        GXPosition3f32(sp1A0[i], sp10[i], temp_f31);
        GXNormal3f32(sp1A0[i], sp10[i], 0.0f);
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, temp_f31);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(sp1A0[i], -sp10[i], temp_f31);
        GXNormal3f32(0.0f, 0.0f, 1.0f);
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, temp_f30);
    GXNormal3f32(0.0f, 0.0f, -1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(sp1A0[i], sp10[i], temp_f30);
        GXNormal3f32(0.0f, 0.0f, -1.0f);
    }
    GXEnd();

    RestoreVertState();
}

void GXDrawSphere(u8 numMajor, u8 numMinor) {
    GXAttrType ttype;
    f32 radius = 1.0f;
    f32 majorStep = 3.1415927f / numMajor;
    f32 minorStep = 6.2831855f / numMinor;
    s32 i, j;
    f32 a, b;
    f32 r0, r1;
    f32 z0, z1;
    f32 c;

    GXGetVtxDesc(GX_VA_TEX0, &ttype);
    GetVertState();

    if (ttype != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    }

    for (i = 0; i < numMajor; i++) {
        a = i * majorStep;
        b = a + majorStep;
        r0 = radius * sinf(a);
        r1 = radius * sinf(b);
        z0 = radius * cosf(a);
        z1 = radius * cosf(b);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numMinor + 1) * 2);
        for (j = 0; j <= numMinor; j++) {
            f32 x, y;
            c = j * minorStep;
            x = cosf(c);
            y = sinf(c);
            GXPosition3f32(x * r1, y * r1, z1);
            GXNormal3f32((x * r1) / radius, (y * r1) / radius, z1 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)(i + 1) / (f32)numMajor);
            }
            GXPosition3f32(x * r0, y * r0, z0);
            GXNormal3f32((x * r0) / radius, (y * r0) / radius, z0 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)i / (f32)numMajor);
            }
        }
        GXEnd();
    }
    RestoreVertState();
}
