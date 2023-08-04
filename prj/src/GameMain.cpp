#include"GameMain.h"
#include "WinMain.h"
#include"Wall1.h"
#include"Wall2.h"
#include"Wall3.h"
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include"Random.h"
#include"Building1.h"
#include"Building2.h"
#include"Building3.h"
#include"Building4.h"
#include"Building5.h"
#include"Hit.h"
using namespace std;

void GameMain::SetBuil(int type, size_t idx)
{
	m_buil.resize(idx + 1);
	if (m_buil[idx] != nullptr)
		return;

	switch (type)
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
}

void GameMain::OpenMap(int map_num)
{
	vector<Vector3> pos;
	vector<int> type;
	int m_map_num = map_num;
	fstream	file;
	string file_name;
	//printf_s(file_name.c_str(), "data/map/map%d.txt", map_num);
	file.open("data/map/map0.txt", ios::in);
	if (!file.is_open())
		return;
	for (int i = 0; i < 2; ++i) {
		string sg_str;
		stringstream sg_sstr;
		getline(file, sg_str);
		if (file.eof())
			return;
		size_t idx = (size_t)i;
		type.resize(idx + 1);
		pos.resize(idx + 1);
		sg_sstr << sg_str;
		sg_sstr >> type[i] >> pos[i].x >> pos[i].y >> pos[i].z;

	}
	pos[0].y += player.GetRadius();
	player.SetPos(pos[0]);
	player.Update();
	m_goal = new Goal;
	m_goal->Init(pos[1]);
	size_t i = 0;
	do
	{
		string	str;
		getline(file, str);
		if (file.eof())
			break;
		stringstream sstr;
		sstr << str;
		pos.resize(i + 1);
		type.resize(i + 1);
		sstr >> type[i] >> pos[i].x >> pos[i].y >> pos[i].z;
		++i;
	} while (!file.eof());
	file.close();

	for (size_t i = 0; i < type.size(); ++i) {
		SetBuil(type[i], i);
		m_buil[i]->Init(pos[i]);
	}
}

int GameMain::GetGoalTime()
{
	return m_goal_time;
}
// =====================================================
//		初期化
//	ゲーム開始直後に最初に1回だけ実行される関数
//	最初の値を変数に入れたいときに使う
// =====================================================
void GameMain::Init()
{
	player.Init();
	camera.Init();
	ground.Init();

	m_wall[0] = new Wall1;
	m_wall[1] = new Wall1;
	m_wall[2] = new Wall2;
	m_wall[3] = new Wall2;
	m_wall[4] = new Wall3;
	m_wall[5] = new Wall3;

	m_wall[0]->SetPos(MAP_SIZE / 2, -1.0f, MAP_SIZE / 2);
	m_wall[1]->SetPos(MAP_SIZE / 2, 800.0f, MAP_SIZE / 2);
	m_wall[2]->SetPos(MAP_SIZE / 2, 0.0f, 0.0f);
	m_wall[3]->SetPos(MAP_SIZE / 2, 0.0f, MAP_SIZE);
	m_wall[4]->SetPos(0.5f, 0.0f, MAP_SIZE / 2);
	m_wall[5]->SetPos(MAP_SIZE - 0.5f, 0.0f, MAP_SIZE / 2);

	OpenMap(0);

	m_start = false;
	m_time = 5 * 60;
	m_goal_time = 0;
	m_arrow_image = LoadGraph("data/arrow.png");
}
// =====================================================
//		更新
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	1フレームで行う処理をここに書く
// =====================================================
int GameMain::Update()
{
	Vector3 player_vect(sinf(player.GetRot().y),0.0f,cosf(player.GetRot().y));
	Vector3 pg_vect = m_goal->GetPos()-player.GetPos();
	pg_vect.y = 0.0f;
	m_goal_angle = GetVector3Angle(player_vect, pg_vect);


	if (GetVector3Cross(player_vect, pg_vect).y < 0) {
		m_goal_angle = TO_RADIAN(360.0f) - m_goal_angle;
	}

	if (m_start) {
		if (!m_goal->GetGoal())
			m_goal_time++;
		player.Update();
	}

	camera.Update(&player);

	ground.Update(&player);
	for (size_t i = 0; i < 6; ++i) {
		if (m_wall[i] == nullptr)
			continue;
		m_wall[i]->Updete(&player);
	}
	for (size_t i = 0; i < 6; ++i) {
		if (m_wall[i] == nullptr)
			continue;
		player.SetTarget(m_wall[i]);
	}

	m_goal->UpDete(player);

	if (m_goal->GetGoal())
		return RESULTS;

	if (m_start)
		return GAME;

	if (m_time < 0)
		m_start = true;
	m_time--;
	return GAME;
}
// =====================================================
//		描画
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	GameUpdate関数が実行された後に実行される関数
// =====================================================
void GameMain::Draw()
{

	camera.Render();
	for (size_t i = 0; i < 5; ++i) {
		if (m_wall[i] == nullptr)	continue;
		m_wall[i]->Draw();
	}
	for (size_t i = 0; i < m_buil.size(); ++i) {
		if (m_buil[i] == nullptr)	continue;
		m_buil[i]->Draw();
	}

	ground.Render();
	player.Draw();
	m_goal->Draw();

		if (!m_start) {
		SetFontSize(128);
		Vector3 time_pos = Vector3(WINDOW_W / 2 - (128 / 3), WINDOW_H / 2 - (128 / 2), 0.0f);
		DrawFormatString(time_pos.x, time_pos.y, GetColor(255, 255, 255), "%d", m_time / 60);
	}

	SetFontSize(24);
	DrawFormatString(10, 10, GetColor(255, 255, 255), " %02d:%02d.%02.0f", (m_goal_time / 60) / 60 % 60, (m_goal_time / 60 % 60), (m_goal_time % 60) * 1.6f);

	Vector3 pos = m_goal->GetPos();
	Vector3 player_pos = player.GetPos();
	DrawRotaGraph(WINDOW_W/2,WINDOW_H/2, 0.5, m_goal_angle, m_arrow_image,true);

}
// =====================================================
//		終了
//	ゲームが終了する前に1回だけ実行される関数
//	何か最後に後片付けを行うときに使う
// =====================================================
void GameMain::Exit()
{


}
