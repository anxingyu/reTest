#include "CBomb.h"

#include "MapManager.h"


bool Bomb::init()
{
	if (!Node::init())
	{
		return false;
	}
	MapManager::getManager()->addBoomItem(this);
	m_loopCount = 0;
	m_level = 3;
	m_timeOut = 3;
	m_effectCount = 0;
	m_armature = Armature::create("Bomb");
	m_armature->getAnimation()->play("ation1");
	this->addChild(m_armature);
	scheduleOnce(CC_CALLBACK_1(Bomb::timeOut, this), m_timeOut, "timeOut");

	return true;
}
void Bomb::creatEffectH(const Node * node)
{
	Armature * armature = Armature::create("Bomb");
	armature->getAnimation()->play("ation3");
	armature->setPosition(node->getPosition());
	//armature->getAnimation()->setMovementEventCallFunc([this](Armature * armature, MovementEventType movementType, const std::string & movementID) {
	//	if (movementType == LOOP_COMPLETE&&movementID.compare("ation2") == 0)
	//	{
	//		armature->removeFromParent();
	//	}
	//});
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Bomb::animationCallBack, this));
	this->addChild(armature);
	m_effectCount++;
}
void Bomb::creatEffectV(const Node * node)
{
	Armature * armature = Armature::create("Bomb");
	armature->getAnimation()->play("ation3");
	armature->setRotation(-90);	
	armature->setPosition(node->getPosition());
	//armature->getAnimation()->setMovementEventCallFunc([this](Armature * armature, MovementEventType movementType, const std::string & movementID) {
	//	if (movementType == LOOP_COMPLETE&&movementID.compare("ation2") == 0)
	//	{
	//		armature->removeFromParent();
	//	}
	//});
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Bomb::animationCallBack, this));
	this->addChild(armature);
	m_effectCount++;
}

void Bomb::creatEffect(const Node * node, bool isV)
{
	Armature * armature = Armature::create("Bomb");
	armature->getAnimation()->play("ation3");
	if (isV)
	{
		armature->setRotation(-90);
	}	
	armature->setPosition(node->getPosition());
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Bomb::animationCallBack, this));
	this->addChild(armature);
	m_effectCount++;
}

void Bomb::animationCallBack(Armature * armature, MovementEventType movementType, const std::string & movementID)
{
	if (movementType == LOOP_COMPLETE&&movementID.compare("ation3") == 0)
		{			
		armature->removeFromParent();
		m_effectCount--;
			if (m_effectCount == 0)
			{
				MapManager::getManager()->removeBoomItem(this);
				this->removeFromParent();
			}
			
		}
}

void Bomb::timeOut(float dt)
{
	auto manager = MapManager::getManager();
	m_effectCount = 0;
	m_armature->getAnimation()->setMovementEventCallFunc(
		[this](Armature *armature, MovementEventType movementType, const std::string& movementID) {
		if (movementType == LOOP_COMPLETE&&movementID.compare("ation1") == 0)
		{		
				armature->getAnimation()->play("ation2");			
		}
	});
	//创建一堆爆炸效果  上下左右四个方向
	for (int i = 0; i < m_level; i++)		//上
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(0, i + 1));
		if (type!=BREAK_FALSE)
		{
			//放特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(0, manager->getMapTiledSize().height *(i + 1)));
			auto callback = CCCallFuncND::create(this, SEL_CallFuncND(&Bomb::creatEffect), (void*)true);
		/*CCCallFuncN::create(CC_CALLBACK_1(Bomb::creatEffectV,this));*/
			node->runAction(Sequence::create(DelayTime::create(i*0.2f), callback, nullptr));
		}
		if (type!=BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)		//下
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(0, -i - 1));
		if (type != BREAK_FALSE)
		{
			//放特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(0, manager->getMapTiledSize().height *(-1 - i)));
			auto callback = CCCallFuncND::create(this, SEL_CallFuncND(&Bomb::creatEffect), (void*)true);
			node->runAction(Sequence::create(DelayTime::create(i*0.2f), callback, nullptr));
		}
		if (type != BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)		//左
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(-i - 1,0));
		if (type != BREAK_FALSE)
		{
			//放特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(manager->getMapTiledSize().width *(-1 - i), 0));
			auto callback = CCCallFuncND::create(this, SEL_CallFuncND(&Bomb::creatEffect), (void*)false);
			node->runAction(Sequence::create(DelayTime::create(i*0.2f), callback, nullptr));
		}
		if (type != BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)		//右
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(i + 1, 0));
		if (type != BREAK_FALSE)
		{
			//放特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(manager->getMapTiledSize().width *(i + 1), 0));
			auto callback = CCCallFuncND::create(this, SEL_CallFuncND(&Bomb::creatEffect), (void*)false);
			node->runAction(Sequence::create(DelayTime::create(i*0.2f), callback, nullptr));		
		}
		if (type != BREAK_NONE)
		{
			break;
		}
	}
}


