#pragma once
#include <stdlib.h>

void traceBack(int* nums, int numsSize, int* track, int trackSize) {
    if (trackSize == numsSize) {
        for (int i = 0; i < numsSize; i++) {
            printf("%d", track[i]);
            if (i == numsSize - 1) {
                printf("\n");
            }
            else {
                printf(",");
            }
        }
        return;
    }
    for (int i = 0; i < numsSize; i++) {
        char isContained = 0;
        for (int j = 0; j < trackSize; j++) {
            if (nums[i] == track[j]) isContained = 1;
        }
        if (isContained == 1) continue;
        track[trackSize] = nums[i];
        traceBack(nums, numsSize, track, trackSize+1);
    }
}

void permute(int* nums, int numsSize) {
    int* track = malloc(sizeof(int) * numsSize);
    
    traceBack(nums, numsSize, track, 0);
}