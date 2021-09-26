#ifndef __LIST__
#define __LIST__

#define HEAD    next       /* first node in list */
#define TAIL    previous   /* last node in list */

#define LIST_ENTRY(ptr, type, member)                           \
        ((type *)((char *)ptr - (size_t)&((type *)0)->member))

#define LIST_FOR_EACH(pos, list)    \
        for(pos = lstFirst(list);   \
            pos != list;            \
            pos = pos->next)

/* initializes a list descriptor */
#define LIST_HEAD_INIT(name) { &(name), &(name) } 

typedef struct _NODE_ {       /* node of a linked list. */
    struct _NODE_ *next;      /* Points at the next node in the list */
    struct _NODE_ *previous;  /* Points at the previous node in the list */
} NODE;


/* initializes a list descriptor */
void lstInit(NODE* list);

/* find first node in list */
NODE* lstFirst(NODE* list);

/* find last node in a list */
NODE* lstLast(NODE* list);

/* find the next node in a list */
NODE *lstNext(NODE *node);

/* get the list empty status */
int lstEmpty(NODE* list);

/* report the number of nodes in a list */
int lstCount(NODE *list);

/* insert a node in a list after a specified node */
void lstInsertAfter(NODE* pre, NODE* _new);

/* add a node to the end of a list */
void lstAdd(NODE* list, NODE* _new);

void __lstDelete(NODE *prev, NODE *next);

/* delete a specified node from a list */
void lstDelete(NODE* entry);

#endif /* !__LIST__ */
