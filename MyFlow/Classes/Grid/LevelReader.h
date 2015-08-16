/*
 * GridReader.h
 *
 *  Created on: Dec 11, 2012
 *      Author: mvptech
 */

#ifndef GRIDREADER_H_
#define GRIDREADER_H_

#include "Grid.h"
#include "Pack.h"
#include "GridSize.h"
#include "Level.h"
#include "GridDelegate.h"
#include "../Utility/FileReader.h"

using namespace std;

class LevelReader {

	static void readFlow(Grid* grid, FileReader& reader);
	static GridPosition readFlowPosition(FileReader& reader);

public:
	static Grid* fromFile(Pack pack, GridSize gridSize, int levelNumber, GridDelegate* delegate);
	virtual ~LevelReader();
};

#endif /* GRIDREADER_H_ */
