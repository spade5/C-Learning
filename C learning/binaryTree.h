#pragma once
#include <stdlib.h>
#include <string.h>
#define NULL 0

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};



struct TreeNode* createNode(int* nums, int index, int size) {
    if (index > size || nums[index - 1] == NULL) return NULL;
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = nums[index - 1];
    node->left = createNode(nums, index * 2, size);
    node->right = createNode(nums, index * 2 + 1, size);
    return node;
}

char* traverse(struct TreeNode* node) {
    if (node == NULL) return "\0";
    char* left = traverse(node->left);
    char* right = traverse(node->right);
    return "";
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize) {

}

void test() {
    int arr[] = { 1, 2, 3, 4, NULL, 2, 4, NULL, NULL, 4 };
    struct TreeNode* root = createNode(arr, 1, 10);
}