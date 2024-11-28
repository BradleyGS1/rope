

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

RopeNode *allocate_leaf(char *str);
void free_leaf(RopeNode *leaf);

#endif

