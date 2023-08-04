#include "Results.h"
#include"WinMain.h"
#include <fstream>
#include <sstream>
using namespace std;

Results::Results()
{
	for (int i = 0; i < RANK_MAX; ++i) {
		m_rank_time[i] = 1000000;
		m_name[i] = "_";
	}
	m_goal_time = 0;
	m_player_name = "_";
}

void Results::SetClearTime(int goal_time, string name = "_")
{
	m_goal_time = goal_time;
	m_player_name = "_";
	if (m_goal_time <= 30)
		return;
	SetRanking();
}

void Results::SetRanking()
{
	int idx = -1;
	for (int i = RANK_MAX - 1; i >= 0; --i) {
		if (m_goal_time > m_rank_time[i])
			continue;
		idx = i;
	}

	if (idx < 0)
		return;
	for (int i = RANK_MAX - 1; i >= idx; --i) {
		if (i < 0)
			break;
		m_rank_time[i] = m_rank_time[i-1];
	}
	m_rank_time[idx] = m_goal_time;


}

void Results::Init()
{

	m_pad.SetJoyPad();

	m_time = 0;
	m_goal_time = 0;
	m_player_name = "_";
	for (int i = 0; i < RANK_MAX; ++i) {
		m_rank_time[i] = 1000000;
		m_name[i] = "_";
	}
	fstream file;
	file.open("data/rank/rank.txt", ios::in);
	if (!file.is_open())
		return;
	for (int i = 0; i < RANK_MAX; ++i) {
		string str;
		getline(file, str);
		if (file.eof())
			break;
		stringstream sstr;
		sstr << str;
		sstr >> m_rank_time[i] >> m_name[i];
	}
	file.close();
}

int Results::Update()
{
	if (m_time > 60 * (60 * 3))
		return TITOL;
	m_time++;

	if (IsKeyOn(KEY_INPUT_RETURN) ||
		m_pad.Botan(PAD_INPUT_1)) {
		return TITOL;
	}
	return RESULTS;
}

void Results::Draw()
{
	SetFontSize(63);

	if (m_goal_time <= 30) {
		DrawString(300, 70, "ランキング表", GetColor(255, 255, 255));
	}
	else {
		DrawString(300, 30, "ランキング表", GetColor(255, 255, 255));
		SetFontSize(45);
		int time = m_goal_time;
		DrawFormatString(200, 120, GetColor(255, 255, 255), "ゴールタイム: %02d:%02d.%02.0f", (time / 60) / 60 % 60, (time / 60 % 60), (time % 60) * 1.6f);
	}

	SetFontSize(45);

	for (int i = 0; i < RANK_MAX; ++i) {
		if (m_rank_time[i] < 0)
			m_rank_time[i] = 1000000;
		int time = m_rank_time[i];
		if (time == 1000000) {
			DrawFormatString(100 + (i / 5 * 400), 220 + (i % 5 * 60), GetColor(255, 255, 255), "%2d位  ==:==.==", i + 1, (time / 60) / 60 % 60, (time / 60 % 60), (time % 60) * 1.6f);
			continue;
		}
		DrawFormatString(100 + (i / 5 * 400), 220 + (i % 5 * 60), GetColor(255, 255, 255), "%2d位  %02d:%02d.%02.0f", i + 1, (time / 60) / 60 % 60, (time / 60 % 60), (time % 60) * 1.6f);
	}
}

void Results::Exit()
{

	fstream file;
	file.open("data/rank/rank.txt", ios::out);
	if (!file.is_open())
		return;
	for (int i = 0; i < RANK_MAX; ++i) {
		file << m_rank_time[i] << " " << m_name[i] << " " << "\n";
	}
	file.close();
}
