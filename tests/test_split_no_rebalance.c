

#include "../include/rope.h"


void test_split_no_re_1() {
    RopeNode *root = testing_create_tree_1();
    // By splitting at index 11 we do not have to divide any leaves
    SplitRopeNodes *split_nodes = split_no_rebalance(root, 11);

    int left_lengths[] = {6, 3, 9, 2, 2, 2, 11};
    int left_heights[] = {1, 1, 2, 1, 2, 3, 4};
    int left_weights[] = {6, 3, 6, 2, 2, 2, 9};
    int left_index = 0;
    int left_size = 7;
    assert(compare_nodes(split_nodes->first, left_lengths, left_heights, left_weights, &left_index, left_size));

    int right_lengths[] = {3, 1, 6, 7, 10};
    int right_heights[] = {1, 1, 1, 2, 3};
    int right_weights[] = {3, 1, 6, 1, 3};
    int right_index = 0;
    int right_size = 5;
    assert(compare_nodes(split_nodes->second, right_lengths, right_heights, right_weights, &right_index, right_size));

    free_tree(split_nodes->first);
    free_tree(split_nodes->second);
    free(split_nodes);
}

void test_split_no_re_2() {
    RopeNode *root = testing_create_tree_1();
    // By splitting at index 14 it is necessary to divide the leaf into two
    SplitRopeNodes *split_nodes = split_no_rebalance(root, 14);

    int left_lengths[] = {6, 3, 9, 2, 3, 3, 5, 5, 14};
    int left_heights[] = {1, 1, 2, 1, 1, 2, 3, 4, 5};
    int left_weights[] = {6, 3, 6, 2, 3, 3, 2, 5, 9};
    int left_index = 0;
    int left_size = 9; // Notice compared to prev test we have two new nodes because of divide_leaf
    assert(compare_nodes(split_nodes->first, left_lengths, left_heights, left_weights, &left_index, left_size));

    int right_lengths[] = {1, 1, 6, 7, 8};
    int right_heights[] = {1, 1, 1, 2, 3};
    int right_weights[] = {1, 1, 6, 1, 1};
    int right_index = 0;
    int right_size = 5;
    assert(compare_nodes(split_nodes->first, right_lengths, right_heights, right_weights, &right_index, right_size));

    free_tree(split_nodes->first);
    free_tree(split_nodes->second);
    free(split_nodes);
}
int main() {
    test_split_no_re_1();
    test_split_no_re_2();
    return 0;
}

