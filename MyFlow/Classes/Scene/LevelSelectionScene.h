/*
 * LevelSelectionScene.h
 *
 *  Created on: Dec 18, 2012
 *      Author: mvptech
 */

#ifndef LEVELSELECTIONSCENE_H_
#define LEVELSELECTIONSCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../GlowFlow.h"
#include "../ResourceFinder.h"
#include "Layer/LevelSelectionLayer.h"
#include "PackSelectionScene.h"
#include "Node/Pager.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LevelSelectionLayer;

class LevelSelection: public cocos2d::CCLayer, ResourceFinder {
	static const int LEVEL_SELECTION_LAYER;
	static const int TOTAL_PAGES;

	CCSize padSize;
	void onBackPressed(CCObject *sender);

public:
	virtual bool init();

	static CCScene* scene();

	CREATE_FUNC(LevelSelection)

	void onPagePressed(CCObject* sender);

	const char* getResourceDirectory() {
		return "LevelSelection";
	}

	virtual ~LevelSelection();
};

#endif /* LEVELSELECTIONSCENE_H_ */
