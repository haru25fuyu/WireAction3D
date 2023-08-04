#pragma once
#include "Main.h"

//---------------------------------------------------------------------------------
//	Vector3 �N���X�i x y z ������N���X�j
//---------------------------------------------------------------------------------
class Vector3
{
public:
	float	x;
	float	y;
	float	z;

	Vector3();	//	�R���X�g���N�^
	Vector3(float x, float y, float z);
	void clear();								//	�[��������
	void set( float x, float y, float z );		//	�l�̃Z�b�g
	void set( const Vector3 &v );

	float GetLength();							//	�����擾
	void normalize();							//	���K��
	void SetLength( float length );				//	�����ݒ�

	Vector3& operator = ( const Vector3 &v );	//	= ���Z�q�̃I�[�o�[���[�h

	Vector3& operator += ( const Vector3 &v );	//	+= ���Z�q�̃I�[�o�[���[�h
	Vector3& operator -= ( const Vector3 &v );	//	-= ���Z�q�̃I�[�o�[���[�h
	Vector3& operator *= ( const float f );		//	*= ���Z�q�̃I�[�o�[���[�h
	VECTOR VGet();
	void VSet(VECTOR& v);

	
};

//	+ ���Z�q�̃I�[�o�[���[�h
Vector3 operator + ( const Vector3 &v0, const Vector3 &v1 );
Vector3 operator + (const Vector3& v, const float& f);
//	- ���Z�q�̃I�[�o�[���[�h
Vector3 operator - ( const Vector3 &v0, const Vector3 &v1 );
Vector3 operator - (const Vector3 &v,const float &f);
//	* ���Z�q�̃I�[�o�[���[�h
Vector3 operator * ( const Vector3 &v, const float f );

//	�Q�� Vector2 �̋��������߂�
float GetVector3Distance( Vector3 &p0, Vector3 &p1 );
//	�Q�� Vector3 �̓��ς����߂�
float GetVector3Dot( Vector3 &v0, Vector3 &v1 );
//�@�Q��Vector3�@�̂Ȃ��p�����߂�
float GetVector3Angle(Vector3 &v0,Vector3 &v1);
//�@�Q�� Vector3 �̊O�ς����߂�
Vector3 GetVector3Cross(Vector3& v0, Vector3& v1);
Vector3 GetCamera3DPos(Vector3& pos_2D);
Vector3 Get3DScreenPos(Vector3& pos_3D);