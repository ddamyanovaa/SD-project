#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED
#include<vector>
using std::ostream;
using std::vector;
template<typename T>
using Condition=bool(*)(T);

template<typename T>
class Container
{


public:
    std::string typeOfContainer;
    Container<T>(const std::string& str):typeOfContainer(str){}
    virtual int countNodes()=0;
    virtual bool member(const T& x)=0;
    virtual void push(const T& x)=0;
    virtual void pop()=0;
    virtual void sort()=0;
    virtual void filter(Condition<T>)=0;
    virtual bool satisfyCondition(Condition<T>)=0;
    virtual void print()=0;
    virtual void erase(const T&)=0;
    virtual vector<T> getValues()=0;
    virtual bool empty()=0;
    virtual void printToFile(ostream& )=0;

};


#endif // CONTAINER_H_INCLUDED
