#include "Monster.h"
#include "EntityModule.h"

Monster::Monster(MonsterId id): m_monster_id(id)
{
	m_entity_id = ++EntityModule::entity_count;
	memset(m_attr_list, 0, sizeof(m_attr_list));
	OnInit();
}

Monster::~Monster()
{

}

void Monster::OnInit()
{
	left_ani = std::make_unique<Animation>(_T("img/enemy_left_%d.png"), 0.3);
	right_ani = std::make_unique<Animation>(_T("img/enemy_right_%d.png"), 0.3);
	position.x = 0;
	position.y = 0;
}

void Monster::OnMove(const Vector2D<float>& target, double deltaTime)
{
	position.direct = position.getDirectionTo(target);
	position.x = target.x;
	position.y = target.y;
	OnRender(deltaTime);
}

void Monster::OnRender(double deltaTime)
{
	if (position.direct == Direction::Left)
	{
		left_ani->PlayAnimation(position.x, position.y, deltaTime);
	}
	else
	{
		right_ani->PlayAnimation(position.x, position.y, deltaTime);
	}
}

void Monster::OnUpdate(double detalTime)
{
	OnRender(detalTime);
	OnAILogic(detalTime);
}

void Monster::OnCollision(Entity* other)
{

}

void Monster::OnAttack(Entity* beAttacker)
{

}

void Monster::OnBeAttack(Entity* attacker)
{

}

void Monster::OnDeath()
{

}

void Monster::OnAILogic(double deltaTime)
{
	auto& player_map = EntityModule::GetInstance()->GetPlayerMap(); // 获取引用
	Player* nearestPlayer = nullptr;
	float minDistance = FLT_MAX;

	for (auto& it : player_map)
	{
		Vector2D<float> target_position = it.second->GetPlayerPoint();
		float diff_distance = position.getDistance(target_position);
		if (diff_distance < minDistance)
		{
			minDistance = diff_distance;
			nearestPlayer = it.second.get();
		}
	}


	if (nearestPlayer != nullptr)
	{
		Vector2D<float> direction = nearestPlayer->GetPlayerPoint() - position; // 计算方向向量
		direction.normalize();
		Vector2D<float> moveVector = direction * 0.1 * deltaTime; // 计算移动向量
		Vector2D<float> newPosition = position + moveVector; // 计算新的位置
		OnMove(newPosition, deltaTime);
	}
}

