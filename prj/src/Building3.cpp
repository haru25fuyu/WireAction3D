#include "Building3.h"

Building3::Building3() :
	BuildingBase()
{

}

void Building3::SetBuil()
{
	m_model = MV1LoadModel("data/buil_model/buil3.mqoz");
	m_pos1.set(m_pos.x - 70.0f, m_pos.y, m_pos.z - 70.0f);
	m_pos2.set(m_pos.x + 70.0f, m_pos.y + 330.0f, m_pos.z + 70.0f);
	m_color = GetColor(255, 0, 0);
}