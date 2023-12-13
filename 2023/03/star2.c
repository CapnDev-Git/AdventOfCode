#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

struct grid_info
{
    char **grid;
    size_t rows;
    size_t cols;
};

struct point
{
    size_t x;
    size_t y;
};

struct number
{
    struct point pt;
    size_t len;
};

static char **build_grid(FILE *fptr, size_t *rows, size_t *cols)
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

static void free_grid(struct grid_info gi)
{
    // Free successively all the rows then the entire grid
    for (size_t i = 0; i < gi.rows; ++i)
        free(gi.grid[i]);
    free(gi.grid);
}

static void print_grid(struct grid_info gi)
{
    for (size_t i = 0; i < gi.rows; ++i)
    {
        for (size_t j = 0; j < gi.cols; ++j)
            printf("%c", gi.grid[i][j]);
        printf("\n");
    }
}

static struct number init_number(size_t x, size_t y, size_t len)
{
    struct point p = { x, y };
    struct number new = { p, len };
    return new;
}

static struct grid_info init_grid_info(FILE *fptr)
{
    size_t rows, cols;
    char **grid = build_grid(fptr, &rows, &cols);
    struct grid_info new = { grid, rows, cols };
    return new;
}

static int is_valid_pos(struct grid_info gi, size_t x, size_t y)
{
    return x >= 0 && y >= 0 && x <= gi.rows - 1 && y <= gi.cols - 1;
}

static void replace_dots(struct grid_info gi, struct number nb)
{
    for (size_t i = 0; i < nb.len; ++i)
    {
        if (is_valid_pos(gi, nb.pt.x, nb.pt.y + i))
            gi.grid[nb.pt.x][nb.pt.y + i] = '.';
    }
}

static struct point search_other_number(struct grid_info gi, struct point gear)
{
    // Check the 3 before
    for (int i = -1; i < 2; ++i)
    {
        if (is_valid_pos(gi, gear.x + i, gear.y - 1)
            && isdigit(gi.grid[gear.x + i][gear.y - 1]))
            return (struct point){ gear.x + i, gear.y - 1 };
    }

    // Check the 2 before
    for (int i = -1; i < 2; ++i)
    {
        if (is_valid_pos(gi, gear.x + i, gear.y + 1)
            && isdigit(gi.grid[gear.x + i][gear.y + 1]))
            return (struct point){ gear.x + i, gear.y + 1 };
    }

    // Check the spot above
    if (is_valid_pos(gi, gear.x - 1, gear.y)
        && isdigit(gi.grid[gear.x - 1][gear.y]))
        return (struct point){ gear.x - 1, gear.y };

    // Check the spot below
    if (is_valid_pos(gi, gear.x + 1, gear.y)
        && isdigit(gi.grid[gear.x + 1][gear.y]))
        return (struct point){ gear.x + 1, gear.y };

    // If no other number was found
    return (struct point){ -1, -1 };
}

static struct point check_neighbors(struct grid_info gi, struct number nb)
{
    // Check the vertical 2 spots before the number
    for (int i = -1; i < 2; ++i)
    {
        if (is_valid_pos(gi, nb.pt.x + i, nb.pt.y - 1)
            && gi.grid[nb.pt.x + i][nb.pt.y - 1] == '*')
            return (struct point){ nb.pt.x + i, nb.pt.y - 1 };
    }

    // Check the vertical 2 spots after the number
    size_t yf = nb.pt.y + nb.len - 1;
    for (int i = -1; i < 2; ++i)
    {
        if (is_valid_pos(gi, nb.pt.x + i, yf + 1)
            && gi.grid[nb.pt.x + i][yf + 1] == '*')
            return (struct point){ nb.pt.x + i, yf + 1 };
    }

    // Loop for checking below the number
    for (size_t i = 0; i < nb.len; ++i)
    {
        // Check all below
        if (is_valid_pos(gi, nb.pt.x + 1, nb.pt.y + i)
            && gi.grid[nb.pt.x + 1][nb.pt.y + i] == '*')
            return (struct point){ nb.pt.x + 1, nb.pt.y + i };
    }

    // No '*' characters found around the given number substring
    return (struct point){ -1, -1 };
}

static int get_part_numbers(FILE *fptr)
{
    int res = 0;
    struct grid_info gi = init_grid_info(fptr);
    print_grid(gi);

    // Iterate through the grid
    for (size_t i = 0; i < gi.rows; ++i)
    {
        for (size_t j = 0; j < gi.cols; ++j)
        {
            int n1 = 0;
            int start = j;

            // Find a number to check
            while (is_valid_pos(gi, i, j) && isdigit(gi.grid[i][j]))
                n1 = n1 * 10 + (gi.grid[i][j++] - '0');

            // Launch the neighbors detection
            if (n1)
            {
                struct number found_number = init_number(i, start, j - start);
                struct point gear = check_neighbors(gi, found_number);
                if (gear.x != -1 && gear.y != -1)
                {
                    gi.grid[gear.x][gear.y] = '.';
                    replace_dots(gi, found_number);
                    struct point other = search_other_number(gi, gear);
                    if (other.x != -1 && other.y != -1)
                    {
                        int n2 = 0;

                        // Build the found other number
                        size_t beg = other.y;
                        size_t end = other.y;

                        // Find the beginning & end pointers for the other
                        // number
                        while (is_valid_pos(gi, other.x, beg)
                               && isdigit(gi.grid[other.x][beg]))
                            beg--;
                        while (is_valid_pos(gi, other.x, end)
                               && isdigit(gi.grid[other.x][end]))
                            end++;

                        // Build the other number
                        size_t k = beg + 1;
                        while (end - k > 0)
                            n2 = n2 * 10 + (gi.grid[other.x][k++] - '0');

                        // Add to the result & remove the asterix & the second
                        // number
                        res += n1 * n2;
                        struct number other_number =
                            init_number(other.x, beg + 1, end - beg - 1);
                        replace_dots(gi, other_number);
                    }
                }
            }
        }
    }

    // Free the grid
    print_grid(gi);
    free_grid(gi);

    // Return the sum of part numbers
    return res;
}

int main(int argc, char *argv[])
{
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
