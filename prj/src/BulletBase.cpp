#include "BulletBase.h"
#include "Hit.h"
#include"Random.h"

BulletBase::BulletBase() :
	Base()
{
	m_de = false;
	m_timer = 0;
	m_speed = 0.0f;
	m_damege = 0.0f;
	m_rate_of_fire = 1;
	m_reload_time = 0;
	m_damage_range = 0.0f;
	m_tracking = false;
	m_magazine_size = 10;
	m_reload = false;
	m_cllider_type = SPHER;
	m_reload = 0;
	m_shoot_num = 0;
	m_image = 0;
	m_tracking_performance = 0.0f;
	m_magnitude_of_recoil = 0.0f;
}

float BulletBase::GetDamage()
{
	return m_damege;
}

float BulletBase::GetDamegeRange()
{
	return m_damage_range;
}

int BulletBase::GetRateOfFire()
{
	return m_rate_of_fire;
}

int BulletBase::ReloadTime()
{
	return m_reload_time;
}

bool BulletBase::GetDe()
{
	return	m_de;
}

int BulletBase::GetMagazineSize()
{
	return m_magazine_size;
}

int BulletBase::GetTime()
{
	return m_timer;
}

int BulletBase::GetShootNum()
{
	return m_shoot_num;
}

bool BulletBase::GetReLoade()
{
	return m_reload;
}

void BulletBase::AddSootNum()
{
	m_shoot_num++;
}

void BulletBase::Reload()
{
	m_reload = true;
	m_shoot_num = 0;
	m_timer = 0;
}

Vector3 BulletBase::SetReaction(Vector3 rot_)
{
	float magnitude_of_recoil = m_magnitude_of_recoil * 0.01f;
	Vector3 vect(atan2f(magnitude_of_recoil, 1.0f), atan2f(GetRandomF(-0.01f, 0.01f), 1.0f), 0.0f);
	return rot_ + vect;
}


void BulletBase::Init()
{
	m_de = false;
	m_timer = 0;
	SetType();
	m_obj_type = BULLET;
	m_shoot_num = 0;
	m_image = LoadGraph("data/aaa.png");
}

void BulletBase::Set(Base* obj_)
{
	m_timer = 0;
	if (m_de)	return;
	m_pos = obj_->GetPos();
	m_rot = obj_->GetRot();
	m_vect.x = m_speed * sinf(m_rot.y);
	m_vect.z = m_speed * cosf(m_rot.y);
	m_vect.y = m_speed * sinf(m_rot.x);
	m_vect += obj_->GetVect();
	//obj_->SetRot(SetReaction(obj_->GetRot()));
	m_de = true;
}
void BulletBase::Set(Vector3& pos, Vector3& vect, Vector3& obj_vect)
{
	m_timer = 0;
	if (m_de)	return;
	m_pos = pos;
	m_rot = Vector3(atan2f(vect.y, vect.x), atan2f(vect.x, vect.z), 0.0f);
	m_vect.x = m_speed * sinf(m_rot.y);
	m_vect.z = m_speed * cosf(m_rot.y);
	m_vect.y = m_speed * sinf(m_rot.x);
	m_vect += obj_vect;
	m_de = true;
}

void BulletBase::Move()
{
	m_timer++;
	if (m_timer > m_reload_time)
		m_reload = false;
	if (!m_de)	return;
	m_pos += m_vect;
	m_vect.x *= 0.99f;
	m_vect.z *= 0.99f;
	m_vect.y -= 0.05f;


	int		target_idx = -1;
	int		target_type = 0;
	float	min_length = 100000.0f;
	if (!m_tracking)  return;
	//’Ç”ö‹@”\‚ªƒIƒ“‚È‚ç
	
	for (size_t i = 0; i < m_target.size();++i) {
		if (!HitCheck_Sphere_Sphere(m_target[i]->GetPos().VGet(), m_target[i]->GetRadius(), m_pos.VGet(), GUIDAN_RADIUSE))
			continue;
		Vector3 target_pos = m_target[i]->GetPos();
		float length = GetVector3Distance(m_pos, target_pos);
		if (min_length > length)
			target_idx = i;
		min_length = length;
	}
	

	if (target_idx == -1)
		return;
	if (m_target[target_idx]->GetObjType()> 3)
		return;

	Vector3 vect = m_vect;
	vect.normalize();
	Vector3 vect_ob = m_target[target_idx]->GetPos() - m_pos;
	vect_ob.normalize();
	float ob_dot = GetVector3Dot(vect, vect_ob);
	if (ob_dot < 0) return;

	vect.clear();
	vect.x = sinf(m_rot.y + TO_RADIAN(90.0f));
	vect.z = cosf(m_rot.y + TO_RADIAN(90.0f));
	vect.normalize();

	float vect_length = m_vect.GetLength();
	if (GetVector3Dot(vect, vect_ob) < 0) {
		m_rot.y -= m_tracking_performance;
		m_vect.x = vect_length * sinf(m_rot.y);
		m_vect.z = vect_length * cosf(m_rot.y);
	}
	else {
		m_rot.y += m_tracking_performance;
		m_vect.x = vect_length * sinf(m_rot.y);
		m_vect.z = vect_length * cosf(m_rot.y);
	}
	vect.x = 0.0f;
	vect.z = 0.0f;
	vect.y = sinf(m_rot.x + TO_RADIAN(90.0f));
	vect.normalize();
	if (GetVector3Dot(vect, vect_ob) < 0) {
		m_rot.x -= m_tracking_performance;
		m_vect.y = vect_length * sinf(m_rot.x);
	}
	else {
		m_rot.x += m_tracking_performance;
		m_vect.y = vect_length * sinf(m_rot.x);
	}
}

void BulletBase::Draw()
{
	DrawString(100, 100, "aaaaa", GetColor(255, 255, 255));
	//DrawGraph(100, 100, m_image, false);

	
	if (!m_de)	return;
	float camera_length=GetCameraLength(m_pos);
	if (camera_length < 3.0f)
		return;
	//MV1SetPosition(m_model,VGet(m_pos.x,m_pos.y,m_pos.z));
	//MV1SetRotationXYZ(m_model,VGet(m_rot.x,m_rot.y,m_rot.z));
	//MV1DrawModel(m_model);
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), 0.3f, 32, GetColor(255, 255, 0),GetColor(255,255,0), true);
}

void BulletBase::Hit(Base* obj)
{
	
}

void BulletBase::Delete()
{
	m_de = false;
}
