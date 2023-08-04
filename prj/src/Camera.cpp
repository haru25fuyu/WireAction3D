#include "WinMain.h"
#include "GameMain.h"
#include "Camera.h"
#include "Random.h"
#include"Hit.h"



//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Camera::Init()
{
	m_pos.set(CAMERA_START_POS);
	m_look.set(CAMERA_START_LOOK);
	m_rot.set(CAMERA_START_ROTA);
	m_camera_type = false;
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Camera::Update(CharBase* char_)
{
	m_camera_type = false;
	m_pos = char_->GetPos();
	m_pos.x += CAMERA_LENGTH * sinf(PI + char_->GetRot().y);
	m_pos.z += CAMERA_LENGTH * cosf(PI + char_->GetRot().y);
	m_pos.y += CAMERA_LENGTH * sinf(PI + char_->GetRot().x) + 1.5f;
	m_look = char_->GetPos();
	m_look.x += 10 * sinf(char_->GetRot().y);
	m_look.z += 10 * cosf(char_->GetRot().y);
	m_look.y += 10 * sinf(char_->GetRot().x) + 1.5f;
}
void Camera::Update()
{
	m_camera_type = true;
	int mouse_x = GetMouseX();


	if (IsKeyRepeat(KEY_INPUT_LALT) || IsKeyRepeat(KEY_INPUT_RALT)) {
		m_rot.y += ((float)mouse_x - m_reference_pos.x) * ROTETION_SENSITIVITY;
	}

	if (IsKeyRepeat(KEY_INPUT_A)) {
		m_pos.x += CAMERA_LENGTH * sinf(m_rot.y - (PI * 0.5f));
		m_pos.z += CAMERA_LENGTH * cosf(m_rot.y - (PI * 0.5f));

	}
	if (!IsKeyRepeat(KEY_INPUT_LCONTROL) && IsKeyRepeat(KEY_INPUT_D)) {
		m_pos.x += CAMERA_LENGTH * sinf(m_rot.y + (PI * 0.5f));
		m_pos.z += CAMERA_LENGTH * cosf(m_rot.y + (PI * 0.5f));

	}
	if (IsKeyRepeat(KEY_INPUT_W)) {
		m_pos.x += CAMERA_LENGTH * sinf(m_rot.y);
		m_pos.z += CAMERA_LENGTH * cosf(m_rot.y);

	}
	if (IsKeyRepeat(KEY_INPUT_S)) {
		m_pos.x += CAMERA_LENGTH * sinf(m_rot.y - PI);
		m_pos.z += CAMERA_LENGTH * cosf(m_rot.y - PI);

	}

	m_reference_pos.set((float)mouse_x, 0);
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Camera::Render()
{
	if (!m_camera_type) {
		SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
	}
	else {
		SetCameraPositionAndAngle(m_pos.VGet(), m_rot.x, m_rot.y, m_rot.z);
	}

}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}

Vector3 Camera::GetPos()
{
	return m_pos;
}
