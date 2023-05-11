#include "Autocomplete.h"

Autocomplete::Autocomplete() 
{
    root = new TrieNode();
    root->setEndOfWord(false);
}

Autocomplete::~Autocomplete() 
{
    delete root;
}


void Autocomplete::insert(string word)
{
    return insertWord(word);
}



/**
* Insert word into Autocomplete
*
* @param string word
*
* @return void
*/
void Autocomplete::insertWord(string word) {

    TrieNode* curNode = root;

    int wordLength = word.length();
    int index = 0;

    // finding the position for insertion of word
    // looking through nodes,if not present
    // creting new ones.
    while (index < wordLength) {

        char curLetter = word[index];
        TrieNode* childNode = curNode->getChild(curLetter);

        if (childNode == nullptr) {
            childNode = curNode->setChild(curLetter);
        }

        curNode = childNode;
        index++;
    }

    // setting endOfWord=True for cuurent node
    // to denote end of word
    curNode->setEndOfWord(true);
}

/**
* Insert word list
*
* @param vectory<string> wordList
*
* @return void
*/
void Autocomplete::insertWordList(vector<string> wordList) {

    for (auto word : wordList) {
        insertWord(word);
    }
}


/**
* Check whether word exists in Autocomplete
*
* @param string word
*
* @return void
*/
bool Autocomplete::wordExists(string word) {

    TrieNode* curNode = root;

    int wordLength = word.length();
    int index = 0;

    while (index < wordLength) {

        TrieNode* childNode = curNode->getChild(word[index]);

        if (childNode == nullptr) {
            return false;
        }

        curNode = childNode;
        index++;
    }

    return curNode->getEndOfWord();
}

/**
* Delete word
*
* this method deletes a word from Autocomplete
* the word may have a another word
* as child, thus, the nodes for that word cant be removed
* if no child we keep removing nodes
* until we reach a node that has a child
* or is end of a word.
* removing nodes happen in the reverse order
* meaning node farthest from root is removed first.
*
* @param string word
*
* @return void
*/
void Autocomplete::deleteWord(string word) {

    // first, we reach the endofword for the word,
    // while storing the path nodes in stack.
    // if word doesnt exist, then print so.
    stack<TrieNode*> nodeStack;
    TrieNode* childNode, * curNode = root;

    int index = 0;
    int wordLength = word.length();

    while (index < wordLength) {

        nodeStack.push(curNode);
        childNode = curNode->getChild(word[index]);

        if (childNode == nullptr) {
            return;
        }

        curNode = childNode;
        index++;
    }

    // curNode has the value of EOW for
    // this current word
    // setting EOW for this node to false,
    // to denote removal of word
    curNode->setEndOfWord(false);

    // if last node has children,
    // then we cant delete any node.
    if (!curNode->hasChildren()) {

        int index = 0;

        while (!nodeStack.empty()) {

            curNode = nodeStack.top();
            nodeStack.pop();

            cout << "deleting letter....\n" << word[wordLength - index - 1] << endl;
            curNode->removeChild(word[wordLength - index - 1]);
            index++;

            // if that node has endOfWord==true or hasChildren>0
            // then other we cant delete nodes anymore.
            // as haschildren>0 means other nodes are linked to it.
            // and EOW==true means this node is end of word for some word
            if (curNode->getEndOfWord() || curNode->getNumOfChildren() > 0) {
                break;
            }
        }
    }
}


vector<string> Autocomplete::getSuggestions(string partialWord) 
{
    TrieNode* curNode = root, * childNode;
    int index = 0;
    int wordLength = partialWord.length();

    while (index < wordLength) 
    {
        childNode = curNode->getChild(partialWord[index]);
        if (childNode == nullptr) 
        {
            return vector<string>();
        }
        index++;
        curNode = childNode;
    }

    // now curNode contains the node whose children are suggestions.
    vector<string> suggestionsList;
    vector<string>::iterator it;
    getSuggestionsHelper(curNode, suggestionsList, partialWord);

    return suggestionsList;
}

/**
* Suggestions helper
*
* @param TrieNode* node
* @param fstream& s
*
* @return void
*/
void Autocomplete::getSuggestionsHelper(
    TrieNode* curNode,
    vector<string>& suggestionsList,
    string subWord
) {

    if (curNode->getEndOfWord()) {
        suggestionsList.push_back(subWord);
    }

    vector<char>::iterator it;
    vector<char> keys = curNode->getChildrenKeys();

    for (it = keys.begin(); it != keys.end(); it++) {
        getSuggestionsHelper(curNode->getChild(*it), suggestionsList, subWord + (*it));
    }

}
