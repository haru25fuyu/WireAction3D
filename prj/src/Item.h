#pragma once
#include "Base.h"
class Item :
    public Base
{
    Item();
    void Init();
    void Set(Vector3 pos);
    void Updete(Base* char_);
    void Drew();
};

