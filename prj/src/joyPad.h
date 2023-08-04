#pragma once
#include"WinMain.h"
#include"Vector3.h"
class joyPad
{
private:
	XINPUT_STATE x_input;
	int input_type;
public:
	void SetJoyPad(int padnum= DX_INPUT_PAD1);	//コントローラー情報の取得
	Vector3 GetRStick();						// 右スティックの情報の取得（0.0f～1.0f)
	Vector3 GetLStick();						//左スティックの情報の取得（0.0f～100.0f)
	float RTorigger();							//右トリガー情報のの取得(0.0f～100.0f)
	float LTorigger();							//左トリガー情報のの取得(0.0f～100.0f)
	bool Botan(int botan);			//ボタンが押されているかのフラグ

};

