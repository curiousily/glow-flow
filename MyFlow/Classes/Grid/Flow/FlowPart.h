//
//  PipePart.h
//  MyFlow
//
//

#ifndef __MyFlow__PipePart__
#define __MyFlow__PipePart__

#include "cocos2d.h"
#include "../GridPosition.h"
#include "../../ResourceFinder.h"

USING_NS_CC;

class FlowPart: public cocos2d::CCNode, ResourceFinder {
public:
	enum Direction {
		NONE, LEFT, RIGHT, TOP, BOTTOM
	};

CC_SYNTHESIZE(CCSprite*, sprite, Sprite)

CC_SYNTHESIZE(CCPoint, position, Position)

CC_SYNTHESIZE(GridPosition, gridPosition, GridPostion)

CC_SYNTHESIZE(CCArray*, connections, Connections)

private:
	bool isEndingPart;
	Direction direction;
	const char* flowName;

	virtual bool initWithFileAndPosition(const char* flowName,
			CCPoint position, Direction direciton, GridPosition gridPosition,
			float scaleFactor, bool shouldBeEndPart);

	bool hasTwoConnections();
	bool hasSingleConnection();
	bool hasNoConnections();

	void replaceSpriteWith(const char* spriteName);

	static FlowPart* doCreate(const char* flowName, CCPoint position,
			Direction direciton, GridPosition gridPosition, float scaleFactor,
			bool shouldBeEndPart);

public:
	static FlowPart* createWithFileAndPosition(const char* flowName,
			CCPoint position, Direction direciton, GridPosition gridPosition,
			float scaleFactor);
	static FlowPart* createEndPartWithFileAndPosition(const char* flowName,
			CCPoint position, Direction direciton, GridPosition gridPosition,
			float scaleFactor);
	void alignDirectionWithConnections(CCString* flowName);
	void reverseDirection();
	void connectTo(FlowPart*);
	bool isEndPart();
	void setDirection(Direction direction);
	Direction getDirection();

	bool isWithinOneStep(const GridPosition&);
	bool isWithinOneHorizontalStep(const GridPosition&);
	bool isWithinOneVerticalStep(const GridPosition&);

	bool isOnTopOf(const GridPosition& otherPosition);
	bool isToTheLeftOf(const GridPosition& otherPosition);

	const char* getResourceDirectory() {
		return "Game";
	}

	virtual ~FlowPart();
};

#endif /* defined(__MyFlow__PipePart__) */
