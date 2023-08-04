#include "Building4.h"

Building4::Building4() :
	BuildingBase()
{

}

void Building4::SetBuil()
{
	m_model = MV1LoadModel("data/buil_model/buil4.mqoz");
	m_pos1.set(m_pos.x - 50.0f, m_pos.y, m_pos.z - 100.0f);
	m_pos2.set(m_pos.x + 50.0f, m_pos.y + 150.0f, m_pos.z + 100.0f);
	m_color = GetColor(255, 0, 0);
}
