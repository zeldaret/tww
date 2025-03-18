#ifndef C_PHASE_H
#define C_PHASE_H

typedef int cPhs_State;
enum {
    /* 0x0 */ cPhs_INIT_e,
    /* 0x1 */ cPhs_LOADING_e,
    /* 0x2 */ cPhs_NEXT_e,
    /* 0x3 */ cPhs_STOP_e, // similar to error, except doesn't indicate anything bad
    /* 0x4 */ cPhs_COMPLEATE_e,
    /* 0x5 */ cPhs_ERROR_e,
};

typedef cPhs_State (*cPhs__Handler)(void*);
typedef cPhs_State (*request_of_phase_process_fn)(void*);

typedef struct request_of_phase_process_class {
    /* 0x00 */ cPhs__Handler* mpHandlerTable;
    /* 0x04 */ int id; // Index into the handler table
} request_of_phase_process_class;  // Size: 0x08

void cPhs_Reset(request_of_phase_process_class* pPhase);
void cPhs_Set(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable);
void cPhs_UnCompleate(request_of_phase_process_class* pPhase);
cPhs_State cPhs_Compleate(request_of_phase_process_class* pPhase);
cPhs_State cPhs_Next(request_of_phase_process_class* pPhase);
cPhs_State cPhs_Do(request_of_phase_process_class* pPhase, void* pUserData);
cPhs_State cPhs_Handler(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable,
                 void* pUserData);

#endif /* C_PHASE_H */
