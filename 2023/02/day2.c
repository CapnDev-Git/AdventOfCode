#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code by Eliott 'The Shark' Flechtner, 2023/12/02 */

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

static int handle_pick(char *pick)
{
    int n = 0;
    char *saveptr = NULL;
    char *color = NULL;

    // Split & convert the pick
    n = atoi(strtok_r(pick, " ", &saveptr));
    color = saveptr;

    // Determine whether the game is valid depending on the color
    if (!strcmp(color, "red"))
        return n <= MAX_RED;
    if (!strcmp(color, "green"))
        return n <= MAX_GREEN;
    if (!strcmp(color, "blue"))
        return n <= MAX_BLUE;
}

static int get_possible_games(FILE *fptr)
{
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;

    // Read every line of the given file
    while ((nbytes = getline(&line, &len, fptr)) != -1)
    {
        int is_game_valid = 1;
        char *saveptr1 = NULL;
        char *subset = NULL;

        // Separate the "Game" keyword to get the ID
        strtok_r(line, " ", &saveptr1);
        char *id = strtok_r(NULL, ":", &saveptr1);
        while (is_game_valid && (subset = strtok_r(NULL, ";", &saveptr1)))
        {
            char *saveptr2 = NULL;
            char *pick = strtok_r(subset, ",\n", &saveptr2);
            while (is_game_valid && pick)
            {
                // Get out as soon as finding an invalid game
                is_game_valid = handle_pick(pick);
                pick = strtok_r(NULL, ",\n", &saveptr2);
            }
        }

        // If a game as been detected as valid, increase the result
        if (is_game_valid)
            res += atoi(id);
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
    int sum = get_possible_games(fptr);
    printf("sum=%d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
