/* 链式栈
 优点：1.只组织数据，不负责数据的创建和销毁。
       2.无内存消耗，无拷贝操作，节省内存、速度快。
 缺点：1.需要嵌入结构体一个节点。
      2.适用于结构体较大、数据结构复杂、拷贝代价大的情形。
      3.因为只负责组织数据，所以入栈的数据不能是临时对象。 
 */

#ifndef _LINK_STACK_
#define _LINK_STACK_

typedef struct _STNODE_ {
    struct _STNODE_ *next;
} linkNode, linkStack;

#define STACK_ENTRY(ptr, type, member)                           \
        ((type *)((char *)ptr - (size_t)&((type *)0)->member))

void linkStackInit(linkStack *handle);

void linkStackPush(linkStack *handle, linkNode *node);

linkNode *linkStackTop(linkStack *handle);

char linkStackEmpty(linkStack *handle);

void linkStackPop(linkStack *handle);

size_t linkStackSize(const linkStack *handle);

#endif

