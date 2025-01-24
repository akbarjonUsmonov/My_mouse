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

#include "stack.h"

void stack_push(struct stack* stack, struct coordinates data)
{
    struct stack_node* node = malloc(sizeof(struct stack_node));
    node->data = data;
    node->next = stack->node;
    stack->node = node;
}

struct coordinates stack_pop(struct stack* stack)
{
    struct stack_node* head = stack->node;
    struct coordinates popped = head->data;
    stack->node = head->next;
    free(head);
    return popped;
}

struct coordinates stack_peek(struct stack* stack)
{
    struct coordinates result = {0, 0};
    if (stack->node)
    {
        result.columns = stack->node->data.columns;
        result.rows = stack->node->data.rows;
    }
    return result;
}

void stack_deconstruct(struct stack* stack)
{
    while (stack->node) stack->vtable->pop(stack);
    free(stack->vtable);
    free(stack);
}

struct stack_vtable* create_stack_vtable()
{
    struct stack_vtable* vtable = malloc(sizeof(struct stack_vtable));
    vtable->push = &stack_push;
    vtable->pop = &stack_pop;
    vtable->peek = &stack_peek;
    vtable->deconstruct = &stack_deconstruct;
    return vtable;
}

struct stack* create_stack()
{
    struct stack* stack = malloc(sizeof(struct stack));
    stack->node = NULL;
    stack->vtable = create_stack_vtable();
    return stack;
}
