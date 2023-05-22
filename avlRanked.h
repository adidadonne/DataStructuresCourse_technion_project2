
#ifndef WET1SUMMER_AVLRANKED_H
#define WET1SUMMER_AVLRANKED_H

#include "avlRankedNode.h"
#include <math.h>
#include <iostream>
#include <stdexcept>
using std::exception;
using namespace std;

class avlRanked {

private:
    avlRankedNode* root_;
    int size_;
    int max_label;
public:
    class IDAlreadyExists : public exception {
    public :
        const char* what() const noexcept override { return "ID already exists in tree"; }
    };

    class IDNotExists : public exception {
    public :
        const char* what() const noexcept override { return "ID not exists in tree"; }
    };

    class allocationError : public exception {
    public :
        const char* what() const noexcept override { return "Memory allocation error"; }
    };
    avlRankedNode *minNode_;
    avlRanked();
    ~avlRanked();
    void deleteTree( avlRankedNode* node ) ;
    avlRankedNode *getRoot() ;

    avlRankedNode* findNode(avlRankedNode* root ,int key) ;
    void insertNode( int key, int score);
    avlRankedNode* insertNodeAux( avlRankedNode* root , avlRankedNode* newNode, int key);
    avlRankedNode* removeNode(avlRankedNode* root , int key);
    avlRankedNode* findMax(avlRankedNode* root);
    void swap(avlRankedNode* A, avlRankedNode * B);
    int checkHeight( avlRankedNode* root) ;
    int findHeight( avlRankedNode* root) ;
    int findBalance( avlRankedNode* root) ;


    avlRankedNode* leftRotation(avlRankedNode* node);
    avlRankedNode* rightRotation(avlRankedNode* node);

    void printTest(avlRankedNode* root);
    void cleantree();
    avlRankedNode* climb(int m);
    int getsize();
    bool isEmpty();

    avlRankedNode* select(avlRankedNode* root, int k);

    int findMaxScore(avlRankedNode *root);
    int findMaxLable(avlRankedNode *root);
    int get_max_label();
    void set_max_label(int new_max_lable);

    void mergeTrees(avlRankedNode *root1, avlRankedNode *root2, int m, int n);
    void arrInorder(avlRankedNode* node, int label[], int score[], int *index);
    void merge(int mergedLabel[], int mergedScore[], int lable1[], int lable2[], int score1[], int score2[], int m, int n, int *dup);
    avlRankedNode* ArrToAVL(int label[], int score[], int start, int end);


};



#endif //WET1SUMMER_AVLRANKED_H
