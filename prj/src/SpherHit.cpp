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
//	線と球の当たり判定
//---------------------------------------------------------------------------------
bool SpherHit::CheckLineHit(Vector3& line_start, Vector3& line_goal)
{
	//1:線のどちらかの座標が当たっているか
	Vector3 spher_pos = m_info->GetPos();
	float	spher_r = m_info->GetRadius();

	if (GetVector3Distance(line_start, spher_pos) <= spher_r) {
		return true;
	}
	if (GetVector3Distance(line_goal, spher_pos) <= spher_r) {
		return true;
	}
	//２：二つの座標の内側にいるか
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
	//3：線上の一番近い座標を取得当たり判定
	//線のスタートからゴール座標へのベクトルは正規化する
	dir_sg.normalize();
	float dot_line = GetVector3Dot(dir_sg, dir_sb);
	//線上の一番近い座標の設定
	Vector3 line_pos = line_start + dir_sg * dot_line;
	if (GetVector3Distance(line_pos, spher_pos) <= spher_r) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	球同士の当たり判定
//---------------------------------------------------------------------------------
void SpherHit::CheckHitSpher()
{
	//自分の情報を変数に代入
	Vector3 spher_pos = m_info->GetPos();
	float	spher_r = m_info->GetRadius();
	//相手の情報を全部取得する

	for (size_t i = 0; i < m_target_info.size(); ++i) {
		if (m_target_info[i]->GetClliderType() != SPHER)
			continue;
		Vector3 spher1_pos = m_target_info[i]->GetPos();
		float	spher1_r = m_target_info[i]->GetRadius();
		//二つの距離を取得
		float distance = GetVector3Distance(spher_pos, spher1_pos);
		//二つの半径を足した距離よりも小さかったら
		if (distance < spher_r + spher1_r) {
			//自分に当たった物の種類と当たったことを伝える
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			return;
		}
		//あったていなかったら早すぎてすり抜けしたと仮定する
		//オブジェクトの一つ前のフレームの進行方向の逆にターゲットがいたらそれは省く
		Vector3 vect_up_to_target1 = m_target_pos_memory[i] - m_pos_memory;
		Vector3 spher_vect1 = m_vect_memory;
		float dot = GetVector3Dot(vect_up_to_target1, spher_vect1);
		if (dot < 0) {
			continue;
		}

		//オブジェクトの進行方向にターゲットがいたらあったっていない
		Vector3 vect_up_to_target2 = spher1_pos - spher_pos;
		Vector3 spher_vect2 = m_info->GetVect();
		dot = GetVector3Dot(vect_up_to_target2, spher_vect2);
		if (dot > 0) {
			continue;
		}

		//今のフレームでオブジェクトの進行の逆にいたらすり抜けの可能性が高い
		//ひとつ前のフレームから今のフレームまでの移動距離を使ってカプセルを作り
		//それを使って当たり判定を行う
		Vector3  sher1_pos_memory = m_target_pos_memory[i];
		if (false) {
			//自分に当たった物の種類と当たったことを伝える
			m_info->SetHitOBjType(m_target_info[i]->GetObjType());
			m_info->SetIsHit(true);
			return;
		}
	}
}
//キューブは動いていないとする
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
		//あったていなかったら早すぎてすり抜けしたと仮定する
		//オブジェクトの一つ前のフレームの進行方向の逆にターゲットがいたらそれは省く
		Vector3 spher_vect = m_info->GetVect();
		Vector3 vect_sc_m = m_target_pos_memory[i] - m_pos_memory;
		if (GetVector3Dot(m_vect_memory, vect_sc_m) < 0.0f)
			continue;

		//オブジェクトの進行方向にターゲットがいたらあったっていない
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

//貫通しないキューブとの当たり判定
void SpherHit::SetReboundVectBox(Cube& cube) {
	//カプセルのせってい
	Capsule capsule;
	capsule.line.s_pos = m_pos_memory;
	capsule.line.g_pos = m_info->GetPos();
	capsule.radius = m_info->GetRadius();
	//当たった座標を取得する
	Vector3 hit_pos = GetHitCapsuleCubePos(capsule, cube);
	m_info->SetPos(hit_pos);
	//壁ずり処理
	Vector3 normal = m_info->GetPos() - hit_pos;
	normal.normalize();
	Vector3 obj_vect = m_info->GetVect();
	Vector3 vect = obj_vect - (normal * GetVector3Dot(obj_vect, normal));
	obj_vect.normalize();
	//壁から離れる動きのときは何もしない
	if (0.0f <= GetVector3Dot(obj_vect, normal))	return;
	//めり込んだ分を壁ずり修正
	hit_pos = GetHitCubeCapsulePos(capsule, cube);
	float length = GetVector3Distance(capsule.line.s_pos, hit_pos);
	m_info->SetVect(vect);
	vect.normalize();
	m_info->SetPos(vect * length);
}