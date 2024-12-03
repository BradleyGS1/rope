

#include "../include/rope.h"


// Tests that make sure the function should return true when all the node data arrays
// are correct

void test_positive_1() {
    RopeNode *root = testing_create_tree_1();

    int lengths[] = {6, 3, 9, 2, 4, 6, 1, 6, 7, 13, 22};
    int heights[] = {1, 1, 2, 1, 1, 2, 1, 1, 2, 3, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 1, 6, 1, 6, 9};
    int index = 0;
    int size = 11;

    assert(compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_positive_2() {
    RopeNode *root = testing_create_tree_2();

    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 5, 3, 8, 16, 30, 7, 6, 13, 43};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 1, 2, 3, 4, 1, 1, 2, 5};
    int weights[] = {4, 3, 4, 6, 1, 6, 7, 4, 4, 4, 5, 3, 5, 8, 14, 7, 6, 7, 30};
    int index = 0;
    int size = 19;

    assert(compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

// Tests that make sure the function should return false when any one of the node data
// arrays have an incorrect entry

void test_negative_1() {
    RopeNode *root = testing_create_tree_1();

    // Single incorrect value compared to test_positive_1
    int lengths[] = {6, 3, 9, 2, 4, 6, 1, 6, 7, 13, 21}; // Changed 22 to 21
    int heights[] = {1, 1, 2, 1, 1, 2, 1, 1, 2, 3, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 1, 6, 1, 6, 9};
    int index = 0;
    int size = 11;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_negative_2() {
    RopeNode *root = testing_create_tree_1();

    // Single missing value compared to test_positive_1
    int lengths[] = {6, 3, 9, 2, 4, 1, 6, 7, 13, 21}; // Removed a 6 from the middle of this array
    int heights[] = {1, 1, 2, 1, 1, 2, 1, 1, 2, 3, 4};
    int weights[] = {6, 3, 6, 2, 4, 2, 1, 6, 1, 6, 9};
    int index = 0;
    int size = 11;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_negative_3() {
    RopeNode *root = testing_create_tree_1();

    // All arrays have their last value removed and size is reduced by 1
    // compared to test_positive_1
    int lengths[] = {6, 3, 9, 2, 4, 6, 1, 6, 7, 13};
    int heights[] = {1, 1, 2, 1, 1, 2, 1, 1, 2, 3};
    int weights[] = {6, 3, 6, 2, 4, 2, 1, 6, 1, 6};
    int index = 0;
    int size = 10;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_negative_4() {
    RopeNode *root = testing_create_tree_2();

    // Single incorrect value compared to test_positive_2
    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 5, 3, 8, 16, 30, 7, 6, 13, 43};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 1, 2, 3, 4, 1, 1, 2, 5};
    int weights[] = {4, 3, 4, 6, 1, 6, 7, 4, 4, 4, 4, 3, 5, 8, 14, 7, 6, 7, 30}; // Changed a 5 to a 4
    int index = 0;
    int size = 19;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_negative_5() {
    RopeNode *root = testing_create_tree_2();

    // Single missing value compared to test_positive_2
    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 5, 3, 8, 16, 30, 7, 6, 13, 43};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 5}; // Removed the 4 from the array
    int weights[] = {4, 3, 4, 6, 1, 6, 7, 4, 4, 4, 5, 3, 5, 8, 14, 7, 6, 7, 30};
    int index = 0;
    int size = 19;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

void test_negative_6() {
    RopeNode *root = testing_create_tree_2();

    // All arrays have their last value removed and size is reduced by 1
    // compared to test_positive_2
    int lengths[] = {4, 3, 7, 6, 1, 7, 14, 4, 4, 8, 5, 3, 8, 16, 30, 7, 6, 13};
    int heights[] = {1, 1, 2, 1, 1, 2, 3, 1, 1, 2, 1, 1, 2, 3, 4, 1, 1, 2};
    int weights[] = {4, 3, 4, 6, 1, 6, 7, 4, 4, 4, 5, 3, 5, 8, 14, 7, 6, 7};
    int index = 0;
    int size = 18;

    assert(!compare_nodes(root, lengths, heights, weights, &index, size));
    free_tree(root);
}

int main() {
    test_positive_1();
    test_positive_2();
    test_negative_1();
    test_negative_2();
    test_negative_3();
    test_negative_4();
    test_negative_5();
    test_negative_6();
    return 0;
}

