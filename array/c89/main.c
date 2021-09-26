#include <stdio.h>
#include <stdint.h>
#include "array.h"

typedef struct _DATA_ {
    uint64_t id;
    uint64_t buf[64];
    uint8_t name[128];
} DATA;


static void test1() {
    int *nums = NULL;
    int i = 0;
    for (i = 0; i < 16; i++) {
        array_push_back(nums, i);
        printf("insert %d,\tsize: %3ld\tcapacity: %3ld\n", i, array_size(nums), array_capacity(nums));
    }

    int *item;
    for (item = arry_begin(nums); item != array_end(nums); item++)
        printf("%d ", *item);
    printf("\n");
    printf("size: %ld\n\n", array_size(nums));
    array_free(nums);
}

static void test2() {
    int i = 0;
    DATA *d = NULL;
    for (i = 0; i < 16; i++) {
        DATA data;
        data.id = i;
        sprintf((char *)data.name, "index->%d", i+1);
        array_push_back(d,data);
        printf("id %d,\tsize: %3ld\tcapacity: %3ld\n", i, array_size(d), array_capacity(d));
    }

    DATA *item;
    for (item = arry_begin(d); item != array_end(d); item++) {
        printf("id: %ld\t%s\n", item->id, item->name);
    }
    array_free(d);
}

int main() {
    test1();
    test2();
    return 0;
} 


