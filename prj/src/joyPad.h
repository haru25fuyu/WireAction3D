#pragma once
#include"WinMain.h"
#include"Vector3.h"
class joyPad
{
private:
	XINPUT_STATE x_input;
	int input_type;
public:
	void SetJoyPad(int padnum= DX_INPUT_PAD1);	//�R���g���[���[���̎擾
	Vector3 GetRStick();						// �E�X�e�B�b�N�̏��̎擾�i0.0f�`1.0f)
	Vector3 GetLStick();						//���X�e�B�b�N�̏��̎擾�i0.0f�`100.0f)
	float RTorigger();							//�E�g���K�[���̂̎擾(0.0f�`100.0f)
	float LTorigger();							//���g���K�[���̂̎擾(0.0f�`100.0f)
	bool Botan(int botan);			//�{�^����������Ă��邩�̃t���O

};

