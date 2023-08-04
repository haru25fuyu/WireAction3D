#pragma once
#include "Base.h"
#include"BulletBase.h"
#include"AssaultRifle.h"
#include<fstream>
class CharBase :
    public Base
{
    static int m_obj_num;
    int m_timer;
protected:
   
    int m_near_item;
public:
    CharBase();
    void SetNearItem(int type);
    void Init();
    virtual void SetChar() = 0;
    virtual void Move() = 0;
   
    void Update();
    virtual void Draw();
    void Exit();
};

