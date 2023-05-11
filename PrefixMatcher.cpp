#include "PrefixMatcher.h"



int PrefixMatcher::selectRouter(string networkAddress)
{
	vector<string> sug = m_cAuto.getSuggestions(networkAddress);
	for (auto it : m_mRouter)
	{
		if (it.second == sug[0])
			return it.first;
	}

	return 0;
}

void PrefixMatcher::insert(string address, int routerNumber)
{
	m_cAuto.insert(address);
	m_mRouter[routerNumber] = address;
}

