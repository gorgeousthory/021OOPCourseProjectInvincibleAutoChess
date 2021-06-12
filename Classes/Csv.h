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

	void parseWithFile(const std::string& csvFilename);	//读取数据表格

	size_t getRowCount() const { return _dataInfo.size(); }	//获取行最大值
	size_t getColumnCount() const { return _titles.size(); }	//获取列最大值
	size_t finditem(const std::string& src) const;	//找到某个数据所在的行

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