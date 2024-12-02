#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: part 2
// sum the list from smallest to biggest
// the difference must be smaller than 3 * (len - 1)

int comp(int a, int b) {
  if (a < b) {
    return -1;
  } else if (a > b) {
    return 1;
  }
  return 0;
}


int main() {

  FILE* filep;
  filep = fopen("day2.txt", "r");
  if (filep == NULL) {
    perror("Error reading file");
    exit(1);
  }

  int first = 0;
  int last = 0;
  int result = 0;
  char line[24];
  char* token;
  int i = 0;
  int j = 0;

  while (fgets(line, sizeof(line), filep) != NULL) {
    int direction = 0;
    int state = 0;
    int count = 0;
    token = strtok(line, " ");
    first = atoi(token);
    last = atoi(token);
    while (token != NULL && atoi(token) != 0) {
      count++;

      int num = atoi(token);

      if (direction == 0) {
        direction = comp(num, first);
      }

      if (direction == 0) {
        token = strtok(NULL, " ");
        continue;
      }

      if (first < num && last < num && direction == 1) {
        if (abs(first - num) <= 3 || abs(last - num) <= 3) {
          state++;
        }
      } else if (first > num && last > num && direction == -1) {
        if (abs(first - num) <= 3 || abs(last - num) <= 3) {
          state++;
        }
      }
      last = num;
      token = strtok(NULL, " ");
    }
    if ((state + 1) == count) {
      result++;
    }
  }

  printf("%d\n", result);

  fclose(filep);
  return 0;

}
