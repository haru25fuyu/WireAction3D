#include "Building2.h"

Building2::Building2() :
	BuildingBase()
{

}
void Building2::SetBuil()
{
	m_model = MV1LoadModel("data/buil_model/buil2.mqoz");
	m_pos1.set(m_pos.x - 120.0f, m_pos.y, m_pos.z - 50.0f);
	m_pos2.set(m_pos.x + 120.0f, m_pos.y + 150.0f, m_pos.z + 50.0f);
	m_color = GetColor(255, 0, 0);
}