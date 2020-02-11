#pragma once
#include"Container.h"
#include<cassert>

template <typename T>
struct QueueNode {
    T value;
    QueueNode<T>* next;
    QueueNode(const T& _value) : value(_value), next(nullptr) {}
};

template <typename T>
class Queue :public Container<T>
{
private:
    QueueNode<T>* first;
    QueueNode<T>* last;
    void pushFront(QueueNode<T>*);
    void insertionSort(Queue<T>& ,const T& );
    void deleteAllNodes();
public:
    Queue();
    ~Queue();
    Queue& operator =(const Queue<T>&);

    void push(const T& );
    void pop();
    bool empty();
    bool member(const T&);
    void sort();
    bool satisfyCondition(Condition<T>);
    void print();
    void erase(const T&);
    void filter(Condition<T> pred);
    int countNodes();
    vector<T> getValues();
    void printToFile(ostream&);
};
template<typename T>
Queue<T>:: Queue() :Container<T>("queue"), first(nullptr), last(nullptr) {}
template<typename T>
Queue<T>:: ~Queue() {
   deleteAllNodes();
}
template<typename T>
void Queue<T>:: push(const T& x) {
    if (last == nullptr) {
        first = new QueueNode<T>(x);
        last = first;
        return;
    }
    last->next = new QueueNode<T>(x);
    last = last->next;
}
template<typename T>
void Queue<T>:: pop() {
    if (first == nullptr) {
        return;
    }
    QueueNode<T>* popped = first;
    first = first->next;
    delete popped;
    if (first == nullptr) {
        last = nullptr;
    }
}
template<typename T>
void Queue<T>:: deleteAllNodes()
{
    if (first == nullptr) {
        return;
    }
    while (first != nullptr) {
        QueueNode<T>* save=first;
        first = first->next;
        delete save;
    }
}
template<typename T>
Queue<T>& Queue<T>::operator = (const Queue<T>& other)
{
    if (this != &other) {
        deleteAllNodes();
        first = last = nullptr;
        QueueNode<T>* crr=other.first;
        while(crr!=nullptr)
        {
            push(crr->value);
            crr=crr->next;
        }
    }
    return *this;
}
template<typename T>
bool Queue<T>:: empty() {
    return first == nullptr;
}
template<typename T>
bool Queue<T>:: member(const T& x)
{
    QueueNode<T>* crr;
    crr=first;
    while(crr!=nullptr)
    {
        if(crr->value==x)
            return true;
        crr=crr->next;
    }
    return false;
}
template<typename T>
void Queue<T>:: pushFront(QueueNode<T>* node)
{
    if(this->empty())
    {
        this->push(node->value);
    }
    QueueNode<T>*save=first;
    first=node;
    first->next=save;
}
template<typename T>
void Queue<T>:: insertionSort(Queue<T>& newQueue,const T& x)
{
    if(newQueue.empty())
    {
        newQueue.push(x);
        return;
    }
    QueueNode<T>* crr=newQueue.first;
    QueueNode<T>* crrPrev;

    while( crr!=nullptr && crr->value <= x )
    {
        crrPrev = crr;
        crr=crr->next;
    }

    if(crr == nullptr)
    {
        newQueue.push(x);
        return;
    }

    if(newQueue.first->value >= x)
    {
        newQueue.pushFront(new QueueNode<T>(x));
        return;
    }
    crrPrev->next = new QueueNode<T>(x);
    crrPrev->next->next = crr;
    return;
}


template<typename T>
void Queue<T>:: sort()
{
    if(this->empty())
        return;
    QueueNode<T>* crr=first;
    Queue<T> sortedQueue;
    while(crr!=nullptr)
    {
        this->insertionSort(sortedQueue,crr->value);
        crr=crr->next;
    }
    *this=sortedQueue;
}
template<typename T>
void Queue<T>:: printToFile(ostream& out)
{

   QueueNode<T>*crr=first;
   while(crr->next->next!=nullptr)
   {
       out<<crr->value<<" ";
       crr=crr->next;
   }
   out<<crr->value;
}
template<typename T>
void Queue<T>:: print()
{

    if(first==nullptr)
    {
        std::cout<<"The container is empty!\n";
        return;
    }
    QueueNode<T>* crr=first;
    while(crr!=nullptr)
    {
        std::cout<<crr->value<<" ";
        crr=crr->next;
    }
    std::cout<<std::endl;
}
template<typename T>
bool Queue<T>::satisfyCondition(Condition<T> pred)
{
    if(first==nullptr)
        return false;
    QueueNode<T>* crr=first;
    while(crr!=nullptr)
    {
        if(pred(crr->value))
            return true;
        crr=crr->next;
    }
    return false;

}
template<typename T>
void Queue<T>::erase (const T& toErase)
{
    if(!(this->member(toErase)))
        return;
    if(first==nullptr)
        return;
    if(toErase==first->value)
    {
        this->pop();
        return;
    }
    QueueNode<T>* crr=first;
    while(crr->next->value!=toErase)
        crr=crr->next;

    QueueNode<T>* helper=crr->next;
    crr->next=helper->next;
    delete helper;
}
template<typename T>
void Queue<T>::filter(Condition<T> pred)
{
   QueueNode<T>* crr=first;
   while(crr!=nullptr)
   {
       if(pred(crr->value))
            this->erase(crr->value);
        crr=crr->next;
   }
}
template<typename T>
int Queue<T>:: countNodes()
{
    if(first==nullptr)
        return 0;
    int counter=0;
    QueueNode<T>* crr=first;
    while(crr!=nullptr)
    {
        counter++;
        crr=crr->next;
    }
    return counter;
}
template<typename T>
vector<T> Queue<T>:: getValues()
{
    if(this->empty())
        return vector<T>();
    vector<T> vec;
    QueueNode<T>* crr=first;
    while(crr!=nullptr)
    {
        vec.push_back(crr->value);
        crr=crr->next;
    }
    return vec;
}
