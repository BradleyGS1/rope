

#include "../include/rope.h"


int main() {
    RopeNode *root = testing_create_tree_1();

    int lengths[] = {6, 3, 9, 2, 4, 6, 1, 6, 7, 13, 22};
    int heights[] = {1, 1, 2, 1, 1, 2, 1, 1, 2, 3, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 1, 6, 1, 6, 9};
    int index = 0;
    int size = 11;

    assert(compare_nodes(root, lengths, heights, weights, &index, size));

    free_tree(root);

    return 0;
}

