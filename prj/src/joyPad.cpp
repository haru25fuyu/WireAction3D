#include "joyPad.h"

//コントローラー情報の取得
void joyPad::SetJoyPad(int padnum) {
	GetJoypadXInputState(padnum, &x_input);
	input_type = padnum;
}

//左スティックの情報の取得（0.0f～1.0f)
Vector3 joyPad::GetLStick() {
	//まずは左スティックの横と縦の値を取得
	int l_stick_x ;
	int l_stick_z;
	GetJoypadAnalogInput(&l_stick_x, &l_stick_z, input_type);
	
	Vector3 l;
	l.x =(float) l_stick_x ;
	l.z =(float) l_stick_z;
	
	//微妙に倒れている値の時は移動させたくないので0にする
	if (l.GetLength() < 10) {
		l.x = 0;
		l.z = 0;
	}
	l.z *= -1;
	return  l ;
}
//右スティックの情報の取得（0.0f～100.0f)
Vector3 joyPad::GetRStick() {
	//まずは右スティックの横と縦の値を取得
	int r_stick_x ;
	int r_stick_z ;
	GetJoypadAnalogInputRight(&r_stick_x, &r_stick_z, input_type);
	
	Vector3 r;
	r.x = (float)r_stick_x ;
	r.z = (float)r_stick_z ;

	
	//微妙に倒れている値の時は移動させたくないので0にする
	if (r.GetLength() < 10) {
		r.x = 0;
		r.z = 0;
	}
	r.z *= -1;
	return  r;
}
//左トリガー情報のの取得(0.0f～100.0f
float joyPad::LTorigger() {
	XINPUT_STATE input;
	//左トリガーの値を取得します
	GetJoypadXInputState(input_type,&input);
	int l_trigger = input.LeftTrigger;
	//この取得した値（０～２５５）を0.0～100.0にしたい
	float radius = l_trigger / 2.55f;

	return radius;
}

//右トリガー情報のの取得(0.0f～100.0f
float joyPad::RTorigger() {
	XINPUT_STATE input;
	//右トリガーの値を取得します
	GetJoypadXInputState(input_type, &input);
	int r_trigger = input.RightTrigger;
	//この取得した値（０～２５５）を0.0～100.0にしたい
	float radius = r_trigger / 2.55f;

	return radius;
}
//ボタンが押されているかのフラグ
bool joyPad::Botan(int botan) {
	return GetJoypadInputState(input_type) & botan;
}