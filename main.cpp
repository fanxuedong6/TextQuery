#include"TextQuery.h"
#include"Query.h"
using namespace std;

int main()
{
	string filename = "";
	fstream fileopen(filename);
	TextQuery tq(fileopen);
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string s;
		// stop if we hit end-of-file on the input or if a 'q' is entered
		if (!(cin >> s) || s == "q") break;
		// run the query and print the results
		print(cout, tq.query(s)) << endl;
	}
	Query q = (~Query("Murphy") | Query("Murphy"))&Query("this");
	cout << q.rep() << ":" << endl;
	print(cout, q.eval(tq));
	system("pause");
	return 0;
}