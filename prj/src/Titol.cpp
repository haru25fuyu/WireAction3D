#include "Titol.h"
#include "WinMain.h"
#include"Hit.h"
#include<string>

Titol::Titol() :
	SeenBase()
{
	m_back_image = -1;
	m_titol_image = -1;
	for (int i = 0;i < BOTAN_NUM;++i) {
		m_botan_image[i] = -1;
	}
}

void Titol::Init()
{
	m_pad.SetJoyPad();
	m_back_image = LoadGraph("");
	m_titol_image = LoadGraph("");
	for (int i = 0;i < BOTAN_NUM;++i) {
		char text[30];
		sprintf_s(text, "data/titol_botan%d.png", i + 1);
		m_botan_image[i] = LoadGraph(text);
	}

	for (int i = 0; i < BOTAN_NUM; ++i) {
		m_botan_pos[i].set(245.0f + +(i / 2) * (BOTAN_SIZE_W + 150.0f), 300.0f + (i % 2) * (BOTAN_SIZE_H + 50.0f), 0.0f);
		Vector3 botan_pos2 = m_botan_pos[i];
		botan_pos2.x += BOTAN_SIZE_W;
		botan_pos2.y += BOTAN_SIZE_H;
		m_botan_hit_box[i] = MakeBoxTowPos(m_botan_pos[i], botan_pos2);
	}
	num = MakeKeyInput(10, false, false, false);
	SetActiveKeyInput(num);
	m_next_seen = TITOL;
	m_select_num = 0;
	m_page = 0;
	for (int i = 0;i < 4;++i) {
		m_old_direction[i] = true;
	}
	m_old_botan = true;
	
}

int Titol::Update()
{

	//マウス座標取得
	Vector3 mouse_pos;
	mouse_pos.x = (float)GetMouseX();
	mouse_pos.y = (float)GetMouseY();
	mouse_pos.z = 0.0f;

	//ボタンをクリックした時の反応
	for (int i = 0; i < BOTAN_NUM; ++i) {
		m_botan_pos[i] = m_botan_hit_box[i].vertex_pos[0];
		m_botan_display[i] = true;
		if (m_page == 1)
			continue;
		if (ChaekHitPointBox(mouse_pos, m_botan_hit_box[i])) {
			m_select_num = i;
			if (!GetMouseInput())
				continue;
			m_next_seen = i + 1;
			m_time = 60;
		}

	}
	bool direction[4] = {
		m_pad.Botan(PAD_INPUT_UP),m_pad.Botan(PAD_INPUT_DOWN),
		m_pad.Botan(PAD_INPUT_RIGHT),m_pad.Botan(PAD_INPUT_LEFT)
	};

	if ((direction[0] || IsKeyOn(KEY_INPUT_UP)) && !m_old_direction[0]) {
		m_select_num--;
	}
	
	if ((direction[1] || IsKeyOn(KEY_INPUT_DOWN)) && !m_old_direction[1]) {
		m_select_num++;
	}
	
	if ((direction[2] || IsKeyOn(KEY_INPUT_RIGHT)) && !m_old_direction[2]) {
		m_select_num += 2;
	}
	
	if ((direction[3] || IsKeyOn(KEY_INPUT_LEFT)) && !m_old_direction[3]) {
		m_select_num -= 2;
	}
	
	
	for(int i=0;i<4;++i){
		m_old_direction[i] = direction[i];
	}

	m_select_num %= 4;

	m_botan_pos[m_select_num].x -= 5.0f;
	m_botan_pos[m_select_num].y -= 5.0f;

	bool botan = m_pad.Botan(PAD_INPUT_1);
	if (IsKeyOn(KEY_INPUT_RETURN) ||
		botan && !m_old_botan) {
		m_next_seen = m_select_num+1;
		m_time = 60;
	}
	m_old_botan = botan;
	
	if (m_page == 1) {
		if (IsKeyOn(KEY_INPUT_RETURN) ||
			m_pad.Botan(PAD_INPUT_1)) {
			m_next_seen = GAME;
			m_time = 60;
		}
	}

	//選択されたら点滅して時間になったら画面遷移する
	if (m_time > 0) {
		m_botan_pos[m_next_seen - 1].x -= 5.0f;
		m_botan_pos[m_next_seen - 1].y -= 5.0f;
		if (m_time % 10 < 5)
			m_botan_display[m_next_seen - 1] = false;
	}
	else {
		if constexpr (false) {
			if (m_next_seen == GAME && m_page != 1) {
				m_select_num = TITOL;
				m_next_seen = TITOL;
				m_page = 1;
				return TITOL;
			}
		}
		return m_next_seen;
	}

	

	m_time--;
	return TITOL;
}

void Titol::Draw()
{
	if (m_page == 1) {
		std::string str;

		DrawKeyInputModeString(0, 10);
		DrawKeyInputString(100, 10, num);


		if (CheckKeyInput(num) != 0) {
			GetKeyInputString(text, num);
			DeleteKeyInput(num);
			str = text;
			DrawString(30, 20, str.c_str(), GetColor(255, 255, 255));
		}
	}
	else {
		for (int i = 0; i < BOTAN_NUM; ++i) {
			DrawBoxAA(m_botan_hit_box[i].vertex_pos[0].x,
				m_botan_hit_box[i].vertex_pos[0].y, 
				m_botan_hit_box[i].vertex_pos[2].x,
				m_botan_hit_box[i].vertex_pos[2].y,
				GetColor(0, 0, 0), true);
			if (m_botan_display[i]) {
				DrawGraph(m_botan_pos[i].x, m_botan_pos[i].y, m_botan_image[i], true);
			}
		}

		DrawGraph(0, 0, m_back_image, true);
		DrawGraph(0, 0, m_titol_image, true);
	}
}

void Titol::Exit()
{
}
