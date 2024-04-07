#include "CodeSnippetManager.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string,int> usecounter; //globally initialised map to store the usage of snippets

void CodeSnippetManager::addSnippet(const std::string &tag, const std::string &code) { //T.C= O(1) and S.C = O(1)
    snippets[tag]=code; //each input tag has a corresponding input code snippet associated with it through a map
    usecounter[tag]=0;
}
void CodeSnippetManager::retrieveSnippet(const std::string &tag) {
    auto it =snippets.find(tag);  //automataic iterator used to find our desired code snippet corresponding to the tag we input
    //T.C = O(logn) and S.C. = O(1)
    if(it!=snippets.end()){
        cout<<"The snippet for the given tag  is"<<"\n"<<it->second<<endl;
        usecounter[tag]++; //each time we use a snippet its associated usage counter increases
    }
    else{ //if snippet not found it(i.e. the iterator) will automatically point to the end of the map
        cout<<"Error 404;( No snippet found for the given tag"<<"\n";
        recommendtags(tag);
    }
}
bool CodeSnippetManager::editSnippet(const std::string &tag, const std::string &newcode) { //T.C= O(n) n is number of existing code snippets and S.C = O(1)
    for(auto& it: snippets){
        if(it.first==tag){              // if snippet for the given tag exists in file/map then it allows to edit/replace with new code snippet
            snippets[tag]=newcode; //the new edited code is now assigned to the tag
            return true;
        }
    }
    return false;
}
int CodeSnippetManager::countSnippet() { // T.C = O(1) map size is fetched in constant time and S.C = O(1)
    return snippets.size();  //size of map/snippets represent the number of total snippets in the file
}

bool customcomparatorsort(const pair<string, int> &a, const pair<string, int> &b) { //a custom comparator function that is called for comparisions during sorting
    return a.second > b.second; // Sort in descending order of second element T.C= O(1)
}

void CodeSnippetManager::mostusedsnippets() { //is used to determine top 5 most used snippets based on number of times it is retrived by the user
    vector<pair<string,int>> counter(usecounter.begin(),usecounter.end()); // S.C = O(n) as we made an extra data structure of size n
    //the usagecounter map is copied to above vector pair so that we can sort it customly into descending order
    sort(counter.begin(),counter.end(), customcomparatorsort); //overall T.C = O(nlogn) for this custom descending sort

    int cnt=0;

    for(auto it=counter.begin();it!=counter.end();it++){ //T.C = O(n)
        if(it->second>0 and cnt<5){//the top 5 snippets are printed
            cout<<it->first<<" : Used For = "<<it->second<<" times\n"; // if two snippets have same number of use then the one which is ahead lexicographically is printed first
            ++cnt;
        }
    }

    if(cnt==0){
        cout<<"No Snippets Are Accessed till now by the user after running the file\n";
    }
}

bool checkforsubstring(string s1, string s2) {  // function to check if string s1 is substring of string s2
    int n = s1.length();
    int m = s2.length();                     //T.C = O(n+m) and S.C = O(1) because no additional data structures used

    // If the length of s1 is greater than s2,
    // s1 cannot be a substring of s2
    if (n > m)
        return false;

    for (int i = 0; i <= m - n; ++i) {
        int j;
        // Check if the substring of s2 starting from index i
        // matches s1
        for (j = 0; j < n; ++j) {
            if (s2[i + j] != s1[j])
                break;
        }
        // If the inner loop completed without breaking,
        // it means s1 is found as a substring of s2
        if (j == n)
            return true;
    }
    // If s1 is not found as a substring of s2 after iterating through all possibilities
    return false;
}


