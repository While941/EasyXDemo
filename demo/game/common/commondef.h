#pragma once
typedef int Attribute;
typedef __int64 RoleId;
typedef __int64 MonsterId;
typedef __int64 EntityId;
#include <cmath>  // ����cmath����ʹ��sqrt����
#include <limits> // ����limits����ʹ��epsilon

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
	Unknown, // ��������������κη����򷵻ش�ֵ
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

    T getDistance(const Vector2D& other)
    {
		Vector2D<T> diff{ other.x - x, other.y - y };
		T distanceSquared = diff.x * diff.x + diff.y * diff.y;  // ��������ƽ��
		return std::sqrt(distanceSquared);  // ���ؾ��루ƽ������
    }

    void normalize()
    {
        T length = std::hypot(x,y);
        if (std::abs(length) > std::numeric_limits<T>::epsilon())
        {
            x /= length;
            y /= length;
        }
    }

    Vector2D<T> operator-(const Vector2D<T>& other)
    {
        return Vector2D<T>{ x - other.x,y - other.y };
    }

	Vector2D<T> operator+(const Vector2D<T>& other)
	{
		return Vector2D<T>{ x + other.x,y + other.y };
	}

    Vector2D<T> operator*(float value)
    {
        return Vector2D<T>{ x * value,y * value };
    }
};

