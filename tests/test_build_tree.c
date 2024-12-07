

#include "../include/rope.h"


void test_build_tree_1() {
    RopeNode *root = testing_create_tree_1();
    RopeNode **leaves = NULL;
    int index = 0;
    collect_leaves(root, &leaves, &index);

    free_tree_except_leaves(root);
    RopeNode *new_root = build_tree(&leaves, index);

    int lengths[] = {6, 3, 9, 2, 4, 6, 15, 1, 6, 7, 22};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 9, 1, 6, 1, 15};
    int idx = 0;
    int size = 11;
    assert(compare_nodes(new_root, lengths, heights, weights, &idx, size));

    free_tree(new_root);
    free(leaves);
}

void test_build_tree_2() {
    RopeNode *root = testing_create_tree_2();
    RopeNode **leaves = NULL;
    int index = 0;
    collect_leaves(root, &leaves, &index);

    free_tree_except_leaves(root);
    RopeNode *new_root = build_tree(&leaves, index);

    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 22, 5, 3, 8, 7, 6, 13, 21, 43};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 4, 1, 1, 2, 1, 1, 2, 3, 5};
    int weights[] = {4, 3, 4, 6, 1, 6, 7, 4, 4, 4, 14, 5, 3, 5, 7, 6, 7, 8, 22};
    int idx = 0;
    int size = 19;
    assert(compare_nodes(new_root, lengths, heights, weights, &idx, size));

    free_tree(new_root);
    free(leaves);
}

int main() {
    test_build_tree_1();
    return 0;
}

