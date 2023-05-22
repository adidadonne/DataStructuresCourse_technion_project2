
#include "library.h"
#include "ImageTagger.h"

void *Init(int pixels) {
    ImageTagger* DS;
    try
    {
        DS = new ImageTagger(pixels);
    }
    catch (std::bad_alloc &e)
    {
        return NULL;
    }
    return (void*)DS;
}

StatusType AddImage(void* DS, int imageID)
{
    try
    {
        return ((ImageTagger*)DS)->AddImage(DS,imageID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType DeleteImage(void *DS, int imageID)
{
    try
    {
        return ((ImageTagger*)DS)->DeleteImage(DS,imageID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score)
{
    try
    {
        return ((ImageTagger*)DS)->SetLabelScore( DS,  imageID, pixel, label,score);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label)
{
    try
    {
        return ((ImageTagger*)DS)->ResetLabelScore( DS, imageID, pixel, label);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label)
{
    try
    {
        return ((ImageTagger*)DS)->GetHighestScoredLabel(DS,imageID, pixel,label);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2)
{
    try
    {
        return ((ImageTagger*)DS)->MergeSuperPixels(DS, imageID, pixel1, pixel2);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
void Quit(void **DS)
{
    if (DS==NULL) return;
    delete ((ImageTagger*) *DS);
    *DS=NULL;
}