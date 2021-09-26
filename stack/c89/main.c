/* gcc main.c -W -Wall -std=c89  */
#include <stdio.h>

/* #define NDEBUG */
#include <assert.h>

#include "arrayStack.h"
#include "linkStack.h"

/********************************* Test *************************************/

typedef struct _DATA_ {
    char *name;
    char rank;
    linkNode node;
} DATA;

static DATA data[] = {
    {"1.bob", 100, {NULL}},
    {"2.Alice", 97, {NULL}},
    {"3.bruce", 95, {NULL}},
    {"4.trump", 89, {NULL}},
    {"5.lee", 77, {NULL}},
    {"6.Talor", 59, {NULL}},
    {NULL, -1, {NULL}}
};

/************************* Test Array Stack ********************************/
static void arrayStackTest1() {
    printf("\n=============== Array Stack ==============\n");
    arrayStack *handle = arrayStackInit(sizeof(DATA));
    assert(handle);
    int i;
    printf("size: %ld\tcapacity: %ld\n", arrayStackSize(handle), arrayStackCapacity(handle));
    printf("== start push ==\n");
    for (i = 0; data[i].name; i++) {
        printf("push:  %s\t%d ==\n", data[i].name, data[i].rank);
        arrayStackPush(handle, &data[i]);
    }
    printf("== push OK ==\n");
    printf("size: %ld\tcapacity: %ld\n", arrayStackSize(handle), arrayStackCapacity(handle));
    
    while (!arrayStackEmpty(handle)) {
        DATA *top = (DATA *)arrayStackTop(handle);
        printf("pop: %s\t%d\n", top->name, top->rank);
        arrayStackPop(handle);
    }
    printf("== empty ==\n");
    printf("size: %ld\tcapacity: %ld\n", arrayStackSize(handle), arrayStackCapacity(handle));
    arrayStackDestroy(handle);
}


/************************* Test Link Stack ********************************/

static void linkStackTest1() {
    printf("\n=============== Link Stack ===============\n");
    linkNode *pos = NULL;
    DATA *var = NULL;
    linkStack stack;
    linkStack *handle = &stack;
    linkStackInit(handle);
    int i;
    printf("size: %ld\n", linkStackSize(handle));
    printf("== start push ==\n");
    for (i = 0; data[i].name; i++) {
        printf("push:  %s\t%d ==\n", data[i].name, data[i].rank);
        linkStackPush(handle, &data[i].node);
    }
    printf("== push OK ==\n");
    printf("size: %ld\n", linkStackSize(handle));
    while (!linkStackEmpty(&stack)) {
        pos = linkStackTop(handle);
        var = STACK_ENTRY(pos, DATA, node);
        printf("pop: %s\t%d\n", var->name, var->rank);
        linkStackPop(handle);
    }
    printf("== empty ==\n");
    printf("size: %ld\n", linkStackSize(handle));
}

int main() {
    arrayStackTest1();
    linkStackTest1();
    return 0;
}

 
