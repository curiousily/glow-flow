/*
 * MainMenuScene.cpp
 *
 *  Created on: Nov 21, 2012
 */

#include "MainMenuScene.h"

void MainMenu::onPlayPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(PackSelection::scene());
}

void MainMenu::onExitPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

CCScene* MainMenu::scene() {
	CCScene *scene = CCScene::create();
	MainMenu *layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

void MainMenu::onSettingsPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(Settings::scene());
}

void MainMenu::animateConnectingDots() {
	CCSpriteFrameCache *spriteCache =
			CCSpriteFrameCache::sharedSpriteFrameCache();
	spriteCache->addSpriteFramesWithFile("MainMenu/ConnectingDots.plist");
	CCAnimation *connectingDotsAnimation = CCAnimation::create();
	for (int i = 1; i <= 29; i++) {
		CCString *name = i < 10 ? CCString::createWithFormat(
				"ConnectingDots0%d.png", i) : CCString::createWithFormat(
				"ConnectingDots%d.png", i);
		CCSpriteFrame *spriteFrame = spriteCache->spriteFrameByName(
				name->getCString());
		connectingDotsAnimation->addSpriteFrame(spriteFrame);
	}
	connectingDotsAnimation->setDelayPerUnit(0.05f);
	CCSprite *initialFrame = CCSprite::createWithSpriteFrameName(
			"ConnectingDots01.png");
	initialFrame->setPosition(
			ccp(VisibleRect::center().x, VisibleRect::bottom().y + 60));
	initialFrame->runAction(CCAnimate::create(connectingDotsAnimation));
	addChild(initialFrame);
}

bool MainMenu::init() {
	if (!CCLayer::init()) {
		return false;
	}

	addBackground(this);

	CCMenuItemSprite* playButton = CCMenuItemSprite::create(
			imageSprite("StartButtonNormal"), imageSprite("StartButtonTapped"),
			this, menu_selector(MainMenu::onPlayPressed));
	playButton->setPosition(ccp(VisibleRect::center().x, 315));

	CCMenuItemSprite* settingsButton = CCMenuItemSprite::create(
			imageSprite("SettingsNormal"), imageSprite("SettingsTapped"), this,
			menu_selector(MainMenu::onSettingsPressed));
	settingsButton->setPosition(ccp(545, 900));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCMenu* menu = CCMenu::create(playButton, settingsButton, NULL);
#else
	CCMenuItemSprite* exitButton = CCMenuItemSprite::create(
			imageSprite("ExitNormal"), imageSprite("ExitTapped"), this,
			menu_selector(MainMenu::onExitPressed));
	exitButton->setPosition(ccp(105, 900));

	CCMenu* menu = CCMenu::create(playButton, settingsButton, exitButton, NULL);
#endif

	menu->setPosition(CCPointZero);
	addChild(menu);
	animateConnectingDots();
	return true;
}

MainMenu::~MainMenu() {
}
