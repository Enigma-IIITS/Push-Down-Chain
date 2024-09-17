#ifndef UTILITY_H
#define UTILITY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct bNode{
    int data;
    struct bNode *left;
    struct bNode *right;
    struct bNode *nextParent;
}bNode;

typedef struct bRootNode{
    int data;
    bNode *left;
    bNode *right;
    int level;
    int col;
    struct bNode* lastParent;
}bRootNode;

typedef struct popHeapResult{
    int data;
    uint8_t result;
}popHeapResult;

/***********************************************/
/*          Function prototypes          */
/***********************************************/
bNode* CreatebNode(int data);
bRootNode* CreatebRootNode(int data);
bool MaxMin(int a, int b, bool returnMax);
bool MaxMinEqual(int a, int b, bool returnMax);
void destroybTree(bNode *root);
int power(int base, int exponent);

#endif