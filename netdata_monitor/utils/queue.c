#include <FreeRTOS.h>

#include "../config.h"
#include "utils.h"

void queue_init(queue_t *q) {
    q->head.next = NULL;
    q->tail = &(q->head);
}

void queue_enqueue_raw(queue_t *q, node_t *n) {
    q->tail->next = n;
    q->tail = n;
}

void queue_enqueue(queue_t *q, void *d) {
    node_t *n = pvPortMalloc(sizeof(node_t));
    n->data = d;
    n->next = NULL;
    queue_enqueue_raw(q, n);
}

node_t *queue_dequeue_raw(queue_t *q) {
    if (q->head.next == NULL) return NULL;
    node_t *old = q->head.next;
    q->head.next = old->next;
    if (old == q->tail) q->tail = &(q->head);
    return old;
}

void *queue_dequeue(queue_t *q) {
    node_t *old = queue_dequeue_raw(q);
    if (old == NULL) return NULL;
    void *d = old->data;
    vPortFree(old);
    return d;
}

int queue_isempty(queue_t *q) {
    return &(q->head) == q->tail;
}
