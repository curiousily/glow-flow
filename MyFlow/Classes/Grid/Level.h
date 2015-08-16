/*
 * Level.h
 *
 *  Created on: Dec 19, 2012
 *      Author: mvptech
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "cocos2d.h"
#include "LevelReader.h"
#include "GridSize.h"
#include "Pack.h"

USING_NS_CC;

class Level {

public:
	enum LevelStatus {
		NotTried, Tried, Done, DoneOptimal
	};

private:
	const static char* CURRENT_LEVEL_KEY;
	const static char* LEVEL_STATUS_KEY_PREFIX;

	static const int DEFAULT_LEVEL = 1;

	LevelStatus status;

	CCUserDefault* db;

	const char* buildStatusKey();

public:

	Level(int number);

CC_SYNTHESIZE_READONLY(int, number, Number)

	static void setCurrentLevel(int number);
	static Level levelFor(int number);
	static Level currentLevel();

	void setStatus(LevelStatus status);
	void makeTriedIfNot();

	Pack getPack();
	GridSize getGridSize();

	bool isDone();
	bool isDoneOptimal();
	bool isTried();
	bool isNotTried();

	virtual ~Level();
};

#endif /* LEVEL_H_ */
