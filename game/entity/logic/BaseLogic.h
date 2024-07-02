#pragma once
#include "common/commondef.h"

class Entity;
class PlayerLogicItem;
struct Logic
{
public:
    Logic() {};
    virtual ~Logic()=default; // 基类析构函数需要virtual
    virtual void RegisterLogicItem(PlayerLogicItem* logcItem) = 0;
    virtual void UnRegisterLogicItem(int id) = 0;
};

// template <class T>
struct BaseLogic : Logic
{
public:
    BaseLogic() {};
    BaseLogic(Entity *entity) {}
    virtual ~BaseLogic() = default;
    virtual void RegisterLogicItem(PlayerLogicItem *logcItem)  {};
    virtual void UnRegisterLogicItem(int id)  {};
};
