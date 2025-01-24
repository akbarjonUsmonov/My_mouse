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

#include "read_file.h"

bool buffering_check_dimensions(struct dimensions dimensions)
{
    bool error = false;
    if (dimensions.base.rows > 1000 || dimensions.base.columns > 1000)
    {
        my_perror("Map is too big");
        error = true;
    }
    else if (dimensions.base.rows < 3 || dimensions.base.columns < 3)
    {
        my_perror("Map is too small");
        error = true;
    }
    return error;
}

// Checks the size of the map. Initializes the map.
struct mouse_map* buffering_initialize(struct string buffer, int* read_size,
                                       bool* error)
{
    struct mouse_map* map = NULL;
    struct dimensions dimensions = get_dimensions(buffer, error);
    *error = (*error) ? true : buffering_check_dimensions(dimensions);
    if (!*error)
    {
        map = mouse_map_initialize(map, dimensions);
        *error = tiles_to_string(buffer, map);
        int i = 0;
        while (buffer.string[i] != '\n') i++;
        *read_size -= i + 1;
    }
    return map;
}

// Keeps track of the read amount in a variable of the caller, performs
// the initial and routine writes to the structure.
struct mouse_map* buffering(struct mouse_map* map, struct string buffer,
                            uint32_t* read_amount, uint16_t* last_row,
                            bool* error)
{
    int32_t read_size = buffer.size;
    if (!*read_amount)
    {
        map = buffering_initialize(buffer, &read_size, error);
    }
    if (map && map->bitmap->row && !*error)
    {
        *last_row = map->bitmap->fill(map, buffer, *read_amount, error);
    }
    *read_amount += read_size;
    return map;
}

void read_file_errors(int read_size, uint16_t last_row, struct mouse_map* map,
                      bool* error)
{
    if (read_size == -1)
    {
        my_perror("Cannot read file");
        *error = true;
    }
    else if (!*error && last_row != map->bitmap->dimensions.base.rows)
    {
        my_perror("Too few lines");
        *error = true;
    }
}

// Defines the page size, allocates the reading buffer, reads the file until
// the end, saving it to the mouse_map structure.
struct mouse_map* read_file(int file_descriptor, bool* error)
{
    struct mouse_map* map = NULL;
    unsigned page_size = 4096;
    unsigned buffer_size = 15 * page_size;
    char* string = malloc(buffer_size);
    uint16_t last_row = 0;
    int32_t read_size = 0;
    uint32_t read_amount = 0;
    while ((read_size = read(file_descriptor, string, buffer_size)) > 0 &&
           !*error)
    {
        struct string buffer = {string, read_size};
        map = buffering(map, buffer, &read_amount, &last_row, error);
    }
    free(string);
    read_file_errors(read_size, last_row, map, error);
    return map;
}
