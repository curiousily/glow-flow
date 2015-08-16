/*
 * Pager.h
 *
 *  Created on: Mar 5, 2013
 *      Author: mvptech
 */

#ifndef PAGER_H_
#define PAGER_H_

#include "cocos2d.h"
#include "../../GlowFlow.h"

USING_NS_CC;

class Pager: public cocos2d::CCNode, ResourceFinder {
public:
	static Pager* create();

	void addPage(CCLayer* page);

	int getPageCount();

	int getCurrentPage();

	void setOnPagePressed(CCObject* target, SEL_CallFuncN callback);

	const char* getResourceDirectory() {
		return "";
	}

	virtual ~Pager();
private:

	int currentPage;
	CCArray* pages;

	CCLabelTTF* pageLabel;

	CCMenuItemSprite* leftButton;
	CCMenuItemSprite* rightButton;

	CCCallFuncN* onPagePressedCallback;

	Pager();

	bool init();

	void hidePageButtons();

	void onLeftPressed(CCObject* sender);
	void onRightPressed(CCObject* sender);

	void slideEachPageBy(float xDistance, SEL_CallFuncN onSlideComplete);

	void onSlideComplete(CCObject* sender);

	void updatePageNumber();
};

#endif /* PAGER_H_ */
