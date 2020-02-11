/**This header includes all the functions which are used for reading from file,creating a HLlist,
working with containers.Work interactive with the list.**/
#include"Container.h"
#include"HLlist.h"
#include"DList.h"
#include"Queue.h"
#include"Stack.h"
#include<fstream>
#include<vector>
using std::cin;
using std::vector;
using std::string;
using std:: ifstream;
using std::ofstream;
using std::cout;
template<typename T>
void readFromFile(HLlist<T>& newList,int numberOfContainers,ifstream& in,string& nameOfFile,vector<Container<T>*>& toDelete)
{
    T element;
    string type;
    Container<T>** containers = new Container<T>*[numberOfContainers];
    int counter=0;

    in.open(nameOfFile);
    in.seekg(0,in.end);//I get this length because I want the position of the end.
    int length=in.tellg();
    in.seekg(0,in.beg);
    while(in.peek()!=10)//so as to remove the first line,which show the type of elements.
       in.get();

    while(in.tellg()!=length&&counter<=numberOfContainers-1)
    {

        in>>type;
        if(type=="queue")
        {
            containers[counter]=new Queue<T>;
        }

        else if(type=="stack")
        {
            containers[counter]=new Stack<T>;
        }

        else if(type=="doubly-linked-list")
        {
            containers[counter]=new DLList<T>;
        }

        while(in.peek()!=10)
        {
            in>>element;
            containers[counter]->push(element);
        }

         in.get();

         newList.addContainer(containers[counter]);
         toDelete.push_back(containers[counter]);
         counter ++;

    }
}
bool correctFile(string& nameFile)
{
    ifstream in(nameFile);
    if(in.is_open())
    {
        in.close();
        return true;
    }
    else
    {
        cout<<"The file is not found!Please enter another name!\n";
        cin>>nameFile;
        nameFile+=".txt";
        return correctFile(nameFile);
    }
}
template<typename T>
void deleteContainers(vector<Container<T>*>& toDelete)
{
    for(int i=0;i<toDelete.size();i++)
    {
        delete toDelete[i];
    }

}
template<typename T>
void creatingList(int size,ifstream& in,HLlist<T>& newList,string& nameFile,string type)
{
    vector<Container<T>*> toDelete;
    readFromFile(newList,size,in,nameFile,toDelete);
    workingWithList(newList,type,nameFile,toDelete);
}
template<typename T>
void backToFile(HLlist<T>& newList,string type,string& nameOfFile)
{
    ofstream o(nameOfFile);
    o<<type;
    o<<std::endl;
    o<<newList;
    o.close();
}
template<typename T>
void workingWithList(HLlist<T>& lst,string type,string nameOfFile,vector<Container<T>*>& toDelete)
{
    cout<<"You successfully load the containers from the file!\n "
        <<"Your options for working with the Heterogeneous list are:\n\n"
        <<"print;\n"
        <<"add;\n"
        <<"remove;\n"
        <<"add-container;\n"
        <<"member;\n"
        <<"sort;\n"
        <<"save;\n"
        <<"saveas;\n"
        <<"exit;\n\n";
    string command;
    T element ;
    while(command!="exit")
    {
        cin>>command;
        if(command=="print")
        {
            lst.print();
        }
        else if(command=="add")
        {

            cout<<"Please enter an element of type: "<<type<<"\n";
            cin>>element;
            lst.add(element);
        }
        else if(command=="remove")
        {
            cout<<"Enter an element of type "<<type<<"\n";
            cin>>element;
            lst.remove(element);
        }
        else if(command=="add-container")
        {
            cout<<"Please enter a type:\n";
            cin>>command;
            if(command=="queue")
            {
                Container<T>* _container=new Queue<T>();
                toDelete.push_back(_container);
                lst.addContainer(_container);

            }
            else if(command=="stack")
            {
                Container<T>* _container=new Stack<T>();
                toDelete.push_back(_container);
                lst.addContainer(_container);

            }
            else
            {
                Container<T>* _container=new DLList<T>();
                toDelete.push_back(_container);
                lst.addContainer(_container);

            }
        }
        else if(command=="member")
        {
            cout<<"Enter an element of type: "<<type<<"\n";
            cin>>element;
            if(lst.member(element))
                cout<<"The element is a member!\n";
            else
                 cout<<"The element is not a member!\n";
        }
        else if(command=="sort")
        {
            lst.sort();
        }
        else if(command=="save")
        {
            backToFile(lst,type,nameOfFile);
            cout<<"File is successfully saved!\n";
        }
        else if(command=="saveas")
        {
            cout<<"Enter a name of file:\n";
            cin>>command;
            command+=".txt";
            backToFile(lst,type,command);
            cout<<"File is successfully saved!\n";

        }
        else
        {
            if(command!="exit")
                cout<<"Invalid command.Please input a valid one!"<<std::endl;

        }

    }
    cout<<"You successfully exit the program!\n";
    deleteContainers(toDelete);
}
