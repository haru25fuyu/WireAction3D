#include "Main.h"
#include "SpherHit.h"
#include "Hit.h"

SpherHit::SpherHit()
{

	m_target_pos_memory.clear();
	m_target_vect_memory.clear();

}

SpherHit::~SpherHit()
{

	m_target_pos_memory.clear();
	m_target_vect_memory.clear();

}

void SpherHit::UpDate(Base* obj_, std::vector<Base*>& target_)
{
	ChackCubeHit();
	CheckHitSpher();
	m_target_pos_memory.clear();
	m_target_vect_memory.clear();
	for (size_t i = 0; i < m_target_info.size(); ++i) {
		m_target_pos_memory.resize(i + 1);
		m_target_vect_memory.resize(i + 1);
		m_target_pos_memory[i] = m_target_info[i]->GetPos();
		m_target_vect_memory[i] = m_target_info[i]->GetVect();
	}
	for (size_t j = 0; j < target_.size(); ++j) {
		bool de = false;
		for (size_t i = 0; i < m_target_info.size(); ++i) {
			if (m_target_info[i]->GetSerialNumber() == target_[j]->GetSerialNumber()) {
				de = true;
				break;
			}
		}
		if (!de);
		size_t size = m_target_info.size();
		m_target_info.resize(size + 1);
		m_target_info[size] = target_[j];
	}
	m_pos_memory = m_info->GetPos();
	m_vect_memory = m_info->GetVect();
	m_info = obj_;
}

void SpherHit::Set(Base* obj_, std::vector<Base*> target_) {
	for (size_t j = 0; j < target_.size(); ++j) {
		bool de = false;
		for (size_t i = 0; i < m_target_info.size(); ++i) {
			if (m_target_info[i]->GetSerialNumber() == target_[j]->GetSerialNumber()) {
				de = true;
				break;
			}
		}
		if (!de);
		size_t size = m_target_info.size();
		m_target_info.resize(size + 1);
		m_target_info[size] = target_[j];
	}
	m_info = obj_;
}


