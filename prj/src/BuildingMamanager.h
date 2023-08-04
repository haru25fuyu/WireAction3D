#pragma once
#include "Base.h"
#include"BuildingBase.h"
#include<vector>

class BuildingMamanager 
{
	std::vector<BuildingBase*> building;

public:
	void Init();
	void Updete();
	void Draw();
	void Exit();
};

