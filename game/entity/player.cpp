#include "player.h"
#include <iostream>

Player::Player()
{
	memset(m_attr_list, 0, sizeof(m_attr_list));

	m_entity_id = ++EntityModule::entity_count;
	SetEntityType(EntityType::ET_PLAYER);
	m_player_logic = std::make_shared<PlayerLogic>(this);
	if (m_player_logic != nullptr)
	{
		m_player_logic->RegisterAllLogic();
	}

	// ¶©ÔÄÏà¹Ø
	/*MessageCenter::GetInstance()->subscribe<MoveMessage>([this](const std::shared_ptr<Message>& msg) {
		auto myMsg = std::static_pointer_cast<MoveMessage>(msg);
		this->handleMessage1(myMsg);
		});*/

	
	OnInit();
}

Player::~Player()
{
}

void Player::OnInit()
{
	left_ani = std::make_unique<Animation>(_T("img/player_left_%d.png"), 0.3);
	right_ani = std::make_unique<Animation>(_T("img/player_right_%d.png"), 0.3);
}

void Player::OnMove(const Vector2D<int>& target,double deltaTime)
{
	player_point.direct = player_point.getDirectionTo(target);
	player_point.x = target.x;
	player_point.y = target.y;
	OnRender(deltaTime);
}

void Player::OnRender(double deltaTime)
{
	if (player_point.direct == Direction::Left)
	{
		left_ani->PlayAnimation(player_point.x, player_point.y, deltaTime);
	}
	else
	{
		right_ani->PlayAnimation(player_point.x, player_point.y, deltaTime);
	}
}

void Player::OnUpdate(double detalTime)
{
	OnRender(detalTime);
}




