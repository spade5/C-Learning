#pragma once
#include <stdlib.h>

int combinationNum(int n, int m) {
    if (m == n) return 1;
    float ret = 1;
    int i;
    for (i = n - m + 1; i <= n; i++) {
        ret = ret * i / (n - i + 1);
    }
    printf("%f\n", ret);
    printf("%d\n", (int)ret);
    return (int)ret;
}

char* kthSmallestPath(int* destination, int destinationSize, int k) {
    int m = destination[0];
    int n = destination[1];
    char* ret = malloc(sizeof(char) * (m + n + 1));
    int index = 0;
    while (1) {
        printf("m:%d, n:%d, k:%d\n", m, n, k);
        if (n == 0) {
            if (m < 1) {
                break;
            }
            ret[index++] = 'V';
            m--;
            continue;
        }
        if (m == 0) {
            if (n < 1) {
                break;
            }
            ret[index++] = 'H';
            n--;      
            continue;
        }
        if (combinationNum(m + n - 1, m) >= k) {
            ret[index++] = 'H';
            n--;
        }
        else {
            ret[index++] = 'V';
            k -= combinationNum(m + n - 1, m);
            m--;
        }
    }
    ret[index] = '\0';
    return ret;
}