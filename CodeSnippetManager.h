#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class CodeSnippetManager{
public:
     unordered_map<string,string> snippets;  //unordered map used to decrease T.C compared to map

     void addSnippet(const string& tag, const string& code); //to add code snippet to our file

     void retrieveSnippet(const string& tag); //to access the code snippets stored in our file

     bool editSnippet(const string& tag,const string& code); //to edit the existing code snippet

     int countSnippet(); //to count the number of code snippets existing in the file

     void findTags(const string& tag); //to find similar tags based on partially searched tags

     void recommendtags(const string& str); //to recommend a tags for an incorrect/partial search

     void deleteSnippet(const string& str); //to delete snippet in the file/map

     void mostusedsnippets(); //to give analytics for the most used/accessed tags

     bool savetoFile(const string& filename);
     bool loadtoFile(const string& filename);

};

