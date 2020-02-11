#include<iostream>
#include"main-header.h"
int main()
{
    cout<<"Please enter name of file you want to open!\n";
    string nameFile;
    cin>>nameFile;
    nameFile+=".txt";
    if(correctFile(nameFile))
    {
        cout<<"You successfully opened the file!\n";
        cout<<"How many containers do you want to load? Please enter a number:\n";
        ifstream in(nameFile);
        int n;
        cin>>n;
        string typeOfElements;
        in>>typeOfElements;
        in.close();
        if(typeOfElements=="bool")
        {
             HLlist<bool> newList;
             creatingList(n,in,newList,nameFile,typeOfElements);
        }
        else if(typeOfElements=="char")
        {
            HLlist<char> newList;
            creatingList(n,in,newList,nameFile,typeOfElements);
        }
        else if(typeOfElements=="int")
        {
            HLlist<int> newList;
            creatingList(n,in,newList,nameFile,typeOfElements);

        }
        else if(typeOfElements=="string")
        {
            HLlist<string> newList;
            creatingList(n,in,newList,nameFile,typeOfElements);
        }

    }

    return 0;
}
