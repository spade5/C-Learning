#pragma once
#include <string.h>
#include <stdlib.h>

typedef struct LinkNode {
    int startIndex;
    int len;
    struct LinkNode* next;
} LinkNode;

char* simplifyPath(char* path) {
    LinkNode* head = malloc(sizeof(LinkNode));
    head->next = 0;
    int index = 1;
    int len = strlen(path);
    LinkNode* temp = 0;
    for (; index < len; index++) {
        char ch = path[index];
        if (ch >= 'a' && ch <= 'z') {
            if (temp == 0) {
                temp = malloc(sizeof(LinkNode));
                temp->startIndex = index;
                temp->len = 1;
            }
            else {
                temp->len++;
            }
        }
        else {
            if (ch == '/') {
                if (temp != 0) {
                    temp->next = head->next;
                    head->next = temp;
                    temp = 0;
                }
            }
            else if (ch == '.' && path[index + 1] == '.') {
                if (head->next != 0) {
                    head->next = head->next->next;
                }
            }
        }
    }
    char* ret = malloc(sizeof(char) * (len + 1));
    index = 0;
    temp = head->next;
    while (temp != 0) {
        for (int i = temp->len - 1; i >= 0; i--) {
            ret[index++] = path[temp->startIndex + i];
        }
        ret[index++] = '/';
        temp = temp->next;
    }
    if (index == 0) {
        ret[index] = '/';
    }
    else {
        for (int i = 0; i < index / 2; i++) {
            char ch = ret[i];
            ret[i] = ret[index - i - 1];
            ret[index - i - 1] = ch;
        }
    }
    
    ret[index] = '\0';
    return ret;
}