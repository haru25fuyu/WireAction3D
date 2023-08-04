#include "AssaultRifle.h"

void AssaultRifle::SetType()
{
	m_speed = 10.0f;
	m_tracking = true;
	m_rate_of_fire = 6;
	m_reload_time = 60 * 3;
	m_magazine_size = 30;
	m_tracking_performance = TO_RADIAN(10.0f);
	m_magnitude_of_recoil = 10.0f;
}
