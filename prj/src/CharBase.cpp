#include "CharBase.h"
int CharBase::m_obj_num = 0;

CharBase::CharBase() :
	Base()
{
	
	m_timer = 0;
	m_obj_num++;
	m_cllider_type = SPHER;
	m_near_item = 0;
}

void CharBase::SetNearItem(int type)
{
	m_near_item = type;
}

void CharBase::Init()
{
	SetChar();
	m_timer = 0;
}

void CharBase::Update()
{
	Move();
	
	m_vect.x *= 0.99f;
	m_vect.z *= 0.99f;
	m_vect.y -=0.019f;
	m_timer++;
	if (m_rot.x > TO_RADIAN(80.0f)) {
		m_rot.x = TO_RADIAN(80.0f);
	}
	if (m_rot.x < TO_RADIAN(-80.0f)) {
		m_rot.x = TO_RADIAN(-80.0f);
	}
}

void CharBase::Draw()
{
	
}

void CharBase::Exit()
{
}

