/*
 * PackSelectionScene.h
 *
 *  Created on: Feb 5, 2013
 *      Author: mvptech
 */

#ifndef PACKSELECTIONSCENE_H_
#define PACKSELECTIONSCENE_H_

#include "cocos2d.h"
#include "../GlowFlow.h"
#include "../ResourceFinder.h"
#include "Layer/PackSelectionLayer.h"
#include "Node/Pager.h"

USING_NS_CC;

class PackSelection: public cocos2d::CCLayer, ResourceFinder {
public:
	PackSelection();
	virtual ~PackSelection();

	static CCScene* scene();

	virtual bool init();

	const char* getResourceDirectory() {
		return "PackSelection";
	}

	CREATE_FUNC(PackSelection)

private:

	void onBackPressed(CCObject* sender);
};

#endif /* PACKSELECTIONSCENE_H_ */
