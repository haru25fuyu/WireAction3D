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
	bool		m_de;					//��������Ԃ�
	int			m_timer;				//�o�ߎ���
	float		m_speed;				//�e��
	float		m_damege;				//�A�ˑ��x
	int			m_rate_of_fire;			//�U���͈�
	int			m_reload_time;			//�����[�h����
	float		m_damage_range;		    //�_���[�W�͈�
	bool		m_tracking;				//�ǔ����邩
	float		m_tracking_performance;	//�ǔ����\
	int			m_magazine_size;		//�e�q�̃T�C�Y
	bool		m_reload;				//�����[�h����
	int			m_shoot_num;			//��������
	int			m_image;				//�e�̃C���[�W�f�[�^
	std::string m_name;					//�e�̎�ޖ�
	float       m_magnitude_of_recoil;	//�����̑傫��

public:
	BulletBase();
	//�Q�b�^�[�ϐ�
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

