#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>
#include <vector>

class Future;

class Result
{
public:
	Result(bool successful, boost::any result);
	bool is_successful();
	void wait_for_next();
	bool should_stop();
	boost::any get_result();
	void chain_future(Future *);

private:
	Future* parent_;
	bool successful_;
	bool should_stop_;
	boost::any result_;
};

typedef boost::function<void(Result*)> Callback;

class Future
{
public:
	Future();
	~Future();
	void add_callback(Callback);
	bool is_complete();
	Result* wait();
	void callback(Result*);

private:
	std::vector<Callback> callbacks;
	Result* result_;
};
