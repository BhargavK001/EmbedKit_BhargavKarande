#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// size must be power of 2 so the bitwise AND trick works
#define BUFFER_SIZE 8

#define RB_OK       0
#define RB_FULL    -1
#define RB_EMPTY   -2

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head;   // write side
    uint8_t tail;   // read side
    uint8_t count;  // tracks how many bytes are in buffer right now
} RingBuffer;

void rb_init(RingBuffer *rb)
{
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;
}

bool rb_is_full(RingBuffer *rb)
{
    return (rb->count == BUFFER_SIZE);
}

bool rb_is_empty(RingBuffer *rb)
{
    return (rb->count == 0);
}

/*
 * Write one byte into the buffer.
 * Returns RB_FULL if no space -- we never overwrite unread data.
 *
 * head wrap: using & (BUFFER_SIZE - 1) instead of % BUFFER_SIZE
 * both give same result but & is single instruction on MCU,
 * % compiles to division which is slow on chips without hardware divider.
 * this only works when BUFFER_SIZE is a power of 2.
 */
int8_t rb_write(RingBuffer *rb, uint8_t data)
{
    if (rb_is_full(rb)) {
        return RB_FULL;
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) & (BUFFER_SIZE - 1);
    rb->count++;

    return RB_OK;
}

// Read one byte out, tail moves forward same way as head
int8_t rb_read(RingBuffer *rb, uint8_t *out)
{
    if (rb_is_empty(rb)) {
        return RB_EMPTY;
    }

    *out = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) & (BUFFER_SIZE - 1);
    rb->count--;

    return RB_OK;
}

int main(void)
{
    RingBuffer rb;
    rb_init(&rb);

    uint8_t val;

    // fill buffer with 0x41 to 0x48 ('A' to 'H' in ASCII)
    for (uint8_t i = 0x41; i <= 0x48; i++) {
        rb_write(&rb, i);
        printf("[WRITE] 0x%02X -> OK (count=%d)%s\n",
               i, rb.count,
               rb_is_full(&rb) ? " FULL" : "");
    }

    // buffer is full now, this write should fail
    if (rb_write(&rb, 0x99) == RB_FULL) {
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");
    }

    // read 3 bytes out, frees 3 slots
    for (uint8_t i = 0; i < 3; i++) {
        if (rb_read(&rb, &val) == RB_OK) {
            printf("[READ] -> 0x%02X (count=%d)\n", val, rb.count);
        }
    }

    // write 3 new bytes into the freed slots
    uint8_t new_data[] = {0x49, 0x4A, 0x4B};
    for (uint8_t i = 0; i < 3; i++) {
        rb_write(&rb, new_data[i]);
        printf("[WRITE] 0x%02X -> OK (count=%d)%s\n",
               new_data[i], rb.count,
               rb_is_full(&rb) ? " FULL" : "");
    }

    // drain everything remaining
    while (!rb_is_empty(&rb)) {
        rb_read(&rb, &val);
        printf("[READ] -> 0x%02X (count=%d)\n", val, rb.count);
    }

    // buffer empty now, read should fail
    if (rb_read(&rb, &val) == RB_EMPTY) {
        printf("[READ] (empty) -> FAIL (buffer empty)\n");
    }

    return 0;
}
