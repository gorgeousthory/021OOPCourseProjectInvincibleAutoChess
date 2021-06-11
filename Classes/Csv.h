#pragma once

#ifndef __CSV_PARSER_H__
#define __CSV_PARSER_H__

#include "cocos2d.h"

class LineString
{
public:
	LineString(const std::string& str);
	virtual ~LineString();

	size_t getColumnCount() const { return _lineStr.size(); }

	std::string& operator[](size_t index)
	{
		CCASSERT(index < this->getColumnCount(), "invalid index in lineInfo");
		return _lineStr[index];
	}

protected:
	void initWithString(const std::string& str);

private:
	std::vector<std::string> _lineStr;
};

class CsvParser
{
public:
	CsvParser();
	virtual ~CsvParser();

	void parseWithFile(const std::string& csvFilename);

	size_t getRowCount() const { return _dataInfo.size(); }
	size_t getColumnCount() const { return _titles.size(); }

	LineString& operator[](size_t index)
	{
		CCASSERT(index < this->getRowCount(), "invalid index in lineInfo"); //this need discussing
		return _dataInfo[index];
	}

private:
	std::vector<std::string> _titles;
	std::vector<LineString> _dataInfo;
};
#endif // __CSV_PARSER_H__
