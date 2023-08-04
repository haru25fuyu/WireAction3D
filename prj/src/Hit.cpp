#include "WinMain.h"
#include "Hit.h"
#include "Base.h"
#include <cmath>


//---------------------------------------------------------------------------------
//	���Ƌ��̓����蔻��
//---------------------------------------------------------------------------------
bool CheckLineBallHit(Vector3& line_start, Vector3& line_goal, Vector3& ball_pos, float ball_radius)
{
	//1:���̂ǂ��炩�̍��W���������Ă��邩
	if (GetVector3Distance(line_start, ball_pos) <= ball_radius) {
		return true;
	}
	if (GetVector3Distance(line_goal, ball_pos) <= ball_radius) {
		return true;
	}
	//�Q�F��̍��W�̓����ɂ��邩
	Vector3 dir_sg = line_goal - line_start;
	Vector3 dir_sb = ball_pos - line_start;
	if (GetVector3Dot(dir_sg, dir_sb) < 0.0f) {
		return false;
	}
	Vector3 dir_gs = line_start - line_goal;
	Vector3 dir_gb = ball_pos - line_goal;
	if (GetVector3Dot(dir_gs, dir_gb) < 0.0f) {
		return false;
	}
	//3�F����̈�ԋ߂����W���擾�����蔻��
	//���̃X�^�[�g����S�[�����W�ւ̃x�N�g���͐��K������
	dir_sg.normalize();
	float dot_line = GetVector3Dot(dir_sg, dir_sb);
	//����̈�ԋ߂����W�̐ݒ�
	Vector3 line_pos = line_start + dir_sg * dot_line;
	if (GetVector3Distance(line_pos, ball_pos) <= ball_radius) {
		return true;
	}

	return false;

}

//�_�ƈ�ԋ߂�����̍��W
Vector3 GetPointLineNearPos(Line& line, Vector3& point) {

	//�Q�F��̍��W�̓����ɂ��邩
	Vector3 dir_sg = line.g_pos - line.s_pos;
	Vector3 dir_sb = point - line.s_pos;
	if (GetVector3Dot(dir_sg, dir_sb) < 0.0f) {
		return line.s_pos;
	}
	Vector3 dir_gs = line.s_pos - line.g_pos;
	Vector3 dir_gb = point - line.g_pos;
	if (GetVector3Dot(dir_gs, dir_gb) < 0.0f) {
		return line.g_pos;
	}
	//3�F����̈�ԋ߂����W���擾�����蔻��
	//���̃X�^�[�g����S�[�����W�ւ̃x�N�g���͐��K������
	dir_sg.normalize();
	float dot_line = GetVector3Dot(dir_sg, dir_sb);
	//����̈�ԋ߂����W�̐ݒ�
	return (line.s_pos + dir_sg * dot_line);

}

//---------------------------------------------------------------------------------
//	���Ɠ_�̍ŒZ����
//---------------------------------------------------------------------------------
float GetLinePointLength(Line& line, Vector3& point) {
	float length;
	//1:���̂ǂ��炩�̍��W���������Ă��邩
	length = GetVector3Distance(line.s_pos, point);
	if (length > GetVector3Distance(line.g_pos, point))
		length = GetVector3Distance(line.g_pos, point);

	//�Q�F��̍��W�̓����ɂ��邩
	Vector3 dir_sg = line.g_pos - line.s_pos;
	Vector3 dir_sb = point - line.s_pos;
	if (GetVector3Dot(dir_sg, dir_sb) < 0.0f) {
		return length;
	}
	Vector3 dir_gs = line.s_pos - line.g_pos;
	Vector3 dir_gb = point - line.g_pos;
	if (GetVector3Dot(dir_gs, dir_gb) < 0.0f) {
		return length;
	}
	//3�F����̈�ԋ߂����W���擾�����蔻��
	//���̃X�^�[�g����S�[�����W�ւ̃x�N�g���͐��K������
	dir_sg.normalize();
	float dot_line = GetVector3Dot(dir_sg, dir_sb);
	//����̈�ԋ߂����W�̐ݒ�
	Vector3 line_pos = line.s_pos + dir_sg * dot_line;
	if (GetVector3Distance(line_pos, point) < length) {
		return GetVector3Distance(line_pos, point);
	}
	return length;
}

//---------------------------------------------------------------------------------
//����̓_�������͈̔͂ɂ��邩������
// ---------------------------------------------------------------------------------
bool ChecLieWithinLineSegment(Line line, Vector3 p) {
	//���̓�_����_�̃x�N�g�����擾
	Vector3 vect_ps = p - line.s_pos;
	Vector3 vect_pg = p - line.g_pos;
	vect_ps.normalize();
	vect_pg.normalize();
	//���̓�̃x�N�g�����}�C�i�X�Ȃ�͈͓��ɂ���
	float dot_p1_s1g1 = GetVector3Dot(vect_ps, vect_pg);
	return (dot_p1_s1g1 < 0.0f);
}

