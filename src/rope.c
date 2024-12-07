

#include "../include/rope.h"


/*
 * Allocates memory for a single rope leaf of type RopeNode and returns its
 * pointer.
 * Parameters:
 * - char *str. This is a small part of the full string that we want to be
 *  represented by this single RopeNode. The full string is the concatenation of
 *   all substrings represented by the leaves of a rope. The argument is copied
 *  and allocated memory and so the user may call free(str) without altering the
 *   created node.
 * Returns:
 * - RopeNode *. This is a pointer to the RopeNode leaf. This leaf (and stored
 *  string) must be freed by the user either explicitly by calling free_leaf(leaf)
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

void free_tree_except_leaves(RopeNode *root) {
    if (!root) {
        printf("Error - argument RopeNode *root cannot be NULL for free_tree_except_leaves.\n");
        return;
    }
    if (root->left) free_tree_except_leaves(root->left);
    if (root->right) free_tree_except_leaves(root->right);
    if (root->left || root->right) free_leaf(root);
}

/*
 * Goes up the tree backpropogating the height values from the current node all
 * the way up to the root node. This is done by recursively calling this function
 * on the parent node.
 * Parameters:
 * - RopeNode *node. The pointer to the node we want to being the height backprop
 *   from. Usually started from a parent of a leaf.
 */
void backprop_height(RopeNode *node) {
    if (!node) return;
    int left_height = (node->left ? node->left->height : 0);
    int right_height = (node->right ? node->right->height : 0);
    node->height = (left_height > right_height ? left_height : right_height) + 1;
    backprop_height(node->parent);
}

void split_node(RopeNode *node, SplitRopeNodes *split_nodes) {
    if (!node || !split_nodes) {
        printf("Error - arguments RopeNode *node and SplitRopeNodes *split_nodes cannot be NULL.\n");
        return;
    }
    if (node->parent) {
        if (node->parent->left == node) node->parent->left = NULL;
        if (node->parent->right == node) node->parent->right = NULL;
    }
    if (split_nodes->second) {
        split_nodes->second = concat_no_rebalance(split_nodes->second, node);
    } else {
        node->parent = NULL;
        split_nodes->second = node;
    }
}

/*
 * A simple boolean function that returns true if both strings are identical, else
 * false.
 * Parameters:
 * - char *str_1.
 * - char *str_2.
 * Returns:
 * - bool. Returns true if both strings are equal otherwise returns false.
 */
