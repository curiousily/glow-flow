//
//  MyFlowAppDelegate.cpp
//  MyFlow
//
//  Created by Mariana Pavlova on 11/7/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"
#include "cocos2d.h"
#include "GlowFlow.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCEGLView* glView = CCEGLView::sharedOpenGLView();
	glView->setDesignResolutionSize(640, 960, kResolutionShowAll);

	CCSize frameSize = glView->getFrameSize();

	CCLog("Frame size w: %f h: %f", frameSize.width, frameSize.height);

	float heightToWidthRatio = frameSize.height / frameSize.width;

	float iphoneDiff = fabs(IPHONE_HEIGHT_WIDTH_RATION - heightToWidthRatio);
	float galaxyDiff = fabs(GALAXY_3_HEIGHT_WIDTH_RATION - heightToWidthRatio);

	if (iphoneDiff > galaxyDiff) {
		CCLog("Galaxy detected");
		CCFileUtils::sharedFileUtils()->setResourceDirectory("galaxy");
		pDirector->setContentScaleFactor(
				MIN(GALAXY_3_SIZE.height/DESIGN_SIZE.height, GALAXY_3_SIZE.width/DESIGN_SIZE.width));
	} else {
		CCLog("Iphone detected");
		CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
		pDirector->setContentScaleFactor(
				MIN(IPHONE_SIZE.height/DESIGN_SIZE.height, IPHONE_SIZE.width/DESIGN_SIZE.width));
	}

	// turn on display FPS
	//	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	SoundManager* soundManager = SoundManager::sharedSoundManager();
	soundManager->onAppStarting();

	soundManager->playLoopingBackground();

	soundManager->loadEffect("FlowConnected");
	soundManager->loadEffect("MenuClick");
	soundManager->loadEffect("LevelPerfect");
	soundManager->loadEffect("LevelComplete");
	GameManager::sharedGameManager()->startWithScene(MainMenu::scene());

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
