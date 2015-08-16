/*
 * GridPosition.h
 *
 *  Created on: Dec 8, 2012
 *      Author: mvptech
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

struct GridPosition {
	int row, column;

	bool operator==(const GridPosition& other) {
		return row == other.row && column == other.column;
	}

	bool isWithinOneStep(const GridPosition& otherPosition) {
		return isWithinOneHorizontalStep(otherPosition)
				|| isWithinOneVerticalStep(otherPosition);
	}

	bool isWithinOneHorizontalStep(const GridPosition& otherPosition) {
		return isToTheLeftOf(otherPosition) || isToTheRightOf(otherPosition);
	}

	bool isWithinOneVerticalStep(const GridPosition& otherPosition) {
		return isOnTopOf(otherPosition) || isOnBottomOf(otherPosition);
	}

	bool isOnTopOf(const GridPosition& otherPosition) {
		return row == otherPosition.row + 1 && column == otherPosition.column;
	}

	bool isOnBottomOf(const GridPosition& otherPosition) {
		return row == otherPosition.row - 1 && column == otherPosition.column;
	}

	bool isToTheLeftOf(const GridPosition& otherPosition) {
		return column == otherPosition.column - 1 && row == otherPosition.row;
	}

	bool isToTheRightOf(const GridPosition& otherPosition) {
		return column == otherPosition.column + 1 && row == otherPosition.row;
	}
};

static GridPosition INVALID_GRID_POSITION = { -1, -1 };

static bool isInvalidPosition(GridPosition & position) {
	return position == INVALID_GRID_POSITION;
}

static bool isValidPosition(GridPosition & position) {
	return !isInvalidPosition(position);
}

#endif /* GRIDPOSITION_H_ */
