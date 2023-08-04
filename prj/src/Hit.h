#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Base.h"

//	���Ƌ��̓����蔻��
bool CheckLineBallHit( Vector3 &line_start, Vector3 &line_goal, Vector3 &ball_pos, float ball_radius );

//�_�ƈ�ԋ߂�����̍��W
Vector3 GetPointLineNearPos(Line& line, Vector3& point);

//	���Ɠ_�̍ŒZ����
float GetLinePointLength(Line& line, Vector3& point);

//����̓_�������͈̔͂ɂ��邩������
bool ChecLieWithinLineSegment(Line line, Vector3 p);

//�_�Ɛ����̂Q�_�̋����̒Z���ق��̓_�̋������擾
float GetNearPointForLineSegment(Line line, Vector3 p);

//3D��ԏ�̓�̐��̋���
float GetLineLength(Line& line1, Line& line2);

//������̍ŒZ�_���Ȃ���(��_)
Line GetLineConnectLine(Line& Line1,Line& line2);

//	�����m�̓����蔻��
bool CheckBallHit( const Vector3 &p0, const float r0, const Vector3 &p1, const float r1 );

//	�J�v�Z�������̓����蔻��
bool CheckCapsuleHit(Capsule& capsule1, Capsule& capsule2);

//	�����̂Ƌ��̓����蔻��
bool ChackCubeShperHit(Cube& cube, Spher& spher);

//	���������̂̓��������Ƃ�����擾
Vector3 GetCubeHitPos(Cube& cube, Spher& spher);

//	���������̂ɂ������������ɔ�������
void SetReboundVectSpherBox(Base* obj_, Cube& cube);

//�����̖̂ʂ̖@���x�N�g�����擾
Vector3 GetNormalVector(Cube& cube, int idx);

//�l�p�`�̖@���x�N�g�����擾����
Vector3 GetNormalVector(Box& box);

//�J��������̋���
float GetCameraLength(Vector3& pos_3D);

//	�����Ƌ�`�Ƃ̍ŒZ����
float GetLineBoxLength(Line& line, Box& box);

//�@�����Ɉ�ԋ߂���`�̍��W
Vector3 GetLineBoxNearPos(Line& line, Box& box);

//	�����Ƌ�`�������������W
Vector3 GetLineBoxHitPos(Line& line, Box& box);

//	��`�̒��ɓ_�������Ă��邩
bool ChaekHitPointBox(Vector3& point, Box& box);

//��`�Ƌ��̓����蔻��
bool CheckHitSpherBox(Box box, Spher& spher);

//���Ƌ�`�������������W
Vector3 GetHitSpherBoxPos(Box box, Spher& spher);

//	�����Ƌ�`�̂����蔻��R�c
bool CheckHitLineBox(Line& line, Box& box);

//	�J�v�Z���Ƌ�`�̂����蔻��R�c
bool CheckHitCapsuleBox(Capsule& capsule, Box& box);

//	���Ɨ����̂̂����蔻��
bool CheckHitLineCube(Line& line, Cube& cube);

//	�J�v�Z���Ɨ����̂̂����蔻��
bool CheckHitCapsuleCube(Capsule& capsule, Cube& cube);

//�J�v�Z���Ɨ����̂̓����������W
Vector3 GetHitCapsuleCubePos(Capsule& capsule, Cube& cube);

//�����̂ƃJ�v�Z���̓����������W�Ɉ�ԋ߂��J�v�Z���̐��̍��W
Vector3 GetHitCubeCapsulePos(Capsule& capsule, Cube& cube);

//�����Ƌ�`�̕ӂ̓����������W
Vector3 GetHitLineEdgeOfBox(Line line,Box box);

//	��`�̒��S���Ƃ�
Vector3 GetBoxCenter(Box& box);

//	��̓_���痧���̂̍\���̂ɕύX����
Cube MakeCubeTowPos(Vector3& pos1, Vector3& pos2) ;

//	��̓_���痧���̂̍\���̂ɕύX����2D
Box MakeBoxTowPos( Vector3& pos1,  Vector3& pos2);
