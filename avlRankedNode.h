

#ifndef WET1SUMMER_AVLRANKEDNODE_H
#define WET1SUMMER_AVLRANKEDNODE_H

#include <math.h>
#include <iostream>
#include <stdexcept>


using std::exception;
using namespace std;

class avlRankedNode{
public:

    int key;
    int score;
    int max_score;
//    /////
//    avlRankedNode* the_other_node;

    avlRankedNode *parent_ = nullptr;
    avlRankedNode *left_ = nullptr;
    avlRankedNode *right_ = nullptr;
    int height;
    int w;

    avlRankedNode()= default;
    avlRankedNode( int key, int score): key(key),score(score),max_score(score), parent_(nullptr), left_(nullptr),
                                        right_(nullptr), height(0), w(1) {};
    ~avlRankedNode()=default;
    void set_max_score(int new_max){
        max_score = new_max;
    };

//        if (key != nullptr) { ////TODO: We know that the key in our use is the same as the data, so we don't need to delete it.
//            delete key;
//        }
};






#endif //WET1SUMMER_AVLRANKEDNODE_H
