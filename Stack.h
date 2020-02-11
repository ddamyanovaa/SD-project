#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include"Container.h"
template<typename T>
struct StackNode
{
    T value;
    StackNode<T>* next;
    StackNode(const T& _value):value(_value),next(nullptr){}
};

template<typename T>
class Stack:public Container<T>
{
private:
	StackNode<T>* first;
	void insertionSort(Stack<T>&,const T&);
	void deleteAllNodes();
	void pushBack( const T&);
public:
	Stack();
	Stack(const T&);
	~Stack();
	Stack& operator = (const Stack<T>&);
	bool empty();
	void push(const T&);
	void pop();
	bool member(const T&);
	bool satisfyCondition(Condition<T>);
	void erase(const T&);
	void print();
	void filter(Condition<T>);
	int countNodes();
	void sort();
	vector<T> getValues();
	void printToFile(ostream&);
};

template<typename T>
Stack<T>::Stack():Container<T>("stack")
{
	first = nullptr;
}
template<typename T>
Stack<T>::Stack(const T& x):Container<T>("stack")
{
    first->value=x;
	first->next=nullptr;
}
template<typename T>
Stack<T>::~Stack()
{
	while(!empty())
    {
        pop();
    }
}
template<typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& other)
{
    if(this!=&other)
    {
        deleteAllNodes();
        first=nullptr;
        StackNode<T>* crr=other.first;
        while(crr!=nullptr)
        {
            this->push(crr->value);
            crr=crr->next;
        }
    }
}
template<typename T>
void Stack<T>::deleteAllNodes()
{
    while(first!=nullptr)
    {
        StackNode<T>* toDelete=first;
        first=first->next;
        delete toDelete;

    }
}
template <typename T>
vector<T> Stack<T> :: getValues()
{
    if(this->empty())
    {
        return vector<T>();
    }
    vector<T> vec;
    StackNode<T>* crr=first;
    while(crr!=nullptr)
    {
        vec.push_back(crr->value);
        crr=crr->next;
    }
    return vec;
}
template<typename T>
void Stack<T>:: pushBack( const T& newNode)
{
    if(this->empty()){
        first=new StackNode<T>(newNode);
        return;
    }

    StackNode<T>* crr=first;
    while(crr->next!=nullptr)
        crr=crr->next;
    crr->next=new StackNode<T>(newNode);
}
template<typename T>
bool Stack<T>::empty()
{
	return first == nullptr;
}

template<typename T>
void Stack<T>::push(const T& newElement)
{
    if(this->empty())
    {
        first=new StackNode<T>(newElement);
        return;

    }
	StackNode<T>* oldfirst = first;
    first = new StackNode<T>(newElement);
    first->next = oldfirst;
}

// Undefined behavior if the stack is empty
template<typename T>
void Stack<T>::pop() {
	StackNode<T>* oldfirst = first;
    first = first->next;
    delete oldfirst;
}
template<typename T>
bool Stack<T>:: member(const T& x)
{
    StackNode<T>* crr=first;
    while(crr!=nullptr)
    {
        if(crr->value==x)
            return true;
        crr=crr->next;
    }
    return false;
}
template<typename T>
bool Stack<T>:: satisfyCondition(Condition<T> pred)
{
    if(first==nullptr)
        return false;

    StackNode<T>*crr=first;
    while(crr!=nullptr)
    {
        if(pred(crr->value))
            return true;
        crr=crr->next;
    }
    return false;

}
template<typename T>
void Stack<T>:: erase(const T& toErase)
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
    StackNode<T>* crr=first;
    while(crr->next->value!=toErase)
        crr=crr->next;
    StackNode<T>* helper=crr->next;
    crr->next=helper->next;
    delete helper;
}
template<typename T>
void Stack<T>::filter(Condition<T> pred)
{
    if(first==nullptr)
        return;
    StackNode<T>*crr=first;
    while(crr!=nullptr)
    {
        if(pred(crr->value))
            this->erase(crr->value);
        crr=crr->next;
    }
}
template<typename T>
void Stack<T>::print()
{

    if(first==nullptr)
    {
        std::cout<<"The container is empty!\n";
        return;
    }
    StackNode<T>* crr=first;
    while(crr!=nullptr)
    {

        std::cout<<crr->value<<" ";
        crr=crr->next;
    }
    std::cout<<std::endl;
}
template<typename T>
int Stack<T>:: countNodes()
{
    if(first==nullptr)
        return 0;
    int counter=0;
    StackNode<T>* crr =first;
    while(crr!=nullptr)
    {
        counter++;
        crr=crr->next;
    }
    return counter;
}
template<typename T>
void Stack<T>:: sort()
{
    if(this->empty())
        return;

    vector<T> vec;
    StackNode<T>* crr=first;
    Stack<T> newStack;
    bool flag=0;
    while(crr!=nullptr)
    {
        flag=0;
        if(vec.empty())
            vec.push_back(crr->value);
        else
        {
            for(int i=0;i<vec.size();i++)
            {
                if(crr->value<vec[i]){
                    vec.insert(vec.begin()+i,crr->value);
                    flag=1;
                    break;
                }


            }
            if(!flag)
                vec.push_back(crr->value);

        }
        crr=crr->next;
    }
    for(int i=0;i<vec.size();i++)
    {
        newStack.push(vec[i]);
    }
    *this=newStack;
}
template<typename T>
void Stack<T>:: printToFile(ostream& out)
{

   StackNode<T>*crr=first;
   while(crr->next->next!=nullptr)
   {
       out<<crr->value<<" ";
       crr=crr->next;
   }
   out<<crr->value;
}
#endif
