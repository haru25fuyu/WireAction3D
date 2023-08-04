#include "WinMain.h"
#include "Base.h"

int Base::m_serial_number = 0;
//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Base::Base()
{
	m_serial_number++;
	m_model = -1;
	m_pos.clear();
	m_rot.clear();
	m_radius = 0.0f;
	m_rebound_factor = 0.0f;
	m_obj_type = 0;
	m_size.clear();
	m_cllider_type = ANNON;
	m_obj_type = 0;
	m_is_hit = false;
	m_hit_obj_type = 0;
}

Vector3 Base::GetPos()	const
{
	return m_pos;
}

Vector3 Base::GetRot()	const
{
	return m_rot;
}

float Base::GetRadius()	const
{
	return m_radius;
}

float Base::GetReboundFactor() const
{
	return  m_rebound_factor;
}

int Base::GetObjType() const
{
	return m_obj_type;
}

bool Base::GetIsHit() const
{
	return m_is_hit;
}

void Base::SetPos(Vector3 pos_)
{
	m_pos = pos_;
}

void Base::SetPos(float pos_x, float pos_y, float pos_z)
{
	m_pos.x = pos_x;
	m_pos.y = pos_y;
	m_pos.z = pos_z;
}

void Base::SetRot(Vector3 rot_)
{
	m_rot = rot_;
}

void Base::SetRadius(float radius_)
{
	m_radius = radius_;
}

void Base::SetTarget(Base* obj_)
{
	for (size_t i = 0; i < m_target.size(); ++i) {
		if (m_target[i]->GetSerialNumber() == obj_->GetSerialNumber()) {
			return;
		}
	}
	size_t size = m_target.size();
	m_target.resize(size + 1);
	m_target[size] = obj_;
}

void Base::SetIsHit(bool flag_)
{
	m_is_hit = flag_;
}

void Base::SetHitOBjType(int type_)
{
	m_hit_obj_type = type_;
}

void Base::SetVect(Vector3& vect_)
{
	m_vect = vect_;
}


void Base::AddPos(Vector3 vect_)
{
	m_pos += vect_;
}

Vector3 Base::GetVect()const
{
	return m_vect;

}

Vector3 Base::GetSize() const
{
	return m_size;
}

int Base::GetClliderType() const
{
	return m_cllider_type;
}

int Base::GetSerialNumber()
{
	return m_serial_number;
}


