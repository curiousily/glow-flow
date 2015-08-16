/*
 * MainMenuScene.h
 *
 *  Created on: Nov 21, 2012
 */

#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "cocos2d.h"
#include "../GlowFlow.h"
#include "../ResourceFinder.h"
#include "SimpleAudioEngine.h"
#include "PackSelectionScene.h"

USING_NS_CC;
using namespace CocosDenshion;

class MainMenu: public cocos2d::CCLayer, ResourceFinder {

public:
	virtual bool init();
	virtual ~MainMenu();

	static CCScene* scene();

	const char* getResourceDirectory() {
		return "MainMenu";
	}

	CREATE_FUNC(MainMenu)

private:
	void onPlayPressed(CCObject* sender);
	void onExitPressed(CCObject* sender);
	void onSettingsPressed(CCObject* sender);
	void animateConnectingDots();
};

#endif /* MAINMENUSCENE_H_ */
