#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code by Eliott 'The Shark' Flechtner, 2023/12/02 */

enum colors
{
    RED = 0,
    GREEN,
    BLUE,
};

static int curr_maxs[3] = { -1, -1, -1 };

static void reset_maxs(void)
{
    curr_maxs[RED] = -1;
    curr_maxs[GREEN] = -1;
    curr_maxs[BLUE] = -1;
}

static const char *color_names[] = {
    [RED] = "red",
    [GREEN] = "green",
    [BLUE] = "blue",
};

static int find_color_index(const char *color)
{
    for (int i = 0; i < sizeof(color_names) / sizeof(color_names[0]); ++i)
    {
        if (!strcmp(color, color_names[i]))
            return i;
    }
}

static void handle_pick(char *pick)
{
    int n = 0;
    char *saveptr = NULL;
    char *color = NULL;

    // Split & convert the pick
    n = atoi(strtok_r(pick, " ", &saveptr));
    color = saveptr;

    // Find & update the current maximum if the color is valid
    int color_index = find_color_index(color);
    if (color_index != -1)
        curr_maxs[color_index] =
            n > curr_maxs[color_index] ? n : curr_maxs[color_index];
}

static int get_min_config(FILE *fptr)
{
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;

    // Read every line of the given file
    while ((nbytes = getline(&line, &len, fptr)) != -1)
    {
        char *saveptr1 = NULL;
        char *subset = NULL;

        // Separate the "Game" keyword to get the ID
        strtok_r(line, " ", &saveptr1);
        char *id = strtok_r(NULL, ":", &saveptr1);
        while ((subset = strtok_r(NULL, ";", &saveptr1)))
        {
            char *saveptr2 = NULL;
            char *pick = strtok_r(subset, ",\n", &saveptr2);
            while (pick)
            {
                // Get out as soon as finding an invalid game
                handle_pick(pick);
                pick = strtok_r(NULL, ",\n", &saveptr2);
            }
        }

        // If a game as been detected as valid, increase the result
        res += curr_maxs[RED] * curr_maxs[GREEN] * curr_maxs[BLUE];
        reset_maxs();
    }

    // Free the allocated line (in getline)
    free(line);

    // Return the sum of valid game IDs
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
    int sum = get_min_config(fptr);
    printf("sum=%d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
