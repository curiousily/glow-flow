/*
 * LoadingScene.cpp
 *
 *  Created on: Dec 15, 2012
 *      Author: mvptech
 */

#include "LoadingScene.h"

CCScene* Loading::scene() {
	CCScene *scene = CCScene::create();
	Loading *layer = Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Loading::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSprite* background = CCSprite::create("Default.png");
	background->setPosition(VisibleRect::center());
	addChild(background);

	runAction(
			CCSequence::create(
					CCDelayTime::create(1.2f),
					CCCallFunc::create(this,
							callfunc_selector(Loading::onLoadingComplete)),
					NULL));
	return true;
}

void Loading::onLoadingComplete(CCObject* sender) {
	CCScene* gameScene = Game::scene();
	GameManager::sharedGameManager()->runScene(gameScene);
}

Loading::~Loading() {
}
