#pragma once

#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

#include "Resource.h"
#include "Macro.h"
#include "Flag.h"
#include "Types.h"

template<typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	
	for(iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	p.clear();
}

template<typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}
	p.clear();
}