#pragma once

#include "common/commondef.h"
#include "entity/player.h"
#include <stdio.h>

class Entity;
class Player;
template <class IType, class EType>
struct BaseLogicItem
{
public:
    BaseLogicItem() {}
    BaseLogicItem(EType *e) {
        printf("init BaseLogicItem \n");
        Register(e);
     }
    virtual ~BaseLogicItem() {}
    virtual void Register(EType *e) { // 注册逻辑
        if(e == nullptr) return;
        auto item = (IType*)this;
        e->GetLogic()->RegisterLogicItem(item);
    }
};



