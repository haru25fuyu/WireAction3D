#pragma once
#include "Common.h"
#include "BaseShape.h"

class Circle:
public BaseShape
{
//private:
//	Vec2 m_pos;				// 座標
//	int	 m_r;				// 半径
//	unsigned int m_color;	// 色

public:
	// コンストラクタ
	Circle();
	// コンストラクタ(引数付き: 座標と半径指定)
	Circle(Vec2 pos_, int r_, unsigned int color_);
	// デストラクタ
	~Circle() = default;

	//// ----------------------------
	////	座標系関数
	//// ----------------------------
	//void setPos(Vec2 pos_);		// 座標 - 設定(Vec2指定)
	//void setPos(int x_, int y_);// 座標 - 設定(x, y指定)
	//Vec2 getPos() const;		// 座標 - 取得
	//int  getPosX() const;		// 座標 - 取得(X)
	//int  getPosY() const;		// 座標 - 取得(Y)

	//// ----------------------------
	////	半径系関数
	//// ----------------------------
	//void setR(int r_);			// 半径 - 設定
	//int getR() const;			// 半径 - 取得

	// ----------------------------
	//	行動系関数
	// ----------------------------
	bool update();				// 更新処理
	void draw();				// 描画処理


};

