#include "Start.h"

Start::Start() :
	BuildingBase()
{
}

Start::~Start()
{
}

void Start::SetBuil()
{
	m_pos1.set(m_pos.x - 5.0f, m_pos.y, m_pos.z - 5.0f);
	m_pos2.set(m_pos.x + 5.0f, m_pos.y + 10.0f, m_pos.z + 5.0f);
	m_color = GetColor(255, 255, 255);
}
