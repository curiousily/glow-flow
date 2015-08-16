//
//  PipePart.cpp
//  MyFlow
//
//

#include "FlowPart.h"

bool FlowPart::initWithFileAndPosition(const char* flowName, CCPoint position,
		Direction direciton, GridPosition gridPosition, float scaleFactor,
		bool shouldBeEndPart) {
	setDirection(direciton);

	setSpriteScaleFactor(scaleFactor);

	isEndingPart = shouldBeEndPart;

	std::string spriteName(flowName);

	if(isEndPart()) {
		spriteName += "Ball";
	} else {
		spriteName += "Straight";
	}
	this->flowName = flowName;
	this->sprite = imageSprite(spriteName.c_str());
	this->sprite->setPosition(position);
	this->position = position;
	if (direciton == TOP || direciton == BOTTOM) {
		this->sprite->setRotation(90);
	}

	this->gridPosition = gridPosition;

	addChild(this->sprite);

	connections = CCArray::create();
	connections->retain();

	return true;
}

FlowPart *FlowPart::doCreate(const char *flowName, CCPoint position,
		Direction direciton, GridPosition gridPosition, float scaleFactor,
		bool shouldBeEndPart) {
	FlowPart* flowPart = new FlowPart();
	if (flowPart && flowPart->initWithFileAndPosition(flowName, position,
			direciton, gridPosition, scaleFactor, shouldBeEndPart)) {
		flowPart->autorelease();
	} else {
		CC_SAFE_DELETE(flowPart);
	}
	return flowPart;
}

FlowPart *FlowPart::createEndPartWithFileAndPosition(const char *flowName,
		CCPoint position, Direction direciton, GridPosition gridPosition,
		float scaleFactor) {
	return doCreate(flowName, position, direciton, gridPosition, scaleFactor,
			true);
}

FlowPart* FlowPart::createWithFileAndPosition(const char* flowName,
		CCPoint position, Direction direciton, GridPosition gridPosition,
		float scaleFactor) {
	return doCreate(flowName, position, direciton, gridPosition, scaleFactor,
			false);
}

void FlowPart::replaceSpriteWith(const char *spriteName) {
	CCPoint position = sprite->getPosition();
	sprite->removeFromParentAndCleanup(true);
	sprite = imageSprite(spriteName);
	sprite->setPosition(ccp(position.x, position.y));
	addChild(sprite);
}

void FlowPart::reverseDirection() {
	switch (direction) {
	case NONE:

		break;
	case LEFT:
		setDirection(RIGHT);
		break;
	case RIGHT:
		setDirection(LEFT);
		break;
	case TOP:
		setDirection(BOTTOM);
		break;
	case BOTTOM:
		setDirection(TOP);
		break;
	}
}

void FlowPart::alignDirectionWithConnections(CCString* flowName) {

	if (hasTwoConnections()) {

		FlowPart* parent = (FlowPart*) connections->objectAtIndex(0);
		FlowPart* child = (FlowPart*) connections->objectAtIndex(1);

		Direction parentDirection = parent->getDirection();
		Direction childDirection = child->getDirection();

		if (parentDirection != NONE && childDirection != parentDirection) {
			const char* spriteName = CCString::createWithFormat("%sRight",
					flowName->getCString())->getCString();
			replaceSpriteWith(spriteName);

			setDirection(childDirection);

			if (parentDirection == BOTTOM && childDirection == LEFT) {
				sprite->setRotation(270.0f);
			} else if (parentDirection == TOP && childDirection == LEFT) {
				sprite->setRotation(180.0f);
			} else if (parentDirection == TOP && childDirection == RIGHT) {
				sprite->setRotation(90.0f);
			}

			if (childDirection == TOP && parentDirection == LEFT) {

			}

			if (parentDirection == RIGHT && childDirection == BOTTOM) {
				sprite->setRotation(180.0f);
			}

			if (childDirection == BOTTOM && parentDirection == LEFT) {
				sprite->setRotation(90.0f);
			}

			if (childDirection == TOP && parentDirection == RIGHT) {
				sprite->setRotation(270.0f);
			}
		}
	}

}

void FlowPart::setDirection(Direction direction) {
	this->direction = direction;
	if (isEndPart()) {
		replaceSpriteWith(
				CCString::createWithFormat("%sBallConnected", flowName)->getCString());
		if (direction == BOTTOM) {
			sprite->setRotation(90.0f);
		} else if (direction == LEFT) {
			sprite->setRotation(180.0f);
		} else if (direction == TOP) {
			sprite->setRotation(270.0f);
		}
	}
}

FlowPart::Direction FlowPart::getDirection() {
	return direction;
}

void FlowPart::connectTo(FlowPart *part) {
	connections->addObject(part);
}

bool FlowPart::hasSingleConnection() {
	return connections->count() == 1;
}

bool FlowPart::hasNoConnections() {
	return connections->count() == 0;
}

bool FlowPart::hasTwoConnections() {
	return connections->count() == 2;
}

bool FlowPart::isEndPart() {
	return isEndingPart;
}

bool FlowPart::isWithinOneStep(const GridPosition& otherPosition) {
	return gridPosition.isWithinOneStep(otherPosition);
}

bool FlowPart::isWithinOneHorizontalStep(const GridPosition& otherPosition) {
	return gridPosition.isWithinOneHorizontalStep(otherPosition);
}

bool FlowPart::isWithinOneVerticalStep(const GridPosition& otherPosition) {
	return gridPosition.isWithinOneVerticalStep(otherPosition);
}

bool FlowPart::isOnTopOf(const GridPosition& otherPosition) {
	return gridPosition.isOnTopOf(otherPosition);
}

bool FlowPart::isToTheLeftOf(const GridPosition& otherPosition) {
	return gridPosition.isToTheLeftOf(otherPosition);
}

inline FlowPart::~FlowPart() {
	connections->release();
}
