#pragma once

#include "Base.h"
#include<vector>



//---------------------------------------------------------------------------------
//	�n�ʃN���X
//---------------------------------------------------------------------------------
class Ground : public Base
{
	//std::vector<bool> m_nav;
public:
	//std::vector<bool>* GetNav();
	//void SetNav();
	void Init();		//	����������
	void Update(Base* char_);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
