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

#ifndef MY_MOUSE_SOURCE_MOUSE_H_BIT_MATRIX_H
#define MY_MOUSE_SOURCE_MOUSE_H_BIT_MATRIX_H

#include <stdbool.h>  // bool
#include <stdlib.h>   // malloc

#include "structures.h"      // dimensions, string
#include "my_stdio.h"        // my_printf, my_perror
#include "my_stdlib.h"       // my_div
#include "my_math.h"         // ceiling_divide
#include "fill_bitmap.h"     // fill_bit_map
#include "get_dimensions.h"  // print_dimensions

// Initializes the bit_matrix structure.
struct bit_matrix* bit_matrix_initialize(struct bit_matrix* map,
                                         struct dimensions dimensions);

#endif  // MY_MOUSE_SOURCE_MOUSE_H_BIT_MATRIX_H
