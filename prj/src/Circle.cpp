#include "Circle.h"
#include "DxLib.h"

// �R���X�g���N�^
Circle::Circle() :
	m_pos({0, 0}),
	m_r(0),
	m_color(0)
{

}

// �R���X�g���N�^(�����t��: ���W�Ɣ��a�w��)
Circle::Circle(Vec2 pos_, int r_, unsigned int color_) :
	m_pos(pos_),
	m_r(r_),
	m_color(color_)
{

}

//// ���W - �ݒ�(Vec2�w��)
//void Circle::setPos(Vec2 pos_)
//{
//	m_pos = pos_;
//}
//
//// ���W - �ݒ�(Vec2�w��)
//void Circle::setPos(int x_, int y_)
//{
//	m_pos = { x_, y_ };
//}
//
//Vec2 Circle::getPos() const
//{
//	return m_pos;
//}
//
//int Circle::getPosX() const
//{
//	return getPos().x;
//}
//
//int Circle::getPosY() const
//{
//	return getPos().y;
//}
//
//void Circle::setR(int r_)
//{
//	m_r = r_;
//}
//
//int Circle::getR() const
//{
//	return m_r;
//}

// �X�V����
bool Circle::update()
{


	return false;
}

// �`�揈��
void Circle::draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_r, m_color, FALSE);
}
