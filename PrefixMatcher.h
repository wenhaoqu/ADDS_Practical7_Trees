#pragma once

#include <string>
#include <iostream>
#include <map>
#include "TrieNode.h"

using namespace std;


class PrefixMatcher
{
private:
	map<int, string> m_mRouter;
	TrieNode* root;
	


public:
	PrefixMatcher();
	~PrefixMatcher();

	int selectRouter(string networkAddress);
	void insert(string address, int routerNumber);

	void getAddress(TrieNode* curNode, string& dest);
};

