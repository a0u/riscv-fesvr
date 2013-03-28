// See LICENSE for license details.

#ifndef _HTIF_PTHREAD_H
#define _HTIF_PTHREAD_H

#include "htif.h"
#include <pthread.h>
#include <unistd.h>
#include <deque>

class htif_pthread_t : public htif_t
{
 public:
  htif_pthread_t(const std::vector<std::string>& target_args,
    int _host_in = STDIN_FILENO, int _host_out = STDOUT_FILENO);

  // target interface
  void send(const void* buf, size_t size);
  void recv(void* buf, size_t size);
  bool recv_nonblocking(void* buf, size_t size);

 protected:
  // host interface
  virtual ssize_t read(void* buf, size_t max_size);
  virtual ssize_t write(const void* buf, size_t size);

  virtual size_t chunk_align() { return 64; }
  virtual size_t chunk_max_size() { return 1024; }

 private:
  pthread_t host;
  pthread_mutex_t th_lock;
  pthread_cond_t th_cond;
  std::deque<char> th_data;
  pthread_mutex_t ht_lock;
  pthread_cond_t ht_cond;
  std::deque<char> ht_data;
  pthread_mutex_t stop_once;
};

#endif
