#pragma once

#include <string>
#include <iostream>
#include <map>
#include "Autocomplete.h"

using namespace std;


class PrefixMatcher
{
private:
	Autocomplete m_cAuto;
	map<int, string> m_mRouter;

public:
	int selectRouter(string networkAddress);
	void insert(string address, int routerNumber);
};

