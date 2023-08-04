#include "WierBase.h"
Vector3 WierBase::LimitLength(Base* obj_)
{
	Vector3 obj_vect = obj_->GetVect();
	Vector3 vect;
	Vector3 normal = m_strat_pos - m_pos;
	normal.normalize();
	vect = obj_vect - (normal * GetVector3Dot(obj_vect, normal));
	obj_vect.normalize();
	if (0.0f >= GetVector3Dot(obj_vect, normal)) vect = obj_->GetVect();
	return vect;
}
void WierBase::Init(Base* obj_)
{
	m_de = false;
	m_is_hit = false;
	m_radius = 0.3f;
	SetMyPos();
	m_pos = GetStartPos(obj_, m_my_pos);
	m_strat_pos = m_pos;
	m_is_pull = false;
}
void WierBase::Move()
{
	if (!m_de)		return;
	if (m_is_hit)	return;
	m_pos += m_vect;
}

Vector3 WierBase::GetStartPos(Base* obj_, float set_rota_)
{
	Vector3 vect = obj_->GetPos();
	vect.x += obj_->GetRadius() * sinf( obj_->GetRot().y + set_rota_);
	vect.z += obj_->GetRadius() * cosf( obj_->GetRot().y + set_rota_);
	return vect;
}

void WierBase::Set(Base* obj_,Vector3 rot_)
{
	if (m_de)	return;
	m_de = true;
	m_rot.y = rot_.y;
	m_rot.x = rot_.x;
	m_vect.x = WIER_SPEED * sinf(m_rot.y);
	m_vect.z = WIER_SPEED * cosf(m_rot.y);
	m_vect.y = WIER_SPEED * sinf(m_rot.x);
	m_vect.x += obj_->GetVect().x;
	m_vect.z += obj_->GetVect().z;
}

void WierBase::UpDate(Base* obj_)
{
	
	Vector3 vect =  m_strat_pos- m_pos;
	float length = vect.GetLength();
	if (length >= LIMIT_LENGTH) {
		if (!m_is_hit) {
			m_is_hit = true;
			m_is_pull = true;
		}
		Vector3 Limit_Length = LimitLength(obj_);
		if(!m_is_pull) obj_->SetVect(Limit_Length);
	}
	Move();
	m_is_pull = false;
	if (m_de) return;
	m_pos = m_strat_pos;
	
}

void WierBase::Delete()
{
	if (!m_de) return;
	m_de = false;
	m_is_hit = false;
	m_vect.clear();
}

Vector3 WierBase::CreateVect()
{
	Vector3 vect;
	m_is_pull = true;
	if (!m_is_hit) return vect;
	vect = m_pos - m_strat_pos;
	vect.normalize();
	vect *= PULL_POWER;
	return vect;
}

void WierBase::Draw(Base* obj_)
{
	m_strat_pos = GetStartPos(obj_, m_my_pos);
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), m_radius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	DrawLine3D(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_strat_pos.x, m_strat_pos.y, m_strat_pos.z), GetColor(1, 1, 1));
}
