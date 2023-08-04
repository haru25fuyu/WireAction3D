#pragma once
#include "SeenBase.h"
#include"Player.h"
#include"Ground.h"
#include"Camera.h"
#include"BuildingBase.h"
#include"Goal.h"


class GameMain :
    public SeenBase
{
    const int WALL_NUM = 6;
    Player player;
    int ground_model;
    Ground ground;   
    BuildingBase* m_wall[6];
    std::vector<BuildingBase*> m_buil;
    Goal* m_goal;
    bool m_start;
    int m_goal_time;
    Camera camera;
    float m_goal_angle;
    int m_arrow_image;
 
    void  OpenMap(int map_num);
    void  SetBuil(int type,size_t idx);
public:
    int GetGoalTime();
    void Init();
    int Update();
    void Draw();
    void Exit();
};

