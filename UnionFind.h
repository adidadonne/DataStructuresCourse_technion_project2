
#ifndef WET2SUMMER_UNIONFIND_H
#define WET2SUMMER_UNIONFIND_H



#include "UfTreeNode.h"



class UnionFind {

private:
    UfTreeNode** elements;
    UFinfo** groups;
    int group_size;

public:
    explicit UnionFind(int size);
    ~UnionFind();

    void MakeSet(int key);
    int Find(int key);
    void Union(int key1, int key2);
    UFinfo* Find_info(int key);


};


#endif //WET2SUMMER_UNIONFIND_H
