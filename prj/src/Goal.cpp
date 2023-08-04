#include "Goal.h"
#include "Hit.h"
#include"WinMain.h"

Goal::Goal() :
	Base()
{
	m_goal = false;
	m_size = Vector3(100.0f, 600.0f, 100.0f);
}

void Goal::SetPos(Vector3& pos)
{
	m_pos = pos;
	m_pos.y = 0.0f;
	m_pos1 = pos-m_size;
	m_pos1.y = 0.0f;
	m_pos2 = pos+m_size;
	m_cube = MakeCubeTowPos(m_pos1, m_pos2);
	m_model = MV1LoadModel("data/buil_model/goal.mqoz");
}

Cube Goal::GetHitCube()
{
	return m_cube;
}


bool Goal::GetGoal()
{
	return m_goal;
}

void Goal::Init(Vector3& pos)
{
	SetPos(pos);
}

void Goal::UpDete(Base& char_)
{
	Spher spher;
	spher.pos = char_.GetPos();
	spher.radius = char_.GetRadius();
	if (ChackCubeShperHit(m_cube, spher)) {
		m_goal = true;
	}
}

void Goal::Draw()
{
	MV1SetPosition(m_model, m_pos.VGet());
	MV1DrawModel(m_model);
	DrawCube3D(m_pos1.VGet(), m_pos2.VGet(), GetColor(0, 0, 0), GetColor(255, 255, 255),false);
}

void Goal::Exit()
{
}
