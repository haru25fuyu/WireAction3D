#include "WinMain.h"
#include "Vector3.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3::Vector3(float x, float y, float z):
	x(x),y(y),z(z)
{
}
//---------------------------------------------------------------------------------
//	ゼロ初期化（ＸＹＺの値を０にします）
//---------------------------------------------------------------------------------
void Vector3::clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
//---------------------------------------------------------------------------------
//	値のセット（ＸＹＺをそれぞれ受け取るバージョン）
//---------------------------------------------------------------------------------
void Vector3::set( float x, float y, float z ) 
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//---------------------------------------------------------------------------------
//	値のセット（ Vector3 を受け取るバージョン ）
//---------------------------------------------------------------------------------
void Vector3::set( const Vector3 &v )
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//---------------------------------------------------------------------------------
//	長さ取得
//---------------------------------------------------------------------------------
float Vector3::GetLength()
{
	return sqrtf( x * x + y * y + z * z );
}
//---------------------------------------------------------------------------------
//	正規化（ベクトルの長さを１にする）
//---------------------------------------------------------------------------------
void Vector3::normalize()
{
	float length = GetLength();
	if( length > 0.0f ){
		x = x / length;
		y = y / length;
		z = z / length;
	}
}
//---------------------------------------------------------------------------------
//	長さ設定
//---------------------------------------------------------------------------------
void Vector3::SetLength( float length )
{
	normalize();
	x = x * length;
	y = y * length;
	z = z * length;
}

//---------------------------------------------------------------------------------
//	= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator = ( const Vector3 &v )
{
	x = v.x;
	y = v.y; 
	z = v.z; 
	return *this; 
}
//---------------------------------------------------------------------------------
//	+= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator += ( const Vector3 &v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	-= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator -= ( const Vector3 &v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	*= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator *= ( const float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

VECTOR Vector3::VGet()
{
	VECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

void Vector3::VSet(VECTOR& v)
{
	v;
	x = v.x;
	y = v.y;
	z = v.z;
}



//---------------------------------------------------------------------------------
//	+ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator + ( const Vector3 &v0, const Vector3 &v1 )
{
	Vector3 v;
	v.x = v0.x + v1.x;
	v.y = v0.y + v1.y;
	v.z = v0.z + v1.z;
	return v;
}
Vector3 operator+(const Vector3& v, const float& f)
{
	Vector3 v1;
	v1.x = v.x + f;
	v1.y = v.y + f;
	v1.z = v.z + f;
	return v1;

}
//---------------------------------------------------------------------------------
//	- 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator - ( const Vector3 &v0, const Vector3 &v1 )
{
	Vector3 v;
	v.x = v0.x - v1.x;
	v.y = v0.y - v1.y;
	v.z = v0.z - v1.z;
	return v;
}
Vector3 operator-(const Vector3& v, const float& f)
{
	Vector3 v1;
	v1.x = v.x - f;
	v1.y = v.y - f;
	v1.z = v.z - f;
	return v1;
}
//---------------------------------------------------------------------------------
//	* 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator * ( const Vector3 &v, const float f )
{
	Vector3 r;
	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	return r;
}

//---------------------------------------------------------------------------------
//	２つの Vector3 の距離を求める
//---------------------------------------------------------------------------------
float GetVector3Distance( Vector3 &p0, Vector3 &p1 )
{
	Vector3 v = p0 - p1;
	return v.GetLength();
}
//---------------------------------------------------------------------------------
//	２つの Vector3 の内積を求める
//---------------------------------------------------------------------------------
float GetVector3Dot( Vector3 &v0, Vector3 &v1 )
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

float GetVector3Angle(Vector3& v0, Vector3& v1)
{
	float cos_sita = GetVector3Dot(v0, v1) / (v0.GetLength() * v1.GetLength());

	return acos(cos_sita);
}



Vector3 GetVector3Cross(Vector3& v0, Vector3& v1)
{
	return Vector3(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x);
}

//２Ｄ座標を３Ｄ座標にする
Vector3 GetCamera3DPos(Vector3& pos_2D)
{
	pos_2D.z = 0.0f;
	MATRIX projection = GetCameraProjectionMatrix();
	MATRIX view = GetCameraViewMatrix();
	MATRIX viewport = GetCameraViewportMatrix();

	MATRIX inverse_projection = MInverse(projection);
	MATRIX inverse_view = MInverse(view);
	MATRIX inverse_viewport = MInverse(viewport);

	VECTOR spos = VTransform(pos_2D.VGet(), inverse_viewport);
	VECTOR cpos = VTransform(spos, inverse_projection);
	VECTOR wpos = VTransform(cpos, inverse_view);
	
	Vector3 ans;
	ans.VSet(wpos);
	return ans;
}

//３Ｄ座標をスクリーン座標にする
Vector3 Get3DScreenPos(Vector3& pos_3D)
{
	MATRIX view = GetCameraViewMatrix();
	MATRIX projection = GetCameraProjectionMatrix();
	MATRIX viewport = GetCameraViewportMatrix();

	VECTOR cpos = VTransform(pos_3D.VGet(), view);
	VECTOR spos = VTransform(cpos, projection);
	spos.x /= spos.z; 
	spos.y /= spos.z;
	spos.z = 0.0f;
	VECTOR draw2dpos = VTransform(spos, viewport);

	Vector3 ans;
	ans.VSet(draw2dpos);
	return ans;
}



