//
//  Pipe.h
//  MyFlow
//
//

#ifndef __MyFlow__Pipe__
#define __MyFlow__Pipe__

#include "cocos2d.h"
#include "FlowDelegate.h"
#include "FlowPart.h"
#include "../GridPosition.h"
#include "../../Utility/VisibleRect.h"
#include "../../Constants.h"

USING_NS_CC;

class Flow: public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate {

	enum FlowState {
		Selected, NotSelected, Complete
	};

	FlowState state;
	GridPosition lastTouchedPosition;
	cocos2d::CCArray* parts;
	cocos2d::CCArray* activeParts;
	FlowDelegate* delegate;
	CCString* name;
	char symbol;
	CCSize tileSize;

	float scaleFactor;

	virtual bool initWithPosition(const GridPosition & startPosition,
			const GridPosition & endPosition, char symbol, CCString* name,
			const CCSize& tileSize, float scaleFactor, FlowDelegate* delegate);

	void makeComplete();

	void createEndParts(const GridPosition & startPosition,
			const GridPosition & endPosition);

	void addPartConnectedTo(GridPosition & partPosition, FlowPart* connection);

	bool flowIsTouched(const CCPoint& touchLocation);

	FlowPart* findConnectionFor(const GridPosition& position);

	void adjustConnectingToPartDirection(FlowPart* connectingToPart,
			FlowPart* connectionPart);

	bool isComplete();

	CCPoint computePartPosition(const GridPosition& position);

	FlowPart* addPartAt(const GridPosition & position,
			FlowPart::Direction direction);

	FlowPart* addEndPartAt(const GridPosition & position,
				FlowPart::Direction direction);

	FlowPart* doAddPart(FlowPart* part);

	void animateGlowingPart(FlowPart* part);

	void onAnimationGlowingPartComplete(CCObject* sender);

public:

	virtual ~Flow();

	static Flow* createWithPosition(const GridPosition & startPosition,
			const GridPosition & endPosition, char symbol, CCString* name,
			const CCSize& tileSize, float scaleFactor, FlowDelegate* delegate);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

};

#endif /* defined(__MyFlow__Pipe__) */
