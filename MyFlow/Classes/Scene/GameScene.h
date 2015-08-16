#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "../ResourceFinder.h"
#include "Layer/LevelInformationLayer.h"
#include "Dialog/LevelCompleteDialog.h"
#include "../Grid/Level.h"

USING_NS_CC;

using namespace std;

class LevelInformationLayer;

class Game: public cocos2d::CCLayer, GridDelegate, ResourceFinder {

	LevelInformationLayer* levelInformationLayer;

	Level level;
	Grid* grid;

	void onReloadPressed(CCObject* sender);

	void onBackPressed(CCObject* sender);

	void onLeftButtonPressed(CCObject* sender);

	void onRightButtonPressed(CCObject* sender);

	void onDisplayLevelCompleteDialog(CCObject* dialog);

	Game();

public:
	virtual bool init();

	void onMoveComplete();
	void onFlowComplete(int completedFlows, int totalFlows);
	void onLevelComplete();

	const char* getResourceDirectory() {
		return "Game";
	}

	virtual ~Game();

	static CCScene* scene();

	CREATE_FUNC(Game)
};

#endif // __HELLOWORLD_SCENE_H__
