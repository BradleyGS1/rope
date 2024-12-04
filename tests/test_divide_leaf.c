

#include "../include/rope.h"


void test_divide_leaf_1() {
    RopeNode *leaf = allocate_leaf("Hello");
    divide_leaf(leaf, 2);

    RopeNode *left = leaf->left;
    RopeNode *right = leaf->right;

    assert(left);
    assert(str_is_equal(left->str, "He"));
    assert(!left->left);
    assert(!left->right);
    assert(left->length == 2);
    assert(left->weight == 2);

    assert(right);
    assert(str_is_equal(right->str, "llo"));
    assert(!right->left);
    assert(!right->right);
    assert(right->length == 3);
    assert(right->weight == 3);

    free_tree(leaf);
}

void test_divide_leaf_2() {
    RopeNode *root = testing_create_tree_1();

    int index = 14;
    RopeNode *leaf = fetch_leaf(root, &index);
    divide_leaf(leaf, 3);
    backprop_height(leaf);

    assert(str_is_equal(leaf->left->str, "me_"));
    assert(str_is_equal(leaf->right->str, "i"));

    int lengths[] = {6, 3, 9, 2, 3, 1, 4, 6, 1, 6, 7, 13, 22};
    int heights[] = {1, 1, 2, 1, 1, 1, 2, 3, 1, 1, 2, 4, 5};
    int weights[] = {6, 3, 6, 2, 3, 1, 3, 2, 1, 6, 1, 6, 9};
    int idx = 0;
    int size = 13;

    assert(compare_nodes(root, lengths, heights, weights, &idx, size));

    free_tree(root);
}

int main() {
    test_divide_leaf_1();
    test_divide_leaf_2();
    return 0;
}

