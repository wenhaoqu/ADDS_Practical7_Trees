#pragma once

#include <map>
#include <vector>

class TrieNode
{
private:
    std::map<char, TrieNode*> children;
    bool endOfWord;

public:
    TrieNode();
    TrieNode* setChild(char letter);
    void setEndOfWord(bool val);
    bool getEndOfWord();
    TrieNode* getChild(char letter);
    void removeChild(char letter);
    bool hasChildren();
    std::vector<char> getChildrenKeys();
    int getNumOfChildren();
    ~TrieNode();
};

