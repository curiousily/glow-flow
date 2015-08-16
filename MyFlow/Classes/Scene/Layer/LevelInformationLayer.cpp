/*
 * LevelProgressLayer.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: mvptech
 */

#include "LevelInformationLayer.h"

LevelInformationLayer* LevelInformationLayer::createWithLevel(Level level,
		int optimalMoves) {
	LevelInformationLayer* levelInformationLayer = new LevelInformationLayer();
	if (levelInformationLayer && levelInformationLayer->initWithLevel(level,
			optimalMoves)) {
		levelInformationLayer->autorelease();
	} else {
		CC_SAFE_DELETE(levelInformationLayer);
	}
	return levelInformationLayer;
}

bool LevelInformationLayer::initWithLevel(Level level, int optimalMoves) {

	if (!CCLayer::init()) {
		return false;
	}

	moves = 0;

	CCSprite* menuBackground = imageSprite("MenuBackground");
	menuBackground->setPosition(ccp(VisibleRect::center().x, 895));
	addChild(menuBackground);

	const char* levelText =
			CCString::createWithFormat("%d", level.getNumber())->getCString();
	CCLabelTTF* levelLabel = hudLabel(levelText);
	levelLabel->setPosition(
			ccp(225, menuBackground->getPosition().y + (menuBackground->getContentSize().height / 2) - 30));
	levelLabel->setAnchorPoint(ccp(0, 0.5));
	addChild(levelLabel);

	moveCountLabel = hudLabel("0");
	moveCountLabel->setAnchorPoint(ccp(0, 0.5));
	moveCountLabel->setPosition(ccp(225, 878));
	addChild(moveCountLabel);

	const char* optimalMovesText = CCString::createWithFormat("%d",
			optimalMoves)->getCString();
	optimalMovesLabel = hudLabel(optimalMovesText);
	optimalMovesLabel->setAnchorPoint(ccp(0, 0.5));
	optimalMovesLabel->setPosition(ccp(424, 878));
	addChild(optimalMovesLabel);

	levelProgress = CCProgressTimer::create(imageSprite("Progress"));
	levelProgress->setType(kCCProgressTimerTypeBar);
	levelProgress->setPosition(
			ccp(menuBackground->getPosition().x - 39, menuBackground->getPosition().y + (menuBackground->getContentSize().height / 2) - 25));
	levelProgress->setAnchorPoint(ccp(0, 0.5));
	levelProgress->setBarChangeRate(ccp(1, 0));
	levelProgress->setMidpoint(ccp(0, 0.5));
	levelProgress->setPercentage(0);

	addChild(levelProgress);

	const char* gridSizeSpriteName = CCString::createWithFormat("GridSize%s",
			level.getGridSize().toString())->getCString();
	CCSprite* gridSize = imageSprite(gridSizeSpriteName);
	gridSize->setPosition(ccp(552, 900));
	addChild(gridSize);

	return true;
}

void LevelInformationLayer::incrementMoves() {
	moves++;
	moveCountLabel->setString(
			CCString::createWithFormat("%d", moves)->getCString());
}

void LevelInformationLayer::setProgressTo(float percentage) {
	levelProgress->runAction(
			CCProgressFromTo::create(0.4, levelProgress->getPercentage(),
					percentage));
}

int LevelInformationLayer::getMoves() {
	return moves;
}

LevelInformationLayer::~LevelInformationLayer() {
}
