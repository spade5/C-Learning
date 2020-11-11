#pragma once

#include <stdlib.h>
#include <string.h>

#define N 26

int minDeletions(char* s) {
    int letters[N];
    int len = strlen(s), i, j, count = 0;
    int* nums = malloc(sizeof(int) * (len + 1));
    nums[len] = -1;

    for (i = 0; i < N; i++) {
        letters[i] = 0;
    }

    for (i = 0; i < len; i++) {
        letters[s[i] - 'a']++;
        nums[i] = -1;
        printf("i:%d,nums[i]:%d\n", i, nums[i]);
    }

    for (i = 0; i < N; i++) {
        if (letters[i] > 0) {
            j = letters[i];
            printf("j:%d,nums[j]:%d\n", j, nums[j]);
            while (nums[j] != -1 && j > 0) {
                j--;
                count++;
                printf("j:%d,nums[j]:%d\n", j, nums[j]);
            }
            nums[j] = i;
        }
    }

    return count;
}