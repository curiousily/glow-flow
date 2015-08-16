/*
 * Constants.h
 *
 *  Created on: Dec 15, 2012
 *      Author: mvptech
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <vector>

static const float GRID_HEIGHT_TOP_OFFSET = 820.0f;
static const float GRID_HEIGHT_BOTTOM_OFFSET = 200.0f;
static const float GRID_WIDTH_OFFSET = 11.0f;

static const float WOOD_PAD_WIDTH_PADDING = 4.0f;
static const float WOOD_PAD_HEIGHT_PADDING = 3.5f;

static const float BACKGROUND_MUSIC_VOLUME = 0.3f;
static const float SOUND_EFFECTS_VOLUME = 0.7f;

static const int MAX_LEVELS = 25;

static const char* __packNames[] = {"Regular", "Adventure"};

static std::vector<const char *> PACKS(__packNames, __packNames + sizeof(__packNames) / sizeof(const char*));

#endif /* CONSTANTS_H_ */
