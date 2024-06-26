# Serial Communication Library

forked from [OpenCat Serial C++](https://github.com/PetoiCamp/opencat_serial_cpp)

## Overiew:

* Update platform toolset to Visual Studio v143
* Wraps API in a namespace
* restore STL wstring conversion
* Compiled for C++20
* Use Visual Studio code layout
* Minor cosmetic code "tidy"
* Add library version macro string (1.2.0)

The Windows Visual Studio 2022 IDE is the primary tool used to maintain the project. No attempt  has been  made  to  alter the environment for other platforms.
The IDE version is:

Microsoft Visual Studio Community 2022 (64-bit) - Current
Version 17.10.1

### Namespace serial

The library API is now wrapped in the namespace "serial" to isolate the API from the global namespace.

    namespace serial {

        // API declarations ...

    }   // namespace serial

### Restore STL wstring conversion

The Windows implementation of the getPort API has been moddified
to use the stl for wstring conversion function operations.

	namespace serial {
		namespace internal {

		#pragma message("std::wstring_convert is deprecated in C++17")
		#pragma message("std::codecvt_utf8_utf16 is deprecated in C++17")
		#pragma message("std::codecvt_utf8_utf16 to be remove in C++26")

			wstring utf8ToUtf16(const string& utf8Str)
			{
				wstring_convert<codecvt_utf8_utf16<wchar_t>> conv;
				return conv.from_bytes(utf8Str);
			}

			string utf16ToUtf8(const wstring& utf16Str)
			{
				wstring_convert<codecvt_utf8_utf16<wchar_t>> conv;
				return conv.to_bytes(utf16Str);
			}
		}	// namespace internal
		using namespace serial::internal;

		string Serial::SerialImpl::getPort() const
		{
			// warning: argument': conversion from 'const wchar_t'
			// to 'const _Elem', possible loss of data
			//return string(port_.begin(), port_.end());
			return utf16ToUtf8(port_);
		}

		// ...

	}	// namespace serial

When the functions are removed from the STL a replacement
of the functionality will be provided.

## Original README

[![Build Status](https://travis-ci.org/wjwwood/serial.svg?branch=master)](https://travis-ci.org/wjwwood/serial)*(Linux and OS X)* [![Build Status](https://ci.appveyor.com/api/projects/status/github/wjwwood/serial)](https://ci.appveyor.com/project/wjwwood/serial)*(Windows)*

**NOTE:** copied from [https://github.com/wjwwood/serial/tree/69e0372cf0d3796e84ce9a09aff1d74496f68720](serial) and remove catkin dependencies.
This is a cross-platform library for interfacing with rs-232 serial like ports written in C++. It provides a modern C++ interface with a workflow designed to look and feel like PySerial, but with the speed and control provided by C++. 

This library is in use in several robotics related projects and can be built and installed to the OS like most unix libraries with make and then sudo make install, but because it is a catkin project it can also be built along side other catkin projects in a catkin workspace.

Serial is a class that provides the basic interface common to serial libraries (open, close, read, write, etc..) and requires no extra dependencies. It also provides tight control over timeouts and control over handshaking lines. 

### Documentation

Website: http://wjwwood.github.io/serial/

API Documentation: http://wjwwood.github.io/serial/doc/1.1.0/index.html

### Dependencies

Required:
* [catkin](http://www.ros.org/wiki/catkin) - cmake and Python based buildsystem
* [cmake](http://www.cmake.org) - buildsystem
* [Python](http://www.python.org) - scripting language
  * [empy](http://www.alcyone.com/pyos/empy/) - Python templating library
  * [catkin_pkg](http://pypi.python.org/pypi/catkin_pkg/) - Runtime Python library for catkin

Optional (for documentation):
* [Doxygen](http://www.doxygen.org/) - Documentation generation tool
* [graphviz](http://www.graphviz.org/) - Graph visualization software

### Install

Get the code:

    git clone https://github.com/wjwwood/serial.git

Build:

    make

Build and run the tests:

    make test

Build the documentation:

    make doc

Install:

    make install

### License

[The MIT License](LICENSE)

### Authors

William Woodall <wjwwood@gmail.com>
John Harrison <ash.gti@gmail.com>

### Contact

William Woodall <william@osrfoundation.org>
