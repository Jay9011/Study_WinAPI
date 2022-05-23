#pragma once

class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);

// vector Safe Á¦°Å
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (auto& item : _vec)
	{
		if (nullptr != item)
		{
			delete item;
		}

		_vec.clear();
	}
}