#ifndef D_MATERIAL_H
#define D_MATERIAL_H

class dMat_ice_c {
public:
    void play();
};

class dMat_control_c {
public:
    static void icePlay() { mIce->play(); }
    static void create(J3DMaterialTable*, J3DAnmTextureSRTKey*);

    static dMat_ice_c* mIce;
};

#endif /* D_MATERIAL_H */