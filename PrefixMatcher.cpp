#include "PrefixMatcher.h"



PrefixMatcher::PrefixMatcher()
{
    root = new TrieNode();
    root->setEndOfWord(false);
}
PrefixMatcher::~PrefixMatcher()
{
    delete root;
}

int PrefixMatcher::selectRouter(string networkAddress)
{
    TrieNode* curNode = root;
    TrieNode* childNode = NULL;
    int addrLength = networkAddress.length();
    int index = 0;
    string dest;

    while (index < addrLength)
    {
        char curLetter = networkAddress[index];
        childNode = curNode->getChild(curLetter);

        if (childNode == nullptr) {
            getAddress(curNode, dest);
            //printf("dest==========%s\n", dest.c_str());
            break;
        }

        index++;
        dest += curLetter;
        curNode = childNode;
    }

    if (childNode != nullptr)
    {
        getAddress(curNode, dest);
        //printf("dest==========%s\n", dest.c_str());
    }

    for (auto it : m_mRouter)
    {
        if (it.second == dest)
        {
            return it.first;
        }
    }

	return 0;
}

void PrefixMatcher::insert(string address, int routerNumber)
{
    TrieNode* curNode = root;
    int addrLength = address.length();
    int index = 0;

    while (index < addrLength)
    {
        char curLetter = address[index];
        TrieNode* childNode = curNode->getChild(curLetter);

        if (childNode == nullptr) {
            childNode = curNode->setChild(curLetter);
        }

        index++;
        curNode = childNode;
    }

    curNode->setEndOfWord(true);

	m_mRouter[routerNumber] = address;
}


void PrefixMatcher::getAddress(TrieNode* curNode, string& dest)
{
    if (curNode->getEndOfWord()) 
    {
        return;
    }

    vector<char>::iterator it;
    vector<char> keys = curNode->getChildrenKeys();

    for (it = keys.begin(); it != keys.end(); it++)
    {
        dest += *it;
        getAddress(curNode->getChild(*it), dest);
    }

}
