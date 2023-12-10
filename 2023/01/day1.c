#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code by Eliott 'The Shark' Flechtner, 2023/12/01 */

// Spelled-out numbers array
static char *numbers[10] = {
    [1] = "one", [2] = "two",   [3] = "three", [4] = "four", [5] = "five",
    [6] = "six", [7] = "seven", [8] = "eight", [9] = "nine",
};

static int get_first_digit(char *buff, size_t len) {
  // Go through the string (line in file)
  for (size_t i = 0; i < len; ++i) {
    // Look for a digit
    if (buff[i] >= '0' && buff[i] <= '9')
      return buff[i] - '0';

    // Look for a lettered digit instead
    for (int j = 1; j <= 9; ++j) {
      // Check if the substring starting from i matches the spelled-out number
      if (!strncmp(&buff[i], numbers[j], strlen(numbers[j])))
        return j;
    }
  }

  // Indicate no digit found
  return -1; // Shouldn't be reached according to inputs
}

static int get_last_digit(char *buff, size_t len) {
  // Go through the string (line in file)
  for (size_t i = len - 1; i >= 0; --i) {
    // Look for a digit
    if (buff[i] >= '0' && buff[i] <= '9')
      return buff[i] - '0';

    // Look for a lettered digit instead
    for (int j = 1; j <= 9; ++j) {
      // Compute the size of the looked-for number
      size_t word_len = strlen(numbers[j]);

      // Check if the substring ending at i matches the spelled-out number
      if (i - word_len + 1 >= 0 &&
          !strncmp(&buff[i - word_len + 1], numbers[j], word_len))
        return j;
    }
  }

  // Indicate no digit found
  return -1; // Shouldn't be reached according to inputs
}

static int get_calibration(FILE *fptr) {
  // Initialize total sum
  int res = 0;

  // Setup for reading line by line
  char *line = NULL;
  size_t len = 0;
  ssize_t nbytes;

  // Read every line of the given file
  while ((nbytes = getline(&line, &len, fptr)) != -1) {
    // Get both digits
    int d1 = get_first_digit(line, nbytes);
    int d2 = get_last_digit(line, nbytes);

    // Add progressively to the result
    res += d1 * 10 + d2;
  }

  // Free the allocated line
  free(line);

  // Return the total sum
  return res;
}

int main(int argc, char *argv[]) {
  // Open the file for reading
  FILE *fptr = fopen(argv[argc - 1], "r");
  if (!fptr)
    errx(1, "main: could not open given file!");

  // Calculate and print the sum of calibration values
  int res = get_calibration(fptr);
  printf("Sum: %d\n", res);

  // Close the file
  fclose(fptr);

  return 0;
}
