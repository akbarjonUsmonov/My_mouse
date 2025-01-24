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

#ifndef MY_MOUSE_SOURCE_LIB_H_STRUCTURES_H_
#define MY_MOUSE_SOURCE_LIB_H_STRUCTURES_H_

#include <stdint.h>  // uint16_t
#include <stdbool.h> // bool

struct coordinates
{
    uint16_t rows;
    uint16_t columns;
};

struct dimensions
{
    struct coordinates base;
    uint32_t (*product)(struct dimensions*);
};

uint32_t dimensions_product(struct dimensions* dimensions);

struct string
{
    char* string;
    unsigned size;
};

struct mouse_map;

struct bit_matrix
{
    struct dimensions dimensions;
    uint8_t* row;
    struct bit_matrix_vtable* vtable;
    uint16_t (*fill)(struct mouse_map*, struct string, uint32_t, bool*);
};

struct bit_matrix_vtable
{
    void (*set_bit)(struct bit_matrix*, struct dimensions, bool);
    uint8_t (*get_bit)(struct bit_matrix*, uint16_t, uint16_t);
    struct bit_matrix* (*initialize)(struct bit_matrix*, struct dimensions);
    void (*deconstruct)(struct bit_matrix*);
};

struct mouse_map
{
    struct bit_matrix* bitmap;
    struct coordinates entrance;
    struct coordinates exit;
    struct string tiles;
    struct mouse_map_vtable* vtable;
};

struct mouse_map_vtable
{
    struct mouse_map* (*initialize)(struct mouse_map*, struct dimensions);
    void (*deconstruct)(struct mouse_map*);
};

struct largest_square
{
    struct coordinates base;
    uint16_t side;
};

#endif  // MY_MOUSE_SOURCE_LIB_H_STRUCTURES_H_