//---------------------------------------------------------------------------------
//�_�Ɛ����̂Q�_�̋����̒Z���ق��̓_���擾����
// ---------------------------------------------------------------------------------
float GetNearPointForLineSegment(Line line, Vector3 p) {
	float length_pg = GetVector3Distance(line.g_pos, p);
	float length_ps = GetVector3Distance(line.s_pos, p);
	if (length_ps <= length_pg) {
		return length_ps;
	}
	return length_pg;
}


//---------------------------------------------------------------------------------
//3D��ԏ�̓�̐��̋���
// ---------------------------------------------------------------------------------
float GetLineLength(Line& line1, Line& line2) {
	//���̃x�N�g�����擾
	Vector3 line1_vect = line1.g_pos - line1.s_pos;
	Vector3 line2_vect = line2.g_pos - line2.s_pos;
	//���̊J�n���W�ǂ����̃x�N�g�����擾
	Vector3 s1s2_vect = line1.s_pos - line2.s_pos;

	//��̐��̓���
	float dot_line1_2 = GetVector3Dot(line1_vect, line2_vect);
	//��̐��̊J�n���W�ǂ����̃x�N�g���Ɛ��̃x�N�g���̓��ς��擾
	float dot_line1_s1s2 = GetVector3Dot(line1_vect, s1s2_vect);
	float dot_line2_s1s2 = GetVector3Dot(line2_vect, s1s2_vect);
	//���̃x�N�g���𐳋K������
	line1_vect.normalize();
	line2_vect.normalize();
	//��̐��K��������������ς��擾
	float dot_line1_2nomal = GetVector3Dot(line1_vect, line2_vect);

	//���K������n���ς�1,-1�̏ꍇ��̐��͕��s�ł���ł���
	if (dot_line1_2nomal == 1 || dot_line1_2nomal == -1) {
		//�J�n���W�ǂ����̒������擾
		float length_s1s2 = s1s2_vect.GetLength();
		//���K��
		s1s2_vect.normalize();
		//�J�n���W�ǂ����̃x�N�g���Ɛ��̓��ς��O�ł���΂��ꂪ��ԋ߂�
		float dot_line1_s1s2 = GetVector3Dot(s1s2_vect, line1_vect);
		if (dot_line1_s1s2 == 0) {
			return length_s1s2;
		}
		//�S�[�����W�ǂ������m�F����
		Vector3 vect_g1g2 = line2.g_pos - line1.g_pos;
		float length_g1g2 = vect_g1g2.GetLength();
		vect_g1g2.normalize();
		float dot_line1_g1g2 = GetVector3Dot(vect_g1g2, line1_vect);
		if (dot_line1_g1g2 == 0) {
			return length_g1g2;
		}

		//���͈̔͒��ɑ���̊J�n���W���S�[�����W�����邩��m��ד����Ă�����
		//���̍��W���g���ċ����𒲂ׂ�
		if (ChecLieWithinLineSegment(line1, line2.s_pos)) {
			Vector3 point = line1.s_pos + line1_vect * dot_line1_s1s2;
			return GetVector3Distance(point, line2.s_pos);
		}
		if (ChecLieWithinLineSegment(line1, line2.g_pos)) {
			Vector3 dot_line1_s1g2 = line2.g_pos - line1.s_pos;
			Vector3 point = line1.s_pos + line1_vect * GetVector3Dot(line1_vect, dot_line1_s1g2);
			return GetVector3Distance(point, line2.g_pos);
		}
		if (ChecLieWithinLineSegment(line2, line1.s_pos)) {
			Vector3 dot_line1_s1s1 = line1.g_pos - line2.s_pos;
			Vector3 point = line2.s_pos + line2_vect * dot_line1_s1s2;
			return GetVector3Distance(point, line1.s_pos);
		}
		float length[4]{
			GetVector3Distance(line1.s_pos,line2.s_pos),
			GetVector3Distance(line1.s_pos,line2.g_pos),
			GetVector3Distance(line1.g_pos,line2.s_pos),
			GetVector3Distance(line1.g_pos,line2.g_pos)
		};
		//���̊e���W�ǂ����̋��������߂Ĉ�ԒZ���l�����߂�
		float min_length = 10000000000000.0f;
		for (int i = 0; i < 4; ++i) {
			if (min_length < length[i])
				continue;
			min_length = length[i];
		}
		return min_length;
	}
	//���s�łȂ������ꍇ
	//�l�b�g�����Q�Ƃ��Đ��P�̊J�n���W����ŒZ�_�܂ł̋��������߂�
	//http://marupeke296.com/COL_3D_No27_CapsuleCapsule.html
	float scalar1 = dot_line1_2 * dot_line2_s1s2 - 1 * dot_line1_s1s2;
	float scalar2 = 1 - dot_line1_2 * dot_line1_2;
	float length_s1p1 = scalar1 / scalar2;

	//���P��̍ŒZ�_�����߂�
	Vector3 point1 = line1.s_pos + line1_vect * length_s1p1;
	Vector3 vect_s2p1 = point1 - line2.s_pos;

	//��̓_���g���ē�_�ڂ������߂�
	line2_vect.normalize();
	float length_s2p2 = GetVector3Dot(line2_vect, vect_s2p1);
	Vector3 point2 = line2.s_pos + line2_vect * length_s2p2;

	//���̍ŒZ�_�������̒��ɂ��邩�𔻒肵
	if (!ChecLieWithinLineSegment(line1, point1)) {
		//�����Ă��Ȃ�������
		Vector3 vect_p1s1 = line1.s_pos - point1;
		Vector3 vect_p2s2 = line2.s_pos - point2;
		vect_p1s1.normalize();
		//�����̓�̍��W�ɋ߂��Ƃ��܂ňړ�����
		point1 += vect_p1s1 * GetNearPointForLineSegment(line1, point1);
		vect_s2p1.clear();
		//�_�̈���������̂ł�������̓_���Ē�`����
		vect_s2p1 = point1 - line2.s_pos;
		length_s2p2 = GetVector3Dot(line2_vect, vect_s2p1);
		point2 = line2.s_pos + line2_vect * length_s2p2;
	}

	//����̓_�������Ă��邩����
	if (!ChecLieWithinLineSegment(line2, point2)) {
		Vector3 vect_p1s1 = line1.s_pos - point1;
		Vector3 vect_p2s2 = line2.s_pos - point2;
		vect_p2s2.normalize();
		//�����̓�̍��W�ɋ߂��Ƃ��܂ňړ�����
		point2 += vect_p2s2 * GetNearPointForLineSegment(line2, point2);
		// �_�̈���������̂ł�������̓_���Ē�`����
		Vector3 vect_p2s1 = point2 - line1.s_pos;
		float dot_line1_p2 = GetVector3Dot(line1_vect, vect_p2s1);
		Vector3 point1_2 = line1.s_pos + line1_vect * dot_line1_p2;
		//���̓_���͈͓��Ȃ炻�̓�_�̋���
		if (ChecLieWithinLineSegment(line1, point1_2))
			return GetVector3Distance(point1_2, point2);
	}

	return GetVector3Distance(point1, point2);
}

