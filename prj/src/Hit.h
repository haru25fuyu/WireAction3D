#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Base.h"

//	線と球の当たり判定
bool CheckLineBallHit( Vector3 &line_start, Vector3 &line_goal, Vector3 &ball_pos, float ball_radius );

//点と一番近い線上の座標
Vector3 GetPointLineNearPos(Line& line, Vector3& point);

//	線と点の最短距離
float GetLinePointLength(Line& line, Vector3& point);

//線上の点が線分の範囲にいるかを見る
bool ChecLieWithinLineSegment(Line line, Vector3 p);

//点と線分の２点の距離の短いほうの点の距離を取得
float GetNearPointForLineSegment(Line line, Vector3 p);

//3D空間上の二つの線の距離
float GetLineLength(Line& line1, Line& line2);

//線分上の最短点をつなぐ線(二点)
Line GetLineConnectLine(Line& Line1,Line& line2);

//	球同士の当たり判定
bool CheckBallHit( const Vector3 &p0, const float r0, const Vector3 &p1, const float r1 );

//	カプセル同氏の当たり判定
bool CheckCapsuleHit(Capsule& capsule1, Capsule& capsule2);

//	立方体と球の当たり判定
bool ChackCubeShperHit(Cube& cube, Spher& spher);

//	球が立方体の当たったところを取得
Vector3 GetCubeHitPos(Cube& cube, Spher& spher);

//	球が立方体にあったった時に反発する
void SetReboundVectSpherBox(Base* obj_, Cube& cube);

//立方体の面の法線ベクトルを取得
Vector3 GetNormalVector(Cube& cube, int idx);

//四角形の法線ベクトルを取得する
Vector3 GetNormalVector(Box& box);

//カメラからの距離
float GetCameraLength(Vector3& pos_3D);

//	線分と矩形との最短距離
float GetLineBoxLength(Line& line, Box& box);

//　線分に一番近い矩形の座標
Vector3 GetLineBoxNearPos(Line& line, Box& box);

//	線分と矩形があたった座標
Vector3 GetLineBoxHitPos(Line& line, Box& box);

//	矩形の中に点が入っているか
bool ChaekHitPointBox(Vector3& point, Box& box);

//矩形と球の当たり判定
bool CheckHitSpherBox(Box box, Spher& spher);

//球と矩形が当たった座標
Vector3 GetHitSpherBoxPos(Box box, Spher& spher);

//	線分と矩形のあたり判定３Ｄ
bool CheckHitLineBox(Line& line, Box& box);

//	カプセルと矩形のあたり判定３Ｄ
bool CheckHitCapsuleBox(Capsule& capsule, Box& box);

//	線と立方体のあたり判定
bool CheckHitLineCube(Line& line, Cube& cube);

//	カプセルと立方体のあたり判定
bool CheckHitCapsuleCube(Capsule& capsule, Cube& cube);

//カプセルと立方体の当たった座標
Vector3 GetHitCapsuleCubePos(Capsule& capsule, Cube& cube);

//立方体とカプセルの当たった座標に一番近いカプセルの線の座標
Vector3 GetHitCubeCapsulePos(Capsule& capsule, Cube& cube);

//線分と矩形の辺の当たった座標
Vector3 GetHitLineEdgeOfBox(Line line,Box box);

//	矩形の中心をとる
Vector3 GetBoxCenter(Box& box);

//	二つの点から立方体の構造体に変更する
Cube MakeCubeTowPos(Vector3& pos1, Vector3& pos2) ;

//	二つの点から立方体の構造体に変更する2D
Box MakeBoxTowPos( Vector3& pos1,  Vector3& pos2);
