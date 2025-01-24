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

#include "mouse_map.h"

void mouse_map_deconstruct(struct mouse_map* map)
{
    map->bitmap->vtable->deconstruct(map->bitmap);
    free(map->tiles.string);
    free(map->vtable);
    free(map);
}

// Allocates and fills in all the nested structures' function pointers.
struct mouse_map* mouse_map_initialize(struct mouse_map* map,
                                       struct dimensions dimensions)
{
    map = malloc(sizeof(struct mouse_map));
    map->bitmap = bit_matrix_initialize(NULL, dimensions);
    map->entrance = (struct coordinates){-1, -1};
    map->exit = (struct coordinates){-1, -1};
    map->tiles = (struct string){calloc(6, sizeof(char)), 5};
    map->vtable = malloc(sizeof(struct mouse_map_vtable));
    map->vtable->initialize = &mouse_map_initialize;
    map->vtable->deconstruct = &mouse_map_deconstruct;
    return map;
}
