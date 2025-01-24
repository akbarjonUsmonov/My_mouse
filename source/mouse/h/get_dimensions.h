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

#ifndef MY_MOUSE_SOURCE_MOUSE_H_GET_DIMENSIONS_H
#define MY_MOUSE_SOURCE_MOUSE_H_GET_DIMENSIONS_H

#include <stdbool.h>  // bool
#include <stdint.h>   // uint16_t
#include <stdlib.h>   // malloc

#include "my_stdio.h"    // my_perror
#include "structures.h"  // dimensions, string

// Gets map dimensions from a file.
struct dimensions get_dimensions(struct string buffer, bool* error);

#endif  // MY_MOUSE_SOURCE_MOUSE_H_GET_DIMENSIONS_H
