#include "LinuxAio.h"

using namespace MyAio;

int main() {
  std::string buf = "hello world";
  std::string file_name = "test.txt";
  int fd = open(file_name.c_str(), O_RDWR | O_CREAT, 0644);
  if (fd < 0) {
    std::cerr << "open file error" << std::endl;
    return -1;
  }
  LinuxAio aio(1, fd);
  aio.CreateWriteEvent(buf, 0);
  aio.Submit();
  aio.GetResult();
  close(fd);
  return 0;
}