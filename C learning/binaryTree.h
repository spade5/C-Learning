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

struct TreeNode* constructMaximumBinaryTree2(int* nums, int start, int numsSize) {
    if (numsSize <= 0) return NULL;
    int max = nums[start], maxIndex = start;
    for (int i = 1; i < numsSize; i++) {
        if (nums[start + i] > max) {
            max = nums[start + i];
            maxIndex = start + i;
        }
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = max;
    printf("left:%d, len:%d, right:%d, len:%d\n", start, maxIndex - start, maxIndex + 1, numsSize - maxIndex + start - 1);
    node->left = constructMaximumBinaryTree2(nums, start, maxIndex - start);
    node->right = constructMaximumBinaryTree2(nums, maxIndex + 1, numsSize - maxIndex + start - 1);
    return node;
}

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    return constructMaximumBinaryTree2(nums, 0, numsSize);
}

struct TreeNode* build(int* postorder, int post_lo, int post_hi, int* inorder, int in_lo, int in_hi) {
    printf("post_lo:%d, post_hi:%d, in_lo:%d, in_hi:%d\n", post_lo, post_hi, in_lo, in_hi);
    if (post_lo > post_hi) return NULL;
    int cur = postorder[post_hi];
    int curIndex = in_lo;
    while (inorder[curIndex] != cur) {
        curIndex++;
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = cur;
    node->left = build(postorder, post_lo, post_lo + curIndex - in_lo, inorder, in_lo, curIndex - 1);
    node->right = build(postorder, post_lo + curIndex - in_lo + 1, post_hi - 1, inorder, curIndex + 1, in_hi);
    return node;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    return build(postorder, 0, postorderSize - 1, inorder, 0, inorderSize - 1);
}

int traverseRight(struct TreeNode* node, int num) {
    if (node == NULL) {
        return num;
    }
    printf("val:%d, num:%d\n", node->val, num);
    int right = num + traverse(node->right, num);
    int val = right + node->val;
    node->val = val;
    int left = traverse(node->left, val);
    return left;
}

struct TreeNode* convertBST(struct TreeNode* root) {
    traverseRight(root, 0);
    return root;
}

void test() {
    int arr[] = { 4,1,6,0,2,5,7, NULL,NULL,NULL,3,NULL,NULL,NULL,8 };
    int inorder[] = { 9, 3, 15, 20, 7 };
    int postorder[] = { 9, 15, 7, 20, 3 };
    struct TreeNode* root = createNode(arr, 1, 15);
    convertBST(root);
}