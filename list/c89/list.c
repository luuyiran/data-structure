#include "list.h"

/* initializes a list descriptor */
void lstInit(NODE* list){
    list->HEAD  = list;
    list->TAIL  = list;
}

/* find first node in list */
NODE* lstFirst(NODE* list){
    return (list->HEAD);
}

/* find last node in a list */
NODE* lstLast(NODE* list){
    return (list->TAIL);
}

/* find the next node in a list */
NODE *lstNext(NODE *node){
    return (node->next);
}

/* get the list empty status */
int lstEmpty(NODE* list){
    return (list->HEAD == list) && (list->TAIL == list);
}

/* report the number of nodes in a list */
int lstCount(NODE *list){
    int count = 0;
    NODE *node = lstFirst(list);
    for (; node != list; node = lstNext(node), count++);
    return count;
}

/* insert a node in a list after a specified node */
void lstInsertAfter(NODE* pre, NODE* _new){
    NODE *next = pre->next;
    pre->next = _new;
    _new->next = next;
    _new->previous = pre;
    next->previous = _new;
}

/* add a node to the end of a list */
void lstAdd(NODE* list, NODE* _new){
    lstInsertAfter(list->TAIL, _new);
}

void __lstDelete(NODE *prev, NODE *next){
    next->previous = prev;
    prev->next = next;
}

/* delete a specified node from a list */
void lstDelete(NODE* entry){
    __lstDelete(entry->previous, entry->next);
/*  entry->next = NULL;
    entry->previous = NULL; */
}
