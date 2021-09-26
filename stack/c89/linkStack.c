
#include <stdio.h>
/* #define NDEBUG */
#include <assert.h>
#include "linkStack.h"

#define TOP next

void linkStackInit(linkStack *handle) {
    assert(handle);
    handle->TOP = handle;
}

void linkStackPush(linkStack *handle, linkNode *node) {
    assert(handle && node);
    linkNode *top = handle->TOP;
    handle->TOP = node;
    node->next = top;
}

linkNode *linkStackTop(linkStack *handle) {
    assert(handle);
    return handle->TOP;
}

char linkStackEmpty(linkStack *handle) {
    assert(handle);
    return handle->TOP == handle;
}

void linkStackPop(linkStack *handle) {
    assert(handle);
    handle->TOP = handle->TOP->next;
}

size_t linkStackSize(const linkStack *handle) {
    size_t count = 0;
    if (!handle) return 0;
    linkNode *pos = handle->TOP;
    for ( ; pos != handle; pos = pos->next, count++);
    return count;
}
