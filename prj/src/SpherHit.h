#pragma once

#include "Vector3.h"
#include"Base.h"

class SpherHit
{
	Base*	m_info;
	Vector3 m_pos_memory;
	Vector3 m_vect_memory;

	std::vector<Base*>	m_target_info;
	std::vector<Vector3> m_target_pos_memory;
	std::vector<Vector3> m_target_vect_memory;

	
	bool CheckLineHit(Vector3& line_start, Vector3& line_goal);
	bool ChackCubeHit();
	//Vector3 GetCubeHitPos(Vector3& c1, Vector3& c2, Base* obj);
	void SetReboundVectBox(Cube& cube);
	void CheckHitSpher();

public:
	void Set(Base* obj_, std::vector<Base*> target_);
	SpherHit();
	~SpherHit();
	
	void UpDate(Base* obj_, std::vector<Base*>& target_);
};



