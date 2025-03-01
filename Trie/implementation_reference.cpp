#include <iostream>
#include <unordered_map>
using namespace std;

// Node class representing each node in the Trie
class TrieNode {
public:
    // A map to store child nodes (characters) and their corresponding TrieNode pointers
    unordered_map<char, TrieNode*> children;

    // A flag to indicate if the current node represents the end of a word
    bool isEndOfWord;

    // Constructor to initialize the node
    TrieNode() : isEndOfWord(false) {}
};

// Trie class representing the overall Trie structure
class Trie {
private:
    // Root node of the Trie
    TrieNode* root;

public:
    // Constructor to initialize the Trie with an empty root node
    Trie() {
        root = new TrieNode();
    }

    // Destructor to clean up dynamically allocated memory
    ~Trie() {
        clear(root);
    }

    // Helper function to recursively delete all nodes in the Trie
    void clear(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }

    // Function to insert a word into the Trie
    void insert(const string& word) {
        TrieNode* current = root;

        // Traverse the Trie for each character in the word
        for (char ch : word) {
            // If the character is not already a child, create a new node
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }

            // Move to the child node corresponding to the current character
            current = current->children[ch];
        }

        // Mark the end of the word at the last node
        current->isEndOfWord = true;
    }

    // Function to search for a word in the Trie
    bool search(const string& word) {
        TrieNode* current = root;

        // Traverse the Trie for each character in the word
        for (char ch : word) {
            // If the character is not found, the word does not exist
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }

            // Move to the child node corresponding to the current character
            current = current->children[ch];
        }

        // Return true only if the last node marks the end of a word
        return current->isEndOfWord;
    }

    // Function to check if any word in the Trie starts with a given prefix
    bool startsWith(const string& prefix) {
        TrieNode* current = root;

        // Traverse the Trie for each character in the prefix
        for (char ch : prefix) {
            // If the character is not found, no words start with this prefix
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }

            // Move to the child node corresponding to the current character
            current = current->children[ch];
        }

        // If we reach here, the prefix exists in the Trie
        return true;
    }
};

// Main function to demonstrate the Trie functionality
int main() {
    Trie trie;
#ifndef ONLINE_JUDGE
    freopen("/home/ironflesh/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/ironflesh/Desktop/DSA_in_cpp/output", "w", stdout);
#endif

    // Insert some words into the Trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("bat");

    // Search for words
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not Found") << endl;

    // Check prefixes
    cout << "Starts with 'app': " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    cout << "Starts with 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << endl;
    cout << "Starts with 'batman': " << (trie.startsWith("batman") ? "Yes" : "No") << endl;

    return 0;
}