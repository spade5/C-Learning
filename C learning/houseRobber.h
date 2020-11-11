#pragma once

#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define NULL 0

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

int* dp(struct TreeNode* node) {
    int res[2] = { 0, 0 };
    if (node == NULL) {
        return res;
    }
    int* left = dp(node->left);
    int* right = dp(node->right);

    res[0] = max(left[0], left[1]) + max(right[0], right[1]);
    res[1] = left[0] + right[0] + node->val;

    return res;
}

int rob(struct TreeNode* root) {
    int* res = dp(root);
    return max(res[0], res[1]);
}

struct TreeNode* createNode(int* nums, int index, int size) {
    if (index > size || nums[index - 1] == NULL) return NULL;
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->val = nums[index - 1];
    node->left = createNode(nums, index * 2, size);
    node->right = createNode(nums, index * 2 + 1, size);
    return node;
}

void testHouseRobber() {
    int nums[] = { 3,4,5,1,3,NULL,1 };
    struct TreeNode* root = createNode(nums, 1, 7);
    printf("%d\n", rob(root));
}