#include "joyPad.h"

//�R���g���[���[���̎擾
void joyPad::SetJoyPad(int padnum) {
	GetJoypadXInputState(padnum, &x_input);
	input_type = padnum;
}

//���X�e�B�b�N�̏��̎擾�i0.0f�`1.0f)
Vector3 joyPad::GetLStick() {
	//�܂��͍��X�e�B�b�N�̉��Əc�̒l���擾
	int l_stick_x ;
	int l_stick_z;
	GetJoypadAnalogInput(&l_stick_x, &l_stick_z, input_type);
	
	Vector3 l;
	l.x =(float) l_stick_x ;
	l.z =(float) l_stick_z;
	
	//�����ɓ|��Ă���l�̎��͈ړ����������Ȃ��̂�0�ɂ���
	if (l.GetLength() < 10) {
		l.x = 0;
		l.z = 0;
	}
	l.z *= -1;
	return  l ;
}
//�E�X�e�B�b�N�̏��̎擾�i0.0f�`100.0f)
Vector3 joyPad::GetRStick() {
	//�܂��͉E�X�e�B�b�N�̉��Əc�̒l���擾
	int r_stick_x ;
	int r_stick_z ;
	GetJoypadAnalogInputRight(&r_stick_x, &r_stick_z, input_type);
	
	Vector3 r;
	r.x = (float)r_stick_x ;
	r.z = (float)r_stick_z ;

	
	//�����ɓ|��Ă���l�̎��͈ړ����������Ȃ��̂�0�ɂ���
	if (r.GetLength() < 10) {
		r.x = 0;
		r.z = 0;
	}
	r.z *= -1;
	return  r;
}
//���g���K�[���̂̎擾(0.0f�`100.0f
float joyPad::LTorigger() {
	XINPUT_STATE input;
	//���g���K�[�̒l���擾���܂�
	GetJoypadXInputState(input_type,&input);
	int l_trigger = input.LeftTrigger;
	//���̎擾�����l�i�O�`�Q�T�T�j��0.0�`100.0�ɂ�����
	float radius = l_trigger / 2.55f;

	return radius;
}

//�E�g���K�[���̂̎擾(0.0f�`100.0f
float joyPad::RTorigger() {
	XINPUT_STATE input;
	//�E�g���K�[�̒l���擾���܂�
	GetJoypadXInputState(input_type, &input);
	int r_trigger = input.RightTrigger;
	//���̎擾�����l�i�O�`�Q�T�T�j��0.0�`100.0�ɂ�����
	float radius = r_trigger / 2.55f;

	return radius;
}
//�{�^����������Ă��邩�̃t���O
bool joyPad::Botan(int botan) {
	return GetJoypadInputState(input_type) & botan;
}