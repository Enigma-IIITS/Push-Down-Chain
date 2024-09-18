#include "heap.h"
#include "stdio.h"
#include "bintree.h"

bRootNode* Arr2Heap(int *arr, int size, bool maxHeap)
{
    bRootNode *root = CreatebRootNode(arr[0]);
    for(int i = 1; i < size; i++)
    {
        pushHeap(root, arr[i], maxHeap);  
    }
    return root;
}

bRootNode* pushHeap( bRootNode *root, int num, bool maxHeap )
{
    int container;

    if ( root == NULL )
    {
        return CreatebRootNode(num);
    }


    int level = root->level - 1;
    int col = root->col;

    bNode* curNode = (bNode*)root;
    if ( MaxMin(num, root->data, maxHeap) )
    {
        container = root->data;
        root->data = num;
        num = container;
    }

    for ( int a = 0 ; a < level ; a++ )
    {
        if ((col >> (level - a)) & 1)
        {
            curNode = curNode->right;
        }
        else 
        {
            curNode = curNode->left;
        }
        if ( MaxMin(num, curNode->data, maxHeap))
        {
            container = curNode->data;
            curNode->data = num;
            num = container;
        } 
    }

    if (col & 1)
    {
        curNode->right = CreatebNode(num);
    }
    else 
    {
        curNode->left = CreatebNode(num);
    }

    root->col++;
    if (root->col == power(2, root->level))
    {
        root->level++;
        root->col = 0;
    }
    return root;
}

popHeapResult popHeap(bRootNode* root, bool maxHeap)
{
    int num, level, col;
    bNode* temp = (bNode*)root;
    popHeapResult res;
    bool swap_with_right = false;
    bool swap_with_left = false;

    // printf("BEF COL : %d LEVEL : %d\n",root->col, root->level);

    if (root == NULL) 
    {
        // Specifiying that heap is empty, so could not pop any element
        res.result = 0;
        return res;
    }

    res.data = root->data;

    if (root->col == 0)
    {
        if (root->level == 1)
        {
            free(root);
            // Specifying that heap is "now" empty, and root is freed
            res.result = 2;
            return res;
        }
        else 
        {
            root->level--;
            root->col = power(2, root->level) - 1;
        }
    }

    else 
    {
        root->col--;
    }

    level = root->level;
    col = root->col;

    // printf("AFT COL : %d LEVEL : %d\n",root->col, root->level);
    // dispNodeTree((Node *)root);


    // printf("level : %d, col : %d\n", level, col);

    // Objective : Free the node in location (root->level, root->col)
    for (int a = 0 ; a < level-1 ; a++)
    {
        if ((col >> (level - 1 - a)) & 1)
        {
            temp = temp->right;
        }
        else 
        {
            temp = temp->left;
        }
    }

    if (col & 1)
    {
        root->data = temp->right->data;
        free(temp->right);
        temp->right = NULL;
    }
    else 
    {
        root->data = temp->left->data;
        free(temp->left);
        temp->left = NULL;
    }

    // dispNodeTree((Node *)root);
    temp = (bNode *)root;
    // printf("Root : %d",root->data);
    // Objective : Heapify.. (Bubble down)
    while (1) 
    {
        swap_with_left = false;
        swap_with_right = false;

        // if right is not null, left is definitely not null
        if (temp->right != NULL)
        {
            if ( MaxMin( temp->right->data, temp->data, maxHeap ))
            {
                swap_with_right = true;
                if ( MaxMin( temp->left->data, temp->right->data, maxHeap ) )
                {
                    swap_with_right = false;
                    swap_with_left = true;
                }
            }
            else if ( MaxMin( temp->left->data, temp->data, maxHeap ) )
            {
                swap_with_left = true;
            }
        }
        
        else if (temp->left != NULL)
        {
            if ( MaxMin( temp->left->data, temp->data, maxHeap ) )
            {
                swap_with_left = true;
            }
        }
        
        if (swap_with_left)
        {
            num = temp->left->data;
            temp->left->data = temp->data;
            temp->data = num;
            temp = temp->left;
        }
        else if (swap_with_right)
        {
            num = temp->right->data;
            temp->right->data = temp->data;
            temp->data = num;
            temp = temp->right;
        }
        else
        {
            // printf("NUM : %d\n", temp->data);
            break;    
        }
    }
    // dispNodeTree((Node *)root);
    res.result = 1;
    return res;
}

bool HeapIsValid(bNode *root, bool maxHeap)
{
    if (root == NULL) 
    {
        return 1;
    }
    
    if ( root->left != NULL )
    {
        if ( MaxMin(root->left->data,root->data, maxHeap) )
        {
            return 0;
        }
    }
    
    if ( root->right != NULL )
    {
        if ( MaxMin(root->right->data, root->data, maxHeap) )
        {
            return 0;
        }
    }
    return 1;
}