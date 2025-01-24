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

#include "print_bitmap.h"

// Writes the bit tiles to the row.
void print_bit_row_cases(struct mouse_map* map, struct dimensions coordinates,
                         char* row)
{
    if (map->bitmap->vtable->get_bit(map->bitmap, coordinates.base.columns,
                                     coordinates.base.rows))
    {
        row[coordinates.base.columns] = map->tiles.string[0];
    }
    else
    {
        row[coordinates.base.columns] = map->tiles.string[1];
    }
}

// Overwrites bit tiles with exits in the row.
void print_bit_row_exits(char* row, struct mouse_map* map, uint16_t y)
{
    if (y == map->entrance.rows)
    {
        row[map->entrance.columns] = map->tiles.string[3];
    }
    else if (y == map->exit.rows)
    {
        row[map->exit.columns] = map->tiles.string[4];
    }
}

// Overwrites bit tiles with the route in the row.
void print_bit_row_route(char* row, struct mouse_map* map, uint16_t y,
                         struct stack* route)
{
    while (route->vtable->peek(route).rows == y)
    {
        row[route->vtable->peek(route).columns] = map->tiles.string[2];
        route->vtable->pop(route);
    }
}

void print_bit_row(struct mouse_map* map, uint16_t y, struct stack* route,
                   char* row)
{
    uint16_t x = 0;
    uint16_t columns = map->bitmap->dimensions.base.columns;
    while (x < columns)
    {
        struct coordinates base = {y, x};
        struct dimensions coordinates = {base, &dimensions_product};
        print_bit_row_cases(map, coordinates, row);
        x++;
    }
    print_bit_row_route(row, map, y, route);
    print_bit_row_exits(row, map, y);
    row[columns] = '\n';
    write(1, row, columns + 1);
}

// Iterates over rows.
void print_bit_map(struct mouse_map* map, struct stack* route)
{
    uint16_t y = 0;
    my_printf("%dx%d%s\n", map->bitmap->dimensions.base.rows,
              map->bitmap->dimensions.base.columns, map->tiles.string);
    char* row = malloc(map->bitmap->dimensions.base.columns + 1);
    while (y < map->bitmap->dimensions.base.rows)
    {
        print_bit_row(map, y, route, row);
        y++;
    }
    free(row);
}
