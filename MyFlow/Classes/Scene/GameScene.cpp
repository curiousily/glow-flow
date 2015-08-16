#include "GameScene.h"

Game::Game() :
	level(Level::currentLevel()) {
}

CCScene* Game::scene() {
	CCScene *scene = CCScene::create();
	Game *layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}

	grid = LevelReader::fromFile(level.getPack(), level.getGridSize(),
			level.getNumber(), this);

	addChild(grid, 1);

	levelInformationLayer = LevelInformationLayer::createWithLevel(level,
			grid->getOptimalMoves());
	addChild(levelInformationLayer, 2);

	CCSprite* background = imageSprite("Background");
	background->setPosition(VisibleRect::center());
	addChild(background);

	CCMenuItemSprite* backButton = CCMenuItemSprite::create(
			globalSprite("BackButton"), globalSprite("BackButtonTapped"), this,
			menu_selector(Game::onBackPressed));
	backButton->setAnchorPoint(ccp(0, 0));
	backButton->setPosition(ccp(35, 860));

	CCMenuItemSprite* leftButton = CCMenuItemSprite::create(
			imageSprite("ButtonLeft"), imageSprite("ButtonLeftTapped"), this,
			menu_selector(Game::onLeftButtonPressed));
	leftButton->setPosition(ccp(120, 100));

	CCMenuItemSprite* reloadButton = CCMenuItemSprite::create(
			imageSprite("ButtonReload"), imageSprite("ButtonReloadTapped"),
			this, menu_selector(Game::onReloadPressed));
	reloadButton->setPosition(ccp(310, 100));

	CCMenuItemSprite* rightButton = CCMenuItemSprite::create(
			imageSprite("ButtonRight"), imageSprite("ButtonRightTapped"), this,
			menu_selector(Game::onRightButtonPressed));
	rightButton->setPosition(ccp(510, 100));

	CCMenu* menu = CCMenu::create(leftButton, reloadButton, rightButton,
			backButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu, 2);
	if (level.getNumber() + 1 > MAX_LEVELS) {
		rightButton->setVisible(false);
	}
	if (level.getNumber() - 1 < 1) {
		leftButton->setVisible(false);
	}
	return true;
}

void Game::onLeftButtonPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	int previousLevel = level.getNumber() - 1;
	Level::setCurrentLevel(previousLevel);
	Level level = Level::levelFor(previousLevel);
	level.makeTriedIfNot();
	GameManager::sharedGameManager()->runScene(Loading::scene());

}

void Game::onRightButtonPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	int nextLevel = level.getNumber() + 1;
	Level::setCurrentLevel(nextLevel);
	Level level = Level::levelFor(nextLevel);
	level.makeTriedIfNot();
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

void Game::onBackPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(LevelSelection::scene());
}

void Game::onReloadPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(Loading::scene());
}

void Game::onFlowComplete(int completedFlows, int totalFlows) {
	playSoundEffect("FlowConnected");
	float levelProgress = ((float) ((float) completedFlows / totalFlows))
			* 100.0f;
	levelInformationLayer->setProgressTo(levelProgress);
}

void Game::onMoveComplete() {
	levelInformationLayer->incrementMoves();
}

void Game::onLevelComplete() {
	int moves = levelInformationLayer->getMoves();
	LevelCompleteDialog* dialog;
	if (moves == grid->getOptimalMoves()) {
		playSoundEffect("LevelPerfect");
		level.setStatus(Level::DoneOptimal);
		dialog = LevelCompleteDialog::createDonePerfectDialogWithLevelAndMoves(
				level.getNumber(), moves);
	} else {
		playSoundEffect("LevelComplete");
		if (!level.isDoneOptimal()) {
			level.setStatus(Level::Done);
		}
		dialog = LevelCompleteDialog::createDoneDialogWithLevelAndMoves(
				level.getNumber(), moves);
	}
	runAction(
			CCSequence::create(
					CCDelayTime::create(1.5f),
					CCCallFuncO::create(
							this,
							callfuncO_selector(Game::onDisplayLevelCompleteDialog),
							dialog), NULL));
}

void Game::onDisplayLevelCompleteDialog(CCObject *dialog) {
	CCNode* dialogNode = (CCNode*) dialog;
	dialogNode->setScale(0.5f);
	addChild(dialogNode, 2);
	dialogNode->runAction(CCScaleTo::create(0.2, 1.0f));
}

Game::~Game() {
}
