/*
 * GridSize.cpp
 *
 *  Created on: Jan 2, 2013
 *      Author: mvptech
 */

#include "GridSize.h"

const char* GridSize::ROWS_KEY = "current_grid_size_rows";
const char* GridSize::COLUMNS_KEY = "current_grid_size_columns";

const int GridSize::DEFAULT_ROWS = 5;
const int GridSize::DEFAULT_COLUMNS = 5;

GridSize::GridSize(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
}

GridSize GridSize::createDefault() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setIntegerForKey(ROWS_KEY, DEFAULT_ROWS);
	db->setIntegerForKey(COLUMNS_KEY, DEFAULT_COLUMNS);
	db->flush();
	return GridSize::currentGridSize();
}

GridSize GridSize::currentGridSize() {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	int rows = db->getIntegerForKey(ROWS_KEY, DEFAULT_ROWS);
	int columns = db->getIntegerForKey(COLUMNS_KEY, DEFAULT_COLUMNS);
	GridSize gridSize(rows, columns);
	return gridSize;
}

void GridSize::setSizeForPage(int pageNumber) {
	CCUserDefault* db = CCUserDefault::sharedUserDefault();
	db->setIntegerForKey(ROWS_KEY, pageNumber - 1 + DEFAULT_ROWS);
	db->setIntegerForKey(COLUMNS_KEY, pageNumber - 1 + DEFAULT_COLUMNS);
	db->flush();
}

const char *GridSize::toString() {
	return CCString::createWithFormat("%dx%d", rows, columns)->getCString();
}

GridSize::~GridSize() {
}
