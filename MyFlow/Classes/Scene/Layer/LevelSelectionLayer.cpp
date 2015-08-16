/*
 * LevelSelectionCell.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: mvptech
 */

#include "LevelSelectionLayer.h"

const int LevelSelectionLayer::WOOD_PAD_TAG = 100;

const int LevelSelectionLayer::LEVEL_ROWS = 5;
const int LevelSelectionLayer::LEVEL_COLUMNS = 5;

LevelSelectionLayer::LevelSelectionLayer(const GridSize& gridSize,
		const CCSize padSize) :
	gridSize(gridSize), padSize(padSize) {

}

void LevelSelectionLayer::addAchievement(float & cellX, float & cellY,
		Level level) {
	CCPoint
			achievementPosition =
					ccp(cellX + (padSize.height / 2) - 20, cellY + (padSize.height / 2) - 25);
	if (level.isDoneOptimal()) {
		CCSprite *star = imageSprite("Star");
		star->setPosition(achievementPosition);
		addChild(star);
	} else if (level.isDone()) {
		CCSprite *checkBox = imageSprite("CheckBox");
		checkBox->setPosition(achievementPosition);
		addChild(checkBox);
	}
}

void LevelSelectionLayer::addPackLabels() {

	CCMenu* menu = CCMenu::create();

	CCNode* woodPad = getChildByTag(WOOD_PAD_TAG);
	float initialX = woodPad->getPosition().x
			- (woodPad->getContentSize().width / 2) + (padSize.width / 2) + 3.5;

	float cellX = initialX;
	float cellY = woodPad->getPosition().y + woodPad->getContentSize().height
			- (padSize.height / 2) - 3;

	for (int row = 1; row <= LEVEL_ROWS; row++) {
		for (int column = 1; column <= LEVEL_COLUMNS; column++) {
			int number = column + ((row - 1) * LEVEL_COLUMNS);
			Level level = Level::levelFor(number);
			if (!level.isNotTried()) {
				addPadBackground(ccp(cellX + 2, cellY - 2));
				addAchievement(cellX, cellY, level);
			}
			menu->addChild(addLabel(number, ccp(cellX, cellY)));
			cellX += padSize.width + WOOD_PAD_WIDTH_PADDING;
		}
		cellY -= padSize.height + WOOD_PAD_HEIGHT_PADDING;
		cellX = initialX;
	}

	menu->setPosition(CCPointZero);
	addChild(menu);
}

void LevelSelectionLayer::addPadBackground(const CCPoint& position) {
	CCSprite* donePadBackground = imageSprite("LevelDonePad");
	donePadBackground->setPosition(position);
	addChild(donePadBackground);
}

CCMenuItemLabel* LevelSelectionLayer::addLabel(int number,
		const CCPoint & position) {
	const char* text = CCString::createWithFormat("%d", number)->getCString();
	CCLabelTTF* label = levelLabel(text);
	//	label->setPosition(position);
	CCMenuItemLabel* labelItem = CCMenuItemLabel::create(label, this,
			menu_selector(LevelSelectionLayer::onLevelSelected));
	labelItem->setPosition(position);
	return labelItem;
	//	addChild(label, 0, number);
}

void LevelSelectionLayer::addWoodPad() {
	CCSprite* woodPad = imageSprite("WoodPad");
	woodPad->setPosition(ccp(VisibleRect::center().x, 162));
	woodPad->setAnchorPoint(ccp(0.5, 0));
	woodPad->setTag(WOOD_PAD_TAG);
	addChild(woodPad);
}

LevelSelectionLayer *LevelSelectionLayer::createWithGridAndPadSize(
		const GridSize & gridSize, CCSize padSize) {
	LevelSelectionLayer* levelSelectionLayer = new LevelSelectionLayer(
			gridSize, padSize);
	if (levelSelectionLayer && levelSelectionLayer->initWithGridAndPadSize()) {
		levelSelectionLayer->autorelease();
	} else {
		CC_SAFE_DELETE(levelSelectionLayer);
	}
	return levelSelectionLayer;
}

//void LevelSelectionLayer::ccTouchesBegan(CCSet *touches, CCEvent *event) {
//	CCTouch* touch = (CCTouch*) touches->anyObject();
//	for (int levelNumber = 1; levelNumber <= 25; levelNumber++) {
//		CCNode* label = getChildByTag(levelNumber);
//		if (label != NULL) {
//			CCRect
//					boundingBox =
//							CCRectMake(label->getPositionX() - padSize.width / 2, label->getPositionY() - padSize.height / 2, padSize.width, padSize.height);
//			if (boundingBox.containsPoint(touch->getLocation())) {
//				onLevelTouched(levelNumber);
//			}
//		}
//	}
//}

void LevelSelectionLayer::onLevelTouched(int number) {
	playSoundEffect("MenuClick");
	Level::setCurrentLevel(number);
	Level level = Level::levelFor(number);
	level.makeTriedIfNot();
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

void LevelSelectionLayer::onLevelSelected(CCObject* sender) {
	CCMenuItemLabel* itemLabel = (CCMenuItemLabel*) sender;
	CCLabelTTF* label = (CCLabelTTF*) itemLabel->getLabel();
	int number =
			CCString::createWithFormat("%s", label->getString())->intValue();
	playSoundEffect("MenuClick");
	Level::setCurrentLevel(number);
	Level level = Level::levelFor(number);
	level.makeTriedIfNot();
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

bool LevelSelectionLayer::initWithGridAndPadSize() {
	if (!CCLayer::init()) {
		return false;
	}

	//	setTouchEnabled(true);

	addWoodPad();

	CCString* gridSizeSpriteName = CCString::createWithFormat("%sLarge",
			gridSize.toString());
	CCSprite* gridSizeSprite = imageSprite(gridSizeSpriteName->getCString());
	gridSizeSprite->setPosition(ccp(VisibleRect::center().x, 805));
	addChild(gridSizeSprite);

	addPackLabels();
	return true;
}

LevelSelectionLayer::~LevelSelectionLayer() {
}
