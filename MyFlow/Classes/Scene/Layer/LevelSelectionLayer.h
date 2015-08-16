/*
 * LevelSelectionCell.h
 *
 *  Created on: Dec 23, 2012
 *      Author: mvptech
 */

#ifndef LEVELSELECTIONCELL_H_
#define LEVELSELECTIONCELL_H_

#include "cocos2d.h"
#include "../../GlowFlow.h"
#include "../../Grid/Level.h"

USING_NS_CC;

class LevelSelectionLayer: public CCLayer, ResourceFinder {

public:
	LevelSelectionLayer(const GridSize& gridSize, const CCSize padSize);

	static LevelSelectionLayer* createWithGridAndPadSize(
			const GridSize& gridSize, CCSize padSize);

	virtual ~LevelSelectionLayer();

//	void ccTouchesBegan(CCSet *touches, CCEvent *event);

	const char* getResourceDirectory() {
		return "LevelSelection";
	}

private:

	static const int LEVEL_ROWS;
	static const int LEVEL_COLUMNS;
	static const int WOOD_PAD_TAG;

	GridSize gridSize;
	CCSize padSize;

	bool initWithGridAndPadSize();

	void addPackLabels();

	void addPadBackground(const CCPoint& position);

	CCMenuItemLabel* addLabel(int number, const CCPoint& position);

	void addWoodPad();

	void onLevelSelected(CCObject* sender);

	void onLevelTouched(int number);
	void addAchievement(float & cellX, float & cellY, Level level);
};

#endif /* LEVELSELECTIONCELL_H_ */