//������̍ŒZ�_���Ȃ���(��_)
Line GetLineConnectLine(Line& line1, Line& line2)
{
	Line connect_line;
	//���̃x�N�g�����擾
	Vector3 line1_vect = line1.g_pos - line1.s_pos;
	Vector3 line2_vect = line2.g_pos - line2.s_pos;
	//���̊J�n���W�ǂ����̃x�N�g�����擾
	Vector3 s1s2_vect = line1.s_pos - line2.s_pos;

	//��̐��̓���
	float dot_line1_2 = GetVector3Dot(line1_vect, line2_vect);
	//��̐��̊J�n���W�ǂ����̃x�N�g���Ɛ��̃x�N�g���̓��ς��擾
	float dot_line1_s1s2 = GetVector3Dot(line1_vect, s1s2_vect);
	float dot_line2_s1s2 = GetVector3Dot(line2_vect, s1s2_vect);
	//���̃x�N�g���𐳋K������
	line1_vect.normalize();
	line2_vect.normalize();
	//��̐��K��������������ς��擾
	float dot_line1_2nomal = GetVector3Dot(line1_vect, line2_vect);

	//���K������n���ς�1,-1�̏ꍇ��̐��͕��s�ł���ł���
	if (dot_line1_2nomal == 1 || dot_line1_2nomal == -1) {
		//�J�n���W�ǂ����̒������擾
		float length_s1s2 = s1s2_vect.GetLength();
		//���K��
		s1s2_vect.normalize();
		//�J�n���W�ǂ����̃x�N�g���Ɛ��̓��ς��O�ł���΂��ꂪ��ԋ߂�
		float dot_line1_s1s2 = GetVector3Dot(s1s2_vect, line1_vect);
		if (dot_line1_s1s2 == 0) {
			connect_line.s_pos = line1.s_pos;
			connect_line.g_pos = line2.s_pos;
			return connect_line;
		}
		//�S�[�����W�ǂ������m�F����
		Vector3 vect_g1g2 = line2.g_pos - line1.g_pos;
		float length_g1g2 = vect_g1g2.GetLength();
		vect_g1g2.normalize();
		float dot_line1_g1g2 = GetVector3Dot(vect_g1g2, line1_vect);
		if (dot_line1_g1g2 == 0)
		{
			connect_line.s_pos = line1.g_pos;
			connect_line.g_pos = line2.g_pos;
			return connect_line;
		}

		//���͈̔͒��ɑ���̊J�n���W���S�[�����W�����邩��m��ד����Ă�����
		//���̍��W���g���ċ����𒲂ׂ�
		if (ChecLieWithinLineSegment(line1, line2.s_pos)) {
			Vector3 point = line1.s_pos + line1_vect * dot_line1_s1s2;
			connect_line.s_pos = point;
			connect_line.g_pos = line2.s_pos;
			return connect_line;
		}
		if (ChecLieWithinLineSegment(line1, line2.g_pos)) {
			Vector3 dot_line1_s1g2 = line2.g_pos - line1.s_pos;
			Vector3 point = line1.s_pos + line1_vect * GetVector3Dot(line1_vect, dot_line1_s1g2);
			connect_line.s_pos = point;
			connect_line.g_pos = line2.g_pos;
			return connect_line;
		}
		if (ChecLieWithinLineSegment(line2, line1.s_pos)) {
			Vector3 dot_line1_s1s1 = line1.g_pos - line2.s_pos;
			Vector3 point2 = line2.s_pos + line2_vect * dot_line1_s1s2;
			connect_line.s_pos = line1.s_pos;
			connect_line.g_pos = point2;
			return connect_line;
		}
		float length[4]{
			GetVector3Distance(line1.s_pos,line2.s_pos),
			GetVector3Distance(line1.s_pos,line2.g_pos),
			GetVector3Distance(line1.g_pos,line2.s_pos),
			GetVector3Distance(line1.g_pos,line2.g_pos)
		};
		Line line[4];
		line[0].s_pos = line1.s_pos; line[0].g_pos = line2.s_pos;
		line[1].s_pos = line1.s_pos; line[1].g_pos = line2.g_pos;
		line[2].s_pos = line1.g_pos; line[2].g_pos = line2.s_pos;
		line[3].s_pos = line1.g_pos; line[3].g_pos = line2.g_pos;
		//���̊e���W�ǂ����̋��������߂Ĉ�ԒZ���l�����߂�
		float min_length = 10000000000000.0f;
		int idx = -1;
		for (int i = 0; i < 4; ++i) {
			if (min_length < length[i])
				continue;
			min_length = length[i];
			idx = i;
		}
		return line[idx];
	}
	//���s�łȂ������ꍇ
	//�l�b�g�����Q�Ƃ��Đ��P�̊J�n���W����ŒZ�_�܂ł̋��������߂�
	//http://marupeke296.com/COL_3D_No27_CapsuleCapsule.html
	float scalar1 = dot_line1_2 * dot_line2_s1s2 - 1 * dot_line1_s1s2;
	float scalar2 = 1 - dot_line1_2 * dot_line1_2;
	float length_s1p1 = scalar1 / scalar2;

	//���P��̍ŒZ�_�����߂�
	Vector3 point1 = line1.s_pos + line1_vect * length_s1p1;
	Vector3 vect_s2p1 = point1 - line2.s_pos;

	//��̓_���g���ē�_�ڂ������߂�
	line2_vect.normalize();
	float length_s2p2 = GetVector3Dot(line2_vect, vect_s2p1);
	Vector3 point2 = line2.s_pos + line2_vect * length_s2p2;

	//���̍ŒZ�_�������̒��ɂ��邩�𔻒肵
	if (!ChecLieWithinLineSegment(line1, point1)) {
		//�����Ă��Ȃ�������
		Vector3 vect_p1s1 = line1.s_pos - point1;
		Vector3 vect_p2s2 = line2.s_pos - point2;
		vect_p1s1.normalize();
		//�����̓�̍��W�ɋ߂��Ƃ��܂ňړ�����
		point1 += vect_p1s1 * GetNearPointForLineSegment(line1, point1);
		vect_s2p1.clear();
		//�_�̈���������̂ł�������̓_���Ē�`����
		vect_s2p1 = point1 - line2.s_pos;
		length_s2p2 = GetVector3Dot(line2_vect, vect_s2p1);
		point2 = line2.s_pos + line2_vect * length_s2p2;
	}

	//����̓_�������Ă��邩����
	if (!ChecLieWithinLineSegment(line2, point2)) {
		Vector3 vect_p1s1 = line1.s_pos - point1;
		Vector3 vect_p2s2 = line2.s_pos - point2;
		vect_p2s2.normalize();
		//�����̓�̍��W�ɋ߂��Ƃ��܂ňړ�����
		point2 += vect_p2s2 * GetNearPointForLineSegment(line2, point2);
		// �_�̈���������̂ł�������̓_���Ē�`����
		Vector3 vect_p2s1 = point2 - line1.s_pos;
		float dot_line1_p2 = GetVector3Dot(line1_vect, vect_p2s1);
		Vector3 point1_2 = line1.s_pos + line1_vect * dot_line1_p2;
		//���̓_���͈͓��Ȃ炻�̓�_�̋���
		if (ChecLieWithinLineSegment(line1, point1_2)) {
			connect_line.s_pos = point1_2;
			connect_line.g_pos = point2;
			return connect_line;
		}
	}
	connect_line.s_pos = point1;
	connect_line.g_pos = point2;
	return connect_line;
	
}

