

#include "../include/rope.h"


/*
 * Allocates memory for a single rope leaf of type RopeNode and returns its
 * pointer.
 * Parameters:
 * - char *str. This is a small part of the full string that we want to be
 *   represented by this single RopeNode. The full string is the concatenation of
 *   all substrings represented by the leaves of a rope. The argument is copied
 *   and allocated memory and so the user may call free(str) without altering the
 *   created node.
 * Returns:
 * - RopeNode *. This is a pointer to the RopeNode leaf. This leaf (and stored
 *   string) must be freed by the user either explicitly by calling free_leaf(leaf)
 *   or implicitly by calling free_tree(root) where root is the pointer to the root 
 *   node of the tree which contains leaf.
 */
RopeNode *allocate_leaf(char *str) {
    if (!str) {
        printf("Error - Argument char *str cannot be NULL for allocate_leaf.\n");
        return NULL;
    }
    RopeNode *leaf = (RopeNode *) malloc(sizeof(RopeNode));
    if (!leaf) {
        printf("Error - Failed to allocate memory for allocate_leaf.\n");
        return NULL;
    }
    leaf->str = strdup(str);
    leaf->left = NULL;
    leaf->right = NULL;
    leaf->parent = NULL;
    leaf->length = strlen(str);
    leaf->height = 1;
    leaf->weight = strlen(str);
    return leaf;
}

void free_leaf(RopeNode *leaf) {
    if (!leaf) {
        printf("Error - Argument RopeNode *leaf cannot be NULL for free_leaf.\n");
        return;
    }
    if (leaf->parent) {
        if (leaf->parent->left == leaf) {
            leaf->parent->left = NULL;
        }
        if (leaf->parent->right == leaf) {
            leaf->parent->right = NULL;
        }
    }
    if (leaf->left) leaf->left->parent = NULL;
    if (leaf->right) leaf->right->parent = NULL;
    if (leaf->str) free(leaf->str);
    leaf->str = NULL;
    free(leaf);
}