void CodeSnippetManager::findTags(const std::string &tag) {  //function to find tags based on partially remembered tags and S.C = O(1) no extra space/data structure
    int cnt=0;                                               // T.C = O(N*(n+m)) where N=number of tags in map, n=size of partial tag , m= size of existing tag in map
    for(auto it=snippets.begin();it!=snippets.end();it++){
        if(checkforsubstring(tag,it->first)){ //checks if the inputted partial tags are substring of existing tags in the file/map
            cout<<"Tag: "<<it->first<<"\n";
            ++cnt;
        }
    }
    if(cnt==0){ //if no such snippet was found with given partial tag
        cout<<"No Such Type Of Tag Was Found"<<"\n";
    }
    cout<<"\n";
}
void CodeSnippetManager::recommendtags(const std::string &str) { //recommend us tags when we want enter a tag to retrive its code snippet but such tag does not exists
    vector<string> vec; //S.C = O(N)                             //so it recommend tags based on our search from the existing snippets file/map
    int cnt=0;
    for(auto it=snippets.begin();it!=snippets.end();it++){  //T.C = O(N*(n+m))
        if(checkforsubstring(str,it->first)){
            vec.push_back(it->first); //we store those tags that are similar to the incorrect/partial tag search
            ++cnt;
        }
    }
    if(cnt!=0){ //if such tags are found , we recommend those to the user
        cout<<"DID YOU MEAN TO SEARCH: "<<"\n";
        for(auto it =vec.begin();it!=vec.end();it++){ //T.C = O(vec.size())
            cout<<"* "<<*it<<"\n";
        }
    }
}
void CodeSnippetManager::deleteSnippet(const std::string &str) { // T.C = O(log n) n is the number of elements in the map and S.C = O(1) as it doesn't require any extra space
    //function deletes the code snippet with given tag
    auto it=snippets.find(str);// find function,if tag not found returns a pointer pointing to the end of the map
    if(it!=snippets.end()){
        snippets.erase(str) ;// erase function deletes the code snippet with the given tag from the map/file
        cout<<"Code Snippet for given tag deleted sucessfully"<<"\n";
    }
    else{ //if snippet not found it(i.e. the iterator) will automatically point to the end of the map
        cout<<"Error 404;( No snippet found for the given tag"<<"\n";
    }
}
bool CodeSnippetManager::savetoFile(const std::string &filename) { // T.C = O(n*m) n is the number of elements in the map and m is the number of characters in the tag and the code snippet
    // function saves all the changes made into map to the text file (snippets.txt)
    ofstream outfile(filename); //opening the file specified by filename for writing
    if(!outfile){
        cout<<"Error 404 ;( (File not found) "<<"\n";
        return false;
    }
    else{
        for(const auto & it: snippets){  //it(iterator across the map)
            outfile << "Tag: "<<it.first<<"\n";
            outfile<<"Code: \n"<<it.second<<"\n";
        }
    }

    outfile.close(); //closing the file
    cout<<"Snippet Sucessfully Saved To File: "<<filename<<"\n";
    return true;
}

bool CodeSnippetManager::loadtoFile(const std::string &filename) { //function load the file into the map with tag as key  and the code snippet
    ifstream ifile(filename); //opening the file
    if(!ifile){
        cout<<"Error 404 ;( (File Unable to open for reading)\n";
        return false;
    }
    snippets.clear(); // clears all the content in the map
    string new_line,curr_tag,curr_code;
    //T.C. = O(m) m=number of lines in the file and S.C.= O(n) n=number of unique tags in the file
    while(getline(ifile, new_line)){ // getlines read the line from the file/input stream and stores it in the string new_line
        if(new_line.find("Tag:")==0){
            curr_tag=new_line.substr(5); // substr return a string excluding first 5 characters of the string new_line
        }
        else if(new_line.find("Code: ")==0){
            curr_code="";
            while(getline(ifile,new_line)&&new_line!=""){// this loop runs till the file has no more lines or it encounters an empty line
                curr_code+=new_line+"\n";
            }
            snippets[curr_tag]=curr_code;
        }

    }
    ifile.close(); // closes the file
    cout<<"Snippets Loaded From File Sucessfully"<<filename<<"\n";
    return true;

}




