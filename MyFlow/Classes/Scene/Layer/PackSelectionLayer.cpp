/*
 * PackSelectionLayer.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: mvptech
 */

#include "PackSelectionLayer.h"

PackSelectionLayer *PackSelectionLayer::createWithPack(const char *packName) {
	PackSelectionLayer* packSelectionLayer = new PackSelectionLayer();
	if (packSelectionLayer && packSelectionLayer->initWithPack(packName)) {
		packSelectionLayer->autorelease();
	} else {
		CC_SAFE_DELETE(packSelectionLayer);
	}
	return packSelectionLayer;
}

bool PackSelectionLayer::initWithPack(const char *packName) {
	if (!CCLayer::init()) {
		return false;
	}

	this->packName = CCString::create(packName);
	this->packName->retain();

	CCSprite* packBackground = imageSprite("BoughtPack");
	packBackground->setPosition(
			ccp(VisibleRect::center().x , VisibleRect::center().y + 10));
	addChild(packBackground);

	CCSprite* packIcon = imageSprite(
			CCString::createWithFormat("%sPackIcon", packName)->getCString());
	packIcon->setPosition(
			ccp(VisibleRect::left().x + 125, VisibleRect::top().y - 220));
	addChild(packIcon);

	CCLabelTTF* packLabel = titleLabel(
			CCString::createWithFormat("%s\nPack", packName)->getCString());
	packLabel->setPosition(
			ccp(VisibleRect::center().x, VisibleRect::top().y - 220));
	addChild(packLabel);

	CCMenuItemSprite* playButton = CCMenuItemSprite::create(
			imageSprite("PlayButtonNormal"), imageSprite("PlayButtonTapped"),
			this, menu_selector(PackSelectionLayer::onPlayPressed));

	playButton->setPosition(
			ccp(VisibleRect::center().x, VisibleRect::bottom().y + 250));

	CCMenu* menu = CCMenu::create(playButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	return true;
}

void PackSelectionLayer::onPlayPressed(CCObject *sender) {
    playSoundEffect("MenuClick");
	Pack::setCurrentPack(packName->getCString());
	GameManager::sharedGameManager()->runScene(LevelSelection::scene());
}

PackSelectionLayer::~PackSelectionLayer() {
	this->packName->release();
}
