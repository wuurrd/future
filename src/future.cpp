#include "future.h"

Result::Result(bool successful, boost::any result)
 :successful_(successful),
  result_(result),
  parent_(NULL),
  should_stop_(false)
{}

bool Result::is_successful()
{
	return successful_;
}

void Result::wait_for_next()
{
	should_stop_ = true;
}

bool Result::should_stop()
{
	return should_stop_;
}

boost::any Result::get_result()
{
	return result_;
}

void Result::chain_future(Future * future)
{
	should_stop();
	Callback future_callback = boost::bind(&Future::callback,
										   boost::ref(parent_),
										   _1
										   );
	future->add_callback(future_callback);
}

Future::Future()
 :result_(NULL)
{
	callbacks = std::vector<Callback>();
}

Future::~Future()
{
	callbacks.clear();
}

void Future::add_callback(Callback callback)
{
	if (result_){
		callback(result_);
		return;
	}
	callbacks.push_back(callback);
}

bool Future::is_complete()
{
	return result_ != NULL;
}

Result* Future::wait()
{
	return NULL;
}

void Future::callback(Result * result)
{
	result_ = result;
	while (!callbacks.empty())
	{
		Callback curr_callback = callbacks.front();
		callbacks.erase(callbacks.begin());
		curr_callback(result);
		if (result -> should_stop())
		{
			break;
		}
	}
}
