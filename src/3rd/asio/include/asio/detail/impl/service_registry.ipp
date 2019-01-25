
#ifndef ASIO_DETAIL_IMPL_SERVICE_REGISTRY_IPP
#define ASIO_DETAIL_IMPL_SERVICE_REGISTRY_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"
#include <vector>
#include "asio/detail/service_registry.hpp"
#include "asio/detail/throw_exception.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

service_registry::~service_registry()
{
  asio::io_service::service* service = first_service_;
  while (service)
  {
    service->shutdown_service();
    service = service->next_;
  }

  while (first_service_)
  {
    asio::io_service::service* next_service = first_service_->next_;
    destroy(first_service_);
    first_service_ = next_service;
  }
}

void service_registry::notify_fork(asio::io_service::fork_event fork_ev)
{
  std::vector<asio::io_service::service*> services;
  {
    asio::detail::mutex::scoped_lock lock(mutex_);
    asio::io_service::service* service = first_service_;
    while (service)
    {
      services.push_back(service);
      service = service->next_;
    }
  }

  std::size_t num_services = services.size();
  if (fork_ev == asio::io_service::fork_prepare)
    for (std::size_t i = 0; i < num_services; ++i)
      services[i]->fork_service(fork_ev);
  else
    for (std::size_t i = num_services; i > 0; --i)
      services[i - 1]->fork_service(fork_ev);
}

void service_registry::init_key(asio::io_service::service::key& key,
    const asio::io_service::id& id)
{
  key.type_info_ = 0;
  key.id_ = &id;
}

bool service_registry::keys_match(
    const asio::io_service::service::key& key1,
    const asio::io_service::service::key& key2)
{
  if (key1.id_ && key2.id_)
    if (key1.id_ == key2.id_)
      return true;
  if (key1.type_info_ && key2.type_info_)
    if (*key1.type_info_ == *key2.type_info_)
      return true;
  return false;
}

void service_registry::destroy(asio::io_service::service* service)
{
  delete service;
}

asio::io_service::service* service_registry::do_use_service(
    const asio::io_service::service::key& key,
    factory_type factory)
{
  asio::detail::mutex::scoped_lock lock(mutex_);

  asio::io_service::service* service = first_service_;
  while (service)
  {
    if (keys_match(service->key_, key))
      return service;
    service = service->next_;
  }

  lock.unlock();
  auto_service_ptr new_service = { factory(owner_) };
  new_service.ptr_->key_ = key;
  lock.lock();

  service = first_service_;
  while (service)
  {
    if (keys_match(service->key_, key))
      return service;
    service = service->next_;
  }

  new_service.ptr_->next_ = first_service_;
  first_service_ = new_service.ptr_;
  new_service.ptr_ = 0;
  return first_service_;
}

void service_registry::do_add_service(
    const asio::io_service::service::key& key,
    asio::io_service::service* new_service)
{
  if (&owner_ != &new_service->get_io_service())
    asio::detail::throw_exception(invalid_service_owner());

  asio::detail::mutex::scoped_lock lock(mutex_);

  asio::io_service::service* service = first_service_;
  while (service)
  {
    if (keys_match(service->key_, key))
      asio::detail::throw_exception(service_already_exists());
    service = service->next_;
  }

  new_service->key_ = key;
  new_service->next_ = first_service_;
  first_service_ = new_service;
}

bool service_registry::do_has_service(
    const asio::io_service::service::key& key) const
{
  asio::detail::mutex::scoped_lock lock(mutex_);

  asio::io_service::service* service = first_service_;
  while (service)
  {
    if (keys_match(service->key_, key))
      return true;
    service = service->next_;
  }

  return false;
}

}
}

#include "asio/detail/pop_options.hpp"

#endif
