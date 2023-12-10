#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

char **build_grid(FILE *fptr, size_t *rows, size_t *cols)
{
    char **grid = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes;

    // Read the first line to determine the size of the grid
    nbytes = getline(&line, &len, fptr);
    if (nbytes == -1)
    {
        free(line);
        return NULL;
    }

    // Exclude newline char
    *rows = nbytes - 1;
    *cols = nbytes - 1;

    // Allocate memory for the grid
    grid = malloc(*rows * sizeof(char *));
    for (size_t i = 0; i < *rows; ++i)
    {
        grid[i] = malloc(*cols * sizeof(char));
        if (!grid[i])
            errx(1, "Memory allocation error");
    }

    // Copy the first line to the grid
    for (size_t i = 0; i < *cols; ++i)
        if (line[i] != '\n')
            grid[0][i] = line[i];

    // Read the remaining lines
    for (size_t row = 1; (nbytes = getline(&line, &len, fptr)) != -1; ++row)
        for (size_t i = 0; i < *cols; ++i)
            if (line[i] != '\n')
                grid[row][i] = line[i];

    // Free the allocated line (in getline)
    free(line);
    return grid;
}

void free_grid(char **grid, size_t rows)
{
    // Free successively all the rows then the entire grid
    for (size_t i = 0; i < rows; ++i)
        free(grid[i]);
    free(grid);
}

static int check_neighbors(char **grid, size_t rows, size_t cols, size_t x, size_t y, size_t length)
{
    // Check the vertical 3 spots before the number
    if ((y && grid[x][y-1] != '.')
            || (x && y && grid[x-1][y-1] != '.')
            || (x != rows-1 && y && grid[x+1][y-1] != '.'))
        return 1;

    // Check vertical 3 spots after the number 3
    size_t yf = y + length - 1;
    if ((yf != cols-1 && grid[x][yf+1] != '.')
            || (x && yf != cols-1 && grid[x-1][yf+1] != '.')
            || (x != rows-1 && yf != cols-1 && grid[x+1][yf+1] != '.'))
        return 1;

    // Loop for checking above and below the number
    for (size_t i = 0; i < length; ++i)
    {
        // 
        if (x)
        {
            if (grid[x-1][y+i] != '.')
                return 1;
        }

        if (x != rows-1)
        {
            if (grid[x+1][y+i] != '.')
                return 1;
        }
    }

    // No invalid characters found
    return 0;
}

static int get_part_numbers(FILE *fptr)
{
    int res = 0;
    size_t rows, cols;
    char **grid = build_grid(fptr, &rows, &cols);

    // Iterate through the grid
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            int part_n = 0;
            int start = j;

            // Find a number to check
            while (j < cols && isdigit(grid[i][j]))
                part_n = part_n * 10 + (grid[i][j++] - '0');

            // Launch the neighbours detection
            if (part_n)
            {
                int f = check_neighbors(grid, rows, cols, i, start, j - start);
                res += f ? part_n : 0;
            }
        }
    }

    // Free the grid
    free_grid(grid, rows);

    // Return the sum of part numbers
    return res;
}

int main(int argc, char *argv[]) {
    // Parse the script inputs
    if (argc != 2)
    {
        errx(1, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    FILE *fptr = fopen(argv[argc - 1], "r");
    if (!fptr)
        errx(1, "main: could not open given file!");

    // Calculate and print the sum of game IDs that are valid
    int sum = get_part_numbers(fptr);
    printf("sum=%d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
