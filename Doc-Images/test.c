#include <disptree.h>

void main()
{
    // 22, 18,19, 14,8,17,15 13,11,5,2,
    Node *root = createNode(22);
    root->left = createNode(18);
    root->right = createNode(19);
    root->left->left = createNode(14);
    root->left->right = createNode(8);
    root->right->left = createNode(17);
    root->right->right = createNode(15);
    root->left->left->left = createNode(13);
    // root->left->left->right = createNode(11);
    // root->left->right->left = createNode(5);
    // root->left->right->right = createNode(2);
    // root->right->left->left = createNode(1);
    // root->right->left->right = createNode(1);
    // root->right->right->right = createNode(1);
    // root->right->right->left = createNode(1);
    dispTree(root);
}

/*

    
    drawNode("A", 0, 0, DEFAULT_TREE_COLOR, "#ffffff");
    drawNode("E", -60, 160, DEFAULT_TREE_COLOR, "#ffffff");
    drawNode("B", -120, 80, '#00ff00', "#ffffff");
    drawNode("D", -180, 160, DEFAULT_TREE_COLOR, "#ffffff");
    drawNode("F", 60, 160, DEFAULT_TREE_COLOR, "#ffffff");
    drawNode("C", 120, 80, "#ff0000", "#ffffff");
    drawNode("G", 180, 160, DEFAULT_TREE_COLOR, "#ffffff");
    drawNode(13, -240, 240, DEFAULT_TREE_COLOR, "#ffffff");



*/