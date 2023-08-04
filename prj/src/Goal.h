#pragma once
#include "Base.h"
class Goal :
	public Base
{
	Vector3 m_pos1;
	Vector3 m_pos2;
	Cube	m_cube;
	bool	m_goal;

public:
	Goal();
	void SetPos(Vector3& pos);
	Cube GetHitCube();

	bool GetGoal();
	void Init(Vector3& pos);
	void UpDete(Base& char_);
	void Draw();
	void Exit();
};



