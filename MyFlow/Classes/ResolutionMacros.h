/*
 * ResolutionMacros.h
 *
 *  Created on: Jan 13, 2013
 *      Author: mvptech
 */

#ifndef RESOLUTIONMACROS_H_
#define RESOLUTIONMACROS_H_

#include "cocos2d.h"

USING_NS_CC;

static const CCSize DESIGN_SIZE = CCSizeMake(640, 960);

static const CCSize IPHONE_SIZE = CCSizeMake(640, 960);
static const CCSize GALAXY_3_SIZE = CCSizeMake(720, 1280);

static const float IPHONE_HEIGHT_WIDTH_RATION = IPHONE_SIZE.height
		/ IPHONE_SIZE.width;
static const float GALAXY_3_HEIGHT_WIDTH_RATION = GALAXY_3_SIZE.height
		/ GALAXY_3_SIZE.width;

#endif /* RESOLUTIONMACROS_H_ */
