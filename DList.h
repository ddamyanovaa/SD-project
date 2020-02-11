#pragma once
#include<queue>
#include"Container.h"
template <typename T>
struct DLNode {
    DLNode<T>* previous;
    T value;
    DLNode<T>* next;
    DLNode(const T& _value) : previous(nullptr), value(_value), next(nullptr) {}
};

// Doubly-linked list
template <typename T>
class DLList:public Container<T>
{

private:
    DLNode<T>* first;
    DLNode<T>* last;
    void insertionSort(DLList<T>& ,const T&);
    void pushFront(DLNode<T>*);
public:
    bool member(const T&);
    DLList();
    DLList(const DLList&);
    ~DLList();
    DLList<T>& operator=(const DLList&);
    void push(const T& );
    void pop();//pops the first element int the list
    void erase(const T&);
    void print();
    int countNodes();
    bool satisfyCondition(Condition<T>);
    void filter(Condition<T>);
    void sort();
    bool empty();
    vector<T> getValues();
    void printToFile(ostream&);

private:
    void deleteAllNodes();
};
template <typename T>
bool DLList<T>:: member(const T&x)
{
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        if(crr->value==x)
            return true;
        crr=crr->next;
    }
    return false;

}
template <typename T>
DLList<T>::DLList() :Container<T>("doubly-linked-list"), first(nullptr), last(nullptr) {}
template <typename T>
DLList<T>::DLList(const DLList& other) :Container<T>("doubly-linked list"), first(nullptr), last(nullptr) {
    DLNode<T>* DLNodeInOther = other.first;
    while (DLNodeInOther != nullptr) {
        push(DLNodeInOther->value);
        DLNodeInOther = DLNodeInOther->next;
    }
}
template<typename T>
bool DLList<T>:: empty()
{
    return first==nullptr;
}

template <typename T>
DLList<T>& DLList<T>:: operator=(const DLList& other) {
    if (this != &other) {
        deleteAllNodes();
        first=last=nullptr;
        DLNode<T>* DLNodeInOther = other.first;
        while (DLNodeInOther!= nullptr) {
            push(DLNodeInOther->value);
            DLNodeInOther= DLNodeInOther->next;
        }
    }
    return *this;
}
template <typename T>
DLList<T>::~DLList() {
    deleteAllNodes();
}
template<typename T>
vector<T> DLList<T>::getValues()
{
    if(this->empty())
        return vector<T>();
    vector<T> vec;
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        vec.push_back(crr->value);
        crr=crr->next;
    }
    return vec;
}
template<typename T>
 void DLList<T>:: deleteAllNodes()
 {
    if (first == nullptr) {
        return;
    }
    DLNode<T>* crr = first;
    while (crr->next != nullptr) {
        crr = crr->next;
        delete crr->previous;
    }
    delete crr;
}
template<typename T>
int DLList<T>:: countNodes()
{
    int counter=0;
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        counter++;
        crr=crr->next;
    }

    return counter;

}
template<typename T>
void DLList<T>:: print()
{
    if(first==nullptr)
    {
        std::cout<<"The container is empty!\n";
        return;
    }
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        std::cout<<crr->value<<" ";
        crr=crr->next;

    }
    std::cout<<std::endl;
}
template<typename T>
void DLList<T>:: erase(const T& toErase)
{
    if(!(this->member(toErase)))
        return;
    if(last==nullptr)
        return;
    else if(toErase==first->value)
    {
         DLNode<T>* helper=first;
         first=first->next;
         if(first!=nullptr)
            first->previous=nullptr;
         delete helper;
         return;
    }
    DLNode<T>* crr=first;
    while(crr->next->value!=toErase)
        crr=crr->next;

    DLNode<T>* helper=crr->next;
    if(helper==last)
    {
        helper->next=nullptr;
        crr->next=helper->next;
        return;
    }
    crr->next=helper->next;
    helper->next->previous=crr;
    delete helper;
}
template<typename T>
void DLList<T>:: push(const T& x)
{
    if (first == nullptr) {
        first = new DLNode<T>(x);
        last = first;
        return;
    }
    last->next = new DLNode<T>(x);
    last->next->previous = last;
    last = last->next;


}
template<typename T>
void DLList<T>:: pushFront(DLNode<T>* node)
{
    if(first==nullptr)
    {
        this->push(node->value);
    }
    DLNode<T>* save=first;
    first=node;
    first->next=save;
    first->previous=nullptr;


}
template<typename T>
void DLList<T>:: pop()
{
    if(first==nullptr)
        return;
    DLNode<T>* toRemove=first;
    first=first->next;
    delete toRemove;

}
template<typename T>
void DLList<T>:: insertionSort(DLList<T>& newList,const T& x)
{
  if(newList.empty())
    {
        newList.push(x);
        return;
    }
    DLNode<T>* crr=newList.first;
    DLNode<T>* crrPrev;

    while( crr!=nullptr && crr->value < x )
    {
        crrPrev = crr;
        crr=crr->next;
    }

    if(crr == nullptr)
    {
        newList.push(x);
        return;
    }

    if(newList.first->value >= x)
    {
        newList.pushFront(new DLNode<T>(x));
        return;
    }

    crrPrev->next = new DLNode<T>(x);
    crrPrev->next->next = crr;
    crr->previous=crrPrev->next;
    crrPrev->next->previous=crrPrev;
    return;
}
template<typename T>
void DLList<T>:: sort()
{

    if(first==nullptr)
        return;

    DLNode<T>* crr = first;
    DLList<T> sortedList;
    while(crr!=nullptr)
    {
        this->insertionSort(sortedList,crr->value);
        crr=crr->next;
    }
    *this=sortedList;

}
template<typename T>
bool DLList<T>:: satisfyCondition(Condition<T> pred)
{
    if(first==nullptr)
        return false;
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        if(pred(crr->value))
            return true;
            crr=crr->next;
    }
    return false;

}
template<typename T>
void DLList<T>:: filter(Condition<T> pred)
{
    if(first==nullptr)
        return;
    DLNode<T>* crr=first;
    while(crr!=nullptr)
    {
        if(pred(crr->value))
        {
           this -> erase(crr->value);
        }

        crr=crr->next;
    }

}
template<typename T>
void DLList<T>:: printToFile(ostream& out)
{

   DLNode<T>* crr=first;
   while(crr->next->next!=nullptr)
   {
       out<<crr->value<<" ";
       crr=crr->next;
   }
   out<<crr->value;
}
