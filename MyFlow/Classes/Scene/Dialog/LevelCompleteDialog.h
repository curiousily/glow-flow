/*
 * LevelCompleteDialog.h
 *
 *  Created on: Dec 20, 2012
 *      Author: mvptech
 */

#ifndef LEVELCOMPLETEDIALOG_H_
#define LEVELCOMPLETEDIALOG_H_

#include "cocos2d.h"
#include "../../GlowFlow.h"
#include "../LoadingScene.h"
#include "../../Constants.h"
#include "../../GameManager.h"
#include "../../Grid/Level.h"
#include "../../Utility/VisibleRect.h"
#include "../../ResourceFinder.h"

USING_NS_CC;

class LevelCompleteDialog: public cocos2d::CCLayer, ResourceFinder {

	int level;

	void onMenuPressed(CCObject* sender);
	void onNextLevelPressed(CCObject* sender);
	void onPlayAgainPressed(CCObject* sender);

public:
	static LevelCompleteDialog* doCreate(int level, int moves, bool isPerfect);

	bool initWithLevelAndMoves(int level, int moves, bool isPerfect);

	static LevelCompleteDialog* createDoneDialogWithLevelAndMoves(int level,
			int moves);
	static LevelCompleteDialog* createDonePerfectDialogWithLevelAndMoves(
			int level, int moves);

	const char* getResourceDirectory() {
		return "LevelComplete";
	}

	virtual ~LevelCompleteDialog();
};

#endif /* LEVELCOMPLETEDIALOG_H_ */
