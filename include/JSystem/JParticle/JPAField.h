#ifndef JPAFIELD_H
#define JPAFIELD_H

#include "JSystem/JParticle/JPAParticle.h"

class JPADataBlockLinkInfo;
class JPAEmitterInfo;
class JPAFieldData;

class JPAFieldManager {
public:
    void initField(JPADataBlockLinkInfo*, JPAEmitterInfo*);
    void init(JPABaseParticle*);
    void preCalc();
    void calc(JPABaseParticle*);
    void deleteField(JPAFieldData*);
    void deleteAllField();
    
    /* 0x00 */ JSUPtrList mList;
    /* 0x0C */ JSUPtrList* field_0x0c;
};

#endif /* JPAFIELD_H */
