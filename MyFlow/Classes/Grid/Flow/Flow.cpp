//
//  Pipe.cpp
//  MyFlow
//
//

#include "Flow.h"

bool Flow::initWithPosition(const GridPosition & startPosition,
		const GridPosition & endPosition, char symbol, CCString* name,
		const CCSize& tileSize, float scaleFactor, FlowDelegate* delegate) {
	parts = CCArray::create();
	parts->retain();
	this->delegate = delegate;

	this->tileSize = tileSize;

	activeParts = CCArray::create();
	activeParts->retain();

	this->name = name;
	this->name->retain();
	this->symbol = symbol;

	state = NotSelected;

	this->scaleFactor = scaleFactor;

	createEndParts(startPosition, endPosition);

	return activeParts;
}

Flow* Flow::createWithPosition(const GridPosition & startPosition,
		const GridPosition & endPosition, char symbol, CCString* name,
		const CCSize& tileSize, float scaleFactor, FlowDelegate* delegate) {
	Flow* pipe = new Flow();
	if (pipe && pipe->initWithPosition(startPosition, endPosition, symbol,
			name, tileSize, scaleFactor, delegate)) {
		pipe->autorelease();
	} else {
		CC_SAFE_DELETE(pipe);
	}
	return pipe;
}

void Flow::onEnter() {
	CCDirector* director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	CCNode::onEnter();
}

