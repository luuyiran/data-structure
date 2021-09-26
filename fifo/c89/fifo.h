#ifndef __K_FIFO_H
#define __K_FIFO_H

#include <string.h>
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

/* size have to be a power of 2 */
static FIFO *fifo_init(uint32_t size) {
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

uint32_t fifo_put(FIFO *fifo, uint8_t *buffer, uint32_t len) {
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

uint32_t fifo_get(FIFO *fifo, uint8_t *buffer, uint32_t len) {
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


#endif /* __K_FIFO_H */
