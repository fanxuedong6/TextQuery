# TextQuery程序设计
## TextQuery程序接口类和操作
__TextQuery__
*  该类读入给定的文件并构建一个查找图。这个类包含一个 query 操作，它接受一个 string 实参，返回一个 QueryResults 对象；该 QueryResults 对象表示 string 出现的行

__QueryResults__
* 该类保存一个 query 操作的结果, 并且包含 begin() 与 end() 操作, 分别返回 std::shared_ptr<std::set<std::size_t>> 的 const_iterator 类型的 begin 与 end 指针，并且包含 get_file() 操作，返回处理的std::shared_ptr<std::vector<std::string>> 文件

__Query_base__
* 各式 query 类的基类，包含纯虚函数 rep() 与 eval(const TextQuery&)
分别返回操作式与对 TextQuery 执行query后返回的QueryResults

__WordQuery__
* 公有继承自 Query_base 对 const std::string 进行查询， 不希望用户私自定义类的对象，所以构造函数应为私有，同时接口类 Query 应当为其友类

__NotQuery__
* 公有继承自 Query_base 对 Query 进行取反操作，含有Query 成员， 不希望用户私自定义类的对象，所以构造函数应为私有，~ 操作符重载函数应当为友元函数

__BinaryQuery__
* 公有继承自 Query_base 对二元参数 const Query &lhs, const Query &rhs 操作， override rep() 函数，继承 Query_base 的 eval() 所以是**虚基类**

__AndQuery__
* 公有继承自 BinaryQuery 对二元参数 const Query &lhs, const Query &rhs 进行取交操作， 含有两个 Query 成员， 不希望用户私自定义类的对象，所以构造函数应为私有，& 操作符重载函数应当为友元函数

__OrQuery__
* 公有继承自 BinaryQuery 对二元参数 const Query &lhs, const Query &rhs 进行取并操作， 含有两个 Query 成员， 不希望用户私自定义类的对象，所以构造函数应为私有，| 操作符重载函数应当为友元函数

__Query__
* 作为一系列Query类的接口类，接口函数为接受 const std::string 的构造函数，为实现多态，保存 std::shared_ptr<Query_base> 指针，为了与其他Query类实现连接，私有构造函数为接受 std::shared_ptr<Query_base> 的构造函数