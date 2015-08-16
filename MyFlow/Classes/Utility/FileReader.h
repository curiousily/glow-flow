/*
 * FileReader.h
 *
 *  Created on: Dec 11, 2012
 *      Author: mvptech
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <string>
#include <vector>
#include <fstream>
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class FileReader {

	const char* fileName;
	vector<string> lines;
	CCFileUtils* fileUtils;
	char* data;
	unsigned long dataSize;
	int currentLine;
public:
	FileReader(const char* fileName);
	bool hasNextLine();
	bool fileCanBeOpen();
	string readLine();
	vector<int> readIntsFromLine(int integerCount);
	virtual ~FileReader();
};

#endif /* FILEREADER_H_ */
