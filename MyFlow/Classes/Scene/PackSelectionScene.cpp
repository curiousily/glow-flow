/*
 * PackSelectionScene.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: mvptech
 */

#include "PackSelectionScene.h"

PackSelection::PackSelection() {

}

CCScene *PackSelection::scene() {
	CCScene *scene = CCScene::create();
	PackSelection *layer = PackSelection::create();
	scene->addChild(layer);
	return scene;
}

bool PackSelection::init() {
	if (!CCLayer::init()) {
		return false;
	}

	addBackground(this);

	CCMenuItemSprite* backButton = CCMenuItemSprite::create(
			globalSprite("BackButton"), globalSprite("BackButtonTapped"), this,
			menu_selector(PackSelection::onBackPressed));
	backButton->setAnchorPoint(ccp(0, 0));
	backButton->setPosition(ccp(35, 860));

	CCLabelTTF* choosePackLabel = titleLabel("Choose Pack");
	choosePackLabel->setPosition(ccp(340, 875));
	choosePackLabel->setAnchorPoint(ccp(0.5, 0));
	addChild(choosePackLabel);

	Pager* pager = Pager::create();
	for (int i = 0; i < PACKS.size(); i++) {
		PackSelectionLayer* layer =
				PackSelectionLayer::createWithPack(PACKS[i]);
		pager->addPage(layer);
	}

	addChild(pager);

	CCMenu* menu = CCMenu::create(backButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	return true;
}

void PackSelection::onBackPressed(CCObject *sender) {
	GameManager::sharedGameManager()->runScene(MainMenu::scene());
}

PackSelection::~PackSelection() {
}
