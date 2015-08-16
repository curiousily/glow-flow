/*
 * Level.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: mvptech
 */

#include "Level.h"

const char* Level::CURRENT_LEVEL_KEY = "current_level";
const char* Level::LEVEL_STATUS_KEY_PREFIX = "status";

const char* Level::buildStatusKey() {
	Pack currentPack = Pack::currentPack();
	GridSize currentGridSize = GridSize::currentGridSize();
	return CCString::createWithFormat("%s_%s_%s_%d", LEVEL_STATUS_KEY_PREFIX,
			currentPack.getName(), currentGridSize.toString(), this->number)->getCString();
}

Level::Level(int number) {
	this->number = number;
	this->db = CCUserDefault::sharedUserDefault();
	int defaultValue = NotTried;
	const char* statusKey = buildStatusKey();
	status = (LevelStatus) db->getIntegerForKey(statusKey, defaultValue);
}

void Level::setCurrentLevel(int number) {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setIntegerForKey(CURRENT_LEVEL_KEY, number);
	db->flush();
}

Level Level::levelFor(int number) {
	Level level(number);
	return level;
}

void Level::setStatus(LevelStatus status) {
	this->status = status;
	const char* statusKey = buildStatusKey();
	db->setIntegerForKey(statusKey, status);
	db->flush();
}

Level Level::currentLevel() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	int number = db->getIntegerForKey(CURRENT_LEVEL_KEY, DEFAULT_LEVEL);
	return Level::levelFor(number);
}

void Level::makeTriedIfNot() {
	if (isNotTried()) {
		setStatus(Tried);
	}
}

bool Level::isDone() {
	return status == Done;
}

bool Level::isDoneOptimal() {
	return status == DoneOptimal;
}

bool Level::isTried() {
	return status == Tried;
}

bool Level::isNotTried() {
	return status == NotTried;
}

GridSize Level::getGridSize() {
	return GridSize::currentGridSize();
}

Pack Level::getPack() {
	return Pack::currentPack();
}

Level::~Level() {
}
