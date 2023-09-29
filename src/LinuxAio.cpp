#include "LinuxAio.h"

namespace MyAio {
LinuxAio::LinuxAio(int max_events, int fd) : max_events_(max_events), fd_(fd) {
  // create a new aio context
  memset(&ctx_, 0, sizeof(io_context_t));
  int ret = io_setup(max_events_, &ctx_);
  if (ret != 0) {
    std::cerr << "io_setup error" << std::endl;
  }
}

LinuxAio ::~LinuxAio() {
  for (size_t i = 0; i < iocbs_.size(); ++i) {
    free(iocbs_[i]);
  }
  // clear iocbs_
  iocbs_.clear();
  // destroy the aio context
  io_destroy(ctx_);
}

void LinuxAio::CreateWriteEvent(std::string &buf, int offset) {
  iocbs_.push_back(new IOCB());  // add a new iocb
  events_.push_back(io_event()); // add a new io_event
  io_prep_pwrite(iocbs_.back(), fd_, const_cast<char *>(buf.c_str()),
                 buf.size(), offset);
}

void LinuxAio::CreateReadEvent(std::string &buf, int offset, int size) {
  iocbs_.push_back((IOCB *)(malloc(sizeof(IOCB)))); // add a new iocb
  events_.push_back(io_event());                    // add a new io_event
  io_prep_pread(iocbs_.back(), fd_, const_cast<char *>(buf.c_str()), size,
                offset);
}

void LinuxAio::Submit() {
  // submit the iocbs
  int ret = io_submit(ctx_, iocbs_.size(), iocbs_.data());
  if (ret != 1) {
    std::cerr << "io_submit error" << std::endl;
    io_destroy(ctx_);
  }
}

int LinuxAio::GetResult() {
  // get the result
  int ret;
  while (true) {
    ret = io_getevents(ctx_, 1, iocbs_.size(), events_.data(), NULL);
    if (ret < 0) {
      std::cerr << "io_getevents error" << std::endl;
      break;
    }
    if (ret > 0) {
      break;
    }
  }
  return ret;
}
} // namespace MyAio