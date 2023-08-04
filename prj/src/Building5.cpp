#include "Building5.h"

Building5::Building5() :
	BuildingBase()
{

}

void Building5::SetBuil()
{
	m_model = MV1LoadModel("data/buil_model/buil5.mqoz");
	m_pos1.set(m_pos.x - 70.0f, m_pos.y, m_pos.z - 70.0f);
	m_pos2.set(m_pos.x + 70.0f, m_pos.y + 200.0f, m_pos.z + 70.0f);
	m_color = GetColor(255, 0, 0);
}
