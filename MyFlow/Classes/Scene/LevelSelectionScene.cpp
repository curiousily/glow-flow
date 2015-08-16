/*
 * LevelSelectionScene.cpp
 *
 *  Created on: Dec 18, 2012
 *      Author: mvptech
 */

#include "LevelSelectionScene.h"

const int LevelSelection::LEVEL_SELECTION_LAYER = 100;
const int LevelSelection::TOTAL_PAGES = 5;

CCScene* LevelSelection::scene() {
	CCScene *scene = CCScene::create();
	LevelSelection *layer = LevelSelection::create();
	scene->addChild(layer);
	return scene;
}

bool LevelSelection::init() {
	if (!CCLayer::init()) {
		return false;
	}

	addBackground(this);

	CCSprite* tempCell = imageSprite("LevelDonePad");
	padSize = tempCell->getContentSize();
	CC_SAFE_DELETE(tempCell);

	Pack currentPack = Pack::currentPack();
	CCLabelTTF
			* packLabel =
					titleLabel(
							CCString::createWithFormat("%s Pack",
									currentPack.getName())->getCString());
	packLabel->setPosition(ccp(340, 875));
	packLabel->setAnchorPoint(ccp(0.5, 0));
	addChild(packLabel);

	Pager* pager = Pager::create();
	for (int page = 1; page <= TOTAL_PAGES; page++) {
		GridSize::setSizeForPage(page);
		LevelSelectionLayer* currentLayer =
				LevelSelectionLayer::createWithGridAndPadSize(
						GridSize::currentGridSize(), padSize);
		currentLayer->setPosition(
				ccp(VisibleRect::left().x, VisibleRect::bottom().y));
		pager->addPage(currentLayer);
	}
	GridSize::setSizeForPage(pager->getCurrentPage());
	pager->setOnPagePressed(this,
			callfuncN_selector(LevelSelection::onPagePressed));
	addChild(pager);

	CCMenuItemSprite* backButton = CCMenuItemSprite::create(
			globalSprite("BackButton"), globalSprite("BackButtonTapped"), this,
			menu_selector(LevelSelection::onBackPressed));
	backButton->setAnchorPoint(ccp(0, 0));
	backButton->setPosition(ccp(35, 860));

	CCMenu* menu = CCMenu::create(backButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu, 2);

	return true;
}

void LevelSelection::onPagePressed(CCObject* sender) {
	Pager* pager = (Pager*) sender;
	int newPage = pager->getCurrentPage();
	GridSize::setSizeForPage(newPage);
}

void LevelSelection::onBackPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(PackSelection::scene());
}

LevelSelection::~LevelSelection() {
}
