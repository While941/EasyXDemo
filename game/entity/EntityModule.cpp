#include "EntityModule.h"

std::unique_ptr<EntityModule,EntityModule::deleter> EntityModule::_instance = nullptr;
std::mutex EntityModule::_mtx;
int EntityModule::entity_count = 0;

void EntityModule::CreateMonster()
{

}

void EntityModule::CreatePlayer()
{
	EntityId id = static_cast<EntityId>(m_entity_list.size() + 1);
	m_role_list[id] = std::make_unique<Player>();
	m_entity_list[id] = (Entity*)m_role_list[id].get();
}

void EntityModule::OnBeginModule()
{
	m_role_list.clear();
	CreatePlayer();
}

void EntityModule::OnEndModule()
{
	m_role_list.clear();
}

void EntityModule::OnUpdate(double detalTime)
{
	for (std::unordered_map<EntityId, std::unique_ptr<Player>>::iterator it = m_role_list.begin();it != m_role_list.end();++it)
	{
		it->second.get()->OnUpdate(detalTime);
	}
}

void EntityModule::OnMove(EntityId entityId, const Vector2D<int>& target,double deltaTime)
{
	Player& player = GetPlayer(entityId);
	player.OnMove(target, deltaTime);
}


Player& EntityModule::GetPlayer(const RoleId& roleId) const
{
	auto it = m_role_list.find(roleId);
	if (it != m_role_list.end())
	{
		return *(it->second);
	}
	throw std::runtime_error("Player not found with the given ID.");
}
