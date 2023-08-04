#include "MapMake.h"
#include <fstream>
#include <string>
#include <sstream>
#include"Building1.h"
#include"Building2.h"
#include"Building3.h"
#include"Building4.h"
#include"Building5.h"
#include "Hit.h"
using namespace std;

MapMake::MapMake()
{
	m_map_num = 0;
	m_buil.clear();
	for (int i = 0; i < PANEL_NUM; ++i) {
		m_Buil_select_panel[i] = -1;
		m_panel_pos[i].clear();
	}
	m_select = false;
	m_buil_idx = -1;
	m_time = 0;
	m_open_menu = false;
}

void MapMake::DeleteBuil(size_t idx)
{
	if (m_buil.size() <= 1) {
		delete(m_buil[0]);
		m_buil[0] = nullptr;
		m_buil.clear();
		m_type.clear();
		m_pos.clear();
		m_select = false;
		m_buil_idx = -1;
		return;
	}
	size_t size = m_buil.size();
	for (size_t i = idx; i < m_buil.size() - 1; ++i) {
		m_buil[i] = nullptr;
		m_type[i] = m_type[i + 1];
		m_pos[i] = m_pos[i + 1];
		SetBuil(i);
	}
	delete(m_buil[size - 1]);
	m_buil[size - 1] = nullptr;
	m_buil.resize(size - 1);
	m_type.resize(size - 1);
	m_pos.resize(size - 1);
	m_select = false;
	m_buil_idx = -1;
}

void MapMake::OpenMap(int map_num)
{
	m_pos.clear();
	m_type.clear();
	m_buil.clear();
	if (m_start != nullptr)
		delete m_start;
	if (m_goal != nullptr)
		delete m_goal;
	m_start = nullptr;
	m_goal = nullptr;

	fstream	file;
	char file_name[50];
	sprintf_s(file_name, "data/map/map%d.txt", map_num);
	file.open(file_name, ios::in);
	if (!file.is_open())
		return;
	//ゴールの情報取得
	for (size_t i = 0; i < START_GOAL; ++i) {
		string sg_str;
		stringstream sg_sstr;
		getline(file, sg_str);
		if (file.eof())
			return;
		
		m_type.resize(i + 1);
		m_pos.resize(i + 1);
		sg_sstr << sg_str;
		sg_sstr >> m_type[i] >> m_pos[i].x >> m_pos[i].y >> m_pos[i].z;

	}
	m_start = new Start;
	m_start->SetPos(m_pos[0]);
	m_goal = new Goal;
	m_goal->Init(m_pos[1]);

	//建物の情報取得
	size_t i = 0;
	do
	{
		string	str;
		getline(file, str);
		if (file.eof())
			break;
		stringstream sstr;
		sstr << str;
		m_type.resize(i + 1);
		m_pos.resize(i + 1);
		sstr >> m_type[i] >> m_pos[i].x >> m_pos[i].y >> m_pos[i].z;
		++i;
	} while (!file.eof());
	file.close();
}

void MapMake::SeveMap()
{

	fstream	file;
	char file_name[50];
	if (m_goal == nullptr || m_start == nullptr) {
		m_seve = false;
		m_time = 2 * 60;
		return;
	}
	sprintf_s(file_name, "data/map/map%d.txt", m_map_num);
	file.open(file_name, ios::out);
	if (!file.is_open())
		return;
	file << 5 << " " << m_start->GetPos().x << " " << m_start->GetPos().y << " " << m_start->GetPos().z << endl;
	file << 6 << " " << m_goal->GetPos().x << " " << m_goal->GetPos().y << " " << m_goal->GetPos().z << endl;
	for (size_t i = 0; i < m_buil.size(); ++i) {
		file << m_type[i] << " "
			<< m_buil[i]->GetPos().x << " " << m_buil[i]->GetPos().y << " " << m_buil[i]->GetPos().z
			<< "\n";
	}
	file.close();
}

void MapMake::SetBuil(size_t idx)
{
	if (m_type[idx] == 5)
		return;
	if (m_buil[idx] != nullptr)
		return;

	switch (m_type[idx])
	{
	case 0:
		m_buil[idx] = new Building1;
		break;
	case 1:
		m_buil[idx] = new Building2;
		break;
	case 2:
		m_buil[idx] = new Building3;
		break;
	case 3:
		m_buil[idx] = new Building4;
		break;
	case 4:
		m_buil[idx] = new Building5;
		break;
	default:
		break;
	}
	m_buil[idx]->Init(m_pos[idx]);
}

Line line2;

