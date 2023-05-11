#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "TrieNode.h"

using namespace std;

class Autocomplete
{
private:
    TrieNode* root;

public:
    Autocomplete();
    ~Autocomplete();

    void insertWord(string word);
    void insertWordList(vector<string> wordList);
    bool wordExists(string word);
    void deleteWord(string word);
    void getSuggestionsHelper(TrieNode* curNode, vector<string>& suggestionsList, string subWord);

public:
	vector<string> getSuggestions(string partialWord);
	void insert(string word);
};

