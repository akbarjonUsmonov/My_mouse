#include "find_route.h"

static int rear;
static coord** queue;

// To check does cell of map is valid.
bool is_valid(int row, int col, struct bit_matrix* map)
{
    int rows = map->dimensions.base.rows;
    int cols = map->dimensions.base.columns;
    if (row < 0 || row >= rows || col < 0 || col >= cols ||
        map->vtable->get_bit(map, col, row) == 1)
    {
        return false;
    }
    return true;
}

// Allocate and add information to new node.
coord* add_new_node(int row, int col, int distance, coord* current)
{
    coord* new_node = (coord*)malloc(sizeof(coord));
    new_node->row = row;
    new_node->col = col;
    new_node->distance = distance;
    new_node->parent = current;
    return new_node;
}

// Allocate bool array and fill with false values.
bool** allocate_visited(int rows, int cols)
{
    bool** visited = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++)
    {
        visited[i] = (bool*)malloc(cols * sizeof(bool));
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }
    return visited;
}

// Free allocated bool array.
void deallocate_visited(bool** visited, struct bit_matrix* map)
{
    int rows = map->dimensions.base.rows;
    for (int i = 0; i < rows; i++)
    {
        free(visited[i]);
    }
    free(visited);
}

// Free allocated queue.
void deallocate_queue()
{
    for (int i = 0; i < rear; i++)
    {
        free(queue[i]);
    }
    free(queue);
}

// Checking directions up> left> right> down.
void bfs_cases(int n_row, int n_col, int distance, bool** visited,
               struct bit_matrix* map, coord* current)
{
    if (is_valid(n_row - 1, n_col, map) && !visited[n_row - 1][n_col])
    {
        queue[rear++] = add_new_node(n_row - 1, n_col, distance, current);
        visited[n_row - 1][n_col] = true;
    }
    if (is_valid(n_row, n_col - 1, map) && !visited[n_row][n_col - 1])
    {
        queue[rear++] = add_new_node(n_row, n_col - 1, distance, current);
        visited[n_row][n_col - 1] = true;
    }
    if (is_valid(n_row, n_col + 1, map) && !visited[n_row][n_col + 1])
    {
        queue[rear++] = add_new_node(n_row, n_col + 1, distance, current);
        visited[n_row][n_col + 1] = true;
    }
    if (is_valid(n_row + 1, n_col, map) && !visited[n_row + 1][n_col])
    {
        queue[rear++] = add_new_node(n_row + 1, n_col, distance, current);
        visited[n_row + 1][n_col] = true;
    }
}

// BFS path finding algorithm process of searching path.
coord* path_finding_bfs_search(int front, bool** visited,
                               struct bit_matrix* map, int target_row,
                               int target_col)
{
    while (front != rear)
    {
        coord* current = queue[front++];
        if (current->row == target_row && current->col == target_col)
        {
            deallocate_visited(visited, map);
            return current;
        }
        bfs_cases(current->row, current->col, current->distance + 1, visited,
                  map, current);
    }
    return 0;
}

// Initialize data structures to bfs search algorithm.
coord* init_bfs_search(struct bit_matrix* map, int start_row, int start_col,
                       int target_row, int target_col)
{
    int front = 0;
    rear = 0;
    int rows = map->dimensions.base.rows;
    int cols = map->dimensions.base.columns;
    queue = (coord**)malloc((rows * cols) * sizeof(coord*));
    queue[rear++] = add_new_node(start_row, start_col, 0, NULL);
    bool** visited = allocate_visited(rows, cols);
    visited[start_row][start_col] = true;
    coord* path =
        path_finding_bfs_search(front, visited, map, target_row, target_col);
    if (path) return path;
    deallocate_queue();
    deallocate_visited(visited, map);
    return NULL;
}

bool no_path_error()
{
    char* error_message = "No path found\n";
    write(2, error_message, my_strlen(error_message));
    return true;
}

// Pushes the path elements to the stack. Deallocates "queue", reports error.
struct stack* path_to_route(coord* path, int* route_length, bool* error)
{
    struct stack* route = create_stack();
    if (path)
    {
        *route_length = path->distance;
        while (path->parent)
        {
            struct coordinates coordinates = {path->row, path->col};
            route->vtable->push(route, coordinates);
            path = path->parent;
        }
        deallocate_queue();
    }
    else
    {
        *error = no_path_error();
    }
    return route;
}

// Receive bit map and other data informations.
struct stack* find_route(struct mouse_map* map, int* route_length, bool* error)
{
    int start_row = map->entrance.rows;
    int start_col = map->entrance.columns;
    int target_row = map->exit.rows;
    int target_col = map->exit.columns;
    coord* path = init_bfs_search(map->bitmap, start_row, start_col, target_row,
                                  target_col);
    return path_to_route(path, route_length, error);
}
