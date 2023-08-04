#pragma once
#include "Common.h"
#include "BaseShape.h"

class Circle:
public BaseShape
{
//private:
//	Vec2 m_pos;				// ���W
//	int	 m_r;				// ���a
//	unsigned int m_color;	// �F

public:
	// �R���X�g���N�^
	Circle();
	// �R���X�g���N�^(�����t��: ���W�Ɣ��a�w��)
	Circle(Vec2 pos_, int r_, unsigned int color_);
	// �f�X�g���N�^
	~Circle() = default;

	//// ----------------------------
	////	���W�n�֐�
	//// ----------------------------
	//void setPos(Vec2 pos_);		// ���W - �ݒ�(Vec2�w��)
	//void setPos(int x_, int y_);// ���W - �ݒ�(x, y�w��)
	//Vec2 getPos() const;		// ���W - �擾
	//int  getPosX() const;		// ���W - �擾(X)
	//int  getPosY() const;		// ���W - �擾(Y)

	//// ----------------------------
	////	���a�n�֐�
	//// ----------------------------
	//void setR(int r_);			// ���a - �ݒ�
	//int getR() const;			// ���a - �擾

	// ----------------------------
	//	�s���n�֐�
	// ----------------------------
	bool update();				// �X�V����
	void draw();				// �`�揈��


};

