#ifndef __LW_ARRAY_H__
#define __LW_ARRAY_H__
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ARRAY_INIT_SIZE 100   /* 初始化默认容量 */
#define ARRAY_INCREMENT 32    /* 容量不够时，每次递增的空间 */

#define BUF_HEAD(ptr)   ((size_t *)ptr - 2)

#define array_free(ptr) free(BUF_HEAD(ptr))
#define array_size(ptr)  (BUF_HEAD(ptr)[0])
#define array_capacity(ptr)  (BUF_HEAD(ptr)[1])

#define arry_begin(ptr)     (ptr)
#define array_end(ptr)      (ptr + array_size(ptr))

#define array_push_back(ptr, val)  do_array_push_back((void **)&ptr, &val, sizeof(val))

static void do_array_push_back(void **ptr, void *src, size_t item_len) {
    size_t *buf = NULL;

    assert(ptr);
    if (*ptr == NULL) {  /* 第一次保存数据 */
        size_t capcity = ARRAY_INIT_SIZE;
        /* 分配capacity 容量 和 两个字节保存 size 和 capacity */
        buf = (size_t *)calloc(1, capcity * item_len + 2 * sizeof(size_t));
        assert(buf);
        buf[0] = 0;
        buf[1] = capcity;
        *ptr = &buf[2];
    } else {
        buf = BUF_HEAD(*ptr);
        if (buf[0] == buf[1]) {
            buf[1] += ARRAY_INCREMENT;
            buf = (size_t *)realloc(buf, item_len * buf[1] + 2 * sizeof(size_t));
            assert(buf);
            *ptr = &buf[2];
        }
    }
    memcpy(*ptr + item_len * buf[0], src, item_len);
    buf[0]++;
}

/*
 * ----------------.EXAMPLE -------------------------
 * int main() {
 *      _Ty *a = NULL;
 *      {
 *          _Ty item;
 *          // construct item
 *          array_push_back(a, item);
 *      }
 *      array_free(a);
 * }
 * 
 * --------------------------------------------------
 */


#endif /* !__LW_ARRAY_H__ */
