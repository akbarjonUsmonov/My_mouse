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

#include "tiles.h"

// Checks for repeating tiles.
bool check_tiles(struct string tiles, char character)
{
    bool result = false;
    uint8_t i = 0;
    while (i < tiles.size)
    {
        if (character == tiles.string[i]) result = true;
        i++;
    }
    return result;
}

// Copies the tiles to the string.
uint16_t tiles_to_string_copying(struct string buffer, uint8_t offset,
                                 struct mouse_map* map, bool* error)
{
    uint16_t i = 0;
    while (i + offset <= buffer.size && buffer.string[i + offset] != '\n' &&
           !*error)
    {
        if (i < map->tiles.size &&
            !check_tiles(map->tiles, buffer.string[i + offset]))
        {
            map->tiles.string[i] = buffer.string[i + offset];
        }
        else
        {
            *error = true;
        }
        i++;
    }
    return i;
}

// Calculates the offset, terminates the string.
bool tiles_to_string(struct string buffer, struct mouse_map* map)
{
    bool error = false;
    uint8_t offset = integer_length(map->bitmap->dimensions.base.rows) + 1 +
                     integer_length(map->bitmap->dimensions.base.columns);
    uint16_t increment = tiles_to_string_copying(buffer, offset, map, &error);
    if (increment != map->tiles.size + 1 &&
        buffer.string[increment + offset] != '\n')
    {
        error = true;
    }
    map->tiles.string[increment] = '\0';
    return error;
}
