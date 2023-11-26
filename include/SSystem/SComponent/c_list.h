#ifndef C_LIST_H
#define C_LIST_H

typedef struct node_class node_class;

typedef struct node_list_class {
    /* 0x00 */ node_class* mpHead;
    /* 0x04 */ node_class* mpTail;
    /* 0x08 */ int mSize;
} node_list_class;

void cLs_Init(node_list_class* pList);
int cLs_SingleCut(node_class* pNode);
int cLs_Addition(node_list_class* pList, node_class* pNode);
int cLs_Insert(node_list_class* pList, int idx, node_class* pNode);
node_class* cLs_GetFirst(node_list_class* pList);
void cLs_Create(node_list_class* pList);

#define LIST_GET_HEAD(pList) ((pList)->mpHead)

#endif /* C_LIST_H */
