#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 64

/* Code by Eliott 'The Shark' Flechtner, 2023/12/04 */

static void get_numbers(char *str, int *arr, size_t *len)
{
    str++;
    char *saveptr = NULL;
    char *n = strtok_r(str, " ", &saveptr);
    while (n)
    {
        arr[(*len)++] = atoi(n);
        n = strtok_r(NULL, " ", &saveptr);
    }
}

static int get_winning_points(FILE *fptr)
{
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;

    // Read every line of the given file
    while ((nbytes = getline(&line, &len, fptr)) != -1)
    {
        // Remove the game header
        char *saveptr1 = NULL;
        strtok_r(line, ":", &saveptr1);

        // Get the winning & card numbers strings
        char *winning_numbers_str = NULL;
        winning_numbers_str = strtok_r(NULL, "|", &saveptr1);
        char *card_numbers_str = NULL;
        card_numbers_str = saveptr1;

        // Get the winning numbers
        int *winning_numbers = malloc(sizeof(int) * MAX_NUMBERS);
        size_t l1 = 0;
        get_numbers(winning_numbers_str, winning_numbers, &l1);

        // Get the card numbers
        int *card_numbers = malloc(sizeof(int) * MAX_NUMBERS);
        size_t l2 = 0;
        get_numbers(card_numbers_str, card_numbers, &l2);

        // Detect the winning numbers from the card numbers
        int won = 0;
        for (size_t i = 0; i < l2; ++i)
        {
            for (size_t j = 0; j < l1; ++j)
            {
                if (card_numbers[i] == winning_numbers[j])
                {
                    won = won ? won * 2 : 1;
                    break;
                }
            }
        }

        // Add to the result
        res += won;

        // Free the arrays
        free(winning_numbers);
        free(card_numbers);
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
    int sum = get_winning_points(fptr);
    printf("Total winning points = %d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
