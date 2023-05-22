# DataStructuresCourse_technion_project2
this is a Tehcnion data Structures course home work project number two. please read the README file for elaborated description

the project "question" / requirements : 

After the dizzying success of the new system of
StaticEye, the company wants your help in building
A new and improved version of the system.
Now, you are required to build a system that will keep the
The IDs of all images and for each image will allow one
Groups of pixels into superpixels. the numbers
The IDs of the photos are positive.
A superpixel is basically an area in an image that contains a collection of
pixels. Any two superpixels are foreign to each other, that is, every
A pixel can belong to at most one superpixel.
In addition, each superpixel in the image can be tagged with tags
different, where each super pixel tag has a score. any labeling
Represented by a unique positive identification number.

The operations that the data structure should support:

void * Init(int pixels)
parameters: pixels - the number of pixels in each photo

Time complexity: O(k) average-case complexity, when k is the pixels number in the photo


StatusType DeleteImage(void *DS, int imageID)

parameters: DS- ptr to data structure, imadeID- id of the image that needs to be deleted

Time complexity: O(k + m) average-case complexity, when k is the pixels number in the photo and m is the number of 
tags in the photo


StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score)

parameters: DS- ptr to data structure, imadeID- id of the image 
pixel - the id of the pixel that belongs to the super pixel that was tagged
label- the pixel tag
score- the score of the tag

Time complexity: O(log*(k) + log(m)) average-case complexity,when k is the pixels number in the photo and m is the number of 
tags in the super pixel that contains the pixel


StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label)

parameters: DS- ptr to data structure, imadeID- id of the image
pixel - the id of the pixel that needs to be reset
lable- the tag that needs to reset


Time complexity: O(log*(k) + log(m)) average-case complexity,when k is the pixels number in the photo and m is the number of 
tags in the super pixel that contains the pixel


StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label)

parameters: DS- ptr to data structure, imadeID- id of the image 
pixel - the id of the pixel that belong to the relevant super pixel
lable- ptr that will be updated to point to the id of the highest score

Time complexity: O(log*(k)) when k is the pixels number in the photo


StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2)

parameters: DS- ptr to data structure, imadeID- id of the image 
pixel1 - the id of the first pixel 
pixel2 - the id of the second pixel 

Time complexity: O(log*(k) + log(m)) average-case complexity,when k is the pixels number in the photo and m is the number of 
tags in *both* of the relevant super pixels


void Quit(void **DS)

parameters: DS- ptr to data structure
Time complexity:  O(n * k * m) worst case,when n is the number of the photoes , 
k is the number of the pixels in every photo and m is the number of the different tags
that exists on the system.

space- complexity:  O(n * k * m) worst case,when n is the number of the photoes , 
k is the number of the pixels in every photo and m is the number of the different tags
that exists on the system.

*********
solution sort explenation: 
We will create a hash table in which we will store all the imageIDs, each imageID will point to a UF structure, 
in the structure we will add in the field of the information about the group another field of a pointer to a rank
tree that will be sorted by label, a field of score will be saved and an additional field of the maximum score in 
the subtree, including the root. We will keep a max field in the tree that will keep the label with the maximum score, 
and it will be updated every time a node enters and exits the tree.

picture to describe the general idea:
![image](https://github.com/adidadonne/DataStructuresCourse_technion_project2/assets/105421424/6ad7f686-d4c8-47ac-8db9-3dbb57d686cf)
















