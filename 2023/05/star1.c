#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEEDS 64
#define MAX_MAPPING 128
#define NB_CATEGORIES 7

/* Code by Eliott 'The Shark' Flechtner, 2023/12/05 */

struct partial_mapping
{
    long long sft;
    long long src;
    long long len;
};

struct mapping
{
    struct partial_mapping pms[MAX_MAPPING];
    long long len;
};

static struct mapping init_mapping(void)
{
    return (struct mapping){(struct partial_mapping){-1, -1, 0}, 0};
}

static long long get_lowest_location(FILE *fptr)
{
    long long res = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nbytes = getline(&line, &len, fptr);

    // Initialize the seeds array
    size_t len_seeds = 0;
    long long *seeds = malloc(sizeof(long long) * MAX_SEEDS);

    // Skip the indicator
    char *saveptr = NULL;
    strtok_r(line, " ", &saveptr);

    // Parse the initial seeds line
    char *seed = NULL;
    while ((seed = strtok_r(NULL, " \n", &saveptr)))
        seeds[len_seeds++] = atoll(seed);

    getline(&line, &len, fptr);
    for (size_t j = 0; j < NB_CATEGORIES; ++j)
    {
        // Initialize the mapping for the current section
        struct mapping m = init_mapping();

        // Skip the empty line, get the header line
        getline(&line, &len, fptr);

        // Get a new mapping line
        nbytes = getline(&line, &len, fptr);
        while (strcmp(line, "\n"))
        {
            // Get the destination, source and length of each ranges
            saveptr = NULL;
            long long dst_start = atoll(strtok_r(line, " ", &saveptr));
            long long src_start = atoll(strtok_r(NULL, " ", &saveptr));
            long long range_len = atoll(strtok_r(NULL, "\n", &saveptr));

            // Compute the difference
            long long shift = dst_start - src_start;
            m.pms[m.len++] = (struct partial_mapping){shift, src_start, range_len};
            
            // Get the next line
            if (getline(&line, &len, fptr) == -1)
                break;
        }
        
        // Find the new seeds values using the mapping found
        for (size_t k = 0; k < len_seeds; ++k)
        {
            long long s = seeds[k];
            for (size_t l = 0; l < m.len; ++l)
            {
                struct partial_mapping pm = m.pms[l];
                if (s >= pm.src && s <= pm.src + pm.len - 1)
                {
                    seeds[k] = s + pm.sft;
                    break;
                }
            }
        }
    }

    // Return the min of the seeds array
    res = seeds[0];
    for (size_t i = 0; i < len_seeds; ++i)
        if (seeds[i] < res)
            res = seeds[i];

    // Free the allocated line (in getline)
    free(line);
    free(seeds);
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
    long long lowest = get_lowest_location(fptr);
    printf("Lowest location number = %lld\n", lowest);

    // Close the file
    fclose(fptr);
    return 0;
}
