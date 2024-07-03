#pragma once
#include "entity.h"
#include "common/commondef.h"
#include "logic/PlayerLogic.h"
#include <memory>
#include <graphics.h>
#include <string>
#include "message/MessageUtil.h"
#include "EntityModule.h"
#include "Animation/Animation.h"

#pragma comment(lib, "MSIMG32.LIB")
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

struct  AttributeCommon;
class Player : Entity , Subscriber
{
public:
	Player();
	virtual ~Player();
	virtual void OnAttack(Entity *target) override {}
	virtual void OnBeAttack(Entity *attacker) override {}
	virtual void OnUpdate(double detalTime) override;
	virtual void OnCollision(Entity *other) override {}
	virtual void OnDeath() override {}
	virtual void OnRender(double deltaTime);
	virtual void OnMove(const Vector2D<float>& target,double deltaTime );

	// 消息接受
	void receive(const std::shared_ptr<Message>& message) override
	{
		auto moveMsg = std::static_pointer_cast<MoveMessage>(message);

	}

	void handleMessage1(const std::shared_ptr<MoveMessage>& message) {
		// 处理消息...
		const Vector2D<float>& target = message->position;
		//OnMove(target);
	}

	EntityId GetEntityId() const { return m_entity_id; }
public:
	Vector2D<float> GetPlayerPoint() const { return position; }
	
	void OnInit();
	std::shared_ptr<PlayerLogic> GetLogic() const { return m_player_logic;}

private:
	Attribute m_attr_list[StructSize::MAX_PLAYER_ATTR_COUNT];	

	std::shared_ptr<PlayerLogic> m_player_logic;

	std::unique_ptr<Animation> left_ani;
	std::unique_ptr<Animation> right_ani;
};