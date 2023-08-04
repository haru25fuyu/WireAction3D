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
	std::vector<Vector3> m_pos;				//建物の座標
	std::vector<int> m_type;				//建物のタイプ
	std::vector<BuildingBase*> m_buil;		//建物クラス
	Goal* m_goal;							//ゴールのクラス
	bool m_select_goal;						//ゴールが選択されているか
	bool m_seve;							//セーブ出来るかどうか
	int m_Buil_select_panel[PANEL_NUM];		//建物を選ぶパネル
	Vector3 m_panel_pos[PANEL_NUM];			//パメル左上座標
	Vector3 m_panel_pos2[PANEL_NUM];		//パネル右下座標
	Box m_hit_box[PANEL_NUM];				//当たり判定の矩形構造体
	bool m_select;							//選んでいるかどうか
	Camera m_camera;						//かめら
	size_t m_buil_idx;						//選択した建物のインデックス
	int m_ground;							//
	int m_time;								//
	Start* m_start;							//スタートクラス
	bool m_select_start;					//スタートを選択してるかどうか
	int m_hamburger_icon_image;				//ハンバーガーアイコンの画像
	bool m_open_menu;						//メニューが開いているか
	bool m_memu_select;						//ハンバーガーアイコン上にマウスがあるか
	int m_triangle_image;					//三角形の画像
	int m_select_map_num;					//開くマップ番号
	int m_cross_image;						//バツの画像
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

