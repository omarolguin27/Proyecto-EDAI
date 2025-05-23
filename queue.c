#include "queue.h"
#include <stdio.h>
#include <string.h>

Queue* Queue_New(size_t capacity) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    if (q != NULL) {
        q->queue = (Pedido*) malloc(sizeof(Pedido) * capacity);
        if (q->queue != NULL) {
            q->capacity = capacity;
            q->front = q->back = q->len = 0;
        } else {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void Queue_Delete(Queue** this) {
    assert(*this);
    free((*this)->queue);
    free(*this);
    *this = NULL;
}

static void Queue_Resize(Queue* this) {
    size_t newCapacity = this->capacity * 2;
    Pedido* newQueue = (Pedido*) malloc(sizeof(Pedido) * newCapacity);

    if (newQueue == NULL) {
        fprintf(stderr, "Error: No se pudo redimensionar la cola.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < this->len; i++) {
        newQueue[i] = this->queue[(this->front + i) % this->capacity];
    }

    free(this->queue);
    this->queue = newQueue;
    this->capacity = newCapacity;
    this->front = 0;
    this->back = this->len;
}

void Queue_Enqueue(Queue* this, Pedido val) {
    if (Queue_IsFull(this)) {
        Queue_Resize(this);
    }

    this->queue[this->back] = val;
    this->back = (this->back + 1) % this->capacity;
    this->len++;
}

Pedido Queue_Dequeue(Queue* this) {
    Pedido val = {0};
    if (!Queue_IsEmpty(this)) {
        val = this->queue[this->front];
        this->front = (this->front + 1) % this->capacity;
        this->len--;
    } else {
        printf("Cola vacía.\n");
    }
    return val;
}

Pedido Queue_Front(Queue* this) {
    Pedido val = {0};
    if (!Queue_IsEmpty(this)) {
        val = this->queue[this->front];
    } else {
        printf("Cola vacía.\n");
    }
    return val;
}

size_t Queue_Len(Queue* this) {
    return this->len;
}

int Queue_IsEmpty(Queue* this) {
    return this->len == 0;
}

int Queue_IsFull(Queue* this) {
    return this->len == this->capacity;
}

