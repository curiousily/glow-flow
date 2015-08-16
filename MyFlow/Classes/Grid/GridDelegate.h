/*
 * GridDelegate.h
 *
 *  Created on: Dec 15, 2012
 *      Author: mvptech
 */

#ifndef GRIDDELEGATE_H_
#define GRIDDELEGATE_H_

#include "cocos2d.h"

USING_NS_CC;

class GridDelegate {
public:
	virtual void onMoveComplete() = 0;
	virtual void onFlowComplete(int completedFlows, int totalFlows) = 0;
	virtual void onLevelComplete() = 0;
};

#endif /* GRIDDELEGATE_H_ */
