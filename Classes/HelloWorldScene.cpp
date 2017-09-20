#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "MapManager.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setContentScaleFactor(1.0f);
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bomb/Bomb.ExportJson");
	auto map = TMXTiledMap::create("map/BoomMap.tmx");
	this->addChild(map);
	MapManager::getManager()->setMapData(map);
	auto objLayer = map->getObjectGroup("Objs");
	auto playerObj = objLayer->getObject("Player");
	auto playerPos = Vec2(playerObj["x"].asFloat(), playerObj["y"].asFloat());
	CCLOG("%f -- %f", playerObj["x"].asFloat(), playerObj["y"].asFloat());
	auto player = Player::create();
	player->setPosition(playerPos);
	this->addChild(player);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
