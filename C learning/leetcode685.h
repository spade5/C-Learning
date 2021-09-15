#pragma once
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdio.h>

#define NULL 0
#define bool int
#define true 1
#define false 0

 /**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct LinkNode {
    int val;
    struct LinkNode* next;
};

struct ListNode1 {
    int val;
    int degIn;
    int degOut;
    struct LinkNode* preList;
    struct LinkNode* postList;
};

struct ListNode1** generateList(int** edges, int edgesSize) {
    //建立邻接链表
    struct ListNode1** list = (struct ListNode1**)malloc(sizeof(struct ListNode1*) * (edgesSize + 1));
    for (int i = 0; i <= edgesSize; i++) {
        struct ListNode1* listNode = (struct ListNode1*)malloc(sizeof(struct ListNode1));
        listNode->val = i;
        listNode->degIn = 0;
        listNode->degOut = 0;
        listNode->preList = NULL;
        listNode->postList = NULL;
        list[i] = listNode;
    }
    for (int i = 0; i < edgesSize; i++) {
        int* edge = edges[i];
        struct LinkNode* pre = (struct LinkNode*)malloc(sizeof(struct LinkNode));
        pre->val = edge[0];
        pre->next = NULL;
        struct LinkNode* post = (struct LinkNode*)malloc(sizeof(struct LinkNode));
        post->val = edge[1];
        post->next = NULL;
        struct LinkNode* preList = list[edge[1]]->preList;
        struct LinkNode* postList = list[edge[0]]->postList;
        while (preList != NULL && preList->next != NULL) {
            preList = preList->next;
        }
        while (postList != NULL && postList->next != NULL) {
            postList = postList->next;
        }
        if (preList == NULL) {
            list[edge[1]]->preList = pre;
        }
        else {
            preList->next = pre;
        }
        if (postList == NULL) {
            list[edge[0]]->postList = post;
        }
        else {
            postList->next = post;
        }
        (list[edge[0]]->degOut)++;
        (list[edge[1]]->degIn)++;
    }
    return list;
}

void visitNode(struct ListNode1** list, int listSize, int val, int* removedEdge, int* sum) {
    if (*sum > listSize) return;
    struct LinkNode* p = list[val]->postList;
    while (p != NULL) {
        if (!(val == removedEdge[0] && p->val == removedEdge[1])) {
            (*sum)++;
            visitNode(list, listSize, p->val, removedEdge, sum);
        }
        p = p->next;
    }
}


bool visitEdge(int** edges, int edgesSize, int index, bool* visited, int* removedEdge) {
    if (visited[index]) return false;
    if (edges[index][0] != removedEdge[0] || edges[index][1] != removedEdge[1]) {
        visited[index] = true;
        int des = edges[index][1];
        for (int i = 0; i < edgesSize; i++) {
            if (edges[i][0] == des && (edges[i][0] != removedEdge[0] || edges[i][1] != removedEdge[1])) {
                if (!visitEdge(edges, edgesSize, i, visited, removedEdge)) {
                    return false;
                }
            }
        }
    }
    return true;
}

//去掉这个边之后是否还有环
bool existCircel(int** edges, int* inDegArr, int edgesSize, int* removedEdge) {
    inDegArr[removedEdge[1]]--;
    
    int root = 0;
    for (int i = 1; i <= edgesSize; i++) {
        if (inDegArr[i] == 0) {
            root = i;
            break;
        }
    }

    bool ans = false;

    if (root == 0) {
        ans = true;
    }
    else {
        bool* visited = (bool*)malloc(sizeof(bool) * edgesSize);
        for (int i = 0; i < edgesSize; i++) visited[i] = false;
        for (int i = 0; i < edgesSize; i++) {
            if (edges[i][0] == root) {
                if (!visitEdge(edges, edgesSize, i, visited, removedEdge)) {
                    ans = true;
                    break;
                }
            }
        }
        if (!ans) {
            int visitedCount = 0;
            for (int i = 0; i < edgesSize; i++) {
                if (visited[i]) visitedCount++;
            }
            if (visitedCount != edgesSize - 1) ans = true;
        }
    }
    
    inDegArr[removedEdge[1]]++;
    return ans;
}

int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    (*returnSize) = 2;
    //找到入度为 2 的节点
    int* inDegArr = (int*)malloc(sizeof(int) * (edgesSize + 1));
    for (int i = 0; i <= edgesSize; i++) inDegArr[i] = 0;
    for (int i = 0; i < edgesSize; i++) {
        inDegArr[edges[i][1]]++;
    }
    for (int i = edgesSize - 1; i >= 0; i--) {
        int* edge = edges[i];
        if (inDegArr[edge[1]] == 2 && !existCircel(edges, inDegArr, edgesSize, edge)) {
            return edge;
        }
    }

    for (int i = edgesSize - 1; i >= 0; i--) {
        int* edge = edges[i];
        if (!existCircel(edges, inDegArr, edgesSize, edge)) {
            return edge;
        }
    }
    (*returnSize) = 0;
    return NULL;
}

void test() {
    //[[1, 2], [2, 1], [2, 3], [3, 4]]
    int n = 10;
    int** edges = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) edges[i] = (int*)malloc(sizeof(int) * 2);
    edges[0][0] = 7;
    edges[0][1] = 2;

    edges[1][0] = 10;
    edges[1][1] = 1;

    edges[2][0] = 2;
    edges[2][1] = 3;

    edges[3][0] = 3;
    edges[3][1] = 5;

    edges[4][0] = 10;
    edges[4][1] = 6;

    edges[5][0] = 4;
    edges[5][1] = 6;

    edges[6][0] = 10;
    edges[6][1] = 9;

    edges[7][0] = 2;
    edges[7][1] = 4;

    edges[8][0] = 7;
    edges[8][1] = 10;

    edges[9][0] = 3;
    edges[9][1] = 8;

    int edgeCol[3] = { 2 };
    int returnSize = 0;
    int* res = findRedundantDirectedConnection(edges, n, edgeCol, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d,", res[i]);
    }
    printf("\n");
}