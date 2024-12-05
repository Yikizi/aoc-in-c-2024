
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_MATCHES 4

int main(void) {
    FILE* filep = fopen("day3.txt", "r");
    if (filep == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[600000];
    const char* regex = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|(do\\(\\)|don't\\(\\))";
    regex_t re;
    int result = 0;

    if (regcomp(&re, regex, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    int condition = 1;

    while (fgets(line, sizeof(line), filep) != NULL) {

        regmatch_t matches[MAX_MATCHES];
        char* ptr = line;

        while (regexec(&re, ptr, MAX_MATCHES, matches, 0) == 0) {

            if (matches[3].rm_so != -1) {
                char optional_str[20] = {0};
                strncpy(optional_str, ptr + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
                condition = (strcmp(optional_str, "don't()") == 0) ? 0 : 1;
            }

            char num1_str[20] = {0};
            strncpy(num1_str, ptr + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
            int num1 = atoi(num1_str);

            char num2_str[20] = {0};
            strncpy(num2_str, ptr + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
            int num2 = atoi(num2_str);

            if (condition) {
              result += num1 * num2;
            }

            ptr += matches[0].rm_eo;
        }
    }

    regfree(&re);
    fclose(filep);

    printf("Final Result: %d\n", result);

    return 0;
}

