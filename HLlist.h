#ifndef HLLIST_H_INCLUDED
#define HLLIST_H_INCLUDED
#include"Container.h"
#include<cassert>
template <typename T>
struct Node
{
    Container<T>* container;
    Node<T>* next;
    Node():next(nullptr){}
    Node(Container<T>* _container)
    {
        container=_container;
        next=nullptr;
    }



};
template <typename T>
class HLlist //it comes from Heterogeneous linked list
{
protected:
    Node<T>* first;
    void deleteNodes();

public:
    class Iterator
    {
    public:
        Node<T>* current;
        Container<T>* crrContainer;
        vector<T> elements;
        int index;
        void step()
        {
            if(current!=nullptr && elements.size()==index+1)
            {
                current=current->next;
                if(current!=nullptr && !current->container->empty()){
                crrContainer=current->container;
                elements.clear();
                elements=crrContainer->getValues();
                index=0;}
            }
            else
                index++;


        }
    public:
        Iterator(Node<T>* _current)
        {
                current=_current;
                if(current!=nullptr){
                crrContainer=current->container;
                elements=crrContainer->getValues();
                index=0;
                }
        }
        bool operator != (const Iterator& other)
        {
            return current!=other.current;
        }
        void operator ++()
        {
            step();
        }
        T operator *() const
        {
            return elements[index];
        }


    };
    Iterator begin()
    {
        return Iterator(first);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }
   /* Iterator memq(const T& x)
    {
        if(!member(x))
            return Iterator(nullptr);
        else
        {
            Node<T>* crr=first
            while(crr!=nullptr)
            {
                if(crr->container->member(x))
                    return getNode
            }
        }
    }*/
    HLlist();
    HLlist(Node<T>*);
    ~HLlist();
    bool member(const T&); //Checks if any container contains the element x!
    bool satisfyCondition(Condition<T>);//checks if there is element in any container which satisfies the condition
    void addContainer(Container<T>*);//Pushes back a new container.
    void filter(Condition<T>);
    void print();
    void add(const T&);//adds a new element in the container with least elements
    bool empty();
    void remove(const T&);
    void printToFile(ostream&);
    template <typename U>
    friend ostream& operator <<(ostream& out,HLlist<U>);
    void sort();



};
template<typename T>
HLlist<T>::HLlist()
{
    first=nullptr;
}
template<typename T>
HLlist<T>::HLlist( Node<T>* crr)
{
    first=crr;
}
template<typename T>
HLlist<T>::~HLlist<T>()
{
    deleteNodes();
}
template<typename T>
bool HLlist<T>:: empty()
{
    return first==nullptr;
}
template<typename T>
void HLlist<T>::deleteNodes()
{
    while(first!=nullptr)
    {
        Node<T>* toDelete=first;
        first=first->next;
        delete toDelete;
    }
}
template<typename T>
bool HLlist<T>:: member(const T& x)
{
    Node<T>* crr=first;
    while(crr!=nullptr)
    {
        if(crr->container->member(x))
            return true;
        crr=crr->next;
    }
    return false;

}
template<typename T>
void HLlist<T>::addContainer(Container<T>* newContainer)
{
    if(first==nullptr)
    {
        first=new Node<T>(newContainer);
        return;
    }
    Node<T>* crr=first;
    while(crr->next!=nullptr)
    {
        crr=crr->next;
    }
    crr->next=new Node<T>(newContainer);
}
template<typename T>
bool HLlist<T>:: satisfyCondition(Condition<T> pred)
{
    if(first==nullptr)
        return false;
    Node<T>* crr=first;
    while(crr!=nullptr)
    {
        if(crr->container->satisfyCondition(pred))
            return true;
        crr=crr->next;
    }
    return false;
}
template<typename T>
void HLlist<T>:: filter(Condition<T> pred)
{
    if(first==nullptr)
        return;
    Node<T>* crr=first;
    while(crr!=nullptr)
    {
        if(crr->container->satisfyCondition(pred))
        {
            crr->container->filter(pred);
        }
        crr=crr->next;

    }


}
template<typename T>
void HLlist<T>::print()
{
    if(first==nullptr)
        return;

    int counter=1;
    Node<T>* crr=first;
    while(crr!=nullptr)
    {
        std::cout<<"Container "<<counter<<" which is a "<<crr->container->typeOfContainer<<": "<<std::endl;
        crr->container->print();
        counter++;
        crr=crr->next;
    }
}
template<typename T>
void HLlist<T>:: add(const T& newElement)//we assume that there is at least one container
{
    assert(first!=nullptr);
    Node<T>* crr=first->next;
    Container<T>* currentContainer=first->container;
    int numberOfNodes=currentContainer->countNodes();

    while(crr!=nullptr)
    {

        if( crr->container->countNodes() < numberOfNodes)
        {
            numberOfNodes=crr->container->countNodes();
            currentContainer=crr->container;
        }
        crr=crr->next;
    }

    currentContainer->push(newElement);

}
template <typename T>
void HLlist<T>:: remove(const T& toRemove)
{
    if(this->empty())
        return;
    if(!(this->member(toRemove)))
    {
        std::cout<<"There's not such an element!\n";
        return;
    }
    Node<T>* crr=first;
    Container<T>* currentContainer;
    while(crr!=nullptr)
    {

        currentContainer=crr->container;
        while(currentContainer->member(toRemove))
            currentContainer->erase(toRemove);
        crr=crr->next;


    }

}
template<typename T>
void HLlist<T>::printToFile(ostream& out)
{
    Node<T>* crr=first;
    while(crr!=nullptr)
    {

        Container<T>* currentContainer=crr->container;
        out<<currentContainer->typeOfContainer;
        out<<" ";
        currentContainer->printToFile(out);
        out<<std::endl;
        crr=crr->next;
    }

}
template<typename U>
ostream& operator <<(ostream& out,HLlist<U> llist)
{
    llist.printToFile(out);
    return out;

}
template<typename T>
void HLlist<T>::sort()
{
    Node<T>* crr=first;
    while(crr!=nullptr)
    {
        crr->container->sort();
        crr=crr->next;
    }
}
#endif // HLLIST_H_INCLUDED
