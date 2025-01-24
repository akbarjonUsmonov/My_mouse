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

#ifndef MY_MOUSE_SOURCE_MOUSE_H_STACK_H
#define MY_MOUSE_SOURCE_MOUSE_H_STACK_H

#include <stdlib.h>

#include "structures.h"

struct stack_node
{
    struct coordinates data;
    struct stack_node* next;
};

struct stack
{
    struct stack_node* node;
    struct stack_vtable* vtable;
};

struct stack_vtable
{
    void (*push)(struct stack*, struct coordinates);
    struct coordinates (*pop)(struct stack* base);
    struct coordinates (*peek)(struct stack* base);
    void (*deconstruct)(struct stack*);
};

// Creates a stack structure.
struct stack* create_stack();

#endif  // MY_MOUSE_SOURCE_MOUSE_H_STACK_H
