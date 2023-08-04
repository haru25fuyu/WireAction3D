#include "BuildingBase.h"
#include"Hit.h"

bool s=false;
BuildingBase::BuildingBase():
	Base()
{
	m_cllider_type = CUBE;
	m_obj_type = BUILDING;
	m_color = GetColor(0, 0, 0);
	m_cube = MakeCubeTowPos(m_pos1, m_pos2);
}
Vector3 BuildingBase::GetPos1()
{
	return m_pos1;
}

Vector3 BuildingBase::GetPos2()
{
	return m_pos2;
}

Cube BuildingBase::GetHitCube()
{
	return m_cube;
}

void BuildingBase::Init( Vector3 under_center_pos)
{
	m_obj_type = BUILDING;
	m_color = GetColor(255, 255, 255);
	SetBuil();
	SetPos(under_center_pos);
}

void BuildingBase::SetPos(Vector3 under_center_pos)
{
	m_pos = under_center_pos;
	SetBuil();
	m_cube = MakeCubeTowPos(m_pos1, m_pos2);
}

void BuildingBase::SetPos(float c_x, float c_y, float c_z)
{
	m_pos.set(c_x, c_y, c_z);
	SetBuil();
	m_cube = MakeCubeTowPos(m_pos1, m_pos2);
}

void BuildingBase::Updete(Base* obj_)
{
	s = false;
	Spher spher;
	spher.pos= obj_->GetPos();
	spher.radius = obj_->GetRadius();

	SetReboundVectSpherBox(obj_, m_cube);
}

void BuildingBase::Draw()
{
	MV1SetPosition(m_model, m_pos.VGet());
	MV1DrawModel(m_model);
	DrawCube3D(VGet(m_pos1.x,m_pos1.y,m_pos1.z),VGet(m_pos2.x, m_pos2.y, m_pos2.z),m_color,m_color,false);
}

void BuildingBase::Exit()
{
}
