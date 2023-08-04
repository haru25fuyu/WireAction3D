#pragma once

#include "Vector3.h"
#include <vector>
#include "BuildingBase.h"
#include "Camera.h"
#include "SeenBase.h"
#include "Goal.h"
#include "Start.h"

const float SELECT_PANEL_SIZE = 72.0f;
const int START_GOAL = 2;
const int PANEL_NUM = BUIL_TYPE_NUM + START_GOAL;
const int HAMBURGER_ICON_SIZE = 50;
const int MENU_BOX_SIZE_W = 600;
const int MENU_BOX_SIZE_H = 400;
const int MENU_BOTAN_W = 150;
const int MENU_BOTAN_H = 60;

class MapMake:
	public SeenBase
{
	int m_map_num;
	std::vector<Vector3> m_pos;				//�����̍��W
	std::vector<int> m_type;				//�����̃^�C�v
	std::vector<BuildingBase*> m_buil;		//�����N���X
	Goal* m_goal;							//�S�[���̃N���X
	bool m_select_goal;						//�S�[�����I������Ă��邩
	bool m_seve;							//�Z�[�u�o���邩�ǂ���
	int m_Buil_select_panel[PANEL_NUM];		//������I�ԃp�l��
	Vector3 m_panel_pos[PANEL_NUM];			//�p����������W
	Vector3 m_panel_pos2[PANEL_NUM];		//�p�l���E�����W
	Box m_hit_box[PANEL_NUM];				//�����蔻��̋�`�\����
	bool m_select;							//�I��ł��邩�ǂ���
	Camera m_camera;						//���߂�
	size_t m_buil_idx;						//�I�����������̃C���f�b�N�X
	int m_ground;							//
	int m_time;								//
	Start* m_start;							//�X�^�[�g�N���X
	bool m_select_start;					//�X�^�[�g��I�����Ă邩�ǂ���
	int m_hamburger_icon_image;				//�n���o�[�K�[�A�C�R���̉摜
	bool m_open_menu;						//���j���[���J���Ă��邩
	bool m_memu_select;						//�n���o�[�K�[�A�C�R����Ƀ}�E�X�����邩
	int m_triangle_image;					//�O�p�`�̉摜
	int m_select_map_num;					//�J���}�b�v�ԍ�
	int m_cross_image;						//�o�c�̉摜
	int m_botan1_image;
	int m_botan2_image;
	bool m_check_cross;						//
	

public:
	MapMake();
	void DeleteBuil(size_t idx);
	void OpenMap(int map_num);
	void SeveMap();
	void SetBuil(size_t idx);
	void Init();
	int Update();
	void Draw();
	void Exit();
};

