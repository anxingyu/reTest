#pragma once
#ifndef __MAPMANAGER_H_
#define __MAPMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;

enum BREAK_WALL_TYPE
{
	BREAK_NONE,		//ûǽ
	BREAK_TRUE,		//������
	BREAK_FALSE,	//������
};

class MapManager
{
public:
	static MapManager * getManager();
	void setMapData(TMXTiledMap* mapdata);
	bool inWall(Vec2 Pos);
	Vec2 getNearMapPos(const Vec2&pos);
	BREAK_WALL_TYPE inBreakWall(const Vec2&pos, const Vec2&dir);
	Size getMapTiledSize();
	void addBoomItem(Node * b);
	void removeBoomItem(Node * b);
	bool inBoom(const Vec2&pos);
private:
	MapManager() {};
	~MapManager() {};
	TMXTiledMap * m_mapData;
	Vector<Node*>m_boomVector;
};

#endif // __MAPMANAGER_H_
