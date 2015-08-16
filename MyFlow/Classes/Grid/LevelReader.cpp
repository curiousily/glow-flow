/*
 * GridReader.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: mvptech
 */

#include "LevelReader.h"

void LevelReader::readFlow(Grid* grid, FileReader& reader) {
	string line = reader.readLine();
	GridPosition startPosition = readFlowPosition(reader);
	GridPosition endPosition = readFlowPosition(reader);
	CCString* flowName = CCString::create(line);
	const char symbol = line[0];
	grid->addFlow(startPosition, endPosition, symbol, flowName);
}

GridPosition LevelReader::readFlowPosition(FileReader& reader) {
	vector<int> positions = reader.readIntsFromLine(2);
	GridPosition position;
	position.row = positions[0];
	position.column = positions[1];
	return position;
}

Grid* LevelReader::fromFile(Pack pack, GridSize gridSize, int levelNumber, GridDelegate *delegate) {

	const char* fileName = CCString::createWithFormat("Levels/%s/%s/%d.txt",
			pack.getName(), gridSize.toString(), levelNumber)->getCString();
	FileReader reader(fileName);
	if (!reader.fileCanBeOpen()) {
		return NULL;
	}
	vector<int> gridInfo = reader.readIntsFromLine(3);
	int rows = gridInfo[0];
	int columns = gridInfo[1];
	int optimalMoves = gridInfo[2];
	Grid* grid = Grid::createWithRowsAndColumns(rows, columns, delegate);
	int flowCount = reader.readIntsFromLine(1)[0];
	for (int i = 0; i < flowCount; i++) {
		readFlow(grid, reader);
	}
	grid->setOptimalMoves(optimalMoves);
	return grid;
}

LevelReader::~LevelReader() {
}
