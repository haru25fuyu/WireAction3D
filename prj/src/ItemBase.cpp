#include "ItemBase.h"
#include"Hit.h"

ItemBase::ItemBase() :
	Base(),m_type(0)
{
}

void ItemBase::Init()
{
	SetItem();
}

void ItemBase::Set(Vector3 pos)
{
	m_pos = pos;
}

void ItemBase::Updete(CharBase* char_)
{
	m_rot.y += 0.1f;
	Vector3 char_pos = char_->GetPos();
	float	char_radius = char_->GetRadius();
	if (!HitCheck_Sphere_Sphere(char_pos.VGet(), char_radius, m_pos.VGet(), 3.0f))
		return;
	char_->SetNearItem(m_type);
}

void ItemBase::Drew()
{
	//MV1SetPosition(m_model,VGet(m_pos.x,m_pos.y,m_pos.z));
	//MV1SetRotationXYZ(m_model,VGet(m_rot.x,m_rot.y,m_rot.z));
	//MV1DrawModel(m_model);
}
