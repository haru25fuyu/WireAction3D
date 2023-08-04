#include "WinMain.h"
#include "SeenManager.h"

//#include <imgui/imgui_impl_dxlib.hpp>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(100, 100, 100);
	SetMainWindowText("ワイヤーアクション");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 255, 255);
	srand(GetNowCount() % RAND_MAX);

	SetCameraNearFar(0.1f, 3000.0f);
	
	SeenManager seen;

	// ---------------
	// 初期化処理
	// ---------------
	KeyInputInit();
	PadInputInit();
	MouseInputInit();
	seen.Init();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ---------------
		// 更新処理
		// ---------------
		SetMouseDispFlag(true);
		KeyInputUpdate();
		PadInputUpdate();
		MouseInputUpdate();
		seen.Update();

		// ---------------
		// 描画処理
		// ---------------
		ClearDrawScreen();
		clsDx();
		seen.Draw();
		ScreenFlip();
	}
	
	// ---------------
	// 終了処理
	// ---------------
	KeyInputExit();
	PadInputExit();
	MouseInputExit();
	seen.Exit();

	DxLib_End();

	return 0;
}
//---------------------------------------------------------------------------------
//	度をラジアンに変換する関数
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	ラジアンを度に変換する関数
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}