void MapMake::Init()
{
	m_buil.clear();
	m_pos.clear();
	m_type.clear();
	m_map_num = 0;
	OpenMap(m_map_num);
	for (int i = 0; i < PANEL_NUM; ++i) {
		m_panel_pos[i] = Vector3(10.0f + i * (SELECT_PANEL_SIZE + 10.0f), 10.0f, 0.0f);
		m_panel_pos2[i] = m_panel_pos[i] + SELECT_PANEL_SIZE;
		m_hit_box[i] = MakeBoxTowPos(m_panel_pos[i], m_panel_pos2[i]);
	}
	for (size_t i = 0; i < m_type.size(); ++i) {
		m_buil.emplace_back();
		SetBuil(i);
	}
	m_camera.Init();
	m_hamburger_icon_image = LoadGraph("data/3line.png");
	m_triangle_image = LoadGraph("data/traiangle.png");
	m_cross_image = LoadGraph("data/batu.png");
	m_botan1_image = LoadGraph("data/map_make_botan1.png");
	m_botan2_image = LoadGraph("data/map_make_botan2.png");
	m_ground = MV1LoadModel("data/Ground.x");
	line2.s_pos.set(0.0f, 5.0f, 1.0f);
	line2.g_pos.set(1.0f, 3.0f, 5.0f);
	m_time = 0;
	m_select_map_num = 0;
	m_select_start = false;
	m_select_goal = false;
	m_open_menu = false;
	m_check_cross = false;
}

