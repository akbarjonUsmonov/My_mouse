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

#include "get_dimensions.h"

bool numeric_check(char character)
{
    bool result = false;
    if (character >= '0' && character <= '9') result = true;
    return result;
}

// Copies the first number of the buffer to the string.
bool rows_to_string(struct string string, struct string buffer)
{
    bool error = false;
    uint16_t i = 0;
    while (numeric_check(buffer.string[i]) && !error && i <= buffer.size)
    {
        if (i < string.size - 1)
        {
            string.string[i] = buffer.string[i];
        }
        else
        {
            error = true;
        }
        i++;
    }
    if (buffer.string[i] != 'x') error = true;
    string.string[i] = '\0';
    return error;
}

// Copies the second number of the buffer to the string.
bool columns_to_string(struct string string, struct string buffer)
{
    bool error = false;
    uint8_t rows = my_strlen(string.string) + 1;
    uint16_t i = 0;
    while (i + rows <= buffer.size && numeric_check(buffer.string[i + rows]) &&
           !error)
    {
        if (i < string.size)
        {
            string.string[i] = buffer.string[i + rows];
        }
        else
        {
            error = true;
        }
        i++;
    }
    string.string[i] = '\0';
    return error;
}

// Puts the first line in a string and sends it to the helper.
struct dimensions get_dimensions(struct string buffer, bool* error)
{
    struct coordinates base = {0, 0};
    struct dimensions dimensions = {base, &dimensions_product};
    int number_length = 5;
    char* number = malloc(number_length);
    struct string string = {number, number_length};
    *error = rows_to_string(string, buffer);
    if (!*error)
    {
        dimensions.base.rows = my_atoi(string.string);
        *error = columns_to_string(string, buffer);
        if (!*error) dimensions.base.columns = my_atoi(string.string);
    }
    if (!(dimensions.base.rows || dimensions.base.columns)) *error = true;
    if (*error) my_perror("File's first line broken");
    free(number);
    return dimensions;
}
