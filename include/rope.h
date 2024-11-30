

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

// Basic functions
RopeNode *allocate_leaf(char *str);
void free_leaf(RopeNode *leaf);
void free_tree(RopeNode *root);

// Utility functions
bool is_balanced(RopeNode *root);
bool compare_nodes(RopeNode *root, int *lengths, int *heights, int *weights, int *index, int size);

// Rope operations
RopeNode *concat_no_rebalance(RopeNode *left, RopeNode *right);

// Testing functions
RopeNode *testing_create_tree_1();

#endif

