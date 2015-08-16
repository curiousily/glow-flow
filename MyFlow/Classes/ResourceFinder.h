/*
 * ResourceFinder.h
 *
 *  Created on: Dec 18, 2012
 *      Author: mvptech
 */

#ifndef RESOURCEFINDER_H_
#define RESOURCEFINDER_H_

#include "cocos2d.h"
#include "Utility/VisibleRect.h"
#include "SoundManager.h"

USING_NS_CC;

class ResourceFinder {

private:
	CCLabelTTF* createLabel(const char* text, int fontSize);

	float scaleFactor;

protected:
	virtual const char* getResourceDirectory() = 0;
	const char* image(const char* name);

	void setSpriteScaleFactor(float scaleFactor);

	CCSprite* imageSprite(const char* name);
	CCSprite* globalSprite(const char* name);
	void addBackground(CCNode* toNode);
	CCLabelTTF* completeTitleLabel(const char* text);
	CCLabelTTF* completeTextLabel(const char* text);
	CCLabelTTF* completeMovesLabel(const char* text);
	CCLabelTTF* titleLabel(const char* text);
	CCLabelTTF* hudLabel(const char* text);
	CCLabelTTF* levelLabel(const char* text);
	void playSoundEffect(const char* name);

public:
	ResourceFinder();
	virtual ~ResourceFinder();
};

#endif /* RESOURCEFINDER_H_ */
