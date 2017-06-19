#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<memory>
#include<vector>
#include<string>
#include<set>
#include<map>
#include"QueryResults.h"

class QueryResults;

class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::fstream&);
	QueryResults query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
