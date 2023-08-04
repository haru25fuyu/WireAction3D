#pragma once
#include "SeenBase.h"
#include "Player.h"
#include"joyPad.h"
#include"Camera.h"



enum {
    SHOT_WIER, MOVE_WIER, REMOVE_WIER,
    SET_WIER, CAMERA_ROTA, FREE,PAGE_MAX
};

class Tutorial :
    public SeenBase
{
    Player m_char;
    joyPad m_pad;
    int m_description_panel;
    int m_circle;
    int m_controller_image[2];
    int m_arrow;
    int m_check_botan;
    bool m_check[2];
    std::string m_text[PAGE_MAX];
    Camera m_camera;
public:
    void Init();
    int Update();
    void Draw();
    void Exit();
};

