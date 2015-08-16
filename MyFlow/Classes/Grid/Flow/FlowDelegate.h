/*
 * PipeDelegate.h
 *
 *  Created on: Nov 29, 2012
 *      Author: mvptech
 */

#ifndef PIPEDELEGATE_H_
#define PIPEDELEGATE_H_

#include "cocos2d.h"
#include "Flow.h"
#include "FlowPart.h"
#include "../GridPosition.h"

USING_NS_CC;

class FlowDelegate {
public:
	virtual void onFlowComplete() = 0;
	virtual bool hasPartOnMap(const GridPosition&) = 0;
	virtual void onFlowTouched(const CCPoint& position) = 0;
	virtual void onFlowTouchEnded() = 0;
	virtual void onPartAdded(const GridPosition&, char) = 0;
	virtual GridPosition gridPositionOf(const FlowPart* part) = 0;
	virtual GridPosition gridPositionOf(const CCPoint & point) = 0;
	virtual GridPosition gridPositionOf(float x, float y) = 0;
};

#endif /* PIPEDELEGATE_H_ */
