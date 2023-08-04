#include "Player.h"
#include"sstream"

void Player::SetChar()
{
	m_pos.set(15.0f, 20.0f, 15.0f);
	m_rot.set(0.0f, 0.0f, 0.0f);
	m_radius = 1.0f;
	m_pad.SetJoyPad(DX_INPUT_PAD1);
	m_wierl.Init(this);
	m_wierr.Init(this);
	m_wier_rotl.set(0, 0, 0);
	m_wier_rotr.set(0, 0, 0);
	m_rebound_factor = 0.0f;
	m_obj_type = PLAYER;
	camera.Init();
	spher.Set(this, m_target);
	m_angle_graph = LoadGraph("data/angle_meter.png");
	m_angle_graph2 = LoadGraph("data/angle_graph.png");
	
}

void Player::Move()
{
	

	Vector3 vectl;
	Vector3 vectr;
	

	if (m_pad.Botan(PAD_INPUT_6)) {
		m_wierr.Delete();
	}
	if (m_pad.Botan(PAD_INPUT_5)) {
		m_wierl.Delete();
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		m_pos.y += 0.1f;
	}

	if (CheckHitKey(KEY_INPUT_T)) {
		m_pos.z += 0.5f;
	}if (CheckHitKey(KEY_INPUT_G)) {
		m_pos.z -= 0.5f;
	}if (CheckHitKey(KEY_INPUT_F)) {
		m_pos.x += 0.5f;
	}if (CheckHitKey(KEY_INPUT_H)) {
		m_pos.x -= 0.5f;
	}
	if (CheckHitKey(KEY_INPUT_Q)) {
		m_pos.y -= 0.1f;
	}
	if (CheckHitKey(KEY_INPUT_R)) {
		m_rot.y += TO_RADIAN(10.0f);
	}
	if (CheckHitKey(KEY_INPUT_C)) {
		m_rot.x += TO_RADIAN(10.0f);
	}
	if (IsKeyOn(KEY_INPUT_W)) {
		vectl.set(-10, 0, 10);
		m_wierl.Set(this, vectl);
	}
	if (IsKeyOn(KEY_INPUT_UP)) {
		vectr.set(10, 0, 10);
		m_wierr.Set(this, vectr);
	}
	if (IsKeyRepeat(KEY_INPUT_Z)) {
		m_vect += m_wierl.CreateVect();
	}
	if (IsKeyRepeat(KEY_INPUT_DOWN)) {
		m_vect += m_wierr.CreateVect();
	}
	if (IsKeyRepeat(KEY_INPUT_X)) {
		m_wierl.Delete();
	}
	if (IsKeyRepeat(KEY_INPUT_RIGHT)) {
		m_wierr.Delete();
	}

	m_wierl.UpDate(this);
	m_wierr.UpDate(this);

	m_pos += m_vect;
	if (m_pad.Botan(PAD_INPUT_DOWN) && m_pad.GetLStick().GetLength() < 100.0f) {
		if (m_pad.GetRStick().GetLength() > 100.0f) {
			Vector3 vec = m_pad.GetRStick();
			m_rot.y += TO_RADIAN(vec.x / 100);
			m_rot.x += TO_RADIAN(vec.z / 100);
		}
		return;
	}

	if (m_pad.Botan(PAD_INPUT_8) || m_pad.RTorigger() >= 50) {

		m_vect += m_wierr.CreateVect();
	}
	if (m_pad.Botan(PAD_INPUT_7) || m_pad.LTorigger() >= 50) {
		m_vect += m_wierl.CreateVect();
	}

	if (m_pad.GetLStick().GetLength() > 100.0f) {
		if (m_pad.GetLStick().x < 0.0f) {
			vectl = m_pad.GetLStick();
			m_wier_rotl.y = atan2f(-vectl.z, vectl.x) + m_rot.y + TO_RADIAN(90.0f);
			m_wierl.Set(this, m_wier_rotl);
		}
		else if (m_pad.GetLStick().x > 0.0f) {
			vectl = m_pad.GetLStick();
			m_wier_rotl.x = atan2f(vectl.z, vectl.x);

		}
	}
	if (m_pad.GetRStick().GetLength() > 100.0f) {
		if (m_pad.GetRStick().x > 0.0f) {
			vectr = m_pad.GetRStick();
			m_wier_rotr.y = atan2f(-vectr.z, vectr.x) + m_rot.y + TO_RADIAN(90.0f);
			m_wierr.Set(this, m_wier_rotr);
		}
		else if (m_pad.GetRStick().x < 0.0f) {
			vectr = m_pad.GetRStick();
			m_wier_rotr.x = atan2f(vectr.z, -vectr.x);
		}
	}
	m_target.size();
	spher.UpDate(this, m_target);
}
#ifdef false



void Player::Attak()
{
	if (m_bullet_sample == nullptr) {
		m_bullet_sample = new AssaultRifle;
	}
	for (int i = 0; i < m_bullet.size(); ++i) {
		if (m_bullet[i] == nullptr)
			continue;
		m_bullet[i]->Move();
	}
	m_bullet_sample->Move();

	if (m_pad.Botan(PAD_INPUT_3)) {
		m_bullet_sample->Reload();
		return;
	}

	if (!m_pad.Botan(PAD_INPUT_DOWN))	return;

	if (!m_pad.Botan(PAD_INPUT_8) && m_pad.RTorigger() <= 50)
		return;


	if (m_bullet_sample->GetReLoade())
		return;
	//if (m_bullet_sample->GetShootNum() > m_bullet_sample->GetMagazineSize())
	//	return;

	Vector3 cross_sphere(WINDOW_W / 2, WINDOW_H / 2, 0.0f);
	Vector3 shoot_pos = GetCamera3DPos(cross_sphere);
	Vector3 shoot_vect = shoot_pos - camera.GetPos();
	if (m_bullet_sample->GetTime() % m_bullet_sample->GetRateOfFire() == 0) {
		for (int i = 0; i < m_bullet.size(); ++i) {
			if (m_bullet[i] == nullptr) {
				m_bullet[i] = new AssaultRifle;
			}
			if (m_bullet[i]->GetDe()) continue;
			m_bullet[i]->Init();
			m_bullet[i]->SetTarget(&m_target);
			m_bullet[i]->Set(shoot_pos, shoot_vect,m_vect);
			m_bullet_sample->Set(this);
			m_bullet_sample->AddSootNum();
			m_bullet.emplace_back(nullptr);
			break;
		}
	}
	m_bullet_sample->Delete();
}
#endif

void Player::Draw()
{
	
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), m_radius, 64, GetColor(255, 255, 255), GetColor(255, 255, 255), true);
	m_wierl.Draw(this);
	m_wierr.Draw(this);
	DrawRotaGraph(380, 450, 2.0,0.0f, m_angle_graph2,true);
	DrawRotaGraph(380, 450, 0.7, m_wier_rotl.x, m_angle_graph,true);
	float angle_r = m_wier_rotr.x * -1.0f + TO_RADIAN(180.0f);
	DrawRotaGraph(580, 450,2.0f, TO_RADIAN(180.0f), m_angle_graph2,true);
	DrawRotaGraph(580, 450, 0.7, angle_r, m_angle_graph,true);
	
}

void Player::Exit()
{
}
