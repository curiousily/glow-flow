/*
 * Pager.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: mvptech
 */

#include "Pager.h"

Pager::Pager() :
	currentPage(1), onPagePressedCallback(NULL) {

}

bool Pager::init() {
	pages = CCArray::create();
	pages->retain();

	CCSprite* numberPlace = globalSprite("NumberPlace");
	numberPlace->setPosition(
			ccp(VisibleRect::center().x, VisibleRect::bottom().y + 80));
	addChild(numberPlace);

	pageLabel = titleLabel("1");
	pageLabel->setPosition(numberPlace->getPosition());
	addChild(pageLabel);

	CCSize numberPlaceSize = numberPlace->getContentSize();

	leftButton = CCMenuItemSprite::create(globalSprite("LeftArrowNormal"),
			globalSprite("LeftArrowTapped"), this,
			menu_selector(Pager::onLeftPressed));
	CCSize leftButtonSize = leftButton->getContentSize();

	float leftButtonXPosition = numberPlace->getPosition().x
			- (numberPlaceSize.width / 2) - (leftButtonSize.width / 2);

	leftButton->setPosition(
			ccp(leftButtonXPosition, VisibleRect::bottom().y + 80));

	rightButton = CCMenuItemSprite::create(globalSprite("RightArrowNormal"),
			globalSprite("RightArrowTapped"), this,
			menu_selector(Pager::onRightPressed));

	float rightButtonXPosition = numberPlace->getPosition().x
			+ (numberPlaceSize.width / 2) + (leftButtonSize.width / 2);

	rightButton->setPosition(
			ccp(rightButtonXPosition, VisibleRect::bottom().y + 80));

	CCMenu* menu = CCMenu::create(leftButton, rightButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	leftButton->setVisible(false);

	return true;
}

Pager *Pager::create() {
	Pager* pager = new Pager();
	if (pager && pager->init()) {
		pager->autorelease();
	} else {
		CC_SAFE_DELETE(pager);
	}
	return pager;
}

void Pager::addPage(CCLayer *page) {
	CCPoint pagePosition = page->getPosition();
	page->setPosition(
			ccp(pagePosition.x + (getPageCount() * VisibleRect::getVisibleRect().size.width), pagePosition.y));
	page->setTag(getPageCount() + 1);
	addChild(page);
	pages->addObject(page);
}

int Pager::getPageCount() {
	return pages->count();
}

void Pager::hidePageButtons() {
	leftButton->setVisible(false);
	rightButton->setVisible(false);
}

void Pager::onLeftPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	currentPage--;
	hidePageButtons();
	slideEachPageBy(VisibleRect::getVisibleRect().size.width,
			callfuncN_selector(Pager::onSlideComplete));
}

void Pager::onRightPressed(CCObject *sender) {
	playSoundEffect("MenuClick");
	currentPage++;
	hidePageButtons();
	slideEachPageBy(-VisibleRect::getVisibleRect().size.width,
			callfuncN_selector(Pager::onSlideComplete));
}

void Pager::onSlideComplete(CCObject* sender) {
	if (onPagePressedCallback != NULL) {
		onPagePressedCallback->execute();
	}
	updatePageNumber();
	if (currentPage > 1) {
		leftButton->setVisible(true);
	}
	if (currentPage + 1 <= getPageCount()) {
		rightButton->setVisible(true);
	}
}

void Pager::slideEachPageBy(float xDistance, SEL_CallFuncN onSlideComplete) {
	CCObject* obj;
	CCARRAY_FOREACH(pages, obj) {
			CCNode* page = (CCNode*) obj;
			page->runAction(CCMoveBy::create(0.8f, ccp(xDistance, 0)));
		}

	runAction(
			CCSequence::create(CCDelayTime::create(1.0f),
					CCCallFuncN::create(this, onSlideComplete), NULL));
}

void Pager::setOnPagePressed(CCObject* target, SEL_CallFuncN callback) {
	onPagePressedCallback = CCCallFuncN::create(target, callback);
	onPagePressedCallback->setTarget(this);
	onPagePressedCallback->retain();
}

int Pager::getCurrentPage() {
	return currentPage;
}

void Pager::updatePageNumber() {
	pageLabel->setString(
			CCString::createWithFormat("%d", currentPage)->getCString());
}

Pager::~Pager() {
	pages->release();
	CC_SAFE_RELEASE(onPagePressedCallback);
}
