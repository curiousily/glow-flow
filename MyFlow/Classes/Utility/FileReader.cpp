/*
 * FileReader.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: mvptech
 */

#include "FileReader.h"

FileReader::FileReader(const char *fileName) {
	this->fileName = fileName;
	this->fileUtils = CCFileUtils::sharedFileUtils();

	this->data = (char*) fileUtils->getFileData(
			fileUtils->fullPathFromRelativePath(fileName), "r", &dataSize);

	string contents;
	contents.append(data);
	istringstream stringStream(contents);
	string line;
	while (getline(stringStream, line)) {
		lines.push_back(line);
	}
	currentLine = 0;
}

bool FileReader::hasNextLine() {
	return currentLine + 1 < lines.size();
}

string FileReader::readLine() {
	return lines[currentLine++];
}

bool FileReader::fileCanBeOpen() {
	return data != NULL && dataSize > 0;
}

vector<int> FileReader::readIntsFromLine(int integerCount) {
	string line = readLine();
	istringstream lineStream(line);
	vector<int> result;
	for (int i = 0; i < integerCount; i++) {
		int number;
		lineStream >> number;
		result.push_back(number);
	}
	return result;
}

FileReader::~FileReader() {
	CC_SAFE_DELETE_ARRAY(data);
}
