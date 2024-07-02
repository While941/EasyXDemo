#pragma once

#include "commondef.h"

struct AttributeCommon
{
    AttributeCommon() :
        // 0 is the default value
        hp(0),
        mp(0),
        attack(0),
        defense(0),
        magic(0),
        magicDefense(0),
        speed(0),
        luck(0),
        critical(0),
        avoid(0)
    {}
    ~AttributeCommon(){}
    Attribute hp;
    Attribute mp;
    Attribute attack;
    Attribute defense;
    Attribute magic;
    Attribute magicDefense;
    Attribute speed;
    Attribute luck;
    Attribute critical;
    Attribute avoid;
};