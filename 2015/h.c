
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the difference for a single string
void calculate_string_difference(const char *line, int *code_count, int *encoded_count) {
    int code_len = strlen(line); // Length of the string in code
    int encoded_len = 2;         // Start with 2 for the surrounding quotes in encoded form

    for (int i = 0; i < code_len; i++) {
        if (line[i] == '"' || line[i] == '\\') {
            // Escaped quotes and backslashes add extra characters
            encoded_len += 2;
        } else {
            encoded_len++;
        }
    }

    *code_count += code_len;
    *encoded_count += encoded_len;
}

int main() {
    FILE *file = fopen("i", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    int total_code_count = 0;
    int total_encoded_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        calculate_string_difference(line, &total_code_count, &total_encoded_count);
    }

    fclose(file);

    int difference = total_encoded_count - total_code_count;
    printf("Total difference: %d, %d\n", total_encoded_count, total_code_count);

    return 0;
}
