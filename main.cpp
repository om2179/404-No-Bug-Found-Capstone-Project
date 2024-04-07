// cmd directory command : cd /d D:\CPP.MY\CapstoneProject
// g++ main.cpp CodeSnippetManager.cpp -o run

#include "CodeSnippetManager.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){

    CodeSnippetManager manager;

    if(manager.loadtoFile("Snippets.txt")){ //we load the existing and previously added snippets from the file
        cout<<"Snippets loaded from file "<<endl;
    }
    else{
        cout<<":( No snippet found "<<endl;
    }

    while(true){
        cout<<"\n";
        cout<<"Existing Number Of Code Snippets In File: "<<manager.countSnippet()<<"\n";
        cout<<"Below are top 5 most used code snippets: "<<"\n";
        manager.mostusedsnippets();
        cout<<"\n";
        cout<<"1. Add Snippet"<<endl;
        cout<<"2. Retrive Snippet"<<endl;
        cout<<"3. Edit Snippet"<<endl;
        cout<<"4. Retrive Snippet Based On Partially Remembered Tags"<<endl;
        cout<<"5. Delete Snippet"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<endl;
        cout<<"Choose an option: ";

        int choice;
        cin>>choice;

        if (choice == 1){
            string tag,code;
            cout<<"Enter tag: ";
            cin>>tag;
            cin.ignore();
            cout<<"Enter code Snippet:\n";
            string line;
            code="";
            while(getline(cin,line)&& line != "%%"){ //as code snippet consists of multiple lines we take line by line input
                code += line +"\n";                        //until %% is encountered
            }
            manager.addSnippet(tag,code);
            cout<<"Snippet added "<<"\n";
        } else if (choice==2){
            string tag;
            cout<<"Enter tag to retrive snippet:";
            cin>>tag;
            manager.retrieveSnippet(tag);

        }else if(choice==3){
            string tag,newcode="";
            cout<<"Enter tag of the code you want to edit: ";
            cin>>tag;
            cin.ignore();

            cout<<"Enter the new edited version of your code snippet: "<<endl;
            string line;
            while(getline(cin,line)&& line != "%%"){
                newcode += line +"\n";
            }
            if(manager.editSnippet(tag,newcode)){
                cout<<"Snippet updated successfully "<<"\n";
            }
            else{
                cout<<"Given Tag provided does not exist"<<"\n";
            }
        }else if(choice==4){
            string dummytag;
            cout<<"Enter part of tag that you remember: ";
            cin>>dummytag;
            cout<<"Following Are Similar Tags Found"<<endl;
            manager.findTags(dummytag);

        }else if(choice==5){
            string tagdelete;
            cout<<"Enter Tag Of CodeSnippet that you want to delete: ";
            cin>>tagdelete;
            manager.deleteSnippet(tagdelete);
        }
        else if (choice==6){
            manager.savetoFile("Snippets.txt");
            cout<<"Snippets saved to file exiting the program"<<"\n";
            break;
        } else{
            cout<<"Error 404 :( Invalid choice";
        }


    }
    return 0;

}

