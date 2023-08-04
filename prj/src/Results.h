#pragma once
#include "SeenBase.h"
#include <vector>
#include <string>
#include"joyPad.h"

class Results :
    public SeenBase
{
    const int RANK_MAX = 10;
    int m_goal_time;
    std::string m_player_name;
    int m_rank_time[10];
    std::string m_name[10];
    joyPad m_pad;
   
public:
    Results();
    void SetClearTime(int goal_time, std::string name);
    void SetRanking();
    void Init();
    int Update();
    void Draw();
    void Exit();
};

