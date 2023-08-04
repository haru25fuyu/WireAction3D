#include "WireL.h"


//void WireL::Set(Vector3 vect_, Base* obj_)
//{
//	if (m_de)	return;
//	m_vect = vect_;
//	m_pos = GetStartPos(obj_, m_my_pos);
//	m_rot.y = atan2f(vect_.z, vect_.y);
//	m_rot.x = atan2f(vect_.y, vect_.x);
//}

void WireL::SetMyPos()
{
	m_my_pos = TO_RADIAN(-90.0f);
}

//void WireL::UpDate(Base* obj_)
//{
//	Move();
//}


//void WireL::Draw(Base* obj_)
//{
//	m_strat_pos = GetStartPos(obj_, TO_RADIAN(-90.0f));
//
//}

