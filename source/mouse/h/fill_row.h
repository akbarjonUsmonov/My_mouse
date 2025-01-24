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

#ifndef MY_MOUSE_SOURCE_MOUSE_H_FILL_ROW_H
#define MY_MOUSE_SOURCE_MOUSE_H_FILL_ROW_H

#include "structures.h"  // dimensions, string
#include "my_stdio.h"    // my_printf, my_perror

// Fills a row of the bitmap, checks for errors on its way.
uint16_t fill_row(struct mouse_map* map, struct string buffer,
                  struct dimensions coordinates, uint16_t i, bool* error);

#endif  // MY_MOUSE_SOURCE_MOUSE_H_FILL_ROW_H
