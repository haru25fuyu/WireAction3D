// �}�E�X���͊Ǘ�
#pragma once
#include "WinMain.h"

void MouseInputInit();		// ������
void MouseInputUpdate();	// �X�V
void MouseInputExit();		// �I��

bool IsMouseOn(int mouse_id);			// 1�񂾂�
bool IsMouseRelease(int mouse_id);		// �����ꂽ
bool IsMouseRepeate(int mouse_id);		// ������

int GetMouseX();			// �}�E�X��X���W �擾
int GetMouseY();			// �}�E�X��Y���W �擾
