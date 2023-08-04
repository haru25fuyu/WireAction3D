#pragma once

#include "Base.h"
#include<vector>



//---------------------------------------------------------------------------------
//	地面クラス
//---------------------------------------------------------------------------------
class Ground : public Base
{
	//std::vector<bool> m_nav;
public:
	//std::vector<bool>* GetNav();
	//void SetNav();
	void Init();		//	初期化処理
	void Update(Base* char_);		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
