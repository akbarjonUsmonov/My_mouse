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

#ifndef MY_MOUSE_SOURCE_MOUSE_H_MOUSE_MAP_H
#define MY_MOUSE_SOURCE_MOUSE_H_MOUSE_MAP_H

#include <stdbool.h>  // bool
#include <stdlib.h>   // malloc

#include "structures.h"
#include "bit_matrix.h"  // bit_matrix_initialize

// Initializes the mouse_map structure.
struct mouse_map* mouse_map_initialize(struct mouse_map* map,
                                       struct dimensions dimensions);

#endif  // MY_MOUSE_SOURCE_MOUSE_H_MOUSE_MAP_H