bool str_is_equal(char *str_1, char *str_2) {
    if (!str_1 || !str_2) {
        printf("Error - arguments char *str_1, char *str_2 cannot be NULL for str_is_equal.\n");
        return false;
    }
    // strcmp returns 0 if they are identical
    return (strcmp(str_1, str_2) == 0);
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
 * Fetches the leaf which contains the character at the provided index of the full
 * string (represented by the concatenation of each leaf substring) and alters the
 * value of index to equal the index of the character from a frame of reference of
 * the fetched leaf node.
 * Parameters:
 * - RopeNode *root. A pointer to the root of the rope tree we want to search.
 * - int *index. A pointer to an integer index representing the index of the
 *   character we want the fetched node to contain. Is updated.
 * Returns:
 * - RopeNode *. A pointer to the node that contains the character at the index.
 */
RopeNode *fetch_leaf(RopeNode *root, int *index) {
    if (!root) {
        printf("Error - argument RopeNode *root, cannot be NULL.\n");
        return NULL;
    }
    if (!root->left && !root->right) {
        return root;
    }
    if (*index < root->weight) {
        if (root->left) return fetch_leaf(root->left, index);
    } else {
        (*index) -= root->weight;
        if (root->right) return fetch_leaf(root->right, index);
    }
    return NULL;
}

/*
 * Fetches an array of pointers which each point to a leaf in the tree with the
 * provided root. This operation works recursively.
 * Parameters:
 * - RopeNode *root. A pointer to the root of the rope tree we want to collect
 *   the leaves of.
 * - RopeNode ***leaves. Pointer to the array of pointers which each point to a
 *   leaf. User should input a reference to a NULL array of type RopeNode **.
 *   The array should contain the leaves after operation.
 * - int *index. A pointer to the integer index. User should input a reference
 *   to an int initialised with value 0. The int should equal the number of
 *   leaves after operation.
 */
void collect_leaves(RopeNode *root, RopeNode ***leaves, int *index) {
    if (!root) return;

    if (root->left) collect_leaves(root->left, leaves, index);
    if (root->right) collect_leaves(root->right, leaves, index);

    if (!root->left && !root->right) {
        RopeNode **temp = realloc(*leaves, (*index + 1) * sizeof(RopeNode *));
        if (!temp) {
            printf("Error - failed to reallocate memory for collect_leaves.\n");
            return;
        }
        *leaves = temp;
        (*leaves)[*index] = root;
        (*index)++;
    }
}

/*
 * Builds a balanced rope tree from the bottom up from the user provided array
 * of leaves.
 * Parameters:
 * - RopeNode ***leaves. A reference to the array of pointers which point to the
 *   leaf nodes.
 * - int size. The size of the leaves array.
 * Returns:
 * - RopeNode *. A pointer to the root node of the newly created balanced tree.
 */
RopeNode *build_tree(RopeNode ***leaves, int size) {
    int power_two = 1;
    while (power_two * 2 <= size) {
        power_two *= 2;
    }
    int remainder = size - power_two;
    for (int i = 0; i < remainder; i++) {
        (*leaves)[i] = concat_no_rebalance((*leaves)[2*i], (*leaves)[2*i+1]);
    }
    if (remainder > 0) {
        for (int i = remainder; i < power_two; i++) {
            (*leaves)[i] = (*leaves)[i + remainder];
        }
    }
    while (power_two >= 2) {
        for (int i = 0; i < power_two / 2; i++) {
            (*leaves)[i] = concat_no_rebalance((*leaves)[2*i], (*leaves)[2*i+1]);
        }
        power_two /= 2;
    }
    return (*leaves)[0];
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
        printf("Error - arguments RopeNode *left, RopeNode *right cannot both be NULL.\n");
        return NULL;
    }

    RopeNode *parent = malloc(sizeof(RopeNode));
    if (!parent) {
        printf("Error - failed to allocate memory for concat_no_rebalance.\n");
        return NULL;
    }

    int left_length = 0, right_length = 0;
    int left_height = 0, right_height = 0;
    int left_weight = 0, right_weight = 0;

    if (left) {
        left->parent = parent;
        left_length = left->length;
        left_height = left->height;
        left_weight = left->weight;
    }
    if (right) {
        right->parent = parent;
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

/*
 * Divides a leaf into two leaves which branch from the original. The length of the string
 * represented by the new left leaf is index and the remaining string goes to the right leaf.
 * This is used in the split operation. DOES NOT AUTOMATICALLY BACKPROP HEIGHT VALUES.
 * Parameters:
 * - RopeNode *leaf. A pointer to the leaf node we want to divide into two new leaves.
 * - int index. The length of the resulting string in the new left leaf.
 */
void divide_leaf(RopeNode *leaf, int index) {
    if (!leaf) {
        printf("Error - argument RopeNode *leaf, cannot be NULL.\n");
        return;
    }
    if (index < 0) {
        printf("Error - index %d is less than 0.\n", index);
        return;
    }
    if (index >= leaf->length) {
        printf("Error - index %d exceeds leaf length %d.\n", index, leaf->length);
        return;
    }

    int right_str_len = leaf->length - index;
    char *left_str = malloc((index + 1) * sizeof(char));
    char *right_str = malloc((right_str_len + 1) * sizeof(char));
    if (!left_str || !right_str) {
        printf("Error - failed to allocate memory for divide_leaf.\n");
        return;
    }

    for (int i = 0; i < index; i++) {
        left_str[i] = leaf->str[i];
    }
    for (int j = 0; j < right_str_len; j++) {
        right_str[j] = leaf->str[j + index];
    }
    left_str[index] = '\0';
    right_str[right_str_len] = '\0';

    RopeNode *left = allocate_leaf(left_str);
    RopeNode *right = allocate_leaf(right_str);
    if (!left || !right) {
        printf("Error - failed to allocate memory for divide_leaf.\n");
        return;
    }

    left->parent = leaf;
    right->parent = leaf;

    free(left_str);
    free(right_str);
    free(leaf->str);

    leaf->str = NULL;
    leaf->left = left;
    leaf->right = right;
    leaf->weight = index;
}

/*
 * Performs the split operation on the rope at the provided index. Will split the full
 * string represented by the rope into two new ropes. The left rope will represent
 * the first index many characters and the remaining will be represented by the right rope.
 * This function DOES NOT PERFORM REBALANCING and does not even check at any stage for
 * the balanced condition. The memory allocated for the output struct must be freed by user.
 * Parameters:
 * - RopeNode *root. The pointer to the root node of the tree we want to split.
 * - int index. The index where we want to perform the split.
 * Returns:
 * - SplitRopeNodes *. This struct contains the pointer to the left rope as member .first 
 *   and the right rope as member .second.
 */
SplitRopeNodes *split_no_rebalance(RopeNode *root, int index) {
    if (!root) {
        printf("Error - argument RopeNode *root cannot be NULL.\n");
        return NULL;
    }

    SplitRopeNodes *split_nodes = malloc(sizeof(SplitRopeNodes));
    if (!split_nodes) {
        printf("Error - failed to allocate memory for split_no_rebalance.\n");
        return NULL;
    }
    split_nodes->first = root;
    split_nodes->second = NULL;

    RopeNode *leaf = fetch_leaf(root, &index);
    if (index > 0) {
        divide_leaf(leaf, index);
        leaf = leaf->right;
    }

    // We first ascend the tree and split off the node that is the first occuring right child.
    RopeNode *node = leaf;
    RopeNode *parent = node->parent;
    while (parent) {
        if (parent->right == node) {
            split_node(node, split_nodes);
            node = parent;
            parent = node->parent;
            break;
        }
        node = parent;
        parent = node->parent;
    }

    // Then we ascend the tree and split off the right sibling if the current node is a
    // left sibling.
    while (node) {
        int left_length = 0, right_length = 0;
        int left_height = 0, right_height = 0;

        if (node->left) {
            left_length = node->left->length;
            left_height = node->left->height;
        }
        if (node->right) {
            right_length = node->right->length;
            right_height = node->right->height;
        }
        node->weight = left_length;
        node->length = left_length + right_length;
        node->height = (left_height > right_height ? left_height : right_height) + 1;

        if (parent && parent->right && parent->left == node) {
            split_node(node, split_nodes);
        }
        node = parent;
        if (node) parent = node->parent;
    }

    return split_nodes;
}

/*
 * TESTING ONLY
 * Creates a tree by performing:
 *  RopeNode *node_1 = allocate_leaf("Hello_");
 *  RopeNode *node_2 = allocate_leaf("my_");
 *  RopeNode *node_3 = allocate_leaf("na");
 *  RopeNode *node_4 = allocate_leaf("me_i");
 *  RopeNode *node_5 = allocate_leaf("s");
 *  RopeNode *node_6 = allocate_leaf("_Simon");
 *  RopeNode *node_7 = concat_no_rebalance(node_3, node_4);
 *  RopeNode *node_8 = concat_no_rebalance(node_5, node_6);
 *  RopeNode *node_9 = concat_no_rebalance(node_1, node_2);
 *  RopeNode *node_10 = concat_no_rebalance(node_7, node_8);
 *  RopeNode *node_11 = concat_no_rebalance(node_9, node_10);
 *  return node_11;
 * Returning the pointer to the root node of the tree. The memory allocated should be
 * freed by calling free_tree(node_11) once done. This tree is a balanced tree.
 * Returns:
 * - RopeNode *. A pointer which points to the root node of the created tree.
 */
RopeNode *testing_create_tree_1() {
    RopeNode *node_1 = allocate_leaf("Hello_");
    RopeNode *node_2 = allocate_leaf("my_");
    RopeNode *node_3 = allocate_leaf("na");
    RopeNode *node_4 = allocate_leaf("me_i");
    RopeNode *node_5 = allocate_leaf("s");
    RopeNode *node_6 = allocate_leaf("_Simon");
    RopeNode *node_7 = concat_no_rebalance(node_3, node_4);
    RopeNode *node_8 = concat_no_rebalance(node_5, node_6);
    RopeNode *node_9 = concat_no_rebalance(node_1, node_2);
    RopeNode *node_10 = concat_no_rebalance(node_7, node_8);
    RopeNode *node_11 = concat_no_rebalance(node_9, node_10);
    return node_11;
}

/*
 * TESTING ONLY
 * Creates a tree by performing:
 *  RopeNode *node_1 = allocate_leaf("The_");
 *  RopeNode *node_2 = allocate_leaf("qui");
 *  RopeNode *node_3 = allocate_leaf("ck_bro");
 *  RopeNode *node_4 = allocate_leaf("w");
 *  RopeNode *node_5 = allocate_leaf("n_fo");
 *  RopeNode *node_6 = allocate_leaf("x_ju");
 *  RopeNode *node_7 = allocate_leaf("mps_o");
 *  RopeNode *node_8 = allocate_leaf("ver");
 *  RopeNode *node_9 = allocate_leaf("_the_la");
 *  RopeNode *node_10 = allocate_leaf("zy_dog");
 *  RopeNode *node_11 = concat_no_rebalance(node_1, node_2);
 *  RopeNode *node_12 = concat_no_rebalance(node_3, node_4);
 *  RopeNode *node_13 = concat_no_rebalance(node_5, node_6);
 *  RopeNode *node_14 = concat_no_rebalance(node_7, node_8);
 *  RopeNode *node_15 = concat_no_rebalance(node_9, node_10);
 *  RopeNode *node_16 = concat_no_rebalance(node_11, node_12);
 *  RopeNode *node_17 = concat_no_rebalance(node_13, node_14);
 *  RopeNode *node_18 = concat_no_rebalance(node_16, node_17);
 *  RopeNode *node_19 = concat_no_rebalance(node_15, node_18);
 *  return node_19;
 * Returning the pointer to the root node of the tree. The memory allocated should be
 * freed by calling free_tree(node_19) once done. This tree is an unbalanced tree.
 * Returns:
 * - RopeNode *. A pointer which points to the root node of the created tree.
 */
RopeNode *testing_create_tree_2() {
    RopeNode *node_1 = allocate_leaf("The_");
    RopeNode *node_2 = allocate_leaf("qui");
    RopeNode *node_3 = allocate_leaf("ck_bro");
    RopeNode *node_4 = allocate_leaf("w");
    RopeNode *node_5 = allocate_leaf("n_fo");
    RopeNode *node_6 = allocate_leaf("x_ju");
    RopeNode *node_7 = allocate_leaf("mps_o");
    RopeNode *node_8 = allocate_leaf("ver");
    RopeNode *node_9 = allocate_leaf("_the_la");
    RopeNode *node_10 = allocate_leaf("zy_dog");
    RopeNode *node_11 = concat_no_rebalance(node_1, node_2);
    RopeNode *node_12 = concat_no_rebalance(node_3, node_4);
    RopeNode *node_13 = concat_no_rebalance(node_5, node_6);
    RopeNode *node_14 = concat_no_rebalance(node_7, node_8);
    RopeNode *node_15 = concat_no_rebalance(node_9, node_10);
    RopeNode *node_16 = concat_no_rebalance(node_11, node_12);
    RopeNode *node_17 = concat_no_rebalance(node_13, node_14);
    RopeNode *node_18 = concat_no_rebalance(node_16, node_17);
    RopeNode *node_19 = concat_no_rebalance(node_15, node_18);
    return node_19;
}

