/*
 * ResourceFinder.cpp
 *
 *  Created on: Dec 18, 2012
 *      Author: mvptech
 */

#include "ResourceFinder.h"

ResourceFinder::ResourceFinder() :
	scaleFactor(1.0f) {

}

const char* ResourceFinder::image(const char *name) {
	return CCString::createWithFormat("%s/%s.png", getResourceDirectory(), name)->getCString();
}

CCSprite* ResourceFinder::imageSprite(const char *name) {
	CCSprite* sprite = CCSprite::create(image(name));
	sprite->setScale(scaleFactor);
	return sprite;
}

CCSprite* ResourceFinder::globalSprite(const char *name) {
	const char* path =
			CCString::createWithFormat("Global/%s.png", name)->getCString();
	return CCSprite::create(path);
}

CCLabelTTF* ResourceFinder::titleLabel(const char *text) {
	return createLabel(text, 48);
}

CCLabelTTF* ResourceFinder::createLabel(const char *text, int fontSize) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCLabelTTF::create(text, "Gafata", fontSize);
#else
	return CCLabelTTF::create(text, "Fonts/Gafata.ttf", fontSize);
#endif

}

CCLabelTTF* ResourceFinder::completeTitleLabel(const char* text) {
	return createLabel(text, 60);
}

CCLabelTTF* ResourceFinder::completeTextLabel(const char* text) {
	return createLabel(text, 28);
}

CCLabelTTF* ResourceFinder::completeMovesLabel(const char* text) {
	return createLabel(text, 48);
}

CCLabelTTF* ResourceFinder::hudLabel(const char *text) {
	return createLabel(text, 24);
}

CCLabelTTF* ResourceFinder::levelLabel(const char *text) {
	return createLabel(text, 45);
}

void ResourceFinder::addBackground(CCNode *toNode) {
	CCSprite* background = imageSprite("Background");
	background->setPosition(VisibleRect::center());
	toNode->addChild(background);
}

void ResourceFinder::setSpriteScaleFactor(float scaleFactor) {
	this->scaleFactor = scaleFactor;
}

void ResourceFinder::playSoundEffect(const char *name) {
	SoundManager::sharedSoundManager()->playSoundEffect(name);
}

ResourceFinder::~ResourceFinder() {
}
