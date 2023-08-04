#pragma once

#include "Vector3.h"
#include "CharBase.h"
#include "Vector2.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
	const Vector3	CAMERA_START_POS		= Vector3(10.0f, 50.0f, 0.0f);
	const Vector3	CAMERA_START_LOOK		= Vector3(10.0f,  0.0f, 0.0f);
	const Vector3	CAMERA_START_ROTA		= Vector3(10.0f,  0.0f, 0.0f);
	const float		ROTETION_SENSITIVITY	= 0.005f;
	const float		CAMERA_LENGTH			= 7.0f;
	//	�J�������W
	Vector3		m_pos;
	//	������W
	Vector3		m_look;
	Vector3     m_rot;
	Vector2		m_reference_pos;
	bool		m_camera_type;
public:
	void Init();						//	����������
	void Update(CharBase* char_);		//	�X�V����
	void Update();
	void Render();						//	�`�揈��
	void Exit();						//	�I������

	Vector3 GetPos();
};
