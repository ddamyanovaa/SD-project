/**This main file test all the functions of the list!**/
#include<iostream>
#include"HLlist.h"
#include"DList.h"
#include"Queue.h"
#include<fstream>
#include"Stack.h"
using std::cout;
bool odd (int x)
{
    return x%2!=0;
}
bool even(int x)
{
    return !odd(x);
}
void testFunctions()
{
    /**doubly-linked-list**/
    DLList<int> d;
    d.push(1);
    d.push(27);
    d.push(4);
    d.push(30);
    d.push(7);
    d.push(4);
    d.push(5);
    /**queue**/
    Queue<int> q;
    q.push(10);
    q.push(10);
    q.push(10);
    q.push(11);
    q.push(15);
    q.push(11);
    q.push(7);
    q.sort();
    /**stack**/
    Stack<int> s;
    s.push(2);
    s.push(1);
    s.push(2);
    s.push(5);
    s.push(12);
    s.push(10);
    s.push(7);
    s.push(11);
    s.push(4);
    s.push(5);

    /**HLlist**/

    Node<int> newNode(&d);
    HLlist<int> hl(&newNode);
    hl.addContainer(&q);
    hl.addContainer(&s);

    /**print**/

    hl.print();
    std::cout<<std::endl;

    /**add**/

    cout<<"Adds new element.\n";
    hl.add(204);
    hl.print();
    cout<<"\n";

    /**remove**/
    cout<<"Removes an elements: "<<2<<" .\n";
    hl.remove(2);
    hl.print();
    cout<<"\n";

    /**member**/

    cout<<"Is 2 a member?"<<hl.member(9);

    /**filter**/

    cout<<"\nFilter-odd numbers.\n";
    hl.filter(odd);
    hl.print();
    cout<<"\n";

    /**add-container**/

    cout<<"Adds new container-> doubly-linked-list.\n";
    DLList<int> d1;
    Container<int>* newContainer=&d1;
    hl.addContainer(newContainer);
    Stack<int> s1;
    Container<int>* newContainer1=&s1;
    hl.addContainer(newContainer1);
    hl.print();
    cout<<"\n";

    /**sort**/

    cout<<"\nTests sort.\n";
    hl.sort();
    hl.print();

    /**iterator**/

    cout<<"\nTests iterator:\n";
    for(HLlist<int>::Iterator it = hl.begin();it!=hl.end();++it)
        std::cout<<*it<<" ";



}
int main()
{
    testFunctions();


 return 0;
}
