#pragma once
#include "Base.h"
#include"Vector3.h"
#include"WinMain.h"


const int BUIL_TYPE_NUM = 5;

class BuildingBase :
    public Base
{
protected:
    unsigned int m_color;
    Vector3 m_pos1;
    Vector3 m_pos2;
    Cube m_cube;

public:
    
    BuildingBase();

    Vector3 GetPos1();
    Vector3 GetPos2();
    Cube GetHitCube();

    void Init(Vector3 under_center_pos);
    virtual void SetBuil() = 0;
    void SetPos(Vector3 under_center_pos);
    void SetPos(float c_x,float c_y,float c_z);
    void Updete(Base* obj_);
    void Draw();
    void Exit();
};

