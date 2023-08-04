#pragma once
#include "SeenBase.h"
#include "WinMain.h"

class SeenManager :
    public SeenBase
{
    int m_seen_num;
public:
    SeenManager();
    void Init();
    void Update();
    void Draw();
    void Exit();
};

