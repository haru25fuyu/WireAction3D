#pragma once
#include "CharBase.h"
#include"joyPad.h"
#include"WierBase.h"
#include"WierR.h"
#include"WireL.h"
#include"BulletBase.h"
#include"AssaultRifle.h"
#include"Camera.h"
#include"SpherHit.h"

class Player :
    public CharBase
{
    int m_angle_graph;
    int m_angle_graph2;
    joyPad m_pad;
    Vector3 m_wier_rotl;
    Vector3 m_wier_rotr;
    WireL m_wierl;
    WierR m_wierr;
    Camera camera;
    SpherHit spher;
public:
    void SetChar();
    void Move();
    void Attak();
    void Draw();
    void Exit();
};

