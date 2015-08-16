/*
 * SettingsScene.h
 *
 *  Created on: Feb 5, 2013
 *      Author: mvptech
 */

#ifndef SETTINGSSCENE_H_
#define SETTINGSSCENE_H_

#include "cocos2d.h"
#include "../GlowFlow.h"
#include "../ResourceFinder.h"

USING_NS_CC;

class Settings: public cocos2d::CCLayer, ResourceFinder {
public:
	Settings();
	virtual ~Settings();

	static CCScene* scene();

	virtual bool init();

	const char* getResourceDirectory() {
		return "Settings";
	}

	CREATE_FUNC(Settings)

private:

	void onDoneTapped(CCObject* sender);
	void onSoundToggle(CCObject* sender);
	void onMusicToggle(CCObject* sender);
};

#endif /* SETTINGSSCENE_H_ */
