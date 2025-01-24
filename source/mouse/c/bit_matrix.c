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

#include "bit_matrix.h"

// Performs bit shiftings to help map the file to memory.
void bit_matrix_set_bit(struct bit_matrix* map, struct dimensions coordinates,
                        bool value)
{
    uint32_t index = map->dimensions.base.columns * coordinates.base.rows +
                     coordinates.base.columns;
    struct div div = my_div(index, 8);
    if (value)
    {
        map->row[div.quotient] |= 1 << div.remainder;
    }
    else
    {
        map->row[div.quotient] &= ~(1 << div.remainder);
    }
}

// Masks the relevant byte of the matrix to get the required bit.
uint8_t bit_matrix_get_bit(struct bit_matrix* map, uint16_t x, uint16_t y)
{
    uint32_t index = map->dimensions.base.columns * y + x;
    struct div div = my_div(index, 8);
    uint8_t row = map->row[div.quotient];
    uint8_t mask = 1 << div.remainder;
    uint8_t masked_row = row & mask;
    uint8_t bit = masked_row >> div.remainder;
    return bit;
}

void bit_matrix_deconstruct(struct bit_matrix* map)
{
    free(map->row);
    free(map->vtable);
    free(map);
}

// Allocates and fills in all the nested structures' function pointers.
struct bit_matrix* bit_matrix_initialize(struct bit_matrix* map,
                                         struct dimensions dimensions)
{
    map = malloc(sizeof(struct bit_matrix));
    map->dimensions = dimensions;
    uint32_t product = map->dimensions.product(&map->dimensions);
    uint32_t bytes_number = ceiling_divide(product, 8);
    map->row = malloc(bytes_number);
    if (!map->row) my_perror("Cannot allocate map->row");
    map->vtable = malloc(sizeof(struct bit_matrix_vtable));
    map->vtable->set_bit = &bit_matrix_set_bit;
    map->vtable->get_bit = &bit_matrix_get_bit;
    map->vtable->initialize = &bit_matrix_initialize;
    map->vtable->deconstruct = &bit_matrix_deconstruct;
    map->fill = &fill_bit_map;
    return map;
}
