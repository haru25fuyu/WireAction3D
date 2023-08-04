#pragma once

#include "DxLib.h"
#include "KeyInput.h"
#include "PadInput.h"
#include "MouseInput.h"
#include "Common.h"
#include <math.h>


#define PI		 3.141592653589793
#define RadToDeg 57.29577951f
#define R2D(rad) rad * RadToDeg

#define DegToRad 0.017453293f
#define D2R(deg) deg * DegToRad

#define BLACK	GetColor(0, 0, 0)
#define WHITE	GetColor(255, 255, 255)
#define RED		GetColor(255, 0, 0)
#define GREEN	GetColor(0, 255, 0)
#define BLUE	GetColor(0, 0, 255)
#define YELLOW	GetColor(255, 255, 0)
#define PINK	GetColor(255, 0, 255)
#define SKYBLUE	GetColor(0, 255, 255)

#define WINDOW_W	960
#define WINDOW_H	540

#define IMG_SIZE	32
float TO_RADIAN(float degree);
float TO_DEGREE(float radian);

const int MAP_SIZE = 1600;

const float PAD_STICK_MAX = 1000.0f;

enum {
	//球型の当たり判定
	PLAYER,ENEMY1,ENEMY2,ENEMY4,BULLET,
	//立方体の当たり判定
	BUILDING,
	OBJ_TYPE_MAX
};

//コライダーの形
enum {
	ANNON, SPHER, CUBE, CAPSULE
};

enum {
	ASSAULTRIFLE = 1
};

