#pragma once
#include"Vector3.h"

// ��`�p�\����
struct Box
{
	Vector3 vertex_pos[4];
};

//�����̗p�\����
struct Cube
{
	Box surface[6];
};
// ���p�\����
struct Line
{
	Vector3 s_pos;	// �n�_
	Vector3 g_pos;	// �I�_
};
//�J�v�Z���p�\����
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