void Flow::onExit() {
	CCDirector* director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

bool Flow::ccTouchBegan(CCTouch *touch, CCEvent *event) {
	if (isComplete()) {
		return false;
	}
	CCPoint touchLocation = touch->getLocation();

	if (flowIsTouched(touchLocation)) {
		CCLog("Touching %s", name->getCString());
		state = Selected;
		lastTouchedPosition = delegate->gridPositionOf(touchLocation);
		return true;
	} else {
		CCLog("Not touching %s", name->getCString());
		state = NotSelected;
		return false;
	}
}

void Flow::ccTouchMoved(CCTouch *touch, CCEvent *event) {
	if (isComplete()) {
		return;
	}

	GridPosition partPosition = delegate->gridPositionOf(touch->getLocation());
	if (isInvalidPosition(partPosition)) {
		lastTouchedPosition = INVALID_GRID_POSITION;
		return;
	}
	delegate->onFlowTouched(touch->getLocation());

	if (isValidPosition(lastTouchedPosition)) {
		FlowPart* activePart1 = (FlowPart*) activeParts->objectAtIndex(0);
		FlowPart* activePart2 = (FlowPart*) activeParts->objectAtIndex(1);

		GridPosition part1Position = activePart1->getGridPostion();
		GridPosition part2Position = activePart2->getGridPostion();

		if (((part1Position == partPosition && part2Position
				== lastTouchedPosition) || (part1Position
				== lastTouchedPosition && part2Position == partPosition))
				&& activePart1->isWithinOneStep(part2Position)) {
			makeComplete();
			return;
		}
	}

	if (delegate->hasPartOnMap(partPosition)) {
		return;
	}

	FlowPart* connection = findConnectionFor(partPosition);
	if (!connection) {
		return;
	}
	addPartConnectedTo(partPosition, connection);
	delegate->onPartAdded(partPosition, symbol);
	if (!(lastTouchedPosition == partPosition)) {
		lastTouchedPosition = partPosition;
	}
}

void Flow::ccTouchEnded(CCTouch *touch, CCEvent *event) {
	delegate->onFlowTouchEnded();
	if (isComplete()) {
		return;
	}
	lastTouchedPosition = INVALID_GRID_POSITION;
	state = NotSelected;
}

bool Flow::flowIsTouched(const CCPoint & touchLocation) {
	CCObject* obj;
	CCARRAY_FOREACH(parts, obj) {
			FlowPart* part = (FlowPart*) obj;
			CCRect partBoundingBox = part->getSprite()->boundingBox();
			if (partBoundingBox.containsPoint(touchLocation)) {
				return true;
			}
		}
	return false;
}

void Flow::createEndParts(const GridPosition & startPosition,
		const GridPosition & endPosition) {
	addEndPartAt(startPosition, FlowPart::NONE);
	addEndPartAt(endPosition, FlowPart::NONE);
}

CCPoint Flow::computePartPosition(const GridPosition& position) {
	float xPosition = (position.column - 1) * tileSize.width + tileSize.width
			/ 2 + GRID_WIDTH_OFFSET;
	float yPosition = position.row * tileSize.height - tileSize.height / 2
			+ GRID_HEIGHT_BOTTOM_OFFSET;
	return ccp(xPosition, yPosition);
}

FlowPart* Flow::addPartAt(const GridPosition & position,
		FlowPart::Direction orientation) {
	return doAddPart(
			FlowPart::createWithFileAndPosition(name->getCString(),
					computePartPosition(position), orientation, position,
					scaleFactor));
}

FlowPart* Flow::addEndPartAt(const GridPosition & position,
		FlowPart::Direction orientation) {
	return doAddPart(
			FlowPart::createEndPartWithFileAndPosition(name->getCString(),
					computePartPosition(position), orientation, position,
					scaleFactor));
}

FlowPart* Flow::doAddPart(FlowPart* part) {
	parts->addObject(part);
	activeParts->addObject(part);
	addChild(part);
	return part;
}

FlowPart *Flow::findConnectionFor(const GridPosition & position) {
	CCObject *obj;
	CCARRAY_FOREACH(activeParts, obj) {
			FlowPart* activePart = dynamic_cast<FlowPart*> (obj);
			if (activePart->isWithinOneStep(position)
					&& activePart->getGridPostion() == lastTouchedPosition) {
				return activePart;
			}
		}
	return NULL;
}

void Flow::addPartConnectedTo(GridPosition & partPosition, FlowPart* connection) {
	GridPosition connectionPosition = delegate->gridPositionOf(connection);
	FlowPart::Direction partDirection = FlowPart::BOTTOM;
	if (connection->isOnTopOf(partPosition)) {
		partDirection = FlowPart::BOTTOM;
	} else if (partPosition.isOnTopOf(connectionPosition)) {
		partDirection = FlowPart::TOP;
	} else if (connection->isToTheLeftOf(partPosition)) {
		partDirection = FlowPart::RIGHT;
	} else if (partPosition.isToTheLeftOf(connectionPosition)) {
		partDirection = FlowPart::LEFT;
	} else {
		// diagonal
		return;
	}

	if (connection->isEndPart()) {
		connection->setDirection(partDirection);
	}

	FlowPart* part = addPartAt(partPosition, partDirection);
	part->connectTo(connection);
	connection->connectTo(part);

	connection->alignDirectionWithConnections(name);

	activeParts->removeObject(connection);
}

void Flow::adjustConnectingToPartDirection(FlowPart* connectingToPart,
		FlowPart* connectionPart) {
	GridPosition connectingToPosition = connectingToPart->getGridPostion();
	GridPosition connectionPosition = connectionPart->getGridPostion();
	if (connectingToPosition.isToTheLeftOf(connectionPosition)) {
		connectingToPart->setDirection(FlowPart::RIGHT);
	} else if (connectionPosition.isToTheLeftOf(connectingToPosition)) {
		connectingToPart->setDirection(FlowPart::LEFT);
	} else if (connectingToPosition.isOnTopOf(connectionPosition)) {
		connectingToPart->setDirection(FlowPart::BOTTOM);
	} else {
		connectingToPart->setDirection(FlowPart::TOP);
	}
}

void Flow::makeComplete() {

	FlowPart* activePart1 = (FlowPart*) activeParts->objectAtIndex(0);
	FlowPart* activePart2 = (FlowPart*) activeParts->objectAtIndex(1);

	activePart1->connectTo(activePart2);
	activePart2->connectTo(activePart1);

	FlowPart* connectingToPart = NULL;
	FlowPart* connectionPart = NULL;

	bool isConnectionBetweenNonEndParts = false;

	if (activePart1->isEndPart()) {
		connectingToPart = activePart1;
		connectionPart = activePart2;
	} else if (activePart2->isEndPart()) {
		connectingToPart = activePart2;
		connectionPart = activePart1;
	} else {
		isConnectionBetweenNonEndParts = true;
		if (activePart1->getGridPostion() == lastTouchedPosition) {
			connectionPart = activePart2;
			connectingToPart = activePart1;
		} else {
			connectionPart = activePart1;
			connectingToPart = activePart2;
		}
	}

	adjustConnectingToPartDirection(connectingToPart, connectionPart);

	connectingToPart->reverseDirection();
	connectionPart->alignDirectionWithConnections(name);
	connectingToPart->reverseDirection();

	if (isConnectionBetweenNonEndParts) {
		connectionPart->reverseDirection();
		connectingToPart->alignDirectionWithConnections(name);
		connectionPart->reverseDirection();
	}

	CCObject* obj;
	CCARRAY_FOREACH(parts, obj) {
			FlowPart* part = (FlowPart*) obj;
			if (part->isEndPart()) {
				animateGlowingPart(part);
			}
		}

	state = Complete;
	delegate->onFlowComplete();
}

void Flow::animateGlowingPart(FlowPart *part) {
	CCSpriteFrameCache *spriteCache =
			CCSpriteFrameCache::sharedSpriteFrameCache();
	spriteCache->addSpriteFramesWithFile("Game/BallGlow.plist");
	CCAnimation *glowingBallAnimation = CCAnimation::create();
	for (int i = 1; i <= 12; i++) {
		CCString *name = i < 10 ? CCString::createWithFormat("BallGlow0%d.png",
				i) : CCString::createWithFormat("BallGlow%d.png", i);
		CCSpriteFrame *spriteFrame = spriteCache->spriteFrameByName(
				name->getCString());
		glowingBallAnimation->addSpriteFrame(spriteFrame);
	}
	glowingBallAnimation->setDelayPerUnit(0.05f);
	CCSprite *initialFrame = CCSprite::createWithSpriteFrameName(
			"BallGlow01.png");
	initialFrame->setScale(scaleFactor);
	initialFrame->setPosition(part->getPosition());
	initialFrame->runAction(
			CCSequence::create(
					CCAnimate::create(glowingBallAnimation),
					CCCallFuncN::create(
							this,
							callfuncN_selector(Flow::onAnimationGlowingPartComplete)),
					NULL));
	addChild(initialFrame, -1);
}

void Flow::onAnimationGlowingPartComplete(CCObject* sender) {
	CCSprite* animationSprite = (CCSprite*) sender;
	animationSprite->removeFromParentAndCleanup(true);
}

bool Flow::isComplete() {
	return state == Complete;
}

Flow::~Flow() {
	name->release();
	parts->release();
	activeParts->release();
}
