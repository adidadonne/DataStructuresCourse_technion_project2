

#ifndef WET2SUMMER_UFINFO_H
#define WET2SUMMER_UFINFO_H

#include "avlRanked.h"

class UfTreeNode;
class UFinfo{

public:
    int group_name;
    int amount;
    UfTreeNode* tree_node; /// element
    avlRanked* label_tree;

public:
    explicit UFinfo(int key, int am, UfTreeNode* treenode)
    {
        group_name=key;
        amount=am;
        tree_node=treenode;
        label_tree= new avlRanked();
    }

    ~UFinfo()
    {
       // delete tree_node; ////////
        tree_node= nullptr;
        delete label_tree;
    }

};


#endif //WET2SUMMER_UFINFO_H
