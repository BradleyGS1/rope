

#include "../include/rope.h"


int main() {
    RopeNode *leaf_1 = allocate_leaf("Hello_");
    RopeNode *leaf_2 = allocate_leaf("my_na");
    RopeNode *leaf_3 = allocate_leaf("is_");
    RopeNode *leaf_4 = allocate_leaf("Simon");

    assert(!leaf_1->left);
    assert(!leaf_1->right);
    assert(!leaf_1->parent);
    assert(leaf_1->length == 6);
    assert(leaf_1->height == 1);
    assert(leaf_1->weight == 6);

    assert(!leaf_2->left);
    assert(!leaf_2->right);
    assert(!leaf_2->parent);
    assert(leaf_2->length == 5);
    assert(leaf_2->height == 1);
    assert(leaf_2->weight == 5);

    assert(!leaf_3->left);
    assert(!leaf_3->right);
    assert(!leaf_3->parent);
    assert(leaf_3->length == 3);
    assert(leaf_3->height == 1);
    assert(leaf_3->weight == 3);

    assert(!leaf_4->left);
    assert(!leaf_4->right);
    assert(!leaf_4->parent);
    assert(leaf_4->length == 5);
    assert(leaf_4->height == 1);
    assert(leaf_4->weight == 5);

    free_leaf(leaf_1);
    free_leaf(leaf_2);
    free_leaf(leaf_3);
    free_leaf(leaf_4);

    return 0;
}

