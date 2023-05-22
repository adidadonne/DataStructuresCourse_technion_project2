
#include "UnionFind.h"

UnionFind::UnionFind(int size)
{
    elements= new UfTreeNode* [size];
    groups= new UFinfo*[size];
    group_size=size;
}

UnionFind::~UnionFind()
{

    for(int i=0;i<group_size;i++)
    {
        elements[i]->father= nullptr;
        elements[i]->info= nullptr;
    }
    for(int i=0;i<group_size;i++)
    {
        delete groups[i];
    }
    delete[] groups;

    for(int i=0;i<group_size;i++)
    {
        delete elements[i];
    }
    delete[] elements;

}

void UnionFind::MakeSet(int key)
{
    ///creating UF node
    UfTreeNode* new_element = new UfTreeNode(key,NULL);
    /// checking the key is within range
    if(key>0 || key==0 || key<group_size)
    {
        /// linking between the groups and the UF info
        groups[key] = new UFinfo(key,1,new_element);
    }
    ///linking between the UF node to the UF info
    new_element->info=groups[key];
    /// linking between the elements array to the UF node
    elements[key]=new_element;
}

int UnionFind::Find(int key)
{
    /// saving ptr for current node that will be the father
    UfTreeNode* father_node = elements[key];
    ///saving ptr for the current node
    UfTreeNode* node=father_node;

/// looking fot the father
    while(father_node->father!=NULL)
    {
        father_node = father_node->father;
    }
/// saving the group ID
    int temp = father_node->info->group_name;

    /// shrinking
    UfTreeNode* temp_node = node;
    while(node->father!=NULL)
    {
        temp_node->father=father_node;
        node=node->father;
        temp_node=node;
    }
    return temp;
}


UFinfo* UnionFind::Find_info(int key)
{
    /// saving ptr for current node that will be the father
    UfTreeNode* father_node = elements[key];
    ///saving ptr for the current node
    UfTreeNode* node=father_node;

/// looking fot the father
    while(father_node->father!=NULL)
    {
        father_node = father_node->father;
    }

    /// saving the group info ptr
    UFinfo* the_info=father_node->info;

    /// shrinking
    UfTreeNode* temp_node=node;
    while(node->father!=NULL)
    {
        temp_node->father=father_node;
        node=node->father;
        temp_node=node;
    }
    return the_info;
}


void UnionFind::Union(int key1, int key2)
{

  int smaller;
  int larger;
  if(groups[key1]->amount < groups[key2]->amount)
  {
      smaller=key1;
      larger = key2;
  }
  else
  {
      smaller=key2;
      larger=key1;
  }
    groups[smaller]->tree_node->father=groups[larger]->tree_node;
    groups[larger]->amount=groups[larger]->amount+groups[smaller]->amount;
    ////// unite data trees!///
    ///
    avlRanked* new_label_tree = new avlRanked();
    new_label_tree->mergeTrees(groups[larger]->label_tree->getRoot(),
                               groups[smaller]->label_tree->getRoot(),
                               groups[larger]->label_tree->getsize(),
                               groups[smaller]->label_tree->getsize());

    int larger_max = 0, smaller_max = 0;
    if(groups[larger]->label_tree->getRoot()){
        larger_max = groups[larger]->label_tree->getRoot()->max_score;
    }
    if(groups[smaller]->label_tree->getRoot()){
        smaller_max = groups[smaller]->label_tree->getRoot()->max_score;
    }
    if (larger_max > smaller_max){
        new_label_tree->set_max_label(groups[larger]->label_tree->get_max_label());
    }
    else{
        new_label_tree->set_max_label(groups[smaller]->label_tree->get_max_label());
    }
    delete groups[larger]->label_tree;
    groups[larger]->label_tree=new_label_tree;
}
