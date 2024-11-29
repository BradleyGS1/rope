

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
        printf("Error - argument char *str cannot be NULL for allocate_leaf.\n");
        return NULL;
    }
    RopeNode *leaf = malloc(sizeof(RopeNode));
    if (!leaf) {
        printf("Error - failed to allocate memory for allocate_leaf.\n");
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
        printf("Error - argument RopeNode *leaf cannot be NULL for free_leaf.\n");
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
    if (leaf->str) free(leaf->str);
    leaf->str = NULL;
    free(leaf);
}

void free_tree(RopeNode *root) {
    if (!root) {
        printf("Error - argument RopeNode *root cannot be NULL for free_tree.\n");
        return;
    }
    if (root->left) free_tree(root->left);
    if (root->right) free_tree(root->right);
    free_leaf(root);
}

/*
 * A simple boolean function that returns true if the tree represented by the
 * given root node is balanced assuming that the left and right subtrees are
 * balanced.
 * Parameters:
 * - RopeNode *root. The pointer to the root of the tree we want to check for 
 *   balance.
 * Returns:
 * - bool. Returns true if the tree is balanced otherwise returns false.
 */
bool is_balanced(RopeNode *root) {
    if (!root) {
        printf("Error - argument RopeNode *root cannot be NULL for is_balanced.\n");
        return false;
    }
    int left_height = (root->left ? root->left->height : 0);
    int right_height = (root->right ? root->right->height : 0);
    return (abs(left_height - right_height) <= 1);
}

/*
 * Compares the nodes internal data values to the provided lists of values. If any
 * value does not match or if the index exceeds the size of the arrays then returns
 * false otherwise returns true.
 * Parameters:
 * - RopeNode *root. The pointer to the root node of the tree we want to check.
 * - int *lengths. The pointer to the array of integer length values.
 * - int *heights. The pointer to the array of integer height values.
 * - int *weights. The pointer to the array of integer weight values.
 * - int *index. Pointer of current index. Should start with value 0.
 * - int size. The size of the arrays. All arrays should be this size.
 * Returns:
 * - bool. Returns true if the internal node data matches with all provided arrays.
 */
bool compare_nodes(RopeNode *root, int *lengths, int *heights, int *weights, int *index, int size) {
    if (*index >= size) {
        printf("Error - index %d exceeds size %d.\n", *index, size);
        return false;
    }
    if (root->left) {
        if (!compare_nodes(root->left, lengths, heights, weights, index, size)) {
            return false;
        }
    }
    if (root->right) {
        if (!compare_nodes(root->right, lengths, heights, weights, index, size)) {
            return false;
        }
    }
    if (lengths[*index] != root->length || heights[*index] != root->height || weights[*index] != root->weight) {
        return false;
    }
    (*index)++;
    return true;
}

/*
 * Concatenates two nodes 'left' and 'right' allocating memory for a new parent
 * node 'parent' and setting the left child of 'parent' to be 'left' and the right
 * child of 'parent' to be 'right'. This function DOES NOT PERFORM REBALANCING and
 * does not even check if the resulting tree is balanced or not. The node created
 * by this function must have the memory allocated for it cleared, the easiest way
 * of doing so is by calling free_tree(parent) which will free the whole subtree
 * with 'parent' as its root. free_leaf(parent) may also be called but is not
 * recommended.
 * Parameters:
 * - RopeNode *left. The pointer to the subtree we want to make the left subtree
 *   of a new node. Only one of left or right can be NULL.
 * - RopeNode *right. The pointer to the subtree we want to make the right subtree
 *   of a new node. Only one of left or right can be NULL.
 * Returns:
 * - RopeNode *. The pointer to the newly created node. Must be freed with free_tree
 *   or free_leaf. IS NOT GUARANTEED TO CREATE A BALANCED TREE.
 */
RopeNode *concat_no_rebalance(RopeNode *left, RopeNode *right) {
    if (!left && !right) {
        printf("Error - arguments RopeNode *left, RopeNode *right cannot both be\
            NULL.\n");
        return NULL;
    }

    RopeNode *parent = malloc(sizeof(RopeNode));
    if (!parent) {
        printf("Error - failed to allocate memory for concat_no_rebalance.\n");
        return NULL;
    }

    parent->str = NULL;
    parent->left = left;
    parent->right = right;

    int left_length = 0, right_length = 0;
    int left_height = 0, right_height = 0;
    int left_weight = 0, right_weight = 0;

    if (left) {
        left_length = left->length;
        left_height = left->height;
        left_weight = left->weight;
    }
    if (right) {
        right_length = right->length;
        right_height = right->height;
        right_weight = right->weight;
    }

    parent->str = NULL;
    parent->left = left;
    parent->right = right;
    parent->parent = NULL;
    parent->length = left_length + right_length;
    parent->height = (left_height > right_height ? left_height : right_height) + 1;
    parent->weight = left_length;

    return parent;
}


