#pragma once
class SeenBase
{
protected:
	int m_time;
	int m_page;
	int m_next_seen;

public:
	static int MAP_MAX;
	SeenBase();
	int GetNextSeen();
	int GetTime();
};

enum {
	TITOL, TUTORIAL,GAME,MAPMAKE,RESULTS
};