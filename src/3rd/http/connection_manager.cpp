
#include "connection_manager.hpp"

namespace http
{
namespace server
{

connection_manager::connection_manager()
{
}

void
connection_manager::start(connection_ptr c)
{
	mutex_.lock();
    connections_.insert(c);
	c->start();
	mutex_.unlock();
}

void
connection_manager::stop(connection_ptr c)
{
	mutex_.lock();
    connections_.erase(c);
	c->stop();
	mutex_.unlock();
}

void
connection_manager::stop_all()
{
    for (auto c : connections_)
        c->stop();
    connections_.clear();
}

} // namespace server
} // namespace http
