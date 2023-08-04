#include "Building1.h"

Building1::Building1() :
	BuildingBase()
{

}

void Building1::SetBuil()
{
	m_model = MV1LoadModel("data/buil_model/buil1.mqoz");
	m_pos1.set(m_pos.x - 50.0f, m_pos.y, m_pos.z - 50.0f);
	m_pos2.set(m_pos.x + 50.0f, m_pos.y+150.0f, m_pos.z + 50.0f);
	m_color = GetColor(255, 0, 0);
}
