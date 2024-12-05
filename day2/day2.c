#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(int a, int b) {
  if (a < b) {
    return -1;
  } else if (a > b) {
    return 1;
  }
  return 0;
}

int check(int* nums, int count, int skip) {
    int direction = 0;
    for (int i = 0; i < count - 1; i++) {
        if (i == skip) continue;

        int next = (i + 1 == skip) ? i + 2 : i + 1;
        if (next >= count) break;

        int current_direction = comp(nums[i], nums[next]);
        if (current_direction == 0 || abs(nums[i] - nums[next]) > 3) return 1;

        if (direction == 0) {
            direction = current_direction;
        } else if (direction != current_direction) {
            return 1;
        }
    }
    return 0;
}

int main() {
  FILE* filep = fopen("day2.txt", "r");
  if (filep == NULL) {
    perror("Error reading file");
    exit(1);
  }

  int result = 0;
  char line[256];

  while (fgets(line, sizeof(line), filep) != NULL) {
    int nums[20];
    int count = 0;
    char* token = strtok(line, " ");

    while (token != NULL && count < 20) {
      nums[count] = atoi(token);
      count++;
      token = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++) {
      int res = check(nums, count, i);
      if (res == 0) {
        result++;
        break;
      }
    }
  }

  printf("%d\n", result);
  fclose(filep);
  return 0;
}