int MapMake::Update()
{
	m_time--;
	//マウス座標取得
	Vector3 mouse_pos;
	mouse_pos.x = (float)GetMouseX();
	mouse_pos.y = (float)GetMouseY();
	mouse_pos.z = 0.0f;

	m_camera.Update();

	//メニュー内処理
	if(m_open_menu){
		Vector3 pos1(550.0f, 100.0f, 0.0f);
		Vector3 pos2(650.0f, 200.0f, 0.0f);
		Box right_triangle = MakeBoxTowPos(pos1, pos2);
		if (IsKeyOn(KEY_INPUT_RIGHT) ||
			(IsMouseOn(1) && ChaekHitPointBox(mouse_pos, right_triangle))) {
			m_select_map_num++;
		}
		pos1.set(300.0f, 100.0f, 0.0f);
		pos2.set(400.0f, 200.0f, 0.0f);
		Box left_triangle = MakeBoxTowPos(pos1, pos2);
		if (IsKeyOn(KEY_INPUT_RIGHT) ||
			(IsMouseOn(1) && ChaekHitPointBox(mouse_pos, left_triangle))) {
			m_select_map_num--;
		}

		m_select_map_num %= MAP_MAX + 1;
		pos1.set(735.0f, 65.0f, 0.0f);
		pos2.set(785.0f, 115.0f, 0.0f);
		Box cross = MakeBoxTowPos(pos1, pos2);
		if(IsMouseOn(1) && ChaekHitPointBox(mouse_pos, cross)){
			if (m_map_num != m_select_map_num) {
				SeveMap();
				m_map_num = m_select_map_num;
				OpenMap(m_map_num);
			}
			m_check_cross = true;
			m_time = 60;
		}

		if (m_time < 0 && m_open_menu && m_check_cross) {
			m_check_cross = false;
			m_open_menu = false;
		}

		pos1.set(400.0f, 250.0f, 0.0f);
		pos2.set(pos1.x + MENU_BOTAN_W, pos1.y + MENU_BOTAN_H, 0.0f);
		Box botan = MakeBoxTowPos(pos1, pos2);
		if (IsMouseOn(1) && ChaekHitPointBox(mouse_pos, botan)) {
			SeveMap();
			fstream file;
			char text[50];
			sprintf_s(text, "data/map/map%d.txt", MAP_MAX + 1);
			file.open(text, ios::out);
			if (file.is_open()) {
				MAP_MAX++;
				m_select_map_num = MAP_MAX;
			}
			file.close();
		}

		pos1.set(400.0f, 360.0f, 0.0f);
		pos2.set(pos1.x + MENU_BOTAN_W, pos1.y + MENU_BOTAN_H, 0.0f);
		botan = MakeBoxTowPos(pos1, pos2);
		if (IsMouseOn(1) && ChaekHitPointBox(mouse_pos, botan)) {
			return TITOL;
		}
	}


	if (m_open_menu) {

		return MAPMAKE;
	}
	//メニューを開く
	{
		Vector3 pos1(WINDOW_W - HAMBURGER_ICON_SIZE, 0.0f, 0.0f);
		Vector3 pos2(WINDOW_W, HAMBURGER_ICON_SIZE, 0.0f);
		Box box_hanberger = MakeBoxTowPos(pos1, pos2);
		if (GetMouseInput() && ChaekHitPointBox(mouse_pos, box_hanberger) &&
			!m_select && !m_select_start && !m_select_goal) {
			m_open_menu = true;
		}
	}

	//エンターキーで
	if (IsKeyOn(KEY_INPUT_SPACE))
		return TITOL;

	if (IsKeyOn(KEY_INPUT_RETURN))
		SeveMap();

	//マウス座標を３Ｄ座標に変換
	Vector3 mouse_pos3D(GetCamera3DPos(mouse_pos));
	Vector3 mouse_vect = mouse_pos3D - m_camera.GetPos();
	mouse_vect.SetLength(1000.0f);

	//当たり判定のために構造体に変換
	Line line;
	line.s_pos = m_camera.GetPos();
	line.g_pos = mouse_pos3D + (mouse_vect);


	//床のも矩形の構造体にする
	Vector3 pos[2];
	pos[0] = Vector3(0.0f, 0.0f, 0.0f);
	pos[1] = Vector3(MAP_SIZE, 0.0f, MAP_SIZE);
	Box floor = MakeBoxTowPos(pos[0], pos[1]);


	//選択した建物を作って表示する
	for (int i = 0; i < PANEL_NUM; ++i) {
		if (ChaekHitPointBox(mouse_pos, m_hit_box[i]) &&
			GetMouseInput() && !m_select && !m_select_goal) {
			if (i == 5) {
				m_start = new Start;
				m_start->Init(mouse_pos3D);
				m_select_start = true;
				break;
			}
			if (i == 6) {
				m_goal = new Goal;
				m_goal->Init(mouse_pos3D);
				m_select_goal = true;
				break;
			}
			m_select = true;
			m_buil.resize(m_buil.size() + 1);
			m_buil_idx = m_buil.size() - 1;
			m_type.resize(m_buil_idx + 1);
			m_pos.resize(m_buil_idx + 1);
			m_type[m_buil_idx] = i;
			SetBuil(m_buil_idx);
			m_pos[m_buil_idx] = mouse_pos3D;
			return MAPMAKE;
		}
	}

	//マウスをクリックしてる間は座標を移動する
	if (m_select && GetMouseInput() && !m_select_goal) {
		if (m_buil[m_buil_idx] != nullptr) {
			m_pos[m_buil_idx] = mouse_pos3D;
			if (CheckHitLineBox(line, floor)) {
				m_pos[m_buil_idx] = GetLineBoxHitPos(line, floor);
			}
			if (IsKeyRepeat(KEY_INPUT_LCONTROL) && IsKeyOn(KEY_INPUT_D))
				DeleteBuil(m_buil_idx);
		}
	}

	//ゴールも同じように
	if (!m_select && GetMouseInput() && m_select_goal) {
		if (m_goal != nullptr) {
			m_goal->SetPos(mouse_pos3D);
			if (CheckHitLineBox(line, floor)) {
				Vector3 pos = GetLineBoxHitPos(line, floor);
				m_goal->SetPos(pos);
			}
		}
	}

	//スタートも
	if (!m_select && GetMouseInput() && !m_select_goal && m_select_start) {
		if (m_start != nullptr) {
			m_start->SetPos(mouse_pos3D);
			if (CheckHitLineBox(line, floor)) {
				Vector3 pos = GetLineBoxHitPos(line, floor);
				m_start->SetPos(pos);
			}
		}
	}

	//出来ている建物を選択
	for (int i = 0; i < m_buil.size(); ++i) {
		if (m_buil[i] == nullptr)
			continue;
		Cube buil = m_buil[i]->GetHitCube();
		if (!CheckHitLineCube(line, buil) || m_select
			|| m_select_goal || m_select_start)
			continue;
		m_select = true;
		m_buil_idx = i;
	}



	//出来ているゴールを選択
	if (GetMouseInput() && !m_select && !m_select_start) {
		if (m_goal != nullptr) {
			Cube buil = m_goal->GetHitCube();
			if (CheckHitLineCube(line, buil) && !m_select) {
				m_select_goal = true;
			}
		}
	}

	//出来ているスタートを選択
	if (GetMouseInput() && !m_select && !m_select_goal) {
		if (m_start != nullptr) {
			Cube buil = m_start->GetHitCube();
			if (CheckHitLineCube(line, buil) && !m_select) {
				m_select_start = true;
			}
		}
	}

	//ビルの座標を posに合わせる
	for (size_t i = 0; i < m_buil.size(); ++i) {
		if (m_buil[i] == nullptr)
			continue;
		m_buil[i]->SetPos(m_pos[i]);
	}

	if (m_time <= 0)
		m_seve = true;

	m_time--;

	//マウスをクリックしてたらここまで
	if (GetMouseInput())
		return MAPMAKE;
	for (int i = 0; i < m_buil.size(); ++i) {
		if (m_buil[i] == nullptr)
			continue;
		Vector3 pos = m_buil[i]->GetPos();
		if (m_buil[i]->GetPos().y == 0.0f)
			continue;
		pos.y = 0.0f;
		m_pos[i] = pos;
	}

	if (m_start != nullptr) {
		Vector3 start_pos = m_start->GetPos();
		if (start_pos.y != 0.0f) {
			m_start->SetPos(start_pos.x, 0.0f, start_pos.z);
			m_start->SetPos(start_pos.x, 0.0f, start_pos.z);
		}
	}

	m_select = false;
	m_select_goal = false;
	m_select_start = false;
	m_buil_idx = -1;
	return MAPMAKE;
}

