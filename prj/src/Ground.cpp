#include "WinMain.h"
#include "GameMain.h"
#include "Ground.h"
#include"CharBase.h"
#include"Hit.h"


//std::vector<bool>* Ground::GetNav()
//{
//	return &m_nav;
//}

//void Ground::SetNav()
//{
//	for (size_t i = 0;i < MAP_SIZE * MAP_SIZE;++i) {
//		Vector3 pos;
//		pos.set((float)(i % MAP_SIZE), 0,(float)( i / MAP_SIZE));
//		m_nav.resize(i + 1);
//		for (size_t j = 0;j < buil.size();j++) {
//			if (buil[j] == nullptr)	continue;
//			Vector3 Pos1 = buil[j]->GetPos1();
//			Vector3 Pos2 = buil[j]->GetPos2();
//			m_nav[i] = true;
//			if (!ChackCubeShperHit(Pos1, Pos2, pos, 0.1f))	continue;
//			m_nav[i] = false;
//			break;
//		}
//	}
//
//}


//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void Ground::Init()
{
	m_pos.clear();
	m_pos.set(40, 0, 40);
	m_rot.clear();
	m_model = MV1LoadModel("data/Ground.x");
	//SetNav();
}
//---------------------------------------------------------------------------------
//	XVˆ—
//---------------------------------------------------------------------------------
void Ground::Update(Base* char_)
{
	
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void Ground::Render()
{
	
	for (int i = 0; i < 400; ++i) {
		MV1SetPosition(m_model, VGet(m_pos.x+(80*(i%20)), m_pos.y, m_pos.z+(80*(i/20))));
		MV1SetRotationXYZ(m_model, VGet(m_rot.x, m_rot.y, m_rot.z));
		MV1DrawModel(m_model);
	}
	
	DrawLine3D( VGet( -40.0f, 0.0f,   0.0f ), VGet( 40.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	DrawLine3D( VGet(   0.0f, 0.0f, -40.0f ), VGet(  0.0f, 0.0f, 40.0f ), GetColor(   0, 0, 255 ) );
	
}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void Ground::Exit()
{
}
