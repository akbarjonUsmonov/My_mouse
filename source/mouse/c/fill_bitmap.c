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

#include "fill_bitmap.h"

// Checks the line's length.
bool fill_map_advance_rows(struct dimensions* coordinates,
                           struct mouse_map* map)
{
    bool error = false;
    if (coordinates->base.columns < map->bitmap->dimensions.base.columns - 1)
    {
        my_perror("Too short line");
        error = true;
    }
    coordinates->base.columns = 0;
    coordinates->base.rows++;
    return error;
}

// Iterates over the map's rows. Calls helper for a row. Returns the last one.
uint16_t fill_loop(struct mouse_map* map, struct string buffer,
                   struct dimensions coordinates, uint16_t i, bool* error)
{
    while (i < buffer.size && !*error)
    {
        if (buffer.string[i] == '\n')
        {
            i++;
            *error = fill_map_advance_rows(&coordinates, map);
        }
        if (coordinates.base.rows == map->bitmap->dimensions.base.rows)
        {
            my_perror("Too many lines");
            *error = true;
        }
        i += fill_row(map, buffer, coordinates, i, error) + 1;
        coordinates.base.rows++;
        coordinates.base.columns = 0;
    }
    return coordinates.base.rows;
}

// Converts the mark on the one-dimensional map representation to
// two-dimensional coordinates and passes them to the helper.
uint16_t fill_bit_map(struct mouse_map* map, struct string buffer,
                      uint32_t read_amount, bool* error)
{
    struct coordinates base = {0, 0};
    struct dimensions coordinates = {base, &dimensions_product};
    uint16_t i = 0;
    if (read_amount > 0)
    {
        struct div div =
            my_div(read_amount, map->bitmap->dimensions.base.columns + 1);
        coordinates.base.rows = div.quotient;
        coordinates.base.columns = div.remainder;
    }
    else
    {
        while (buffer.string[i] != '\n') i++;
        i++;
    }
    uint16_t last_row = fill_loop(map, buffer, coordinates, i, error);
    return last_row;
}
