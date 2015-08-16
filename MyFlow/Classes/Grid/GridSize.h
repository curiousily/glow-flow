/*
 * GridSize.h
 *
 *  Created on: Jan 2, 2013
 *      Author: mvptech
 */

#ifndef GRIDSIZE_H_
#define GRIDSIZE_H_

#include "cocos2d.h"

USING_NS_CC;

class GridSize {

	static const char* ROWS_KEY;
	static const char* COLUMNS_KEY;
	static const int DEFAULT_ROWS;
	static const int DEFAULT_COLUMNS;

	CC_SYNTHESIZE_READONLY(int, rows, Rows)

	CC_SYNTHESIZE_READONLY(int, columns, Columns)

public:

	GridSize(int rows, int columns);

	static void setSizeForPage(int pageNumber);

	static GridSize createDefault();
	static GridSize currentGridSize();

	const char* toString();

	virtual ~GridSize();
};

#endif /* GRIDSIZE_H_ */
