#include "Wall1.h"

void Wall1::SetBuil()
{
	m_pos1.set(m_pos.x - MAP_SIZE / 2, m_pos.y, m_pos.z - MAP_SIZE / 2);
	m_pos2.set(m_pos.x + MAP_SIZE / 2, m_pos.y + 1.0f, m_pos.z + MAP_SIZE / 2);
	m_color = GetColor(255, 0, 0);
}

Wall1::Wall1() :
	BuildingBase()
{
}

