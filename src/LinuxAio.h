#pragma once
#include <fcntl.h>
#include <iostream>
#include <libaio.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace MyAio {
class LinuxAio {

public:
  LinuxAio(int max_events = 1, int fd = 0);
  ~LinuxAio();
  void Submit(/* args */);
  int GetResult(/* args */);
  void CreateWriteEvent(std::string &buf, int offset);
  void CreateReadEvent(std::string &buf, int offset, int size);

private:
  using IOCB = struct iocb;
  io_context_t ctx_;             // io_context_t is a pointer
  int max_events_;               // max events
  int fd_;                       // file descriptor
  std::vector<io_event> events_; // io_event vectors
  std::vector<IOCB *> iocbs_;    // iocb vectors
};

} // namespace MyAio