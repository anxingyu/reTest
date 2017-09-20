#include "MapManager.h"

static MapManager* _ins = nullptr;
MapManager * MapManager::getManager()
{
	if (_ins == nullptr)
	{
		_ins = new MapManager();
	}
	return _ins;
}

void MapManager::setMapData(TMXTiledMap * mapdata)
{
	m_mapData = mapdata;
}

bool MapManager::inWall(Vec2 Pos)
{
	bool ret = false;
	/*
	1.计算检测坐标在地图上的坐标
	2.将坐标转换为地图块坐标
	3.用该坐标需要检测的层去判断是否碰撞
	4.返回碰撞状态
	*/
	if (m_mapData)
	{
		auto mapSize = m_mapData->getContentSize();
		Vec2 mapPos = Vec2(Pos.x, mapSize.height - Pos.y);
		auto layer1 = m_mapData->getLayer("Bound");
		auto layer2 = m_mapData->getLayer("Bomb");
		auto tileSize = m_mapData->getTileSize();
		Vec2 tiledPos = Vec2((int)(mapPos.x / tileSize.width), (int)(mapPos.y / tileSize.height));
		if (layer1->getTileGIDAt(tiledPos) != 0 || layer2->getTileGIDAt(tiledPos) != 0)
		{
			ret = true;
		}
		else
		{
			ret = inBoom(Pos);
		}
	}
	return ret;
}

Vec2 MapManager::getNearMapPos(const Vec2 & pos)
{
	Vec2 ret = Vec2::ZERO;
	if (m_mapData)
	{
		
		Vec2 mapPos = Vec2(pos.x, pos.y);
		auto tileSize = m_mapData->getTileSize();
		Vec2 tiledPos = Vec2((int)(mapPos.x / tileSize.width), (int)(mapPos.y / tileSize.height));
		ret = Vec2(tileSize.width *0.5f + tileSize.width *tiledPos.x, tileSize.height *0.5f + tileSize.height *tiledPos.y);
	}
	return ret;
}

BREAK_WALL_TYPE MapManager::inBreakWall(const Vec2 & pos, const Vec2 & dir)
{
	BREAK_WALL_TYPE ret = BREAK_NONE;
	//TODO...写逻辑
	auto mapSize = m_mapData->getContentSize();
	auto layer1 = m_mapData->getLayer("Bound");
	auto layer2 = m_mapData->getLayer("Bomb");
	auto tileSize = m_mapData->getTileSize();
	Vec2 newPos = pos + Vec2(dir.x * tileSize.width, dir.y * tileSize.height);
	Vec2 mapPos = Vec2(newPos.x, mapSize.height - newPos.y);
	Vec2 tiledPos = Vec2((int)(mapPos.x / tileSize.width), (int)(mapPos.y / tileSize.height));
	if (layer1->getTileGIDAt(tiledPos) == 2)
	{
		ret = BREAK_FALSE;
	}
	else if(layer2->getTileGIDAt(tiledPos) == 4)
	{
		ret = BREAK_TRUE;
		layer2->getTileAt(tiledPos)->removeFromParent();
	}
	return ret;
}

Size MapManager::getMapTiledSize()
{
	if (m_mapData)
	{
		return m_mapData->getTileSize();
	}
	else
	{
		return Size::ZERO;
	}
	
}

void MapManager::addBoomItem(Node * b)
{
	m_boomVector.pushBack(b);
}

void MapManager::removeBoomItem(Node * b)
{
	m_boomVector.eraseObject(b);
}

bool MapManager::inBoom(const Vec2 & pos)
{
	bool ret = false;
	auto mapSize = m_mapData->getContentSize();
	auto tileSize = m_mapData->getTileSize();
	if (m_boomVector.empty() == false)
	{
		for (auto boom : m_boomVector)
		{
			auto boomPos = boom->getPosition();
			if (Rect(boomPos.x - tileSize.width*0.5f, boomPos.y - tileSize.height*0.5f, tileSize.width, tileSize.height).containsPoint(pos))
			{
				ret = true;
				break;
			}
		}
	}
	return ret;
}
