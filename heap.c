#include "heap.h"
#include "config.h"


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
        if (root->level == 2 && root->lastParent == NULL)
        {
            root->lastParent = curNode;
        }
        else if (root->level > 1)
        {
            curNode->nextParent = root->lastParent;
            root->lastParent = curNode;
        }
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
    int num, container;
    bNode* temp = (bNode*)root;
    bool swap_with_right = false;
    bool swap_with_left = false;
    bool left_is_null = false;
    bool right_is_null = false;
    popHeapResult res;
    
    if ( root == NULL )
    {
        res.result = 0;
        return res;
    }

    res.data = root->data;

    if (root->col == 0)
    {
        if ( root->level == 1 )
        {
            free(root);
            res.result = 2;
            return res;
        } 
        else 
        {
            root->level--;
            root->col =  power(2 , root->level)-1;
        }
    }
    
    else
    {
        root->col--;
    }
    
    if ( root->lastParent != NULL )
    {
        if ( root->lastParent->right != NULL )
        {
            num = root->lastParent->right->data;
            free( root->lastParent->right);
            root->lastParent->right = NULL;
        }
        else 
        {
            num = root->lastParent->left->data;
            free( root->lastParent->left );
            root->lastParent->left = NULL;
            root->lastParent = root->lastParent->nextParent;
        }
    }
    
    else 
    {
        if (root->right != NULL)
        {
            num = root->right->data;
            free(root->right);
            root->right = NULL;
        }
        else 
        {
            num = root->left->data;
            free(root->left);
            root->left = NULL;
        }
    }
    
    root->data = num;
    
    while (true)
    {
        swap_with_left = false;
        swap_with_right = false;
        left_is_null = false;
        right_is_null = false;

        if (temp->left == NULL)
        {
            left_is_null = true;
        }
        
        if (temp->right == NULL)
        {
            right_is_null = true;
        }

        if (left_is_null && !right_is_null)
        {
            if( MaxMin(temp->right->data, temp->data, maxHeap) )
            {
                swap_with_right = true;
            }
            else
            {
                break;
            }
        }
        
        else if (!left_is_null && right_is_null)
        {
            if ( MaxMin(temp->left->data, temp->data, maxHeap) )
            {
                swap_with_left = true;
            }
            else 
            {
                break;
            }
        }
        
        else if (!left_is_null && !right_is_null)
        {
            if (MaxMin(temp->left->data, temp->right->data, maxHeap))
            {
                if (MaxMin(temp->left->data, temp->data, maxHeap))
                {
                    swap_with_left = true;
                }
                else 
                {
                    break;
                }
            }
            
            else 
            {
                if (MaxMin(temp->right->data, temp->data, maxHeap))
                {
                    swap_with_right = true;
                }
                else 
                {
                    break;
                }                
            }
        }

        else
        {
            break;
        }

        if (swap_with_left)
        {
            container = temp->data;
            temp->data = temp->left->data;
            temp->left->data = container;
            temp = temp->left;
        }
        
        else if (swap_with_right)
        {
            container = temp->data;
            temp->data = temp->right->data;
            temp->right->data = container;
            temp = temp->right;
        }
    }
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