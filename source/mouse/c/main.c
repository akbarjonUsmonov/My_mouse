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

#include "main.h"

bool main_check_arguments(int argument_counter)
{
    bool boolean = true;
    if (argument_counter != 2)
    {
        my_printf("Usage: my_mouse maps/10x10.txt\n");
        boolean = false;
    }
    return boolean;
}

int get_file_descriptor(char* filename)
{
    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
    {
        my_perror("Cannot open file");
    }
    return file_descriptor;
}

// Checks the exits.
bool map_check(struct mouse_map* map)
{
    bool error = false;
    char* error_message = "MAP ERROR";
    if (map->entrance.rows == (uint16_t)-1)
    {
        write(2, error_message, 9);
        error = true;
    }
    else if (map->exit.rows == (uint16_t)-1)
    {
        write(2, error_message, 9);
        error = true;
    }
    return error;
}

bool main_work_with_map(struct mouse_map* map, bool error)
{
    if (map)
    {
        if (!error) error = map_check(map);
        if (!error)
        {
            // To do: change largest_square to route.
            int route_length = 0;
            struct stack* route = find_route(map, &route_length, &error);
            if (!error)
            {
                print_bit_map(map, route);
                my_printf("%d STEPS!\n", route_length);
            }
            route->vtable->deconstruct(route);
        }
        map->vtable->deconstruct(map);
    }
    return error;
}

// Opens and reads the file, finds and prints the route.
int main(int argc, char** argv)
{
    bool error = false;
    if ((main_check_arguments(argc)))
    {
        int file_descriptor = get_file_descriptor(argv[1]);
        if (file_descriptor != -1)
        {
            struct mouse_map* map = read_file(file_descriptor, &error);
            close(file_descriptor);
            error = main_work_with_map(map, error);
        }
    }
    if (error) return 1;
    return 0;
}
