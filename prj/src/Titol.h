#pragma once
#include "SeenBase.h"
#include "Common.h"
#include"joyPad.h"

const float BOTAN_SIZE_W = 150.0f;
const float BOTAN_SIZE_H = 60.0f;
const int BOTAN_NUM = 4;
class Titol :
    public SeenBase
{
    int m_back_image;
    int m_titol_image;
    int m_botan_image[BOTAN_NUM];
    int num;
    bool m_botan_display[BOTAN_NUM];
    char text[256];
    Vector3 m_botan_pos[BOTAN_NUM];
    Box m_botan_hit_box[BOTAN_NUM];
    int m_select_num;
    joyPad m_pad;
    bool m_old_direction[4];
    bool m_old_botan;

public:
    Titol();
    void Init();
    int Update();
    void Draw();
    void Exit();
};

