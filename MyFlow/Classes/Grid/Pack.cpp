/*
 * Pack.cpp
 *
 *  Created on: Dec 30, 2012
 *      Author: mvptech
 */

#include "Pack.h"

const char* Pack::DEFAULT_PACK = "Regular";
const char* Pack::CURRENT_PACK_KEY = "current_pack";

Pack::Pack(const char * name) {
	this->name = CCString::create(name);
	this->name->retain();
}

Pack Pack::currentPack() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	Pack pack(db->getStringForKey(CURRENT_PACK_KEY, DEFAULT_PACK).c_str());
	return pack;
}

void Pack::setCurrentPack(const char* name) {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setStringForKey(CURRENT_PACK_KEY, name);
	db->flush();
}

const char* Pack::getName() {
	return name->getCString();
}

bool Pack::isUnlocked() {
	if (strcmp(getName(), DEFAULT_PACK) == 0) {
		return true;
	}
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	return db->getBoolForKey(
			CCString::createWithFormat("%s_unlocked", name)->getCString(),
			false);
}

void Pack::unlock() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setBoolForKey(
			CCString::createWithFormat("%s_unlocked", name)->getCString(), true);
	db->flush();
}

Pack::~Pack() {
	name->release();
}
