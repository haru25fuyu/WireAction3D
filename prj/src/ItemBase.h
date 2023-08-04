#pragma once
#include "Base.h"
#include"CharBase.h"
class ItemBase :
    public Base
{
    int m_type;
public:
    ItemBase();
    virtual void    SetItem() = 0;
    void            Init();
    void            Set(Vector3 pos);
    void            Updete(CharBase* char_);
    void            Drew();
};

