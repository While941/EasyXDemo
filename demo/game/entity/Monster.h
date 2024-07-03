#pragma once
#include "entity.h"
#include <memory>
#include "Animation/Animation.h"
#include "common/commondef.h"

struct AttributeCommon;
class Monster : Entity
{
public:
	Monster():m_monster_id(0) { memset(m_attr_list, 0, sizeof(m_attr_list)); }
	Monster(MonsterId id);
	~Monster();

	virtual void OnUpdate(double detalTime) override;
	virtual void OnRender(double deltaTime) override;
	virtual void OnCollision(Entity* other) override;
	virtual void OnMove(const Vector2D<float>& target, double deltaTime) override;
	virtual void OnAttack(Entity* beAttacker) override;
	virtual void OnBeAttack(Entity* attacker) override;
	virtual void OnDeath() override;

private:
	void OnInit();
	void OnAILogic(double deltaTime);
private:
	Attribute m_attr_list[StructSize::MAX_PLAYER_ATTR_COUNT];
	std::unique_ptr<Animation> left_ani;
	std::unique_ptr<Animation> right_ani;
	MonsterId m_monster_id;
};