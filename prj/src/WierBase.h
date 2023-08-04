#pragma once
#include "Base.h"
#include "WinMain.h"
class WierBase :
    public Base
{
protected:
    const float PULL_POWER = 0.1f;
    const float WIER_SPEED = 10.5f;
    const float LIMIT_LENGTH = 100.0f;
    bool m_de;
    bool m_is_hit;
    bool m_is_pull;
    Vector3 m_strat_pos;
    float m_my_pos;
    Vector3 LimitLength(Base* obj_);
public:
    void Init(Base* obj_);
    virtual void SetMyPos() = 0;
    void Move();
    Vector3 GetStartPos(Base* obj_, float set_rota_);
    virtual void Set(Base* obj_,Vector3 rot_);
    virtual void UpDate(Base* obj_);
    void Delete();
    Vector3 CreateVect();
    virtual void Draw(Base* obj_);
};

