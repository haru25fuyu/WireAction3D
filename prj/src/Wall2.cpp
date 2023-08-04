#include "Wall2.h"

void Wall2::SetBuil()
{
	m_pos1.set(m_pos.x - MAP_SIZE/2, m_pos.y, m_pos.z - 0.5f);
	m_pos2.set(m_pos.x + MAP_SIZE/2, m_pos.y+800.0f, m_pos.z + 0.5f);
	m_color = GetColor(0, 255, 0);
}

Wall2::Wall2():
	BuildingBase()
{
}
