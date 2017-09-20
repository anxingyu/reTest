#ifndef __CBOMB_H__
#define __CBOMB_H__
#include "cocostudio\CocoStudio.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace cocostudio;
class Bomb : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Bomb);
	int m_loopCount;
	int m_level;
	int m_timeOut;
	Armature * m_armature;
	void timeOut(float dt);
	void animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void creatEffectH(const Node * node);
	void creatEffectV(const Node * node);
	void creatEffect(const Node * node, bool isV = false);
	int m_effectCount;
};

#endif // __CBOMB_H__
