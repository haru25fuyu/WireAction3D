// �L�[���͊Ǘ�
#pragma once
#include "WinMain.h"

void KeyInputInit();			// ������
int KeyInputUpdate();			// �X�V
void KeyInputExit();			// �I��

bool IsKeyOn(int key_id);		// 1�񂾂�
bool IsKeyRelease(int key_id);	// �����ꂽ
bool IsKeyRepeat(int key_id);	// 2��ȏ�(������)