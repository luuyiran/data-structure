#include <stdlib.h>
#include <string.h>

/* #define NDEBUG */
#include <assert.h>

#include "arrayStack.h"

#define INIT_SIZE 100   /* 初始化默认容量 */
#define INCREMENT 20    /* 容量不够时，每次递增的空间 */

arrayStack *arrayStackInit(size_t size) {
    void *data = calloc(INIT_SIZE, size);
    arrayStack *handle = calloc(1, sizeof(arrayStack));
    assert(data && handle);
    handle->data = data;
    handle->index= -1;
    handle->cell = size;
    handle->capacity = INIT_SIZE;
    return handle;
}

void arrayStackDestroy(arrayStack *handle) {
    if (handle) {
        if (handle->data)
            free(handle->data);
        handle->data = NULL;
        free(handle);
    }
}

void arrayStackClear(arrayStack *handle) {
    if (handle) handle->index = -1;
}

char arrayStackEmpty(const arrayStack *handle) {
    if (!handle) return 1;
    return handle->index == -1;
}

size_t arrayStackSize(const arrayStack *handle) {
    if (!handle) return 0;
    return handle->index + 1;
}

size_t arrayStackCapacity(const arrayStack *handle) {
    if (!handle) return 0;
    return handle->capacity;
}

void *arrayStackTop(const arrayStack *handle) {
    if (arrayStackEmpty(handle)) return NULL;

    return handle->data + handle->index * handle->cell;
}

void arrayStackPush(arrayStack *handle, const void *ele) {
    assert(handle && ele);
    if (arrayStackSize(handle) >= arrayStackCapacity(handle)) {
        handle->data = realloc(handle->data, (handle->capacity + INCREMENT)*handle->cell);
        assert(handle->data);
        handle->capacity += INCREMENT;
    }
    handle->index++;
    memcpy(handle->data + handle->index * handle->cell, ele, handle->cell);
}

int arrayStackPop(arrayStack *handle) {
    if (!handle || arrayStackEmpty(handle)) return -1;
    handle->index--;
    return 0;
}
