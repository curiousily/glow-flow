/*
 * Grid.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: mvptech
 */

#include "Grid.h"

Grid::Grid() :
	completedFlows(0), flows(NULL), rows(0), columns(0), delegate(NULL),
			tileSize(CCSizeZero) {
}

bool Grid::initWithRowsAndColumns(int rows, int columns, GridDelegate* delegate) {
	this->rows = rows;
	this->columns = columns;
	this->delegate = delegate;

	CCSprite* tempTile = imageSprite("Cell");
	tileSize = tempTile->getContentSize();

	float initialX = GRID_WIDTH_OFFSET;

	float lastTileX = initialX;
	float lastTileY = GRID_HEIGHT_TOP_OFFSET;

	float optimalWidth = tileSize.width * 5;
	scaleFactor = 1.0f;
	if (rows > 5) {
		float currentWidth = tileSize.width * rows;
		scaleFactor = optimalWidth / currentWidth;
		tileSize = CCSizeMake(tileSize.width * scaleFactor, tileSize.height * scaleFactor);
	}
	setSpriteScaleFactor(scaleFactor);

	for (int row = 1; row <= rows; row++) {
		for (int column = 1; column <= columns; column++) {
			Matrix[row][column] = NON_PIPE_POSITION;
			CCSprite* tile = imageSprite("Cell");
			tile->setAnchorPoint(ccp(0, 1));
			tile->setPosition(ccp(lastTileX, lastTileY));
			addChild(tile);
			lastTileX += tileSize.width;
		}
		lastTileY -= tileSize.height;
		lastTileX = initialX;
	}

	tapCircle = imageSprite("TappedCircle");
	tapCircle->setVisible(false);
	addChild(tapCircle, 10);

	flows = CCArray::create();
	flows->retain();
	return true;
}

Grid *Grid::createWithRowsAndColumns(int rows, int columns,
		GridDelegate* delegate) {
	Grid* grid = new Grid();
	if (grid && grid->initWithRowsAndColumns(rows, columns, delegate)) {
		grid->autorelease();
	} else {
		CC_SAFE_DELETE(grid);
	}
	return grid;
}

void Grid::addFlow(const GridPosition & startPosition,
		const GridPosition & endPosition, char symbol, CCString* name) {
	Flow* flow = Flow::createWithPosition(startPosition, endPosition, symbol,
			name, tileSize, scaleFactor, this);
	flows->addObject(flow);
	addChild(flow);
	Matrix[startPosition.row][startPosition.column] = symbol;
	Matrix[endPosition.row][endPosition.column] = symbol;
}

char Grid::symbolAt(const GridPosition & position) {
	return Matrix[position.row][position.column];
}

void Grid::onFlowComplete() {
	delegate->onMoveComplete();
	completedFlows++;
	delegate->onFlowComplete(completedFlows, flows->count());
	if (completedFlows == flows->count()) {
		delegate->onLevelComplete();
	}
}

bool Grid::hasPartOnMap(const GridPosition & gridPosition) {
	return symbolAt(gridPosition) != NON_PIPE_POSITION;
}

void Grid::onPartAdded(const GridPosition & gridPosition, char symbol) {
	Matrix[gridPosition.row][gridPosition.column] = symbol;
	delegate->onMoveComplete();
}

void Grid::onFlowTouched(const CCPoint& position) {
	tapCircle->setPosition(position);
	tapCircle->setVisible(true);
}

void Grid::onFlowTouchEnded() {
	tapCircle->setVisible(false);
}

GridPosition Grid::gridPositionOf(const FlowPart* part) {
	CCPoint position = part->getPosition();
	return gridPositionOf(position.x, position.y);
}

GridPosition Grid::gridPositionOf(const CCPoint & point) {
	return gridPositionOf(point.x, point.y);
}

GridPosition Grid::gridPositionOf(float x, float y) {
	float yWithoutOffset = y - GRID_HEIGHT_BOTTOM_OFFSET;
	int tileRow = (yWithoutOffset / tileSize.height) + 1;
	float xWithoutOffset = x - GRID_WIDTH_OFFSET;
	int tileColumn = (xWithoutOffset / tileSize.width) + 1;
	GridPosition position;
	position.row = tileRow;
	position.column = tileColumn;
	if (isOutsideOfTheGrid(position)) {
		return INVALID_GRID_POSITION;
	}
	return position;
}

bool Grid::isOutsideOfTheGrid(const GridPosition & position) {
	int row = position.row;
	int column = position.column;
	return row < 1 || row > rows || column < 1 || column > columns;
}

Grid::~Grid() {
	flows->release();
}
