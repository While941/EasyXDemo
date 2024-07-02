#pragma once
typedef int Attribute;
typedef __int64 RoleId;
typedef __int64 MonsterId;
typedef __int64 EntityId;

namespace StructSize
{
    static const int MAX_PLAYER_ATTR_COUNT = 10;
    static const int MAX_MONSTER_ATTR_COUNT = 10;
    static const int MAX_LOGIC_ITEM_COUNT = 20;
    static const int MAX_ANIM_COUNT = 6;
}

enum class EntityType
{
	ET_UNKNOW = 0,
    ET_PLAYER,
    ET_MONSTER,
    ET_ITEM,
    ET_MAX,
};

enum class Direction
{
	Left,
    Right,
	Unknown, // 如果向量不属于任何方向，则返回此值
};

template <class T>
struct Vector2D
{
    T x;
    T y;

	Direction direct;
	int ani_index;
    Vector2D(T x_val = 0, T y_val = 0, Direction direct_val = Direction::Left,int ani_index_val = 0): x(x_val),y(y_val),direct(direct_val),ani_index(ani_index_val)
    {

    }

    T dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    Direction getDirectionTo(const Vector2D& other)
    {
        Vector2D<T> diff{ other.x - x,other.y - y };
        
        return diff.x > 0 ? Direction::Right : Direction::Left;
    }
};