void MapMake::Draw()
{
	m_camera.Render();
	for (int i = 0; i < 400; ++i) {
		MV1SetPosition(m_ground, VGet((80 * (i % 20)), 0.0f, (80 * (i / 20))));
		MV1DrawModel(m_ground);
	}

	for (int i = 0; i < m_buil.size(); ++i) {
		if (m_buil[i] == nullptr)
			continue;
		//m_buil[i]->Draw();
		Cube cube = m_buil[i]->GetHitCube();
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				DrawLine3D(cube.surface[i].vertex_pos[j].VGet(), cube.surface[i].vertex_pos[(j + 1) % 4].VGet(), GetColor(25, 255, 255));
			}
		}
	}

	if (m_goal != nullptr) {
		//m_goal->Draw();
		Cube cube = m_goal->GetHitCube();
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				DrawLine3D(cube.surface[i].vertex_pos[j].VGet(), cube.surface[i].vertex_pos[(j + 1) % 4].VGet(), GetColor(0, 0, 0));
			}
		}
	}

	if (m_start != nullptr) {
		m_start->Draw();

	}

	for (int i = 0; i < PANEL_NUM; ++i) {
		DrawBoxAA(m_panel_pos[i].x, m_panel_pos[i].y, m_panel_pos2[i].x, m_panel_pos2[i].y, GetColor(255, 255, 255), false);
	}
	SetFontSize(30);
	DrawString(WINDOW_W / 4, WINDOW_H - 40, "エンターキーで保存、スペースキーでタイトルへ", GetColor(255, 0, 0));
	DrawRotaGraph(WINDOW_W - HAMBURGER_ICON_SIZE / 2, HAMBURGER_ICON_SIZE / 2, 0.7, 0.0, m_hamburger_icon_image, true);

	if (!m_seve) {
		SetFontSize(45);
		DrawString(30, 250, "スタートまたは、ゴールが無いためセーブ出来ませんでした", GetColor(255, 255, 0));
	}
	if (m_open_menu) {
		Vector3 pos1((WINDOW_W / 2) - (MENU_BOX_SIZE_W / 2), (WINDOW_H / 2) - (MENU_BOX_SIZE_H / 2), 0.0f);
		Vector3 pos2((WINDOW_W / 2) + (MENU_BOX_SIZE_W / 2), (WINDOW_H / 2) + (MENU_BOX_SIZE_H / 2), 0.0f);
		DrawFillBox(pos1.x, pos1.y, pos2.x, pos2.y, GetColor(0, 0, 0));
		SetFontSize(100);
		DrawFormatString((WINDOW_W / 2 - 30), 100, GetColor(255, 255, 255), "%d", m_select_map_num);
		DrawRotaGraph(600, 150, 1.0, 0.0, m_triangle_image, true);
		DrawRotaGraph(350, 150, 1.0, TO_RADIAN(180.0f), m_triangle_image, true);
		DrawRotaGraph(760, 90, 0.3, 0.0, m_cross_image, true);
		DrawGraph(400,250, m_botan1_image, true);
		DrawGraph(400, 360, m_botan2_image, true);
		SetFontSize(24);
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x: % d,y:%d,,", GetMouseX(), GetMouseY());
}

void MapMake::Exit()
{
	SeveMap();
	MV1DeleteModel(m_ground);
	for (size_t i = 0; i < m_buil.size(); ++i) {
		delete(m_buil[i]);
		m_buil[i] = nullptr;
	}
	
	m_buil.clear();
	delete(m_goal);
	m_goal = nullptr;

	fstream file;
	string str;
	file.open("data/map/map_num.txt", ios::out);
	if (!file.is_open())
		return;
	file << MAP_MAX;
	file.close();
}
