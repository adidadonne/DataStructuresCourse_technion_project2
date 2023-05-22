

#ifndef WET2SUMMER_IMAGETAGGER_H
#define WET2SUMMER_IMAGETAGGER_H
#include "library.h"
#include "UnionFind.h"
#include "HashTable.h"

class ImageTagger {
private:
    int pixels;
    HashTable<UnionFind>* images;

public:
    ImageTagger(int pix);
    ~ImageTagger();
    StatusType AddImage(void* DS, int imageID);
    StatusType DeleteImage(void *DS, int imageID);
    StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score);
    StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label);
    StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label);
    StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2);


};


#endif //WET2SUMMER_IMAGETAGGER_H
