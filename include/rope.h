

#ifndef ROPE_H
#define ROPE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


typedef struct RopeNode {
    char *str;
    int length;
    int height;
    int weight;
    struct RopeNode *left;
    struct RopeNode *right;
    struct RopeNode *parent;
} RopeNode;

typedef struct SplitRopeNodes {
    RopeNode *first;
    RopeNode *second;
} SplitRopeNodes;

// Basic functions
RopeNode *allocate_leaf(char *str);
void free_leaf(RopeNode *leaf);
void free_tree(RopeNode *root);
void backprop_height(RopeNode *node);
void split_node(RopeNode *node, SplitRopeNodes *split_nodes);

// Utility functions
bool str_is_equal(char *str_1, char *str_2);
bool is_balanced(RopeNode *root);
bool compare_nodes(RopeNode *root, int *lengths, int *heights, int *weights, int *index, int size);

// Rope operations
RopeNode *fetch_leaf(RopeNode *root, int *index);
void collect_leaves(RopeNode *root, RopeNode ***leaves, int *index);
RopeNode *concat_no_rebalance(RopeNode *left, RopeNode *right);
void divide_leaf(RopeNode *node, int index);
SplitRopeNodes *split_no_rebalance(RopeNode *root, int index);

// Testing functions
RopeNode *testing_create_tree_1();
RopeNode *testing_create_tree_2();

#endif

