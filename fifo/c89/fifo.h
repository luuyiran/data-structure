/**
 * modified from linux/kfifo.h/.c
*/
#ifndef __K_FIFO_H__
#define __K_FIFO_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#ifndef min
#define min(x,y) ({         \
    typeof(x) _x = (x);     \
    typeof(y) _y = (y);     \
    (void) (&_x == &_y);    \
    _x < _y ? _x : _y; })
#endif /* min */
#ifndef max
#define max(x,y) ({         \
    typeof(x) _x = (x);     \
    typeof(y) _y = (y);     \
    (void) (&_x == &_y);    \
    _x > _y ? _x : _y; })
#endif /* max */

typedef struct _FIFO_ {
    uint8_t     *buffer;    /* the buffer holding the data */
    uint32_t    size;       /* the size of the allocated buffer */
    uint32_t    in;         /* data is added at offset (in % size) */
    uint32_t    out;        /* data is extracted from off. (out % size) */
} FIFO;

/**
 * http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
 */
static bool is_power_of_2(uint32_t v) {
    return (v != 0 && ((v & (v - 1)) == 0));
}

static uint32_t roundup_pow_of_two(uint32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
/* size have to be a power of 2 */
static FIFO *fifo_init(uint32_t size) {
    assert(size);
    if (!is_power_of_2(size)) {
        printf("fifo round up: %d\n", size);
        size = roundup_pow_of_two(size);
    }
    printf("fifo size: %d\n", size);
    FIFO *fifo = (FIFO *)malloc(sizeof(FIFO));
    assert(fifo);
    fifo->buffer = (uint8_t *)malloc(size);
    assert(fifo->buffer);
    fifo->size = size;
    fifo->in = fifo->out = 0;
    return fifo;
}

static void fifo_free(FIFO *fifo) {
    assert(fifo);
    assert(fifo->buffer);
    free(fifo->buffer);
    free(fifo);
}

static uint32_t fifo_put(FIFO *fifo, uint8_t *buffer, uint32_t len) {
    uint32_t l;
    len = min(len, fifo->size - fifo->in + fifo->out);
    /* first put the data starting from fifo->in to buffer end */
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);
    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + l, len - l);
    fifo->in += len;
    return len;
}

static uint32_t fifo_get(FIFO *fifo, uint8_t *buffer, uint32_t len) {
    uint32_t l;

    len = min(len, fifo->in - fifo->out);
    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, fifo->buffer, len - l);
    fifo->out += len;

    return len;
}

static bool empty(FIFO* fifo) {
    assert(fifo);
    return fifo->in == fifo->out;
}

#endif /* __K_FIFO_H__ */
