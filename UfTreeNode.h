
#ifndef WET2SUMMER_UFTREENODE_H
#define WET2SUMMER_UFTREENODE_H
#include "UFinfo.h"
class UfTreeNode{

public:
    int key;
    UfTreeNode* father;
    UFinfo* info;

    explicit UfTreeNode(int key, UFinfo* info): key(key), father(nullptr), info(info) {};
    ~UfTreeNode() {
        father = nullptr;
        info = nullptr;
    }
};


#endif //WET2SUMMER_UFTREENODE_H
