#pragma once
#include "Base.h"
#include "WinMain.h"
#include<string>
//#include "Hit.h"

class BulletBase :
	public Base
{
	
protected:
	const float GUIDAN_RADIUSE = 100.0f;
	bool		m_de;					//撃った状態か
	int			m_timer;				//経過時間
	float		m_speed;				//弾速
	float		m_damege;				//連射速度
	int			m_rate_of_fire;			//攻撃範囲
	int			m_reload_time;			//リロード時間
	float		m_damage_range;		    //ダメージ範囲
	bool		m_tracking;				//追尾するか
	float		m_tracking_performance;	//追尾性能
	int			m_magazine_size;		//弾倉のサイズ
	bool		m_reload;				//リロード中か
	int			m_shoot_num;			//撃った数
	int			m_image;				//銃のイメージデータ
	std::string m_name;					//銃の種類名
	float       m_magnitude_of_recoil;	//反動の大きさ

public:
	BulletBase();
	//ゲッター変数
	float           GetDamage();
	float           GetDamegeRange();
	int             GetRateOfFire();
	int             ReloadTime();
	bool            GetDe();
	int             GetMagazineSize();
	int             GetTime();
	int             GetShootNum();
	bool			GetReLoade();

	void			AddSootNum();
	void			Reload();

	Vector3			SetReaction(Vector3 rot_);

	void            Init();
	virtual void    SetType() = 0;
	void            Set(Base* obj_);
	void            Set(Vector3& pos,Vector3& vect,Vector3& obj_vector);
	void            Move();
	void            Draw();
	void            Hit(Base* obj);
	void			Delete();

};

