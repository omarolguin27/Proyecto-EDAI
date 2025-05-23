#ifndef QUEUE_H
#define QUEUE_H

#include "pedido.h"
#include <stdlib.h>
#include <assert.h>

typedef struct {
    Pedido* queue;
    size_t capacity;
    size_t front;
    size_t back;
    size_t len;
} Queue;

Queue* Queue_New(size_t capacity);
void Queue_Delete(Queue** this);
void Queue_Enqueue(Queue* this, Pedido val);
Pedido Queue_Dequeue(Queue* this);
Pedido Queue_Front(Queue* this);  // <-- Nueva función
size_t Queue_Len(Queue* this);
int Queue_IsEmpty(Queue* this);
int Queue_IsFull(Queue* this);

#endif
