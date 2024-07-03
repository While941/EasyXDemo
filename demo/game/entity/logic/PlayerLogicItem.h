#pragma once
#include "common/Attribute.h"
#include "BaseLogicItem.h"
#include <stdio.h>

class Player;

class PlayerLogicItem : BaseLogicItem<PlayerLogicItem,Player>
{
public:
    PlayerLogicItem(Player *player):BaseLogicItem(player)
    {
        m_sys_id = 0;
        printf("init PlayerLogicItem \n");
    }
    virtual ~PlayerLogicItem() {}
    
    virtual void GetTotalAttr(AttributeCommon& attr);
    virtual void UpdateAttr();
    virtual void SetId(int id) { m_sys_id = id;}
    virtual int GetId() { return m_sys_id;}
protected:
    AttributeCommon m_attr;
    int m_sys_id;

};

class NormalLogicItem : PlayerLogicItem
{
public:
    NormalLogicItem(Player *player):PlayerLogicItem(player)
    {
        printf("init NormalLogicItem \n");
    }

    virtual ~NormalLogicItem() {}

    virtual void GetTotalAttr(AttributeCommon& attr) {}
    virtual void UpdateAttr() {}
};