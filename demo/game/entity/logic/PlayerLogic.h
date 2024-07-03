#pragma once

#include "BaseLogic.h"
#include "common/commondef.h"
#include "common/Attribute.h"
#include <memory>

class Player;
class PlayerLogicItem;
class PlayerLogic : BaseLogic
{
private:
public:
    PlayerLogic() :m_logic_count(0) { memset(m_logic_list, 0, sizeof(m_logic_list));  player = NULL; };
    PlayerLogic(Player *player);
    ~PlayerLogic();

    virtual void RegisterLogicItem(PlayerLogicItem *item);
    virtual void UnRegisterLogicItem(int id);
    virtual void GetTotalAttr(AttributeCommon &attr);
    void RegisterAllLogic();
    PlayerLogicItem *m_logic_list[StructSize::MAX_LOGIC_ITEM_COUNT];
    int m_logic_count;
    Player *player;
};



