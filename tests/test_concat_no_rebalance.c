

#include "../include/rope.h"


int main() {
    RopeNode *node_1 = allocate_leaf("Hello_");
    RopeNode *node_2 = allocate_leaf("my_");
    RopeNode *node_3 = allocate_leaf("na");
    RopeNode *node_4 = allocate_leaf("me_i");
    RopeNode *node_5 = allocate_leaf("s");
    RopeNode *node_6 = allocate_leaf("_Simon");

    RopeNode *node_7 = concat_no_rebalance(node_3, node_4);
    RopeNode *node_8 = concat_no_rebalance(node_5, node_6);

    assert(!node_7->str);
    assert(node_7->left == node_3);
    assert(node_7->right == node_4);
    assert(!node_7->parent);

    RopeNode *node_9 = concat_no_rebalance(node_1, node_2);
    RopeNode *node_10 = concat_no_rebalance(node_7, node_8);

    RopeNode *node_11 = concat_no_rebalance(node_9, node_10);

    assert(!node_7->str);
    assert(node_7->left == node_3);
    assert(node_7->right == node_4);
    assert(node_7->parent == node_10);

    assert(node_7->length == 6);
    assert(node_7->height == 2);
    assert(node_7->weight == 2);

    assert(node_8->length == 7);
    assert(node_8->height == 2);
    assert(node_8->weight == 1);

    assert(node_9->length == 9);
    assert(node_9->height == 2);
    assert(node_9->weight == 6);

    assert(node_10->length == 13);
    assert(node_10->height == 3);
    assert(node_10->weight == 6);

    assert(node_11->length == 22);
    assert(node_11->height == 4);
    assert(node_11->weight == 9);

    free_tree(node_11);

    return 0;
}

