#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code by Eliott 'The Shark' Flechtner, 2023/12/XX */

static int get_(FILE *fptr)
{
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;

    // Read every line of the given file
    while ((nbytes = getline(&line, &len, fptr)) != -1)
    {
        /* PROCESS HERE */
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
    int sum = get_(fptr);
    printf("sum=%d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
