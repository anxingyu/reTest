#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
USING_NS_CC;
enum Move_DIR
{
	MOVE_NONE,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
};

class Player : public Node
{
public:
	virtual bool init();
	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	void onKeyReleased(EventKeyboard::KeyCode, Event*);
	const float m_moveSpeed = 120;
	Move_DIR m_moveState;
	void update(float dt);
	CREATE_FUNC(Player);
};

#endif // __PLAYER_H__
