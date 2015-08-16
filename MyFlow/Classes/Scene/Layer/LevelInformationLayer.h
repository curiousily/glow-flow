/*
 * LevelProgressLayer.h
 *
 *  Created on: Nov 20, 2012
 *      Author: mvptech
 */

#ifndef LEVELPROGRESSLAYER_H_
#define LEVELPROGRESSLAYER_H_

#include "cocos2d.h"
#include "../../GlowFlow.h"

USING_NS_CC;

class Level;

class LevelInformationLayer: public cocos2d::CCLayer, ResourceFinder {

	CCLabelTTF* moveCountLabel;
	CCLabelTTF* optimalMovesLabel;

	int moves;

	CCProgressTimer* levelProgress;

	bool initWithLevel(Level level, int optimalMoves);

public:
	void incrementMoves();

	int getMoves();

	void setProgressTo(float percentage);

	const char* getResourceDirectory() {
		return "Game";
	}

	static LevelInformationLayer* createWithLevel(Level level, int optimalMoves);

	virtual ~LevelInformationLayer();
};

#endif /* LEVELPROGRESSLAYER_H_ */
