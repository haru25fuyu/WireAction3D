#pragma once
#include "Main.h"

//---------------------------------------------------------------------------------
//	Vector3 クラス（ x y z があるクラス）
//---------------------------------------------------------------------------------
class Vector3
{
public:
	float	x;
	float	y;
	float	z;

	Vector3();	//	コンストラクタ
	Vector3(float x, float y, float z);
	void clear();								//	ゼロ初期化
	void set( float x, float y, float z );		//	値のセット
	void set( const Vector3 &v );

	float GetLength();							//	長さ取得
	void normalize();							//	正規化
	void SetLength( float length );				//	長さ設定

	Vector3& operator = ( const Vector3 &v );	//	= 演算子のオーバーロード

	Vector3& operator += ( const Vector3 &v );	//	+= 演算子のオーバーロード
	Vector3& operator -= ( const Vector3 &v );	//	-= 演算子のオーバーロード
	Vector3& operator *= ( const float f );		//	*= 演算子のオーバーロード
	VECTOR VGet();
	void VSet(VECTOR& v);

	
};

//	+ 演算子のオーバーロード
Vector3 operator + ( const Vector3 &v0, const Vector3 &v1 );
Vector3 operator + (const Vector3& v, const float& f);
//	- 演算子のオーバーロード
Vector3 operator - ( const Vector3 &v0, const Vector3 &v1 );
Vector3 operator - (const Vector3 &v,const float &f);
//	* 演算子のオーバーロード
Vector3 operator * ( const Vector3 &v, const float f );

//	２つの Vector2 の距離を求める
float GetVector3Distance( Vector3 &p0, Vector3 &p1 );
//	２つの Vector3 の内積を求める
float GetVector3Dot( Vector3 &v0, Vector3 &v1 );
//　２つのVector3　のなす角を求める
float GetVector3Angle(Vector3 &v0,Vector3 &v1);
//　２つの Vector3 の外積を求める
Vector3 GetVector3Cross(Vector3& v0, Vector3& v1);
Vector3 GetCamera3DPos(Vector3& pos_2D);
Vector3 Get3DScreenPos(Vector3& pos_3D);