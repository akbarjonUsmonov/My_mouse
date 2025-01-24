#ifndef MY_MOUSE_SOURCE_MOUSE_H_FIND_ROUTE_H
#define MY_MOUSE_SOURCE_MOUSE_H_FIND_ROUTE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "structures.h"
#include "queue.h"
#include "stack.h"
#include "my_string.h"

// Listnode to collect shortest path coordinates and steps.
typedef struct s_coord
{
    int row;
    int col;
    int distance;
    struct s_coord* parent;
} coord;

// Looks up the route in the map.
struct stack* find_route(struct mouse_map* map, int* route_length, bool* error);

#endif  // MY_MOUSE_SOURCE_MOUSE_H_FIND_ROUTE_H
