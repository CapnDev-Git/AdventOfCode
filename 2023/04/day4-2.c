#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 64
#define MAX_CARDS 220

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

static int get_winning_points(FILE *fptr) {
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;
  
    // Get the winning numbers
    size_t len_lookup = 0;
    int *lookup = calloc(sizeof(int), MAX_CARDS);
    for (size_t i = 0; i < MAX_CARDS; i++)
        lookup[i] = 1;

    int id = 1;
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
        size_t l1 = 0;
        int *winning_numbers = malloc(sizeof(int) * MAX_NUMBERS);
        get_numbers(winning_numbers_str, winning_numbers, &l1);

        // Get the card numbers
        size_t l2 = 0;
        int *card_numbers = malloc(sizeof(int) * MAX_NUMBERS);
        get_numbers(card_numbers_str, card_numbers, &l2);

        // Count how many cards were won
        int won = 0;
        for (size_t i = 0; i < l2; ++i)
            for (size_t j = 0; j < l1; ++j)
                if (card_numbers[i] == winning_numbers[j])
                    won++;
        
        // Count (exponentially) the amount of copy cards won
        if (won)
            for (int i = id + 1; i < id + won + 1; i++)
                lookup[i-1] += lookup[id-1];

        // Free the arrays
        free(winning_numbers);
        free(card_numbers);
        
        // Increase the game ID
        id++;
    }

    // Update the result
    for (size_t i = 0; i < MAX_CARDS; i++)
        res += lookup[i];

    // Free the allocated line & array
    free(line);
    free(lookup);

    // Return the sum of valid game IDs
    return res;
}

int main(int argc, char *argv[])
{
    // Parse the script inputs
    if (argc != 2)
        errx(1, "Usage: %s <filename>\n", argv[0]);

    // Open the file for reading
    FILE *fptr = fopen(argv[argc - 1], "r");
    if (!fptr)
        errx(1, "main: could not open given file!");

    // Calculate and print the sum of game IDs that are valid
    int sum = get_winning_points(fptr);
    printf("Total scratchcards = %d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
