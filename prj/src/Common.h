#pragma once
#include"Vector3.h"

// 矩形用構造体
struct Box
{
	Vector3 vertex_pos[4];
};

//立方体用構造体
struct Cube
{
	Box surface[6];
};
// 線用構造体
struct Line
{
	Vector3 s_pos;	// 始点
	Vector3 g_pos;	// 終点
};
//カプセル用構造体
struct Capsule {
	Line line;
	float radius;
};

struct Spher {
	Vector3 pos;
	float radius;
};

struct Object {
	Vector3 pos;
	Vector3 vect;
	int type;
	Vector3 size;
	float radius;
};

