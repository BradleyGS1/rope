

#include "../include/rope.h"


void test_collect_leaves_1() {
    RopeNode *root = testing_create_tree_1();
    RopeNode **leaves = NULL;
    int index = 0;
    collect_leaves(root, &leaves, &index);

    assert(leaves[0] == root->left->left);
    assert(leaves[1] == root->left->right);
    assert(leaves[2] == root->right->left->left);
    assert(leaves[3] == root->right->left->right);
    assert(leaves[4] == root->right->right->left);
    assert(leaves[5] == root->right->right->right);
    assert(index = 6);

    free_tree(root);
    free(leaves);
}

void test_collect_leaves_2() {
    RopeNode *root = testing_create_tree_2();
    RopeNode **leaves = NULL;
    int index = 0;
    collect_leaves(root, &leaves, &index);

    assert(leaves[0] == root->left->left->left->left);
    assert(leaves[1] == root->left->left->left->right);
    assert(leaves[2] == root->left->left->right->left);
    assert(leaves[3] == root->left->left->right->right);
    assert(leaves[4] == root->left->right->left->left);
    assert(leaves[5] == root->left->right->left->right);
    assert(leaves[6] == root->left->right->right->left);
    assert(leaves[7] == root->left->right->right->right);
    assert(leaves[8] == root->right->left);
    assert(leaves[9] == root->right->right);
    assert(index = 10);

    free_tree(root);
    free(leaves);
}


int main() {
    test_collect_leaves_1();
    test_collect_leaves_2();
    return 0;
}

