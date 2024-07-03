#pragma once
#include "common/commondef.h"

class Entity
{
public:
	Entity();

	virtual void OnUpdate(double detalTime) = 0;
	virtual void OnRender(double deltaTime) = 0;
	virtual void OnCollision(Entity *other)= 0;
	virtual void OnAttack(Entity *beAttacker)= 0;
	virtual void OnBeAttack(Entity *attacker) = 0;
	virtual void OnDeath() = 0;
	virtual void OnMove(const Vector2D<float> &target, double deltaTime) = 0;
	virtual ~Entity();
	virtual void SetEntityType(EntityType type) { eEntityType = type; }
	virtual EntityType GetEntityType() { return eEntityType; }
	
	//virtual void SetPosition(Vector2 pos) { m_vPosition = pos; }
	//virtual Vector2 GetPosition() { return m_vPosition; }
	Vector2D<float> position = { 500,500 };
	EntityType eEntityType;
	EntityId m_entity_id;
};
