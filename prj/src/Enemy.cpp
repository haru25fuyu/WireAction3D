#include "Enemy.h"
#include"Hit.h"


void Enemy::SetChar()
{
	m_obj_type = ENEMY1;
	m_pos.set(10.0f, 0.5f, 10.0f);
	m_rot.set(TO_RADIAN(90.0f), 0.0f, 0.0f);
	m_radius = 1.0f;
	m_rebound_factor = 0.0f;
	m_obj_type = ENEMY1;
	m_attak = false;
	m_target_idx = 0;
}

void Enemy::Move()
{
	m_attak = false;
	float	low_length=1000.0f;
	int		low_idx = 0;
	Vector3 vector_to_target;
	for (int j = 0; j < OBJ_TYPE_MAX; ++j) {
		for (auto itr = m_target.begin(); itr != m_target.end(); ++itr) {
			vector_to_target = itr->second->GetPos() - m_pos;
			if (vector_to_target.GetLength() > low_length)	continue;
			low_length = vector_to_target.GetLength();
			low_idx = itr->first;

			if (low_length > SEARCH_RANGE)	return;
			m_attak = true;
			vector_to_target = itr->second->GetPos() - m_pos;
		}
	}
	m_rot.y = atan2f(vector_to_target.x, vector_to_target.z);
	m_rot.x = atan2f(vector_to_target.y, vector_to_target.x);
	m_rot.z = atan2f(vector_to_target.y, vector_to_target.z);

}

void Enemy::Attak()
{
}

void Enemy::Draw()
{
	Vector3 m_pos1;
	m_pos1.x = m_pos.x + 100.0f * sinf(m_rot.y);
	m_pos1.z = m_pos.z + 100.0f * cosf(m_rot.y);
	m_pos1.y = m_pos.y + 100.0f * sinf(m_rot.x);

	DrawLine3D(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_pos1.x, m_pos1.y, m_pos1.z), GetColor(255, 0, 255));
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), m_radius, 64, GetColor(0, 255, 255), GetColor(0, 255, 255), true);
}

void Enemy::Exit()
{
}
