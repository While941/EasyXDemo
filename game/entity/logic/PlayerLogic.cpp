#include "PlayerLogic.h"
#include "PlayerLogicItem.h"
#include <stdio.h>

PlayerLogic::PlayerLogic(Player *player): m_logic_count(0)
{
    memset(m_logic_list, 0, sizeof(m_logic_list));
    this->player = player;
}

PlayerLogic::~PlayerLogic()
{
    for(auto id: m_logic_list)
    {
        if(id != NULL)
        {
            delete id;
        }
    }
}

// ×¢²áËùÓÐÄ£¿é
void PlayerLogic::RegisterAllLogic()
{
    new NormalLogicItem(player);
}

void PlayerLogic::RegisterLogicItem(PlayerLogicItem *logicItem)
{
    printf("Register PlayerLogicItem \n");
    if(m_logic_count < StructSize::MAX_LOGIC_ITEM_COUNT)
    {
        printf("RegisterLogicItem success! %d \n" , m_logic_count);
        m_logic_list[m_logic_count++] = logicItem;
    }
    else
    {
        printf("RegisterLogicItem failed! %d \n" , m_logic_count);
    }
}

void PlayerLogic::UnRegisterLogicItem(int id)
{
    m_logic_list[id] = NULL;
}

void PlayerLogic::GetTotalAttr(AttributeCommon &attr)
{
    for(auto logic:m_logic_list)
    {
        if(logic != NULL)
        {
            logic->GetTotalAttr(attr);
        }
    }
}

