#include"Query.h"
#include"TextQuery.h"

Query::Query(const std::string &s) : q(new WordQuery(s)) { }

QueryResults AndQuery::eval(const TextQuery &t) const
{
	auto l = lhs.eval(t), r = rhs.eval(t);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	set_intersection(l.begin(), l.end(),
		r.begin(), r.end(),
		std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResults(rep(), ret_lines, r.get_file());
}

QueryResults OrQuery::eval(const TextQuery &t) const
{
	auto l = lhs.eval(t), r = rhs.eval(t);
	auto ret_lines = std::make_shared<std::set<line_no>>(l.begin(), l.end());
	ret_lines->insert(r.begin(), r.end());
	return QueryResults(rep(), ret_lines, r.get_file());
}

QueryResults NotQuery::eval(const TextQuery &t) const
{
	auto exist = query.eval(t);
	auto beg = exist.begin(), end = exist.end();
	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::size_t num = 0;
	auto sz = exist.get_file()->size();
	for (; num != sz; ++num)
	{
		if (*beg != num || beg == end)
			ret_lines->insert(num);
		else if (beg != end)
			++beg;
	}
	return QueryResults(rep(), ret_lines, exist.get_file());
}
