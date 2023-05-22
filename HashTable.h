#ifndef HASHTABLEIMP_H
#define HASHTABLEIMP_H

#include <math.h>
#include <cmath>
#define START_SIZE 1

using namespace std;

const double goldenRatio = ((sqrt(5) - 1)/2);

template <class T>
class keyValue{
public:
    int key;
    T* value;
    keyValue* next = nullptr;

    keyValue(int key = -1, T* value = nullptr, keyValue* next = nullptr): key(key), value(value), next(next) {};
    ~keyValue<T>() {
        if (value != nullptr){
            delete value;
        }
        if (next != nullptr){
            delete next;
        }
    };


};

template <class T>
class HashTable {
public:
    int sizeTable;
    int numOfElements;
    keyValue<T> ** table = nullptr;

    HashTable():sizeTable(START_SIZE), numOfElements(0), table(new keyValue<T>*[START_SIZE]) {
        for (int i = 0; i < START_SIZE; i++){
            table[i] = nullptr;
        }
    };
    ~HashTable();

    void Insert(int key, T* value);
    int hFunc(int key);
    void resize(int newSize);
    T* Search(int key);
    void Remove(int key);

};


template<class T>
HashTable<T>::~HashTable() {
    if (table != nullptr){
        for (int i = 0; i < sizeTable; i++){
            delete table[i];
        }
        delete [] table;
    }

}

template<class T>
int HashTable<T>::hFunc(int key) {
    double intPart, fracPart;
    fracPart = modf(goldenRatio * key, &intPart);
    return floor(this->sizeTable * fracPart);
}



template<class T>
void HashTable<T>::Insert(int key, T *value) {
    if (value == nullptr) { return; }

//    ////Check if exists in the table already
//    if (this->Search(key) != nullptr) { throw IDAlreadyExists(); }


    ////Table Increase
    if (sizeTable <= (this->numOfElements + 1)){
        resize( 2 * sizeTable);
    }

    int place = hFunc(key);
    table[place] = new keyValue<T>(key,value,table[place]);


    ////After successful Insertion increase the amount of elements
    this->numOfElements++;
}


template<class T>
T *HashTable<T>::Search(int key) {
    int place = hFunc(key);

    keyValue<T>* tmpToFind= table[place];
    while(nullptr != tmpToFind){
        if( tmpToFind->key == key){
            return tmpToFind->value;
        }
        tmpToFind = tmpToFind->next;
    }
    return nullptr;
}

template<class T>
void HashTable<T>::Remove(int key) {

    ////Check if exists in the table already
    if (this->Search(key) == nullptr) { return; }

    int place = hFunc(key);
    keyValue<T>* tmpToRemove= table[place];
    if(tmpToRemove->key == key){
        table[place] = tmpToRemove->next;
        tmpToRemove->next = nullptr;
        delete(tmpToRemove);
    }

    else{
        while(tmpToRemove->next->key != key){
            tmpToRemove = tmpToRemove->next;
        }

        keyValue<T>* toDelete = tmpToRemove->next;
        tmpToRemove->next = toDelete->next;
        toDelete->next= nullptr;
        delete toDelete;
    }

    ////Table Decrease
    int sizeTableChecker = (sizeTable / 4);
    int elementsAfterRemove = (numOfElements - 1);
    if (sizeTableChecker >= elementsAfterRemove) {
        resize(sizeTable / 2);
    }

    this->numOfElements--;
}

template<class T>
void HashTable<T>::resize(int newSize) {

    int oldTableSize = sizeTable;
    sizeTable = newSize;

    ////Backing up pointer to table
    keyValue<T>** oldTable = table;

    ////creating new empty table of size newSize
    table = new keyValue<T>*[newSize];
    for (int i = 0 ; i < newSize; i++) {
        table[i] = nullptr;
    }

    keyValue<T>* listToCopy = nullptr;
    int place;
    for (int i = 0; i < oldTableSize; i++) {
        listToCopy = oldTable[i];
        while(nullptr != listToCopy) {
            oldTable[i] = listToCopy->next;
            place = hFunc(listToCopy->key);

            listToCopy->next = table[place];

            table[place] = listToCopy;

            listToCopy = oldTable[i];
        }
    }


    delete [] oldTable;
}




#endif //HASHTABLEIMP_H
