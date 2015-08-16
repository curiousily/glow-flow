/*
 * SettingsScene.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: mvptech
 */

#include "SettingsScene.h"

Settings::Settings() {

}

Settings::~Settings() {
}

CCScene *Settings::scene() {
	CCScene *scene = CCScene::create();
	Settings *layer = Settings::create();
	scene->addChild(layer);
	return scene;
}

bool Settings::init() {
	if (!CCLayer::init()) {
		return false;
	}

	addBackground(this);

	CCMenuItem* doneButton = CCMenuItemSprite::create(
			imageSprite("DoneNormal"), imageSprite("DoneTapped"), this,
			menu_selector(Settings::onDoneTapped));
	doneButton->setPosition(ccp(545, 900));

	SoundManager* soundManager = SoundManager::sharedSoundManager();

	CCLabelTTF* soundLabel = titleLabel("SOUND");
	soundLabel->setPosition(ccp(VisibleRect::center().x, 760));
	addChild(soundLabel);

	CCMenuItem* onState = CCMenuItemSprite::create(imageSprite("OnState"),
			imageSprite("OffState"));
	CCMenuItem* offState = CCMenuItemSprite::create(imageSprite("OffState"),
			imageSprite("OffState"));

	CCMenuItemToggle* soundButton = CCMenuItemToggle::createWithTarget(this,
			menu_selector(Settings::onSoundToggle), onState, offState, NULL);

	if (!soundManager->isSoundEnabled()) {
		soundButton->setSelectedIndex(1);
	}

	soundButton->setPosition(ccp(VisibleRect::center().x, 630));

	CCLabelTTF* musicLabel = titleLabel("MUSIC");
	musicLabel->setPosition(ccp(VisibleRect::center().x, 490));
	addChild(musicLabel);

	CCMenuItem* onMusicState = CCMenuItemSprite::create(imageSprite("OnState"),
			imageSprite("OffState"));
	CCMenuItem* offMusicState = CCMenuItemSprite::create(
			imageSprite("OffState"), imageSprite("OffState"));

	CCMenuItemToggle* musicButton = CCMenuItemToggle::createWithTarget(this,
			menu_selector(Settings::onMusicToggle), onMusicState,
			offMusicState, NULL);

	musicButton->setPosition(ccp(VisibleRect::center().x, 362));

	if (!soundManager->isMusicEnabled()) {
		musicButton->setSelectedIndex(1);
	}

	CCMenu* menu = CCMenu::create(doneButton, soundButton, musicButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	return true;
}

void Settings::onDoneTapped(CCObject* sender) {
	playSoundEffect("MenuClick");
	GameManager::sharedGameManager()->runScene(MainMenu::scene());
}

void Settings::onMusicToggle(CCObject *sender) {
	CCMenuItemToggle* musicButton = (CCMenuItemToggle*) sender;
	SoundManager* soundManager = SoundManager::sharedSoundManager();
	if (musicButton->getSelectedIndex() == 0) {
		soundManager->unmuteMusic();
	} else {
		soundManager->muteMusic();
	}
	playSoundEffect("MenuClick");
}

void Settings::onSoundToggle(CCObject *sender) {
	CCMenuItemToggle* soundButton = (CCMenuItemToggle*) sender;
	SoundManager* soundManager = SoundManager::sharedSoundManager();
	if (soundButton->getSelectedIndex() == 0) {
		soundManager->unmuteSound();
	} else {
		soundManager->muteSound();
	}
	playSoundEffect("MenuClick");
}
