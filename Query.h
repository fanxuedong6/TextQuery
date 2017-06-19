#pragma once
#include<set>
#include<string>
#include<memory>
#include<algorithm>
#include<iterator>
#include<iostream>

#include"QueryResults.h"
#include"TextQuery.h"

class Query;                                   // extern forward
Query operator~(const Query&);
Query operator|(const Query&, const Query&);
Query operator&(const Query&, const Query&);

class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResults eval(const TextQuery&) const = 0;
	virtual std::string rep() const = 0;
};

class Query {
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&);
	QueryResults eval(const TextQuery &t) const
	{
		return q->eval(t);
	}
	std::string rep() const
	{
		return q->rep();
	}
private:
	Query(std::shared_ptr<Query_base> query) : q(query) { }
	std::shared_ptr<Query_base> q;          // realize the multi-status by base_class pointer
};
inline std::ostream& operator<<(std::ostream& out, Query& q)
{
	out << q.rep();
	return out;
}

class WordQuery : public Query_base {
	friend class Query;
protected:
	QueryResults eval(const TextQuery &t) const
	{
		return t.query(word);
	}
	std::string rep() const
	{
		return word;
	}
private:
	WordQuery(const std::string& w) : word(w) { }
	std::string word;
};

class NotQuery : public Query_base {
	friend Query operator~(const Query&);
	NotQuery(const Query &q) : query(q) { }
	std::string rep() const
	{
		return "~(" + query.rep() + ")";
	}
	QueryResults eval(const TextQuery&) const;
	Query query;
};
inline Query operator~(const Query &q)
{
	return std::shared_ptr<Query_base>(new NotQuery(q));
}

class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) { }
	std::string rep() const
	{
		return "(" + lhs.rep() + opSym + rhs.rep() + ")";
	}
	Query lhs, rhs;
	std::string opSym;
};

class AndQuery : public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "&") { }
	QueryResults eval(const TextQuery&) const;
};
inline Query operator&(const Query &l, const Query &r)
{
	return std::shared_ptr<Query_base>(new AndQuery(l, r));
}

class OrQuery : public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "|") { }
	QueryResults eval(const TextQuery&) const;
};
inline Query operator|(const Query &l, const Query &r)
{
	return std::shared_ptr<Query_base>(new OrQuery(l, r));
}