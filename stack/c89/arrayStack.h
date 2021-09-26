/* 顺序栈
  优点：适用于任何数据结构，不破坏原有数据结构，
  缺点：存储的是副本，有拷贝操作，需要额外的内存，使用完成后要销毁栈释放内存。
 */
#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_
#include <stdio.h>

typedef struct {
    void *data;         /* 内存指针 */
    int   index;        /* 栈顶元素下标，-1表示为空 */
    size_t cell;        /* sizeof(T)  每个元素占用的字节数 */
    size_t capacity;    /* 已分配内存能容纳的元素个数 */
} arrayStack;

arrayStack *arrayStackInit(size_t size);

void arrayStackDestroy(arrayStack *handle);

void arrayStackClear(arrayStack *handle);

char arrayStackEmpty(const arrayStack *handle);

size_t arrayStackSize(const arrayStack *handle);

size_t arrayStackCapacity(const arrayStack *handle);

void *arrayStackTop(const arrayStack *handle);

void arrayStackPush(arrayStack *handle, const void *ele);

int arrayStackPop(arrayStack *handle);

#endif /* !_ARRAY_STACK_ */
