#ifndef __UTILS_H__
#define __UTILS_H__

// queue
typedef struct __node_t {
    void *data;
    struct __node_t *next;
} node_t;

typedef struct {
    node_t head;
    node_t *tail;
} queue_t;

void queue_init(queue_t *q);
void queue_enqueue(queue_t *q, void *d);
void *queue_dequeue(queue_t *q);
int queue_isempty(queue_t *q);

#endif
