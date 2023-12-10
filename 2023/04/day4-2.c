#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 64
#define MAX_WON 4096
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
// static int get_winning_points(FILE *fptr) {
static int get_winning_points(FILE *fptr, int *counts, size_t num_cards) {
    int res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;

    // Prepare a history of wins
    //int *won_history = malloc(sizeof(int) * MAX_WON);
    //won_history[0] = 1;
    //printf("won_history[0]=1\n");
    //int *lookup = calloc(sizeof(int), MAX_WON);

    // Read every line of the given file
    //size_t game_id = 1;
    //size_t k = 1;
    //size_t prev_k = 0;
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

        // Detect the winning numbers from the card numbers
        int won = 0;
        for (size_t i = 0; i < l2; ++i)
        {
            for (size_t j = 0; j < l1; ++j)
            {
                if (card_numbers[i] == winning_numbers[j])
                {
                    won++;
                    break;
                }
            }
        }


        if (won)
        {
            for (size_t i = 0; i < num_cards; ++i)
            {
                if (card_numbers[0] == i + 1)
                {
                    counts[i] += won;
                    break;
                }
            }
        }

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

// Function to update counts array based on card numbers
static void update_counts(int *counts, size_t num_cards, int *card_numbers, size_t l) {
    for (size_t i = 0; i < num_cards; ++i) {
        for (size_t j = 0; j < l; ++j) {
            if (card_numbers[j] == i + 1) {
                counts[i]++;
                break;
            }
        }
    }
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
    //int sum = get_winning_points(fptr);
    //printf("winning points=%d\n", sum);

    // Initialize counts for each card
    int counts[MAX_CARDS] = {0};

    // Loop for processing copies
    while (1)
    {
        int copies_won = 0;  // Track the total number of copies won in this iteration

        // Iterate over each card
        for (size_t i = 0; i < MAX_CARDS; ++i) {
            // Check if this card wins copies
            if (counts[i] > 1) {  // Updated condition to check for copies
                // Update the counts for the copies won
                for (size_t j = 1; j < counts[i]; ++j) {
                    update_counts(counts, MAX_CARDS, card_numbers[i], l);  // Assuming update_counts is appropriately modified
                    copies_won += counts[i] - 1;  // Subtract 1 for the original card
                }
                counts[i] = 1;  // Set the count of the original card to 1
            }
        }

        // Break the loop if no more copies are won
        if (copies_won == 0) {
            break;
        }

        // Add the copies to the total sum
        sum += copies_won;
    }

    // Print the total number of scratchcards
    printf("total scratchcards=%d\n", sum);

    // Close the file
    fclose(fptr);
    return 0;
}
