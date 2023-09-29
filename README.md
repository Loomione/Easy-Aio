
# EasyAio - Linux AIO Library Wrapper

EasyAio is a C++ library that provides a simple and convenient wrapper around the Linux AIO (Asynchronous I/O) API, making it easier to perform asynchronous I/O operations in your applications.

## Features

- **Simplified Interface**: EasyAio abstracts the complexity of the Linux AIO API, providing a user-friendly interface for performing asynchronous I/O operations.

- **Error Handling**: The library includes comprehensive error handling to help you manage errors and exceptions effectively.

- **Thread Safety**: EasyAio is designed to be thread-safe, allowing it to be used in multi-threaded applications without issues.

## Getting Started

### Prerequisites

- A Linux-based operating system (since Linux AIO is a Linux-specific feature).
- The `libaio` library installed on your system.

### Building

To build the library and example program, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/loominoe/Easy-Aio.git
    ```

2. Navigate to the project directory:

    ```bash
    cd Easy-Aio
    ```

3. Build the library:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

### Usage

Here's a basic example of how to use EasyAio:

```cpp
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
```

For more detailed usage instructions and API documentation, please refer to the [documentation](docs/) provided in this repository.

## Contributing

Contributions to EasyAio are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to the Linux AIO developers for providing the underlying asynchronous I/O functionality.
- Inspired by the need for a simple and user-friendly interface for Linux AIO.

---
