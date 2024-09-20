#include "utility.h"
#include <stdio.h>

/***********************************************/
/*          Local function prototypes          */
/***********************************************/

bNode* CreatebNode(int data)
{
    bNode *newbNode = (bNode*)malloc(sizeof(bNode));

    if(newbNode == NULL)
    {
        printf("Error: Unable to allocate memory for new bNode.\n");
        exit(1);
    }

    newbNode->data = data;
    newbNode->right = NULL;
    newbNode->left = NULL;
    newbNode->nextParent = NULL;

    return newbNode;
}

bool MaxMin(int a, int b, bool returnMax)
{
    if (returnMax == true)
    {
        return a > b;
    }
    else 
    {
        return a < b;
    }
    /*
     *  bool result = a < b
     *  return returnMax^result; 
     * The above two lines of code will not work for the case a = 6, b = 6 
     * It is supposed to return false, but returns true
     */
} 

#ifdef DEBUG_HEAP
static int call = 1;    
#endif
// Destroy binary tree 
void destroybTree(bNode *root)
{
    if (root == NULL)
    {
        return;
    }

    destroybTree(root->left);
    destroybTree(root->right);

#ifdef DEBUG_HEAP
    printf("%.2d : %.2d\n", call++, root->data);
#endif
    free(root);
}

bRootNode* CreatebRootNode(int num)
{
    bRootNode* root = (bRootNode*)malloc(sizeof(bRootNode));
    root->left = NULL;
    root->right = NULL;
    root->lastParent = NULL;
    root->level = 1;
    root->col = 0;
    root->data = num;
    return root;
}

int power(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }

    int result = base;
    for (int i = 1; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}