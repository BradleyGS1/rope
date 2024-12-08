

#include "../include/rope.h"


void test_concat_1() {
    // The result of this concatenation would normally be an unbalanced tree
    // but the concat function automatically rebalances when this is the case
    RopeNode *left = testing_create_tree_1();
    RopeNode *right = allocate_leaf("_test");
    RopeNode *parent = concat(left, right);

    int lengths[] = {6, 3, 9, 2, 4, 6, 15, 1, 6, 7, 5, 12, 27};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 3, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 9, 1, 6, 1, 5, 7, 15};
    int index = 0;
    int size = 13;
    assert(compare_nodes(parent, lengths, heights, weights, &index, size));
    assert(testing_tree_is_balanced(parent));

    free_tree(parent);
}

void test_concat_2() {
    RopeNode *left = testing_create_tree_2();
    RopeNode *right_left = allocate_leaf("_an");
    RopeNode *right_right = allocate_leaf("d_cat");
    RopeNode *right = concat(right_left, right_right);
    RopeNode *parent = concat(left, right);

    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 5, 3, 8, 16, 30, 7, 6, 13, 3, 5, 8, 21, 51};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 1, 2, 3, 4, 1, 1, 2, 1, 1, 2, 3, 5};
    int weights[] = {4, 3, 4, 6, 1, 6, 6, 4, 4, 4, 5, 3, 5, 8, 14, 7, 6, 7, 3, 5, 3, 13, 30};
    int index = 0;
    int size = 23;
    assert(compare_nodes(parent, lengths, heights, weights, &index, size));
    assert(testing_tree_is_balanced(parent));

    free_tree(parent);
}

int main() {
    test_concat_1();
    test_concat_2();
    return 0;
}

