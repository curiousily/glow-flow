/*
 * Pack.h
 *
 *  Created on: Dec 30, 2012
 *      Author: mvptech
 */

#ifndef PACK_H_
#define PACK_H_

#include "cocos2d.h"

USING_NS_CC;

class Pack {

	static const char* DEFAULT_PACK;
	static const char* CURRENT_PACK_KEY;

	CCString* name;

public:

	Pack(const char * name);

	static Pack currentPack();
	static void setCurrentPack(const char* name);
	bool isUnlocked();

	void unlock();
	const char* getName();

	virtual ~Pack();
};

#endif /* PACK_H_ */
