# OpenCat Serial C++
Serial interface implementation for [OpenCat](https://github.com/PetoiCamp/OpenCat) robot in C++.

## Install

The project is organized using cmake, to build the project, simply run

```bash
mkdir build && cd build
cmake -DCATKIN_ENABLE=OFF -DBUILD_EXAMPLES=ON ..
make
```

Make sure your computer is connected to your robot, run the example to verify that the library is working.

```bash
./build/serial_examples
```

## Use the library in your own project

The project is built as a dynamic library so that the program can easily link to it. The recommended practice to use the library is to clone it as a git submodule:

```bash
git submodule add https://github.com/PetoiCamp/opencat_serial_cpp opencat_serial
```

If you are using cmake, simply create a `CMakeLists.txt` file and link the library to your executable:

```cmake
cmake_minimum_required(VERSION 3.0.2)
project(serial_examples)
option(CATKIN_ENABLE "Enable using the Catkin make extension to cmake (ie for ROS)" OFF)
add_subdirectory(opencat_serial)
add_executable(serial_examples path/to/cpp)
target_link_libraries(serial_examples opencat_serial)
```

## Examples

Below is a very simple example on how to use the library.

```c++
#include "opencat_serial/opencat_serial.hpp"
int main(int argc, char *argv[])
{
    // connect to the serial device
    OpenCat::Robot rob("/path/to/port");
    // create task
    OpenCat::Task task;
    // set command type to calibration pose
    task.command = OpenCat::Command::CALIB_POSE;
    // time delayed after execution
    task.delay = 2;
    // send command
    rob.SendTask({OpenCat::Command::CALIB_POSE, 2});
    return 0;
}
```

see [examples](./examples/serial_examples.cpp) more a comprehensive example.
