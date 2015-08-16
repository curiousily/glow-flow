/*
 * LoadingScene.h
 *
 *  Created on: Dec 15, 2012
 *      Author: mvptech
 */

#ifndef LOADINGSCENE_H_
#define LOADINGSCENE_H_

#include "cocos2d.h"
#include "../Utility/VisibleRect.h"
#include "GameScene.h"
USING_NS_CC;

class Loading: public cocos2d::CCLayer {

public:
	virtual bool init();
	virtual ~Loading();

	static CCScene* scene();

 	void onLoadingComplete(CCObject* sender);

	CREATE_FUNC(Loading)
	;
};

#endif /* LOADINGSCENE_H_ */
