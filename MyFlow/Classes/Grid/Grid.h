/*
 * Grid.h
 *
 *  Created on: Dec 6, 2012
 *      Author: mvptech
 */

#ifndef GRID_H_
#define GRID_H_

class Flow;

#include "cocos2d.h"
#include "GridDelegate.h"
#include "GridPosition.h"
#include "Flow/Flow.h"
#include "Flow/FlowDelegate.h"
#include "../Constants.h"
#include "../ResourceFinder.h"

USING_NS_CC;

class Grid: public cocos2d::CCNode, public FlowDelegate, ResourceFinder {

	static const int MAX_ROWS = 100;
	static const int MAX_COLUMNS = 100;

	static const char NON_PIPE_POSITION = '.';

	GridDelegate* delegate;

	int rows, columns;

	CCSize tileSize;

	char Matrix[MAX_ROWS][MAX_COLUMNS];

	CCArray* flows;

	int completedFlows;

	CCSprite* tapCircle;

	virtual bool initWithRowsAndColumns(int rows, int columns,
			GridDelegate* delegate);

	float scaleFactor;

	Grid();

	bool isOutsideOfTheGrid(const GridPosition&);

public:

	CC_SYNTHESIZE(int, optimalMoves, OptimalMoves)

	static Grid* createWithRowsAndColumns(int rows, int columns,
			GridDelegate* delegate);

	void addFlow(const GridPosition& startPosition,
			const GridPosition& endPosition, char symbol, CCString* name);

	char symbolAt(const GridPosition& position);

	const char* getResourceDirectory() {
		return "Game";
	}

	void onFlowComplete();
	bool hasPartOnMap(const GridPosition& gridPosition);
	void onPartAdded(const GridPosition& gridPosition, char symbol);
	void onFlowTouched(const CCPoint& position);
	void onFlowTouchEnded();
	GridPosition gridPositionOf(const FlowPart* part);
	GridPosition gridPositionOf(const CCPoint & point);
	GridPosition gridPositionOf(float x, float y);

	virtual ~Grid();
};

#endif /* GRID_H_ */
