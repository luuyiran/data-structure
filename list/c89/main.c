#include <stdio.h>
#include "list.h"

typedef struct __DATA__ {
    int id;
    NODE  node;
    char data[6];
} DATA;

/* static NODE list = LIST_HEAD_INIT(list); */  /* or use lstInit() to initialize */

static DATA data0 = {
    .node = LIST_HEAD_INIT(data0.node),
    .id = 0,
    .data = "data0"
};

static DATA data1 = {
    .node = LIST_HEAD_INIT(data1.node),
    .id = 1,
    .data = "data1"
};

static DATA data2 = {
    .node = LIST_HEAD_INIT(data2.node),
    .id = 2,
    .data = "data2"
};

static DATA data3 = {
    .node = LIST_HEAD_INIT(data3.node),
    .id = 3,
    .data = "data3"
};

static void printAddr(NODE* list){
    NODE *node = lstFirst(list);
    printf("list: %p\n", list);
    while(node != list) {
        printf("%p -> ", node);
        node = lstNext(node);
    }
    printf("%p", node);
    printf("\n========================\n\n");
}

static void test1() {
    NODE *pos = NULL;
    DATA *var = NULL;
    NODE list;
    lstInit(&list);

    /* test add elemens */
#if 1
    /* add to tail */
    lstAdd(&list, &data0.node);
    lstAdd(&list, &data1.node);
    lstAdd(&list, &data2.node);
    lstAdd(&list, &data3.node);
#else 
    /* add to front */
    lstInsertAfter(&list, (NODE*) &data0);
    lstInsertAfter(&list, (NODE*) &data1);
    lstInsertAfter(&list, (NODE*) &data2);
    lstInsertAfter(&list, (NODE*) &data3);
#endif 

    printAddr(&list);
    printf("%d elemens in the list [%p]:\n", lstCount(&list), &list);
    LIST_FOR_EACH(pos, &list) {
        var = LIST_ENTRY(pos, DATA, node);
        printf("id:%d\t%s\t%p\n", var->id, var->data, var);
    }


    printf("========================\n");
    
    /* test deleted elements */
    while (!lstEmpty(&list)) {
        pos = lstFirst(&list);
        var = LIST_ENTRY(pos, DATA, node);
        printf("id:%d\t%s ==> to be deleted\n", var->id, var->data);
        lstDelete(pos);
        printf("after deleted: left %d elemens in list\n", lstCount(&list));
        LIST_FOR_EACH(pos, &list) {
            var = LIST_ENTRY(pos, DATA, node);
            printf("id:%d\t%s\t%p\n", var->id, var->data, var);
        }
        printf("========================\n");
    }
}



int main() {
    test1();
    return 0;
}


