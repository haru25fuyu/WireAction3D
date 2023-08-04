#include "SeenBase.h"
#include<fstream>
#include<string>
using namespace std;

int GetMapNum() {
	fstream file;
	string str;
	file.open("data/map/map_num.txt", ios::in);
	if(!file.is_open())
		return 0;
	getline(file, str);
	file.close();
	int num = stoi(str);
	return num;
}

int SeenBase::MAP_MAX = GetMapNum();

SeenBase::SeenBase()
{
	m_time = 0;
	m_page = 0;
	m_next_seen = 0;
	MAP_MAX = GetMapNum();
}

int SeenBase::GetNextSeen()
{
	return m_next_seen;
}

int SeenBase::GetTime()
{
	return m_time;
}
