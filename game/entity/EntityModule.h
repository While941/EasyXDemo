#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include "common/commondef.h"
#include "entity/player.h"
#include <memory>


class EntityModule
{
private:
	EntityModule() = default;
	~EntityModule() = default;
	// 禁止拷贝构造和赋值
	EntityModule(const EntityModule&) = delete;
	EntityModule& operator=(const EntityModule&) = delete;

	struct deleter
	{
		void operator()(EntityModule* ptr)
		{
			delete ptr;
		}
	};

	static std::unique_ptr<EntityModule,deleter> _instance;
	static std::mutex _mtx;

public:
	static EntityModule* GetInstance()
	{
		std::lock_guard<std::mutex> lock(_mtx);
		if (!_instance)
		{
			_instance.reset(new EntityModule());
		}

		return _instance.get();
	}

public:
	void CreatePlayer();
	void CreateMonster();
	void OnBeginModule();
	void OnEndModule();
	void OnUpdate(double detalTime);
	void OnMove(EntityId entityId, const Vector2D<int>& target,double deltaTime);
	Player& GetPlayer(const RoleId& roleId) const;

	static int entity_count;
private:
	std::unordered_map<EntityId, std::unique_ptr<Player>> m_role_list;

	std::unordered_map<EntityId, Entity*> m_entity_list;
};