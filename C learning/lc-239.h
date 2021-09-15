#pragma once

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

struct MonotonicQueue {
    int* queue;
    int tail;
    int head;
    int size;
};

struct MonotonicQueue* createQueue(int size) {
    struct MonotonicQueue* queue = (struct MonotonicQueue*)malloc(sizeof(struct MonotonicQueue));
    queue->queue = (int*)malloc(sizeof(int) * (size + 1));
    queue->head = queue->tail = 0;
    queue->size = size + 1;
    return queue;
}

bool isEmpty(struct MonotonicQueue* queue) {
    return queue->head == queue->tail;
}

bool getLast(struct MonotonicQueue* queue) {
    return queue->queue[queue->tail];
}

void pushQueue(struct MonotonicQueue* queue, int val) {
    while (!isEmpty(queue) && getLast(queue) < val) {
        queue->tail = (queue->tail + queue->size - 1) % queue->size;
    }

    queue->tail = (queue->tail + queue->size + 1) % queue->size;
    queue->queue[queue->tail] = val;
}

int getMax(struct MonotonicQueue* queue) {
    return queue->queue[queue->head + 1];
}

void popQueue(struct MonotonicQueue* queue, int val) {
    if (getMax(queue) == val) {
        queue->head = (queue->head + queue->size + 1) % queue->size;
    }
}

void printQueue(struct MonotonicQueue* queue) {
    int p = queue->head;
    while (p != queue->tail) {
        printf("%d,", queue->queue[(p + 1 + queue->size) % queue->size]);
        p = (p + 1 + queue->size) % queue->size;
    }
    printf("\n");
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize + 1 - k;
    int* res = (int*)malloc(sizeof(int) * (*returnSize));
    int resIndex = 0;
    struct MonotonicQueue* queue = createQueue(k);
    for (int i = 0; i < numsSize; i++) {
        pushQueue(queue, nums[i]);
        if (i >= k - 1) {
            res[resIndex++] = getMax(queue);
            popQueue(queue, nums[i - k + 1]);
            printQueue(queue);
        }
    }

    return res;
}

void test() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int size = 0;
    int* ans = maxSlidingWindow(nums, 8, 3, &size);
    for (int i = 0; i < size; i++) {
        printf("%d,", ans[i]);
    }
    printf("\n");
}