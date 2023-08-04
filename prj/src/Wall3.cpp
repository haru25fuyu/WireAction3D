#include "Wall3.h"

void Wall3::SetBuil()
{
	m_pos1.set(m_pos.x - 0.5f, m_pos.y, m_pos.z - MAP_SIZE/2);
	m_pos2.set(m_pos.x + 0.5f, m_pos.y+800.0f, m_pos.z + MAP_SIZE/2);
	m_color = GetColor(0, 0, 255);
}

Wall3::Wall3() :
	BuildingBase()
{
}
