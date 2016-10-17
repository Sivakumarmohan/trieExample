#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
using namespace std;


class trie
{
    typedef map <char, class trie*> lettermap;
    
public:
    trie();
    ~trie(); 
    void insert(string word);
    bool find(string word);
    vector <string> searchPrefix(string prefix); //TODO: search based on prefix word.
protected:
    void addWord(string word, class trie* node);
    bool search(string word, class trie* node);
private:
    lettermap children;
    bool endOfWord;

};


trie::trie()
{

}
trie::~trie()
{
//TODO: Delete the tree
}
void trie::addWord(string word, trie* node )
{

     lettermap::iterator it = node->children.find(word[0]);
     if( it == node->children.end()) // New node required
     {
        trie *new_node = new trie;
        new_node->endOfWord = false;

        node->children[word[0]] = new_node;
        if(word.size() > 1)
            addWord(word.substr(1, word.size() -1), new_node);
        else
            new_node->endOfWord = true;
     }
     else
     {
         
         addWord(word.substr(1, word.size()-1), it->second);
        
     }

}


void trie::insert(string word)
{
    addWord(word, this);
}

bool trie::find(string word)
{
    bool ret = false;
     if(search(word, this))
         ret = true;
    return ret;
}

bool trie::search(string word, trie* node)
{
    bool ret = false;
    if (word.size() >= 1)
    {
        lettermap::iterator it = node->children.find(word[0]);
        if( it == node->children.end())
        {
            return ret;
        }

        ret = search(word.substr(1, word.size() -1), it->second);
    }
    else
    {
        ret = true;
    }
    return ret;
}
int main()
{
    trie mycommands;
    mycommands.insert("mkdir");
    mycommands.insert ("mkfile");
    cout << "Search mkdir :" << ((mycommands.find("mkdir")) ? "FOUND": "NOT FOUND") << endl;
    cout << "Search mkdis :" << ((mycommands.find("mkdis")) ? "FOUND": "NOT FOUND") << endl;

}

