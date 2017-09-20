#include "Player.h"
#include "MapManager.h"
#include "CBomb.h"
bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("player/BoomMan.plist", "player/BoomMan.png");
	auto spr = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("12.png"));
	this->addChild(spr);

	auto lis = EventListenerKeyboard::create();
	lis->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	lis->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, this);

	scheduleUpdate();
	return true;
}
void Player::update(float dt)
{
	
	Vec2 newPos = this->getPosition();
	switch (m_moveState)
	{
	case MOVE_NONE:
		break;
	case MOVE_UP:
		newPos.y += m_moveSpeed *dt;
		break;
	case MOVE_DOWN:
		newPos.y -= m_moveSpeed *dt;
		break;
	case MOVE_LEFT:
		newPos.x -= m_moveSpeed *dt;
		break;
	case MOVE_RIGHT:
		newPos.x += m_moveSpeed *dt;
		break;
	}
	//如果主角当前位置在不可行走范围内，就不去检测下一步能否到达
	if (MapManager::getManager()->inBoom(this->getPosition()))
	{
		this->setPosition(newPos);
	}
	else if (!MapManager::getManager()->inWall(newPos))
	{
		this->setPosition(newPos);
	}
}
void Player::onKeyPressed(EventKeyboard::KeyCode code, Event *)
{
	switch (code)
	{

	case EventKeyboard::KeyCode::KEY_A:
		m_moveState = MOVE_LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_moveState = MOVE_RIGHT;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_moveState = MOVE_DOWN;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_moveState = MOVE_UP;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		//创建炸弹
		auto bomb = Bomb::create();
		bomb->setPosition(MapManager::getManager()->getNearMapPos(this->getPosition()));
		this->getParent()->addChild(bomb);
		break;
	}
}

void Player::onKeyReleased(EventKeyboard::KeyCode code, Event *)
{
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_W:
		m_moveState = MOVE_NONE;
	default:
		break;
	}
}


