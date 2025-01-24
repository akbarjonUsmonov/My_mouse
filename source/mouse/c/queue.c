/*Copyright (C) 2023 Timur Timak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program. If not, see
<https://www.gnu.org/licenses/>. */

#include "queue.h"

void deconstruct_queue(struct queue* queue)
{
    while (queue->front) queue->vtable->out(queue);
    free(queue->vtable);
    free(queue);
}

struct coordinates queue_peek(struct queue* queue)
{
    struct coordinates result = {0, 0};
    if (queue->front)
    {
        result.columns = queue->front->pack.columns;
        result.rows = queue->front->pack.rows;
    }
    return result;
}

struct queue_vtable* create_queue_vtable()
{
    struct queue_vtable* vtable = malloc(sizeof(struct queue_vtable));
    vtable->in = &enqueue;
    vtable->out = &dequeue;
    vtable->peek = &queue_peek;
    vtable->deconstruct = &deconstruct_queue;
    return vtable;
}

struct queue* create_queue()
{
    struct queue* queue = malloc(sizeof(struct queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->vtable = create_queue_vtable();
    return queue;
}

struct queue_node* new_queue_node(struct coordinates pack)
{
    struct queue_node* new = malloc(sizeof(struct queue_node));
    new->pack.columns = pack.columns;
    new->pack.rows = pack.rows;
    new->next = NULL;
    return new;
}

void enqueue(struct queue* queue, uint16_t x, uint16_t y)
{
    struct coordinates pack = {y, x};
    struct queue_node* new = new_queue_node(pack);
    if (queue->rear) queue->rear->next = new;
    if (!queue->rear) queue->front = new;
    queue->rear = new;
}

struct coordinates dequeue(struct queue* queue)
{
    struct queue_node* temp = queue->front;
    struct coordinates pack = temp->pack;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    return pack;
}
