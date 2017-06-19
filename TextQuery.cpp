#include"TextQuery.h"
TextQuery::TextQuery(std::fstream& is) :file(new std::vector<std::string>)//constuct with new vector
{
	std::string text;
	while (getline(is, text))//read text by lines
	{
		file->push_back(text);//save lines
		int n = file->size() - 1;//get line_no
		std::stringstream line(text);//split words with stringstream
		std::string word;
		while (line >> word)
		{
			auto &lines = wm[word];//if word not in map, add it, get the line_no set pointer
			if (!lines)
				//if the first time to add the word, the pointer is null, so allocate a set
				lines.reset(new std::set<line_no>);
			lines->insert(n);//insert the line_no
		}
	}
}

QueryResults TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResults(sought, nodata, file);
	else
		return QueryResults(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResults& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " times" << std::endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << std::endl;
	return os;
}

