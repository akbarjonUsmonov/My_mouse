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

#include "fill_row.h"

// Checks the amount of entrances.
bool fill_row_entrance(struct dimensions coordinates, struct mouse_map* map)
{
    bool error = false;
    if (map->entrance.rows == (uint16_t)-1)
    {
        map->entrance = coordinates.base;
    }
    else
    {
        my_perror("More than one entrance");
        error = true;
    }
    return error;
}

// Checks the amount of exits.
bool fill_row_exit(struct dimensions coordinates, struct mouse_map* map)
{
    bool error = false;
    if (map->exit.rows == (uint16_t)-1)
    {
        map->exit = coordinates.base;
    }
    else
    {
        my_perror("More than one exit");
        error = true;
    }
    return error;
}

// Sets the bits of the bitmap.
void fill_row_bits(struct dimensions coordinates, struct mouse_map* map,
                   char character)
{
    if (character == map->tiles.string[0])
    {
        map->bitmap->vtable->set_bit(map->bitmap, coordinates, true);
    }
    else if (character == map->tiles.string[1])
    {
        map->bitmap->vtable->set_bit(map->bitmap, coordinates, false);
    }
}

// Saves the exits' coordinates to the mouse_map structure.
bool fill_row_exits(struct dimensions coordinates, struct mouse_map* map,
                    char character)
{
    bool error = false;
    if (character == map->tiles.string[3])
    {
        error = fill_row_entrance(coordinates, map);
    }
    else if (character == map->tiles.string[4])
    {
        error = fill_row_exit(coordinates, map);
    }
    return error;
}

// Calls one of two helpers in one of two cases.
bool fill_row_cases(struct mouse_map* map, struct dimensions coordinates,
                    char character)
{
    bool error = false;
    if (character == map->tiles.string[0] || character == map->tiles.string[1])
    {
        fill_row_bits(coordinates, map, character);
    }
    else if (character == map->tiles.string[3] ||
             character == map->tiles.string[4])
    {
        error = fill_row_exits(coordinates, map, character);
        map->bitmap->vtable->set_bit(map->bitmap, coordinates, false);
    }
    else
    {
        my_perror("File is broken");
        error = true;
    }
    return error;
}

// Checks the current line and writes it to the mouse_map structure.
uint16_t fill_row(struct mouse_map* map, struct string buffer,
                  struct dimensions coordinates, uint16_t i, bool* error)
{
    unsigned j = 0;
    while (i + j < buffer.size && buffer.string[i + j] != '\n' && !*error)
    {
        if (coordinates.base.columns == map->bitmap->dimensions.base.columns)
        {
            my_perror("Too long line");
            *error = true;
        }
        else
        {
            *error = fill_row_cases(map, coordinates, buffer.string[i + j]);
        }
        coordinates.base.columns++;
        j++;
    }
    return j;
}
