/*
 * PackSelectionLayer.h
 *
 *  Created on: Mar 5, 2013
 *      Author: mvptech
 */

#ifndef PACKSELECTIONLAYER_H_
#define PACKSELECTIONLAYER_H_

#include "cocos2d.h"
#include "../../GlowFlow.h"
#include "../../Grid/Pack.h"

USING_NS_CC;

class PackSelectionLayer: public cocos2d::CCLayer, ResourceFinder {
public:

	static PackSelectionLayer* createWithPack(const char* packName);

	const char* getResourceDirectory() {
		return "PackSelection";
	}

	virtual ~PackSelectionLayer();

private:

	CCString* packName;

	bool initWithPack(const char* packName);


	void onPlayPressed(CCObject* sender);
};

#endif /* PACKSELECTIONLAYER_H_ */
