#pragma once

#include "WinMain.h"
#include "Vector3.h"
#include <vector>
#include <map>

//---------------------------------------------------------------------------------
//	äÓñ{ÉNÉâÉX
//---------------------------------------------------------------------------------
class Base
{

protected:
	const float WIRE_SPEED = 10.0f;
	static int m_serial_number;

	int		m_model;
	Vector3	m_pos;
	Vector3	m_rot;
	Vector3 m_vect;
	Vector3 m_size;
	float	m_radius;
	float   m_rebound_factor;
	int		m_obj_type;
	bool	m_is_hit;
	int		m_hit_obj_type;
	int		m_cllider_type;
	std::vector<Base*> m_target;

public:
	Base();
	//Getterä÷êî
	Vector3 GetPos()			const;
	Vector3 GetRot()			const;
	float	GetRadius()			const;
	float	GetReboundFactor()	const;
	int		GetObjType()		const;
	bool	GetIsHit()			const;
	Vector3 GetVect()			const;
	Vector3	GetSize()			const;
	int		GetClliderType()	const;
	int		GetSerialNumber();

	//Setterä÷êî
	void SetPos(Vector3 pos_);
	void SetPos(float pos_x, float pos_y, float pos_z);
	void SetRot(Vector3 rot_);
	void SetRadius(float radius_);
	void SetTarget(Base* obj_);
	void SetTarget(std::vector<Base*> obj_);
	void SetTarget(std::map<int, Base*>* map);
	void SetIsHit(bool flag_);
	void SetHitOBjType(int type_);
	void SetVect(Vector3& vect_);

	void AddPos(Vector3 vect_);

};
