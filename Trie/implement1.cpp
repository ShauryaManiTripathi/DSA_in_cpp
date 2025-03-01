#include <bits/stdc++.h>
using namespace std;

// Trie node
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord=false;
    bool containsKey(char c){
        return children[c-'a']!=NULL;
    }
    TrieNode* put(char c){
        children[c-'a']=new TrieNode();
        return children[c-'a'];
    }
    TrieNode(){
        for(int i=0;i<26;i++){
            children[i]=NULL;
        }
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void addString(string strr){
        TrieNode* current = root;
        // get words from string, delimitting at space
        stringstream ss(strr);
        string word;
        while(ss>>word){
            for(char ch:word){
                if(!current->containsKey(ch)){
                    current=current->put(ch);
                }else{
                    current=current->children[ch-'a'];
                }
            }
            current->isEndOfWord=true;
        }
    }

    bool search(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->containsKey(ch)) {
                return false;
            }
            current = current->children[ch-'a'];
        }
        return current->isEndOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (!current->containsKey(ch)) {
                return false;
            }
            current = current->children[ch-'a'];
        }
        return true;
    }
};


int main(int argc, char const *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("/home/ironflesh/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/ironflesh/Desktop/DSA_in_cpp/output", "w", stdout);
#endif
    // do a hard testing with edge cases 
    Trie* trie = new Trie();
    trie->addString("hello world");
    trie->addString("hello");
    trie->addString("world");
    trie->addString("world hello");
    trie->addString("world hello world");
    trie->addString("world hello world hello");
    trie->addString("world hello world hello world");
    trie->addString("world hello world hello world hello");
    trie->addString("world hello world hello world hello world");

    cout<<trie->search("hllo")<<endl;
    cout<<trie->search("world")<<endl;
    cout<<trie->search("world hello")<<endl;
    cout<<trie->search("world hello world")<<endl;

    cout<<trie->startsWith("hello")<<endl;
    cout<<trie->startsWith("world")<<endl;
    cout<<trie->startsWith("wok")<<endl;
    return 0;
}
