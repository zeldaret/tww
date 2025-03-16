#ifndef D_A_OBJ_APZL_H
#define D_A_OBJ_APZL_H

#include "f_op/f_op_actor.h"

class daObjApzl_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void getblank() {}

    void move_piece();
    void check_arrow_draw();
    void search_piece(unsigned char);
    void swap_piece(unsigned char, unsigned char);
    void randamize_piece();
    void save_piece();
    void check_clear();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void talk(int);
    void privateCut();
    void CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_APZL_H */
