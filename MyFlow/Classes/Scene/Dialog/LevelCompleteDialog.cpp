/*
 * LevelCompleteDialog.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: mvptech
 */

#include "LevelCompleteDialog.h"

LevelCompleteDialog* LevelCompleteDialog::doCreate(int level, int moves,
		bool isPerfect) {
	LevelCompleteDialog* dialog = new LevelCompleteDialog();
	if (dialog && dialog->initWithLevelAndMoves(level, moves, isPerfect)) {
		dialog->autorelease();
	} else {
		CC_SAFE_DELETE(dialog);
	}
	return dialog;
}

LevelCompleteDialog *LevelCompleteDialog::createDonePerfectDialogWithLevelAndMoves(
		int level, int moves) {
	return doCreate(level, moves, true);
}

bool LevelCompleteDialog::initWithLevelAndMoves(int level, int moves,
		bool isPerfect) {
	if (!CCLayer::init()) {
		return false;
	}

	this->level = level;

	CCSprite* background = isPerfect ? imageSprite("PerfectBackground")
			: imageSprite("DoneBackground");
	background->setPosition(VisibleRect::center());
	addChild(background);

	const char* titleText = isPerfect ? "Level Perfect" : "Level Complete";
	CCLabelTTF* titleLabel = completeTitleLabel(titleText);
	titleLabel->setPosition(ccp(VisibleRect::center().x, 600));
	addChild(titleLabel);

	const char* descriptionText = "you have completed the level in";
	CCLabelTTF* descriptionLabel = completeTextLabel(descriptionText);
	descriptionLabel->setPosition(ccp(VisibleRect::center().x, 505));
	addChild(descriptionLabel);

	const char* movesText =
			CCString::createWithFormat("%d MOVES", moves)->getCString();
	CCLabelTTF* movesLabel = completeMovesLabel(movesText);
	movesLabel->setPosition(ccp(VisibleRect::center().x, 455));
	addChild(movesLabel);

	CCMenuItemSprite* nextLevelButton = CCMenuItemSprite::create(
			imageSprite("NextLevelNormal"), imageSprite("NextLevelTapped"),
			this, menu_selector(LevelCompleteDialog::onNextLevelPressed));
	nextLevelButton->setPosition(ccp(VisibleRect::center().x, 285));
	nextLevelButton->setAnchorPoint(ccp(0.5, 0));

	CCMenuItemSprite* toMenuButton = CCMenuItemSprite::create(
			imageSprite("ToMenuNormal"), imageSprite("ToMenuTapped"), this,
			menu_selector(LevelCompleteDialog::onMenuPressed));
	toMenuButton->setPosition(nextLevelButton->getPosition());
	toMenuButton->setAnchorPoint(nextLevelButton->getAnchorPoint());

	if (level + 1 > MAX_LEVELS) {
		nextLevelButton->setVisible(false);
	} else {
		toMenuButton->setVisible(false);
	}

	CCMenuItemSprite* playAgainButton = CCMenuItemSprite::create(
			imageSprite("PlayAgainNormal"), imageSprite("PlayAgainTapped"),
			this, menu_selector(LevelCompleteDialog::onPlayAgainPressed));
	playAgainButton->setPosition(ccp(VisibleRect::center().x, 162));
	playAgainButton->setAnchorPoint(ccp(0.5, 0));

	CCMenu* menu = CCMenu::create(nextLevelButton, toMenuButton,
			playAgainButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
	return true;
}

LevelCompleteDialog *LevelCompleteDialog::createDoneDialogWithLevelAndMoves(
		int level, int moves) {
	return doCreate(level, moves, false);
}

void LevelCompleteDialog::onNextLevelPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	int nextLevel = level + 1;
	Level::setCurrentLevel(nextLevel);
	Level level = Level::levelFor(nextLevel);
	level.makeTriedIfNot();
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

void LevelCompleteDialog::onPlayAgainPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

void LevelCompleteDialog::onMenuPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(LevelSelection::scene());
}

LevelCompleteDialog::~LevelCompleteDialog() {
}