//---------------------------------------------------------------------------------
//	�����m�̓����蔻��
//---------------------------------------------------------------------------------
bool CheckBallHit(Vector3& p0, float r0, Vector3& p1, float r1)
{
	float distance = GetVector3Distance(p0, p1);

	if (distance < r0 + r1) {
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------
//	�J�v�Z�������̓����蔻��
//---------------------------------------------------------------------------------
bool CheckCapsuleHit(Capsule& capsule1, Capsule& capsule2) {
	float length = GetLineLength(capsule1.line, capsule2.line);
	return (length < (capsule1.radius + capsule2.radius));
}


//---------------------------------------------------------------------------------
//	�����̂Ƌ��̓����蔻��
//---------------------------------------------------------------------------------
bool ChackCubeShperHit(Cube& cube, Spher& spher)
{
	int num = 0;
	//���̍��W���L���[�u�̒��ɓ����Ă��邩�𒲂ׂ�
	for (int i = 0; i < 6; ++i) {
		Vector3 nomal_vect = GetNormalVector(cube, i);
		Vector3 center_pos = GetBoxCenter(cube.surface[i]);
		Vector3 cs_vect = spher.pos - center_pos;
		//�ʂƓ��������� true
		if (CheckHitSpherBox(cube.surface[i], spher)) {
			return true;
		}
		cs_vect.normalize();
		if (GetVector3Dot(nomal_vect, cs_vect) > 0.0f)
			return false;
		++num;
	}
	return true;

}

//---------------------------------------------------------------------------------
//	���������̂̓��������Ƃ�����擾
//---------------------------------------------------------------------------------
Vector3 GetCubeHitPos(Cube& cube, Spher& spher)
{
	if (!ChackCubeShperHit(cube, spher))
		return Vector3(0.0f, 0.0f, 0.0f);
	Vector3 nomal_vect[6];
	Vector3 center_pos[6];
	int num = 0;
	for (int i = 0; i < 6; ++i, ++num) {
		nomal_vect[i] = GetNormalVector(cube, i);
		center_pos[i] = GetBoxCenter(cube.surface[i]);
		Vector3 cs_vect = spher.pos - center_pos[i];
		float bp_length = GetVector3Dot(nomal_vect[i], cs_vect);
		if (bp_length <= spher.radius && bp_length > 0.0f) {
			nomal_vect[i] *= -1;
			return spher.pos + nomal_vect[i];
		}
		cs_vect.normalize();
		if (GetVector3Dot(nomal_vect[i], cs_vect) > 0.0f)
			break;
	}
	return spher.pos;
}

//---------------------------------------------------------------------------------
//	���������̂ɂ������������ɔ�������
//---------------------------------------------------------------------------------
void SetReboundVectSpherBox(Base* obj_, Cube& cube) {
	Spher spher;
	spher.pos = obj_->GetPos();
	spher.radius = obj_->GetRadius();
	//�L���[�u�Ƌ��i�I�u�W�F�N�g�j�����������ĂȂ�������֐��𔲂���
	for (int i = 0; i < 6; ++i) {
		if (!CheckHitSpherBox(cube.surface[i], spher))
			continue;
		Vector3 hit_pos = GetHitSpherBoxPos(cube.surface[i], spher);
		Vector3 normal = GetNormalVector(cube, i);
		Vector3 obj_vect = obj_->GetVect();
		Vector3 vect = obj_vect - (normal * GetVector3Dot(obj_vect, normal));
		obj_vect.normalize();
		if (0.0f <= GetVector3Dot(obj_vect, normal))	return;
		obj_->SetVect(vect);
		return;
	}
}

//�����̖̂ʂ̖@���x�N�g�����擾
Vector3 GetNormalVector(Cube& cube, int idx) {
	Vector3 normal_vect = GetNormalVector(cube.surface[idx]);
	Vector3 m_center_pos = GetBoxCenter(cube.surface[idx]);
	for (int i = 0; i < 6; ++i) {
		Vector3 center_pos = GetBoxCenter(cube.surface[i]);
		Vector3 vect = center_pos - m_center_pos;
		if (GetVector3Dot(normal_vect, vect) > 0.0f)
			normal_vect *= -1.0f;
	}
	normal_vect.normalize();
	return normal_vect;
}

//�l�p�`�̖@���x�N�g�����擾����
Vector3 GetNormalVector(Box& box) {
	float max_length = 1000000.0f;
	int max_length_num = 0;

	for (int i = 1; i < 5; ++i) {
		if (GetVector3Distance(box.vertex_pos[0], box.vertex_pos[i]) <= max_length)
			continue;
		max_length = GetVector3Distance(box.vertex_pos[0], box.vertex_pos[i]);
		max_length_num = i;
	}
	Vector3 vect_p_p[2];
	int idx = 0;
	for (int i = 1; i < 5; ++i) {
		if (i == max_length_num)
			continue;
		vect_p_p[idx] = box.vertex_pos[i] - box.vertex_pos[0];
		idx++;
		if (idx >= 2)
			break;
	}
	Vector3 cross_product;
	cross_product = GetVector3Cross(vect_p_p[0], vect_p_p[1]);
	cross_product.normalize();
	return cross_product;
}

//�J��������̋���
float GetCameraLength(Vector3& pos_3D)
{
	MATRIX view = GetCameraViewMatrix();
	MATRIX projection = GetCameraProjectionMatrix();
	MATRIX viewport = GetCameraViewportMatrix();

	VECTOR cpos = VTransform(pos_3D.VGet(), view);
	return cpos.z;
}

//---------------------------------------------------------------------------------
//	�����Ƌ�`�Ƃ̍ŒZ����
//----------------------------------------------------------------------------------
float GetLineBoxLength(Line& line, Box& box) {
	if (CheckHitLineBox(line, box))
		return 0.0f;


	Vector3 side_line[2] = {
		{box.vertex_pos[3] - box.vertex_pos[0] },
		{box.vertex_pos[1] - box.vertex_pos[0] }
	};
	Vector3 box_normal = GetVector3Cross(side_line[0], side_line[1]);
	box_normal.normalize();
	Vector3 vect_ps = line.s_pos - box.vertex_pos[0];
	Vector3 vect_pg = line.g_pos - box.vertex_pos[0];
	float dot_g = GetVector3Dot(box_normal, vect_pg);
	float dot_s = GetVector3Dot(box_normal, vect_ps);

	Vector3 vect_sg = line.g_pos - line.s_pos;
	float l_length = GetVector3Dot(box_normal, vect_sg);
	float length_percentage = fabsf(dot_s) / fabsf(l_length);
	vect_sg *= length_percentage;
	Vector3 cross_pos = line.s_pos + vect_sg;
	float length;

	if (dot_g >= 0 == dot_s >= 0) {
		if (dot_g != 0 || dot_s != 0) {
			dot_g > dot_s ? length = dot_s : length = dot_g;
			return length;
		}
	}
	if (ChaekHitPointBox(cross_pos, box)) {
		return 0.0f;
	}

	float min_length = 100000.0f;
	Line line_;
	for (int i = 1; i < 4; ++i) {
		line_.s_pos = box.vertex_pos[i - 1];
		line_.g_pos = box.vertex_pos[i];
		if (min_length < GetLinePointLength(line_, cross_pos))
			continue;
		min_length = GetLinePointLength(line_, cross_pos);
	}

	return min_length;
}

//---------------------------------------------------------------------------------
//�@�����Ɉ�ԋ߂���`�̍��W
//----------------------------------------------------------------------------------
Vector3 GetLineBoxNearPos(Line& line, Box& box) {
	if (CheckHitLineBox(line, box))
		return GetLineBoxHitPos(line, box);

	Vector3 side_line[2] = {
		{box.vertex_pos[3] - box.vertex_pos[0] },
		{box.vertex_pos[1] - box.vertex_pos[0] }
	};
	Vector3 box_normal = GetVector3Cross(side_line[0], side_line[1]);
	box_normal.normalize();
	Vector3 vect_ps = line.s_pos - box.vertex_pos[0];
	Vector3 vect_pg = line.g_pos - box.vertex_pos[0];
	float dot_g = GetVector3Dot(box_normal, vect_pg);
	float dot_s = GetVector3Dot(box_normal, vect_ps);

	Vector3 vect_sg = line.g_pos - line.s_pos;
	float length = GetVector3Dot(box_normal, vect_sg);
	float length_percentage = fabsf(dot_s) / fabsf(length);
	vect_sg *= length_percentage;
	Vector3 cross_pos = line.s_pos + vect_sg;
	//float length;
	bool sg = false;
	if (dot_g >= 0 == dot_s >= 0) {
		if (dot_g != 0 || dot_s != 0) {
			fabsf(dot_g) > fabsf(dot_s) ? sg = true : sg = false;
			if (sg) {
				return line.s_pos + box_normal * dot_s;
			}
			return line.s_pos + box_normal * dot_g;
		}
	}

	float min_length = 100000.0f;
	Line line_;
	int idx = 1;
	for (int i = 1; i < 4; ++i) {
		line_.s_pos = box.vertex_pos[i - 1];
		line_.g_pos = box.vertex_pos[i];
		if (min_length < GetLinePointLength(line_, cross_pos))
			continue;
		min_length = GetLinePointLength(line_, cross_pos);
		i = idx;
	}
	line_.s_pos = box.vertex_pos[idx - 1];
	line_.g_pos = box.vertex_pos[idx];
	return GetPointLineNearPos(line_, cross_pos);

}
//---------------------------------------------------------------------------------
//	�����Ƌ�`�������������W
//----------------------------------------------------------------------------------
Vector3 GetLineBoxHitPos(Line& line, Box& box)
{
	if (!CheckHitLineBox(line, box))
		return Vector3(0.0f, 0.0f, 0.0f);
	Vector3 box_normal = GetNormalVector(box);

	Vector3 vect_ps = line.s_pos - box.vertex_pos[0];
	Vector3 vect_pg = line.g_pos - box.vertex_pos[0];
	float dot_g = GetVector3Dot(box_normal, vect_pg);
	float dot_s = GetVector3Dot(box_normal, vect_ps);

	Vector3 vect_sg = line.g_pos - line.s_pos;
	float length = GetVector3Dot(box_normal, vect_sg);
	float length_percentage = fabsf(dot_s) / fabsf(length);
	vect_sg *= length_percentage;
	Vector3 cross_pos = line.s_pos + vect_sg;
	return cross_pos;
}

//---------------------------------------------------------------------------------
//	��`�̒��ɓ_�������Ă��邩
//----------------------------------------------------------------------------------
bool ChaekHitPointBox(Vector3& point, Box& box) {

	Vector3 cross[4];
	for (int i = 0; i < 4; ++i) {
		Vector3 side_line = box.vertex_pos[i] - box.vertex_pos[(i + 1) % 4];
		Vector3 vect_pp = point - box.vertex_pos[i];
		cross[i] = GetVector3Cross(side_line, vect_pp);
		for (int j = 0; j < 4; ++j) {
			if (j >= i)
				break;
			if (GetVector3Dot(cross[i], cross[j]) <= 0.0f) {
				return false;
			}
		}
	}
	return true;
}

//��`�Ƌ��̓����蔻��
bool CheckHitSpherBox(Box box, Spher& spher) {
	Vector3 normal_vect = GetNormalVector(box);
	for (int i = 0; i < 4; ++i) {
		if (CheckLineBallHit(box.vertex_pos[i], box.vertex_pos[(i + 1) % 4], spher.pos, spher.radius))
			return true;
	}
	Vector3 vect = spher.pos - box.vertex_pos[1];
	normal_vect.normalize();
	float tmp_ = GetVector3Dot(normal_vect, vect);
	if (fabsf(tmp_) <= spher.radius) {
		Vector3 hit_pos = spher.pos + normal_vect * (-1 * GetVector3Dot(normal_vect, vect));
		if (ChaekHitPointBox(hit_pos, box))
			return true;
	}
	return false;
}

//���Ƌ�`�������������W
Vector3 GetHitSpherBoxPos(Box box, Spher& spher) {
	Vector3 hit_pos;
	if (CheckHitSpherBox(box, spher))
		return hit_pos;

	float min_length = 1000.0f;
	for (int i = 0; i < 4; ++i) {
		Line line;
		line.s_pos = box.vertex_pos[i];
		line.g_pos = box.vertex_pos[(i + 1) % 4];
		if (CheckLineBallHit(line.s_pos, line.g_pos, spher.pos, spher.radius)) {
			Vector3 pos;
			pos = GetPointLineNearPos(line, spher.pos);
			if (min_length > GetVector3Distance(pos, spher.pos)) {
				hit_pos = pos;
				min_length = GetVector3Distance(pos, spher.pos);

			}
		}
	}
	Vector3 normal_vect = GetNormalVector(box);
	Vector3 vp_s_dir = spher.pos - box.vertex_pos[0];

	float length = GetVector3Dot(normal_vect, vp_s_dir);
	if (min_length > length) {
		return spher.pos + normal_vect * min_length;
	}
	return hit_pos;
}

//---------------------------------------------------------------------------------
//	�����Ƌ�`�̂����蔻��R�c
//----------------------------------------------------------------------------------
bool CheckHitLineBox(Line& line, Box& box) {

	Vector3 box_normal = GetNormalVector(box);

	Vector3 vect_ps = line.s_pos - box.vertex_pos[0];
	Vector3 vect_pg = line.g_pos - box.vertex_pos[0];
	float dot_g = GetVector3Dot(box_normal, vect_pg);
	float dot_s = GetVector3Dot(box_normal, vect_ps);

	if (dot_g >= 0 == dot_s >= 0) {
		if (dot_g != 0 || dot_s != 0) {
			return false;
		}
	}

	Vector3 vect_sg = line.g_pos - line.s_pos;
	float length = GetVector3Dot(box_normal, vect_sg);
	float length_percentage = fabsf(dot_s) / fabsf(length);
	vect_sg *= length_percentage;
	Vector3 cross_pos = line.s_pos + vect_sg;

	return ChaekHitPointBox(cross_pos, box);
}

//---------------------------------------------------------------------------------
//	�J�v�Z���Ƌ�`�̂����蔻��R�c
//----------------------------------------------------------------------------------
bool CheckHitCapsuleBox(Capsule& capsule, Box& box) {
	if (GetLineBoxLength(capsule.line, box) <= capsule.radius) {
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------
//	���Ɨ����̂̂����蔻��
//----------------------------------------------------------------------------------
bool CheckHitLineCube(Line& line, Cube& cube) {
	Vector3 nomal_vect[6];
	Vector3 center_pos[6];

	for (int i = 0; i < 6; ++i) {
		if (CheckHitLineBox(line, cube.surface[i]))
			return true;
	}
	return false;
}


// -------------------------------------------------------------------------------- -
//	�J�v�Z���Ɨ����̂̂����蔻��
//----------------------------------------------------------------------------------
bool CheckHitCapsuleCube(Capsule& capsule, Cube& cube) {
	if (CheckHitLineCube(capsule.line, cube))
		return true;
	for (int i = 0; i < 6; ++i) {
		if (GetLineBoxLength(capsule.line, cube.surface[i]) <= capsule.radius)
			return true;
	}
	return false;
}

//�J�v�Z���Ɨ����̂̓����������W
Vector3 GetHitCapsuleCubePos(Capsule& capsule, Cube& cube) {
	Vector3 pos;
	if (!CheckHitCapsuleCube(capsule, cube))
		return pos;
	std::vector<Vector3> hit_pos;
	for (int i = 0; i < 6; ++i) {
		if (CheckHitLineBox(capsule.line, cube.surface[i])) {
			hit_pos.emplace_back(GetLineBoxHitPos(capsule.line, cube.surface[i]));
		}
		else {
			hit_pos.emplace_back(GetLineBoxNearPos(capsule.line, cube.surface[i]));
		}
	}

	float s_hit_length_near = 100000.0f;
	int idx = 0;
	for (int i = 0; i < hit_pos.size(); i++) {
		if (s_hit_length_near >= GetVector3Distance(capsule.line.s_pos, hit_pos[i])) {
			s_hit_length_near = GetVector3Distance(capsule.line.s_pos, hit_pos[i]);
			idx = i;
		}
	}

	return hit_pos[idx];
}

//�����̂ƃJ�v�Z���̓����������W�Ɉ�ԋ߂��J�v�Z���̐��̍��W
Vector3 GetHitCubeCapsulePos(Capsule& capsule, Cube& cube) {
	Vector3 pos;
	if (!CheckHitCapsuleCube(capsule, cube))
		return pos;
	std::vector<Vector3> hit_pos;
	for (int i = 0; i < 6; ++i) {
		if (CheckHitLineBox(capsule.line, cube.surface[i])) {
			hit_pos.emplace_back(GetLineBoxHitPos(capsule.line, cube.surface[i]));
		}
		else {
			hit_pos.emplace_back(GetLineBoxNearPos(capsule.line, cube.surface[i]));
		}
	}

	float s_hit_length_near = 100000.0f;
	int idx = 0;
	for (int i = 0; i < hit_pos.size(); i++) {
		if (s_hit_length_near >= GetVector3Distance(capsule.line.s_pos, hit_pos[i])) {
			s_hit_length_near = GetVector3Distance(capsule.line.s_pos, hit_pos[i]);
			idx = i;
		}
	}

	Vector3 cs_h_dir = hit_pos[idx] - capsule.line.s_pos;
	Vector3 capeule_vect = capsule.line.g_pos - capsule.line.s_pos;
	capeule_vect.normalize();
	float length = GetVector3Dot(capeule_vect, cs_h_dir);
	return capsule.line.s_pos + capeule_vect * length;
}

Vector3 GetHitLineEdgeOfBox(Line line, Box box)
{
	for (int i = 0; i < 4; ++i) {
		Line edge;
		edge.s_pos = box.vertex_pos[i];
		edge.g_pos = box.vertex_pos[(i + 1) % 4];
		if (GetLineLength(line, edge) != 0.0f)
			continue;
		Line line = GetLineConnectLine(line, edge);
	}
	return Vector3();
}

//---------------------------------------------------------------------------------
//	��`�̒��S���Ƃ�
//---------------------------------------------------------------------------------
Vector3 GetBoxCenter(Box& box) {
	float max_length = 0;
	int idx = 0;

	for (int i = 1; i < 5; ++i) {
		if (GetVector3Distance(box.vertex_pos[0], box.vertex_pos[i]) <= max_length)
			continue;
		max_length = GetVector3Distance(box.vertex_pos[0], box.vertex_pos[i]);
		idx = i;
	}

	Vector3 vect = box.vertex_pos[idx] - box.vertex_pos[0];
	float length = vect.GetLength();
	vect.SetLength(length * 0.5f);
	return box.vertex_pos[0] + vect;
}

//---------------------------------------------------------------------------------
//	��̓_���痧���̂̍\���̂ɕύX����
//---------------------------------------------------------------------------------
Cube MakeCubeTowPos(Vector3& pos1, Vector3& pos2) {
	Cube cube;
	Vector3 vertex_pos[8]{
		pos1,Vector3(pos1.x,pos2.y,pos1.z),Vector3(pos1.x,pos2.y,pos2.z),
		Vector3(pos1.x,pos1.y,pos2.z),Vector3(pos2.x,pos1.y,pos2.z),
		pos2,Vector3(pos2.x,pos2.y,pos1.z),Vector3(pos2.x,pos1.y,pos1.z)
	};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cube.surface[i].vertex_pos[j] = vertex_pos[(j + (i * 2)) % 8];
		}
	}

	cube.surface[4].vertex_pos[0] = vertex_pos[0];
	cube.surface[4].vertex_pos[1] = vertex_pos[3];
	cube.surface[4].vertex_pos[2] = vertex_pos[4];
	cube.surface[4].vertex_pos[3] = vertex_pos[7];
	cube.surface[5].vertex_pos[0] = vertex_pos[1];
	cube.surface[5].vertex_pos[1] = vertex_pos[2];
	cube.surface[5].vertex_pos[2] = vertex_pos[5];
	cube.surface[5].vertex_pos[3] = vertex_pos[6];

	return cube;
}

//---------------------------------------------------------------------------------
//	��̓_�����`�̍\���̂ɕύX����2D
//---------------------------------------------------------------------------------
Box MakeBoxTowPos(Vector3& pos1, Vector3& pos2) {
	Box box;
	float y_length = pos2.y - pos1.y;
	Vector3 vertex_pos[4]{
		pos1,Vector3(pos1.x,pos2.y ,pos2.z),
		pos2,Vector3(pos2.x,pos1.y,pos1.z)
	};
	for (int i = 0; i < 4; ++i) {
		box.vertex_pos[i] = vertex_pos[i];
	}

	return box;
}