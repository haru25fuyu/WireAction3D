#include "Tutorial.h"
#include"Main.h"

void Tutorial::Init()
{
	m_char.Init();
	m_controller_image[0]=LoadGraph("data/game_pad1.png");
	m_controller_image[1] = LoadGraph("data/game_pad2.png");

	m_description_panel = LoadGraph("data/description.png");

	m_circle = LoadGraph("data/circle.png");
	m_arrow = LoadGraph("data/arrow.png");
	m_check_botan = LoadGraph("data/check_botan.png");
	m_check[0] = false;
	m_check[1] = false;
	m_pad.SetJoyPad();
	m_camera.Init();
	m_page = SHOT_WIER;
	m_text[0] = "スティックを外側に倒すと、\n倒した方向にワイヤーを射出する";
	m_text[1] = "トリガーボタンを押すと、\nワイヤーでの機動が出来る";
	m_text[2] = "R,Lボタンを押すと、\nワイヤーがはずれまた射出出来る";
	m_text[3] = "スティックを内側に倒すと、\nワイヤーの射出の縦角度を設定できる";
	m_text[4] = "下ボタンを押しつつ右スティックで、\n方向転換出来る";
}

int Tutorial::Update()
{
	m_char.Update();
	m_camera.Update(&m_char);
	switch (m_page)
	{
	case SHOT_WIER:
		if (m_pad.GetLStick().GetLength() > 100.0f) {
			if (m_pad.GetLStick().x < 0.0f) {
				m_check[0] = true;
			}
		}
		if (m_pad.GetRStick().GetLength() > 100.0f) {
			if (m_pad.GetRStick().x > 0.0f) {
				m_check[1] = true;
			}
		}
		if (m_check[0] && m_check[1]) {
			m_check[0] = false;
			m_check[1] = false;
			m_page = MOVE_WIER;
		}
		break;
	case MOVE_WIER:
		if (m_pad.Botan(PAD_INPUT_8) || m_pad.RTorigger() >= 50) {
			m_check[0] = true;
		}
		if (m_pad.Botan(PAD_INPUT_7) || m_pad.LTorigger() >= 50) {
			m_check[1] = true;
		}
		if (m_check[0] && m_check[1]) {
			m_check[0] = false;
			m_check[1] = false;
			m_page = REMOVE_WIER;
		}
		break;
	case REMOVE_WIER:
		if (m_pad.Botan(PAD_INPUT_5)) {
			m_check[0] = true;
		}
		if (m_pad.Botan(PAD_INPUT_6)) {
			m_check[1] = true;
		}
		if (m_check[0] && m_check[1]) {
			m_check[0] = false;
			m_check[1] = false;
			m_page = SET_WIER;
		}
		break;
	case SET_WIER:
		if (m_pad.GetLStick().GetLength() > 100.0f) {
			if (m_pad.GetLStick().x > 0.0f) {
				m_check[0] = true;
			}
		}
		if (m_pad.GetRStick().GetLength() > 100.0f) {
			if (m_pad.GetRStick().x < 0.0f) {
				m_check[1] = true;
			}
		}
		if (m_check[0] && m_check[1]) {
			m_check[0] = false;
			m_check[1] = false;
			m_page = CAMERA_ROTA;
		}
		break;
	case CAMERA_ROTA:
		if (m_pad.Botan(PAD_INPUT_DOWN) && m_pad.GetLStick().GetLength() < 100.0f) {
			m_check[0] = true;
		}
		if (m_check[0]) {
			m_check[0] = false;
			m_page = FREE;
		}
		break;
	case FREE:
		break;
	default:
		break;
	}
	if (IsKeyOn(KEY_INPUT_RETURN)) {
		m_page++;
	}
	m_page %= FREE;
	return TUTORIAL;
}

void Tutorial::Draw()
{
	m_camera.Render();
	m_char.Draw();
	DrawRotaGraph(750, 150, 0.9, 0.0f, m_description_panel, true);
	SetFontSize(20);
	switch (m_page)
	{
	case SHOT_WIER:
		DrawRotaGraph(750, 320, 0.9, 0.0f, m_controller_image[0], true);
		DrawRotaGraph(675, 308, 0.2, 0.0f, m_circle, true);
		DrawRotaGraph(655, 300, 0.1, TO_RADIAN(270.0f), m_arrow, true);
		DrawRotaGraph(779, 353, 0.2, 0.0f, m_circle, true);
		DrawRotaGraph(795, 350, 0.1, TO_RADIAN(90.0f), m_arrow, true);
		DrawString(575, 105, m_text[SHOT_WIER].c_str(), GetColor(255, 255, 255));
		break;
	case MOVE_WIER:
		DrawRotaGraph(750, 320, 0.5, 0.0f, m_controller_image[1], true);
		DrawRotaGraph(670, 270, 0.3, TO_RADIAN(90.0f), m_check_botan, true);
		DrawRotaGraph(845, 270, 0.3, TO_RADIAN(90.0f), m_check_botan, true);
		DrawString(575, 105, m_text[MOVE_WIER].c_str(), GetColor(255, 255, 255));
		break;
	case REMOVE_WIER:
		DrawRotaGraph(750, 320, 0.5, 0.0f, m_controller_image[1], true);
		DrawRotaGraph(675, 300, 0.3, 0.0f, m_check_botan, true);
		DrawRotaGraph(840, 300, 0.3, 0.0f, m_check_botan, true);
		DrawString(575, 105, m_text[REMOVE_WIER].c_str(), GetColor(255, 255, 255));
		break;
	case SET_WIER:
		DrawRotaGraph(750, 320, 0.9, 0.0f, m_controller_image[0], true);
		DrawRotaGraph(779, 353, 0.2, 0.0f, m_circle, true);
		DrawRotaGraph(675, 308, 0.2, 0.0f, m_circle, true);
		DrawRotaGraph(690, 305, 0.1, TO_RADIAN(90.0f), m_arrow, true);
		DrawRotaGraph(760, 345, 0.1, TO_RADIAN(270.0f), m_arrow, true);
		DrawString(575, 105, m_text[SET_WIER].c_str(), GetColor(255, 255, 255));
		break;
	case CAMERA_ROTA:
		DrawRotaGraph(750, 320, 0.9, 0.0f, m_controller_image[0], true);
		DrawRotaGraph(779, 353, 0.2, 0.0f, m_circle, true);
		DrawRotaGraph(710, 357, 0.2, TO_RADIAN(90.0f), m_check_botan, true);
		DrawString(575, 105, m_text[CAMERA_ROTA].c_str(), GetColor(255, 255, 255));
		break;
	case FREE:
		break;
	default:
		break;
	}
	
	
}

void Tutorial::Exit()
{
}