//---------------------------------------------------------------------------------
//	���Ƌ��̓����蔻��
//---------------------------------------------------------------------------------
bool SpherHit::CheckLineHit(Vector3& line_start, Vector3& line_goal)
{
	//1:���̂ǂ��炩�̍��W���������Ă��邩
	Vector3 spher_pos = m_info->GetPos();
	float	spher_r = m_info->GetRadius();

	if (GetVector3Distance(line_start, spher_pos) <= spher_r) {
		return true;
	}
	if (GetVector3Distance(line_goal, spher_pos) <= spher_r) {
		return true;
	}
	//�Q�F��̍��W�̓����ɂ��邩
	Vector3 dir_sg = line_goal - line_start;
	Vector3 dir_sb = spher_pos - line_start;
	if (GetVector3Dot(dir_sg, dir_sb) < 0.0f) {
		return false;
	}
	Vector3 dir_gs = line_start - line_goal;
	Vector3 dir_gb = spher_pos - line_goal;
	if (GetVector3Dot(dir_gs, dir_gb) < 0.0f) {
		return false;
	}
	//3�F����̈�ԋ߂����W���擾�����蔻��
	//���̃X�^�[�g����S�[�����W�ւ̃x�N�g���͐��K������
	dir_sg.normalize();
	float dot_line = GetVector3Dot(dir_sg, dir_sb);
	//����̈�ԋ߂����W�̐ݒ�
	Vector3 line_pos = line_start + dir_sg * dot_line;
	if (GetVector3Distance(line_pos, spher_pos) <= spher_r) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�����m�̓����蔻��
//---------------------------------------------------------------------------------
void SpherHit::CheckHitSpher()
{
	//�����̏���ϐ��ɑ��
	Vector3 spher_pos = m_info->GetPos();
	float	spher_r = m_info->GetRadius();
	//����̏���S���擾����

	for (size_t i = 0; i < m_target_info.size(); ++i) {
		if (m_target_info[i]->GetClliderType() != SPHER)
			continue;
		Vector3 spher1_pos = m_target_info[i]->GetPos();
		float	spher1_r = m_target_info[i]->GetRadius();
		//��̋������擾
		float distance = GetVector3Distance(spher_pos, spher1_pos);
		//��̔��a�𑫂�����������������������
		if (distance < spher_r + spher1_r) {
			//�����ɓ����������̎�ނƓ����������Ƃ�`����
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			return;
		}
		//�������Ă��Ȃ������瑁�����Ă��蔲�������Ɖ��肷��
		//�I�u�W�F�N�g�̈�O�̃t���[���̐i�s�����̋t�Ƀ^�[�Q�b�g�������炻��͏Ȃ�
		Vector3 vect_up_to_target1 = m_target_pos_memory[i] - m_pos_memory;
		Vector3 spher_vect1 = m_vect_memory;
		float dot = GetVector3Dot(vect_up_to_target1, spher_vect1);
		if (dot < 0) {
			continue;
		}

		//�I�u�W�F�N�g�̐i�s�����Ƀ^�[�Q�b�g�������炠�������Ă��Ȃ�
		Vector3 vect_up_to_target2 = spher1_pos - spher_pos;
		Vector3 spher_vect2 = m_info->GetVect();
		dot = GetVector3Dot(vect_up_to_target2, spher_vect2);
		if (dot > 0) {
			continue;
		}

		//���̃t���[���ŃI�u�W�F�N�g�̐i�s�̋t�ɂ����炷�蔲���̉\��������
		//�ЂƂO�̃t���[�����獡�̃t���[���܂ł̈ړ��������g���ăJ�v�Z�������
		//������g���ē����蔻����s��
		Vector3  sher1_pos_memory = m_target_pos_memory[i];
		if (false) {
			//�����ɓ����������̎�ނƓ����������Ƃ�`����
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			return;
		}
	}
}
//�L���[�u�͓����Ă��Ȃ��Ƃ���
bool SpherHit::ChackCubeHit()
{
	bool hit = false;
	Spher spher;
	spher.pos = m_info->GetPos();
	spher.radius = m_info->GetRadius();
	for (size_t i = 0; i < m_target_info.size(); ++i) {
		if (m_target_info[i]->GetObjType() != BUILDING)
			continue;
		Vector3 cube_pos = m_target_info[i]->GetPos();
		Vector3 cu1 = m_target_info[i]->GetPos() - m_target_info[i]->GetSize();
		Vector3 cu2 = m_target_info[i]->GetPos() - m_target_info[i]->GetSize();
		Cube cube = MakeCubeTowPos(cu1, cu2);
		Vector3 spher_pos = m_info->GetPos();
		float spher_r = m_info->GetRadius();
		if (ChackCubeShperHit(cube, spher)) {
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			SetReboundVectSpherBox(m_info, cube);
			return true;
		}
		//�������Ă��Ȃ������瑁�����Ă��蔲�������Ɖ��肷��
		//�I�u�W�F�N�g�̈�O�̃t���[���̐i�s�����̋t�Ƀ^�[�Q�b�g�������炻��͏Ȃ�
		Vector3 spher_vect = m_info->GetVect();
		Vector3 vect_sc_m = m_target_pos_memory[i] - m_pos_memory;
		if (GetVector3Dot(m_vect_memory, vect_sc_m) < 0.0f)
			continue;

		//�I�u�W�F�N�g�̐i�s�����Ƀ^�[�Q�b�g�������炠�������Ă��Ȃ�
		Vector3 vect_up_to_target2 = cube_pos - spher_pos;
		Vector3 spher_vect2 = m_info->GetVect();
		float dot = GetVector3Dot(vect_up_to_target2, spher_vect2);
		if (dot >= 0) {
			continue;
		}
		Capsule capsule;
		capsule.line.g_pos = spher.pos;
		capsule.line.s_pos = m_pos_memory;
		capsule.radius = spher.radius;
		if (CheckHitCapsuleCube(capsule, cube)) {
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			SetReboundVectBox(cube);
			return true;
		}
	}
	return false;
}

//�ђʂ��Ȃ��L���[�u�Ƃ̓����蔻��
void SpherHit::SetReboundVectBox(Cube& cube) {
	//�J�v�Z���̂����Ă�
	Capsule capsule;
	capsule.line.s_pos = m_pos_memory;
	capsule.line.g_pos = m_info->GetPos();
	capsule.radius = m_info->GetRadius();
	//�����������W���擾����
	Vector3 hit_pos = GetHitCapsuleCubePos(capsule, cube);
	m_info->SetPos(hit_pos);
	//�ǂ��菈��
	Vector3 normal = m_info->GetPos() - hit_pos;
	normal.normalize();
	Vector3 obj_vect = m_info->GetVect();
	Vector3 vect = obj_vect - (normal * GetVector3Dot(obj_vect, normal));
	obj_vect.normalize();
	//�ǂ��痣��铮���̂Ƃ��͉������Ȃ�
	if (0.0f <= GetVector3Dot(obj_vect, normal))	return;
	//�߂荞�񂾕���ǂ���C��
	hit_pos = GetHitCubeCapsulePos(capsule, cube);
	float length = GetVector3Distance(capsule.line.s_pos, hit_pos);
	m_info->SetVect(vect);
	vect.normalize();
	m_info->SetPos(vect * length);
}