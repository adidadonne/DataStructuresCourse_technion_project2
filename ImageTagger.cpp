
#include "ImageTagger.h"



ImageTagger::ImageTagger(int pix)
{
    pixels=pix;
    images= new HashTable<UnionFind>;
}

ImageTagger::~ImageTagger()
{
    delete images;
}

StatusType ImageTagger::AddImage(void* DS, int imageID)
{
    ///checking inputs
    if(DS==NULL || imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    ///check if imageID already exists
    if(images->Search(imageID)!=NULL)
    {
        return FAILURE;
    }
    ///we will add a new image to the images hash table
    UnionFind* imageID_uf= new UnionFind(pixels);
    images->Insert(imageID,imageID_uf);
    /// save a ptr to this union find
    UnionFind* uf=images->Search(imageID);
    /// now we will add all of the pixels as elements to the UF
    for(int i=0; i<pixels;i++)
    {
        uf->MakeSet(i);
    }
    return SUCCESS;
}

StatusType ImageTagger::DeleteImage(void *DS, int imageID)
{
    ///checking inputs
    if(DS==NULL || imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    ///check if imageID already exists
    if(images->Search(imageID)==NULL)
    {
        return FAILURE;
    }
    images->Remove(imageID); /// hash will delete pte and call destructor for UF that wee delete all pointers and hash
    return SUCCESS;
}

StatusType ImageTagger::SetLabelScore(void *DS, int imageID, int pixel, int label, int score)
{

    ///check inputs
    if(DS==NULL || imageID<0 || imageID ==0)
    {
        return INVALID_INPUT;
    }
    if(pixel<0 || pixel> pixels || pixel==pixels)
    {
        return INVALID_INPUT;
    }
    if(label<0 || label==0 || score<0 || score==0)
    {
        return INVALID_INPUT;
    }
    ///check if imageID exists in hash
    if(images->Search(imageID)==NULL)
    {
        return FAILURE;
    }
    /// saving ptr to the image info
    UFinfo* super_pixel_info= images->Search(imageID)->Find_info(pixel);
    //// if the label exist
    if(super_pixel_info->label_tree->findNode(super_pixel_info->label_tree->getRoot(),label) != nullptr)
    {
        ///we will remove the label from the tree
        super_pixel_info->label_tree->removeNode(super_pixel_info->label_tree->getRoot(),label);
    }
    /// we will add the label with this score to the tree
    super_pixel_info->label_tree->insertNode(label,score);
    /// the max_label in the tree will be updated automatically

    return SUCCESS;
}

StatusType ImageTagger::ResetLabelScore(void *DS, int imageID, int pixel, int label) {
    ///check inputs
    if (DS == NULL || imageID < 0 || imageID == 0)
    {
        return INVALID_INPUT;
    }
    if(pixel<0 || pixel> pixels || pixel==pixels)
    {
        return INVALID_INPUT;
    }
    if(label<0 || label==0)
    {
        return INVALID_INPUT;
    }
    ///check if imageID exists in hash
    if(images->Search(imageID)==NULL)
    {
        return FAILURE;
    }
    /// search for the super pixel info
    UFinfo* info_ptr = images->Search(imageID)->Find_info(pixel);
    /// we will check if the label exists in the label tree
   if( info_ptr->label_tree->findNode(info_ptr->label_tree->getRoot(),label) ==NULL)
   {
       return FAILURE;
   }
/// we will remove this label from the tree
   info_ptr->label_tree->removeNode(info_ptr->label_tree->getRoot(),label);

   ////updating mac_label
   if(info_ptr->label_tree->getRoot()){
       int new_max_score = info_ptr->label_tree->findMaxScore(info_ptr->label_tree->getRoot());
       info_ptr->label_tree->getRoot()->set_max_score(new_max_score);
       info_ptr->label_tree->set_max_label(info_ptr->label_tree->findMaxLable(info_ptr->label_tree->getRoot()));
   }
   else{
       info_ptr->label_tree->set_max_label(-1);
   }
   return SUCCESS;
}
StatusType ImageTagger::GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label)
{
    ///check inputs
    if (DS == NULL || imageID < 0 || imageID == 0)
    {
        return INVALID_INPUT;
    }
    if(pixel<0 || pixel> pixels || pixel==pixels || label==NULL)
    {
        return INVALID_INPUT;
    }
    ///check if imageID exists in hash
    if(images->Search(imageID)==NULL)
    {
        return FAILURE;
    }
    /// we will find the label tree and save a ptr
    avlRanked* label_ptr = images->Search(imageID)->Find_info(pixel)->label_tree;
    ///we will check if the label tree is empty
    if(label_ptr->isEmpty())
    {
        return FAILURE;
    }
    *label=label_ptr->get_max_label();

    return SUCCESS;
}
StatusType ImageTagger::MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2)
{
    ///check inputs
    if (DS == NULL || imageID < 0 || imageID == 0)
    {
        return INVALID_INPUT;
    }
    if(pixel1 <0 || pixel1 > pixels || pixel1 == pixels)
    {
        return INVALID_INPUT;
    }
    if(pixel2<0 || pixel2> pixels || pixel2 == pixels)
    {
        return INVALID_INPUT;
    }
    ///check if imageID exists in hash
    if(images->Search(imageID)==NULL)
    {
        return FAILURE;
    }
    ///checking if the pixels are in the same group
    if(images->Search(imageID)->Find(pixel1)== images->Search(imageID)->Find(pixel2))
    {
        return FAILURE;
    }
    /// we will use union find union function

    images->Search(imageID)->Union(images->Search(imageID)->Find(pixel1),images->Search(imageID)->Find(pixel2));

    return SUCCESS;
}