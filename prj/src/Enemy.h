#pragma once
#include "CharBase.h"
#include"WinMain.h"
#include<vector>
#include"Player.h"
#include<fstream>
#include<sstream>

class Enemy :
    public CharBase
{
    const float SEARCH_RANGE = 100.0f;

    bool    m_attak;
    int     m_target_idx;
    
public:
   
    void SetChar();
    void Move();
    void Attak();
    void Draw();
    void Exit();
};

