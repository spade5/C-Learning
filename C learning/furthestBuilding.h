#pragma once
#include <stdlib.h>

int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int* ladderQueue = malloc(sizeof(int) * ladders);
    int ladderNum = 0;
    int offset = 0;
    int shortestIndex = -1, i, j, usedBrickNum = 0;
    for (i = 0; i < heightsSize - 1; i++) {
        offset = heights[i + 1] - heights[i];
        if (offset <= 0) continue;
        if (ladderNum < ladders) {
            shortestIndex = shortestIndex < 0 || offset < ladderQueue[shortestIndex] ? ladderNum : shortestIndex;
            ladderQueue[ladderNum++] = offset;
        }
        else if (ladderNum > 0 && ladderQueue[shortestIndex] < offset) {
            if (usedBrickNum + ladderQueue[shortestIndex] <= bricks) {
                usedBrickNum += ladderQueue[shortestIndex];
                ladderQueue[shortestIndex] = offset;
                shortestIndex = 0;
                for (j = 1; j < ladderNum; j++) {
                    if (ladderQueue[j] < ladderQueue[shortestIndex]) {
                        shortestIndex = j;
                    }
                }
            }
            else if (usedBrickNum + offset <= bricks) {
                usedBrickNum += offset;
            }
            else {
                break;
            }
        }
        else {
            if (usedBrickNum + offset <= bricks) {
                usedBrickNum += offset;
            }
            else {
                break;
            }
        }
    }
    return i;
}